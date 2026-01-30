/*
 * Copyright (C) 2023
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



#ifndef SEQFOR64CONNECTOR_H
#define SEQFOR64CONNECTOR_H

#include <QTcpSocket>
#include "XGeneralFunc.h"
#include <time.h>
#include "XSeqDLLGlobal.h"

class	SenderSocket : public QTcpSocket
{
	Q_OBJECT
public:
    char    ReqBuffer[1000];
    bool    ReqMode;
    bool    UnitStart;

	SenderSocket(QObject * parent = 0):QTcpSocket(parent){}
    bool    SendStr(QString s);

private slots:
	void	SlotReadyRead();
};

class	SeqFor64Connector
{
public:
	SenderSocket	*MachineSocket;

	SeqFor64Connector(void)	{	MachineSocket=NULL;	}

	void    TryConnection(QApplication &App );
	bool    IsConnectedToServer(void);
};

#endif // SEQFOR64CONNECTOR_H