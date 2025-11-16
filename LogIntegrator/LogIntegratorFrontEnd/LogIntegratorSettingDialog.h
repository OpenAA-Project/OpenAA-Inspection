#ifndef LOGINTEGRATORSETTINGDIALOG_H
#define LOGINTEGRATORSETTINGDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "ui_LogIntegratorSettingDialog.h"
#include "LogIntegratorUtil.h"

class LogIntegratorSettingDialog : public QDialog
{
	Q_OBJECT

public:
	LogIntegratorSettingDialog(QWidget *parent = 0);
	~LogIntegratorSettingDialog();

	Ui::LogIntegratorSettingDialogClass ui;
private:
	QString SelectDirectory( QFileDialog::AcceptMode acceptmode, QString DefaultDir );
private slots:
	void on_pushButton_OK_clicked();
	void on_pushButton_Cancel_clicked();
	void on_pushButton_SelectOutputDir_clicked();
	void on_pushButton_SelectLowerLogHD_clicked();
	void on_pushButton_SelectUpperLogHD_clicked();
};

#endif // LOGINTEGRATORSETTINGDIALOG_H
