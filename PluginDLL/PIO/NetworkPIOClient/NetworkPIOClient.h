/*
 * Copyright (C) 2019
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

#ifndef NETWORKPIOCLIENT_H
#define NETWORKPIOCLIENT_H

#include "networkpioclient_global.h"
#include <QTcpSocket>
#include <QMutex>
#include "XTypeDef.h"

class NetworkPIOClient : public QTcpSocket
{
	Q_OBJECT

	QString	IPAddress;
	int		Port;
public:
	int		ID;
	int		InNumb;
	int		OutNumb;

	BYTE	InData[4];
	BYTE	OutData[4];
	bool	WaitToReceive;
	QMutex	AccessMutex;

	NetworkPIOClient(QObject *parent);
	~NetworkPIOClient();

	void	Initial(int _ID ,const QString &Address,int port ,int _InNumb ,int _OutNumb);
	void	Initial(const QString &Something);

	void	OutByte(int port ,BYTE data);
	BYTE	InByte(int port);
	void	OutBit(int BitIndex,BYTE data);
	BYTE	InBit(int BitIndex);
	BYTE	GetOutByte(int port);

	void	ReqData(bool SendOutData=true);
	bool	OpenSocket(void);

private:
	
public slots:
	void ReadyRead();
};


#endif // NETWORKPIOCLIENT_H