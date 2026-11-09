#include "TutrialExecuter.h"
#include <QDir>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

TutrialExecuter::TutrialExecuter(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

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
    // Retrieve current username (fallback to home dir name if USERNAME env is empty)
    QString userName = qEnvironmentVariable("USERNAME");
    if (userName.isEmpty()) {
        userName = QDir::home().dirName();
    }

    // Default path: \Users\<CurrentUserName>\OpenAA
    QString defaultPath = QString("\\Users\\%1\\OpenAA").arg(userName);
    ui.lineEditConfigDir->setText(defaultPath);
}

void TutrialExecuter::onBrowseConfigDir()
{
    // Retrieve current username (fallback to home dir name if USERNAME env is empty)
    QString userName = qEnvironmentVariable("USERNAME");
    if (userName.isEmpty()) {
        userName = QDir::home().dirName();
    }

    // Set the default browsing directory to \Users\<CurrentUserName>
    QString initialDir = QString("\\Users\\%1").arg(userName);

    // Fall back to root/drive path if the user folder does not exist
    if (!QDir(initialDir).exists()) {
        initialDir = "\\Users";
        if (!QDir(initialDir).exists()) {
            initialDir = QDir::rootPath();
        }
    }

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

    // Build arguments list:
    // 1. G + gui file name
    // 2. Q + config folder name
    // 3. NDM
    // 4. W1
    // 5. -R
    QStringList arguments;
    arguments << QString("G%1").arg(guiFile);
    arguments << QString("Q%1").arg(configDir);
    arguments << "NDM";
    arguments << "W1";
    arguments << "-R";

    // Launch the external process detached
    bool started = QProcess::startDetached(program, arguments, QCoreApplication::applicationDirPath());
    if (!started) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to start process:\n%1").arg(program));
    }
}