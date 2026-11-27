#include "TutrialExecuter.h"
#include <QDir>
#include <QFileInfo>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

TutrialExecuter::TutrialExecuter(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

#ifndef Q_OS_WIN
    QDir appDir(QCoreApplication::applicationDirPath());
    if (QFileInfo::exists(appDir.filePath("InspectionFastPlayerApp"))) {
        ui.lineEditProgram->setText("InspectionFastPlayerApp");
    } else {
        ui.lineEditProgram->setText("InspectionFastPlayer");
    }
#endif

    populateGuiFiles();
    initDefaultConfigDir();

    connect(ui.btnBrowseConfigDir, &QPushButton::clicked, this, &TutrialExecuter::onBrowseConfigDir);
    connect(ui.btnStart, &QPushButton::clicked, this, &TutrialExecuter::onStart);
}

TutrialExecuter::~TutrialExecuter()
{}

void TutrialExecuter::populateGuiFiles()
{
    ui.comboBoxGuiFile->clear();

    QDir appDir(QCoreApplication::applicationDirPath());
    QStringList filters;
    filters << "*.gui";

    // Retrieve files sorted alphabetically (case-insensitive)
    QStringList guiFiles = appDir.entryList(filters, QDir::Files, QDir::Name | QDir::IgnoreCase);
    ui.comboBoxGuiFile->addItems(guiFiles);
}

void TutrialExecuter::initDefaultConfigDir()
{
#ifdef Q_OS_WIN
    // Retrieve current username (fallback to home dir name if USERNAME env is empty)
    QString userName = qEnvironmentVariable("USERNAME");
    if (userName.isEmpty()) {
        userName = QDir::home().dirName();
    }

    // Default path: \Users\<CurrentUserName>\OpenAA
    QString defaultPath = QString("\\Users\\%1\\OpenAA").arg(userName);
#else
    // Linux default path: $HOME/OpenAA
    QString defaultPath = QDir::cleanPath(QDir::homePath() + "/OpenAA");
#endif
    ui.lineEditConfigDir->setText(defaultPath);
}

void TutrialExecuter::onBrowseConfigDir()
{
#ifdef Q_OS_WIN
    QString userName = qEnvironmentVariable("USERNAME");
    if (userName.isEmpty()) {
        userName = QDir::home().dirName();
    }

    QString initialDir = QString("\\Users\\%1").arg(userName);
    if (!QDir(initialDir).exists()) {
        initialDir = "\\Users";
        if (!QDir(initialDir).exists()) {
            initialDir = QDir::rootPath();
        }
    }
#else
    QString initialDir = ui.lineEditConfigDir->text().trimmed();
    if (initialDir.isEmpty() || !QDir(initialDir).exists()) {
        initialDir = QDir::homePath();
    }
#endif

    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Select Config Directory"),
        initialDir,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if (!dir.isEmpty()) {
        ui.lineEditConfigDir->setText(QDir::toNativeSeparators(dir));
    }
}

void TutrialExecuter::onStart()
{
    QString program = ui.lineEditProgram->text().trimmed();
    if (program.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please specify an executable program."));
        return;
    }

    QString guiFile = ui.comboBoxGuiFile->currentText().trimmed();
    if (guiFile.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please select a .gui file."));
        return;
    }

    QString configDir = ui.lineEditConfigDir->text().trimmed();
    if (configDir.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please specify a config folder."));
        return;
    }

    QString appDirPath = QCoreApplication::applicationDirPath();
    QDir appDir(appDirPath);
    QString execPath = program;

    // Resolve executable path inside applicationDirPath() when a bare filename is specified
    if (!QFileInfo(program).isAbsolute()) {
        QString candidate = appDir.filePath(program);
        if (QFileInfo::exists(candidate)) {
            execPath = candidate;
        }
#ifndef Q_OS_WIN
        else if (QFileInfo::exists(appDir.filePath(program + "App"))) {
            execPath = appDir.filePath(program + "App");
        }
#endif
    }

    // Build arguments list:
    // 1. G + gui file name
    // 2. Q + config folder name
    // 3. NoCamDevice (optional, if camera is NOT used)
    // 4. NDM
    // 5. W1
    // 6. -R
    QStringList arguments;
    arguments << QString("G%1").arg(guiFile);
    arguments << QString("Q%1").arg(configDir);

    if (!ui.checkBoxUseCamera->isChecked()) {
        arguments << "NoCamDevice";
    }

    arguments << "NDM";
    arguments << "W1";
    arguments << "-R";

    // Launch the external process detached
    bool started = QProcess::startDetached(execPath, arguments, appDirPath);
    if (!started) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to start process:\n%1").arg(execPath));
    }
}