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

#ifndef WATCHDOGREBOOTER_H
#define WATCHDOGREBOOTER_H

#include <QMainWindow>
#include <QTimer>
#include "ui_WatchdogRebooter.h"

#include "XWatchdogRebooter.h"

class WatchdogRebooter : public QMainWindow
{
	Q_OBJECT

	WatchdogPack	WPack;
	QTimer			TM;
public:
	WatchdogRebooter(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~WatchdogRebooter();

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonAddProgram_clicked();
    void on_pushButtonDeleteProgram_clicked();
    void on_pushButtonClose_clicked();
	void SlotTimeOut();
	void	SlotShow();
	void	SlotWatchdogEvent(const QString &ErrorType,const QString &FileName ,int pid);

private:
	Ui::WatchdogRebooterClass ui;

	bool	LoadData(void);
	bool	SaveData(void);
	void	ShowList(void);

	QString		GetDefaultFileName(void)	{	return "ConfigWatchdogRebooter.dat";	}
};

#endif // WATCHDOGREBOOTER_H