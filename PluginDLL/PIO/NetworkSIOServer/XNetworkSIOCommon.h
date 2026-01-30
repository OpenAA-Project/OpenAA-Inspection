/*
 * Copyright (C) 2020
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

#if	!defined(XNetworkSIOCommon_h)
#define	XNetworkSIOCommon_h

#include <QTcpServer>
#include <QTimer>
#include <QTcpSocket>
#include <QBuffer>
#include <QMutex>
#include <QObject>
#include "NList.h"
#include "XTypeDef.h"

#pragma	pack(push,1)
struct	TxRxLowPacket
{
	int32		NowOnXByte;
	int32		NowCmd;
};

#pragma	pack(pop)

class	RecList : public NPList<RecList>
{
public:
	BYTE		*Data;
	int32		Cmd;
	int32		Len;


	RecList(int len);
	~RecList(void);


	BYTE	*GetClassNamePointer(int maxByte);
	BYTE	*GetError(BYTE *fp);

	BYTE	*GetPointer(void){	return(Data);	}
	BYTE	*GetPointer(BYTE *p ,int32 &ret);
	BYTE	*GetPointer(BYTE *p ,WORD &ret );
	BYTE	*GetPointer(BYTE *p ,bool &ret );
	BYTE	*GetPointer(BYTE *p ,BYTE *buff ,int buffByte);
	BYTE	*GetPointer(BYTE *p ,QBuffer &ret);
};


class	SoESocket : public QObject
{
	Q_OBJECT
		
	QTcpSocket	*Sock;

	NPListPack<RecList>	RecData;
	QMutex				MuteRecData;
	int32				LastPacketLoadedSize;
	struct	TxRxLowPacket	Pct;
	int32				FastCommLeafRxReEntrant;

	enum	_RxState{
		_NowOnReceiving
		,_NowOnWaiting
		}RxState;
	time_t		LastReceivingTime;
	RecList		*OnRBuff;
	int32		NowOnPoint;
	int32		NowOnXByte;
	int32		NowCmd;

	QString		IPAddress;
	int			PortNumber;

public:
	SoESocket(QObject *parent ,const QString &_IPAddress,int _PortNumber);
	SoESocket(QObject *parent ,QTcpSocket *sv);
	virtual	~SoESocket(void);

	bool	ConnectToHost(void);
	bool	Send(int32 cmd ,QByteArray &Data);

	bool	IsConnected(void);
	void	WaitReadyRead(int milisec);
	
	RecList	*PopRecDataTop(void);
public slots:
	virtual	void	SlotDisconnected();
	void	ReadyRead ();

signals:
	void	SignalReceived(int Cmd);
private slots:
	void	SlotReceived(int Cmd);
protected:
	virtual	void	Received(int cmd ,QByteArray &data){};

};

struct	CommOpenInfo
{
	int BaudRate;
	int	Character;
	int	Parity;
	int	StopBit;
};

#define	CmdComm_None			0
#define	CmdComm_Open			1
#define	CmdComm_Tx				2
#define	CmdComm_Rx				3
#define	CmdComm_RxByte			4

#define	CmdComm_Ack_OK			101
#define	CmdComm_Ack_NG			102
#define	CmdComm_Ack_Received	103
#define	CmdComm_Ack_RxByte		104



#endif