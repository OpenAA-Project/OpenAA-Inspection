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

#ifndef BOOTER_H
#define BOOTER_H

#include <QMainWindow>
#include "ui_Booter.h"
#include "XSocketClient.h"
#include "NListComp.h"
#include "XBooter.h"

class	Booter;

class	ConnectionList : public SocketClient
{
	Q_OBJECT

public:
	QString		AccessName;
	QString		IPAddress;
	int			PortNumber;

	ConnectionList(QObject *parent=NULL);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	bool	OpenConnection(void);
	bool	IsOpenConnection(void);
	bool	SendOK(void);

public slots:
	void	SlotReceived(int);
};

class	ConnectionContainer : public NPListPack<SocketClient>
{
	Booter	*Parent;
public:
	ConnectionContainer(Booter *parent):Parent(parent){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	BooterServer : public SocketServer
{
};

class Booter : public QMainWindow
{
	Q_OBJECT

public:
	SocketServer		Server;
	ConnectionContainer	Connections;
	QString				SettingFileName;
	BooterParameter		BooterData;

	Booter(const QString &settingFile ,int OpePort ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~Booter();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonSetting_clicked();

private:
	Ui::BooterClass ui;
};

#define	CmdOK	0x10

#endif // BOOTER_H