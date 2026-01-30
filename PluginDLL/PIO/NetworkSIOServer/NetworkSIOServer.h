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

#ifndef NETWORKSIOSERVER_H
#define NETWORKSIOSERVER_H

#include <QMainWindow>
#include "ui_NetworkSIOServer.h"
#include <QTcpServer>
#include <QTimer>
#include <QTcpSocket>
#include <QBuffer>
#include <QMutex>
#include <QObject>
#include <QSerialPort>
#include "NList.h"
#include "XTypeDef.h"
#include "XNetworkSIOCommon.h"

class NetworkSIOServer;

class	SocketInServer : public NPList<SocketInServer> ,public SoESocket
{	
	NetworkSIOServer	*Parent;
public:
	int		ClientID;
	QString	ClientIP;
	int		ClientPortNumber;
	int		HandleNumber;

	SocketInServer(NetworkSIOServer *parent,QTcpSocket *sv);

private:
	void	Received(int cmd ,QByteArray &data);
	virtual	void	SlotDisconnected();
};


class NetworkSIOServer : public QMainWindow
{
	Q_OBJECT

	int	ComPort;
	int	LanPort;
	QTcpServer	Server;
	SoESocket	*Client;
	QTimer		Timer;
		
public:
	QSerialPort				*sio;
	struct	CommOpenInfo	SIOInfo;

	NPListPack<SocketInServer>	SocketContainer;
		
	bool	OpenPort(void);
public:
	NetworkSIOServer(int ComPort ,int LanPortNumber ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~NetworkSIOServer();

private slots:
    void	on_pushButtonReOpen_clicked();
	void	SlotNewConnection ();
	void	SlotTimeout();
private:
	Ui::NetworkSIOServerClass ui;
};


#endif // NETWORKSIOSERVER_H