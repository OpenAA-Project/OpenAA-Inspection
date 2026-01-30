/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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