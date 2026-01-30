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

#ifndef AUTOSTARTLIST_H
#define AUTOSTARTLIST_H

#include <QMainWindow>
#include "ui_AutoStartList.h"
#include "XAutoStartListThread.h"
#include <QCloseEvent>
#include <QTimer>
#include "XAutoStart.h"
#include <QSystemTrayIcon>
#include <QMenu>

class AutoStartList : public QMainWindow
{
	Q_OBJECT

	QSystemTrayIcon		*TrayIcon;
	QMenu				*TrayIconMenu;
	bool				EnableClose;
public:
	AutoStartList(bool EnableClose ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~AutoStartList();

	volatile	bool	Ticking;
	volatile	bool	Counting;
	volatile	bool	AllFinished;
	bool	IsFinishedAll(void);
	bool	ExecuteAll(void);

	AutoStartExeList	AutoStartExeListData;

protected:
	virtual	void	closeEvent(QCloseEvent *ev)	override;
private:
	Ui::AutoStartListClass ui;
	ThreadAutoStartList	LThread;

	QTimer	TM;

	QAction	*minimizeAction;
	QAction	*showAction;
	QAction	*quitAction;

private slots:
	void on_pushButtonParam_clicked();
	void on_toolButtonStop_clicked();
	void on_pushButtonStart_clicked();
	void	Timeout();
};

#endif // AUTOSTARTLIST_H