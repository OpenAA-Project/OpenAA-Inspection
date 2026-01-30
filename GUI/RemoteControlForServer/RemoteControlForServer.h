/*
 * Copyright (C) 2022
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

#ifndef REMOTECONTROLFORSERVER_H
#define REMOTECONTROLFORSERVER_H

#include "remotecontrolforserver_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"
#include <QTcpServer>
#include <QTcpSocket>

class	RemoteControlForServer;

class	RCSocket : public QObject ,public NPList<RCSocket>
{
	Q_OBJECT
	
	RemoteControlForServer	*Parent;
public:
	int	ID;
	QTcpSocket	*Sock;

	RCSocket(RemoteControlForServer *parent);

	void	Initial(void);
signals:
	void	Disconnect(int id);

private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
};

class	RemoteControlForServer : public GUIFormBase
{
	Q_OBJECT

	QTcpServer	Server;
	NPListPack<RCSocket>	SocketPointer;
public:
	int32		PortNo;

	RemoteControlForServer(LayersBase *Base ,QWidget *parent);
	~RemoteControlForServer(void);

	virtual	void	Prepare(void)	override;

	int		GetMaxSocketID(void);
	void	RemoveSocket(RCSocket *c);

private slots:
	void SlotNewConnection ();
};
#endif // REMOTECONTROLFORSERVER_H