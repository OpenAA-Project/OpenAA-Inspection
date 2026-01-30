/*
 * Copyright (C) 2012
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

#ifndef LOGERRDIALOG_H
#define LOGERRDIALOG_H

#include <QDialog>
#include "ui_logerrdialog.h"
#include "LogIntegrator_pack.h"

class LogErrDialog : public QDialog
{
	Q_OBJECT

public:
	LogErrDialog(QWidget *parent = 0);
	~LogErrDialog();

	void setError(clsLogItemContainer &ErrList);
	void setSuccess(clsLogItemContainer &List);
	void ClearLogs(void);

	bool IsErrLog(void);

private:
	Ui::LogErrDialogClass ui;

	void setCellItem(QTableWidget *tableWidget, int row, int col, QString val);
	void removeCellItem(QTableWidget *tableWidget, int row);
	QString bindDate(QString src);
	QString bindTime(QString src);

private slots:
	void on_pbCancel_clicked();
	void on_pushButton_clicked();
};

#endif // LOGERRDIALOG_H