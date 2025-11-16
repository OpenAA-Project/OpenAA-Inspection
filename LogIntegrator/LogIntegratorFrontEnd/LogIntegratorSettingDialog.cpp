#include "LogIntegratorSettingDialog.h"
#include <QDir>
#include <QMessageBox>

LogIntegratorSettingDialog::LogIntegratorSettingDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.lineEdit_UpperLogHD, SIGNAL(returnPressed()), this, SLOT(on_pushButton_OK_clicked()) );
	connect( ui.lineEdit_LowerLogHD, SIGNAL(returnPressed()), this, SLOT(on_pushButton_OK_clicked()) );
	connect( ui.lineEdit_OutputDir,  SIGNAL(returnPressed()), this, SLOT(on_pushButton_OK_clicked()) );

}

LogIntegratorSettingDialog::~LogIntegratorSettingDialog()
{

}

QString LogIntegratorSettingDialog::SelectDirectory( QFileDialog::AcceptMode acceptmode, QString DefaultDir="" )
{
	QFileDialog Dialog(this, Qt::Dialog);
	if( !DefaultDir.isEmpty() )
		Dialog.setDirectory(DefaultDir);
	Dialog.setFileMode(QFileDialog::DirectoryOnly);
	Dialog.setAcceptMode(acceptmode);
	if( Dialog.exec()==QDialog::Accepted )
		return Dialog.selectedFiles().takeFirst();
	else
		return "";
}

void LogIntegratorSettingDialog::on_pushButton_SelectUpperLogHD_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, QString("上面ログのあるHDを指定してください"),
                                                 ui.lineEdit_UpperLogHD->text(),
                                                 QFileDialog::ShowDirsOnly
                                                 );
	if( dir.isNull() )
		return;
	ui.lineEdit_UpperLogHD->setText( QDir::toNativeSeparators(dir) );
}

void LogIntegratorSettingDialog::on_pushButton_SelectLowerLogHD_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, QString("下面ログのあるHDを指定してください"),
                                                 ui.lineEdit_LowerLogHD->text(),
                                                 QFileDialog::ShowDirsOnly
                                                 );
	if( dir.isNull() )
		return;
	ui.lineEdit_LowerLogHD->setText( QDir::toNativeSeparators(dir) );
}

void LogIntegratorSettingDialog::on_pushButton_SelectOutputDir_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, QString("統合したログの出力先フォルダを指定してください"),
                                                 ui.lineEdit_OutputDir->text(),
                                                 QFileDialog::ShowDirsOnly
                                                 );
	if( dir.isNull() )
		return;
	ui.lineEdit_OutputDir->setText( QDir::toNativeSeparators(dir) );
}

void LogIntegratorSettingDialog::on_pushButton_OK_clicked()
{
	accept();
}

void LogIntegratorSettingDialog::on_pushButton_Cancel_clicked()
{
	reject();
}