/*
 * Copyright (C) 2017
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

#ifndef NETWORKSIOCLIENTLIB_H
#define NETWORKSIOCLIENTLIB_H

#include "networksioclientlib_global.h"
#include "XNetworkSIOCommon.h"

class	NetworkSIOClientLib;

class	SocketInClient : public SoESocket
{	
	NetworkSIOClientLib	*Parent;
public:
	QByteArray	RxData;
	int			RxCmd;

	SocketInClient(NetworkSIOClientLib *parent ,const QString &_IPAddress,int _PortNumber);

	void	Clear(void);
private:
	void	Received(int cmd ,QByteArray &data);
	virtual	void	SlotDisconnected();
};

class  NetworkSIOClientLib : public QObject
{
	Q_OBJECT

	SocketInClient	*Client;
public:
	NetworkSIOClientLib(QObject *parent);
	~NetworkSIOClientLib();

	bool	StartConnection(const QString &IPAddress ,int PortNumber=28210);

	bool	OpenPort(int BaudRate ,int Character ,int Parity ,int StopBit);
	bool	SendData(char *fp ,int Len);
	bool	GetReceivedByte(int &RxLen);
	bool	ReceiveData(char *fp ,int &RxLen ,int MaxLen);

private:

};

#endif // NETWORKSIOCLIENTLIB_H