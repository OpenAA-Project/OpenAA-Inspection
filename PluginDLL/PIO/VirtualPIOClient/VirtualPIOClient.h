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

#ifndef VIRTUALPIOCLIENT_H
#define VIRTUALPIOCLIENT_H

#include <QMainWindow>
#include "ui_VirtualPIOClient.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>
#include <QCloseEvent>
#include "XVirtualPIOClient.h"

class VirtualPIOClient : public QMainWindow
{
	Q_OBJECT

	QAction	*minimizeAction;
	QAction	*showAction;
	QAction	*quitAction;
	QSystemTrayIcon		*TrayIcon;
	QMenu				*TrayIconMenu;
	QTimer				TM;
	QTimer				CommOpe;

	PIOAdapter			Adapter;
	bool				FirstTimeOut;
public:
	VirtualPIOClient(const QString &IPAddress,int PortNumber ,const QString &AccessMemoryName ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~VirtualPIOClient();

	void	ShowGrid(void);
private:
	Ui::VirtualPIOClientClass ui;
	void	closeEvent( QCloseEvent *ev);
	
private slots:
	void	SlotTimeOut();
	void	SlotTimeOutComm();
};

#endif // VIRTUALPIOCLIENT_H