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

#pragma once

#include<QTcpSocket>
#include<QBuffer>
#include<QMutex>
#include "XTypeDef.h"
#include "NList.h"
#include "XSocketComm.h"

class ErrorCodeList;
class RegulusWorld;
class RWRecList;

class RWClientSocket : public QTcpSocket , public NPList<RWClientSocket>
{
	Q_OBJECT

	int				ID;
	RegulusWorld	*Parent;

	NPListPack<RWRecList>	RecData;
	QMutex					MuteRecData;
	int32					LastPacketLoadedSize;
	struct	RWTxRxLowPacket	Pct;
	int32					FastCommLeafRxReEntrant;

	enum	_RxState{
		_NowOnReceiving
		,_NowOnWaiting
		}RxState;
	time_t		LastReceivingTime;
	RWRecList	*OnRBuff;
	int32		NowOnPoint;
	int32		NowOnXByte;
	int32		NowCmd;

	NPListPack<RWTxList>	TxQueueBuff;
public:
	RWClientSocket(RegulusWorld *p,QObject *parent);

	int		GetID(void)			const	{	return ID;			}
	bool	TxData(int32 cmd ,const QString &EmitterName,const QString &CmdClass 
					,QBuffer *f,int32 IDForUndo,ErrorCodeList &ErrorData);
	bool	WaitForReadyRead(int milisec);
private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
signals:
	void	SignalReceived(int ID,int Cmd);
	void	SignalDisconnected(int id);
};