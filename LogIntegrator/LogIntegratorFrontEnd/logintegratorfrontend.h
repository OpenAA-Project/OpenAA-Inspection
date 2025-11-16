#ifndef LOGINTEGRATORFRONTEND_H
#define LOGINTEGRATORFRONTEND_H

#include <QMainWindow>
#include "ui_logintegratorfrontend.h"

#include <QThread>
#include <QFileDialog>
#include "LogIntegratorlib.h"
#include "LogIntegratorSettingDialog.h"
#include "LogIntegratorProcessForm.h"

class LogIntegratorFrontEnd : public QMainWindow
{
	Q_OBJECT

public:
	LogIntegratorFrontEnd(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LogIntegratorFrontEnd();

private:
	Ui::LogIntegratorFrontEndClass ui;

	LogIntegratorSettingDialog SettingDialog;

	QString UpperLogHD;
	QString LowerLogHD;
	QString OutputDir;
	QRegExpValidator LotNoValidator;

	LogIntegratorProcessForm *ProcessForm;

	bool ExecuteIntegration(QString LotNo);

protected:
	clsLogIntegratorLib LibObj;

	QString IniFilePath;

private slots:
	void on_pushButton_DateRun_clicked();
	void on_pushButton_Run_clicked();
	void ShowSettingDialog(void);
};

#endif // LOGINTEGRATORFRONTEND_H
