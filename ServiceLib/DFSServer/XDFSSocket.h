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

#if	!defined(XDFSSocket_h)
#define	XDFSSocket_h


#include "XTypeDef.h"
#include <QBuffer>
#include <QMutex>
#include <QObject>
#include <QTcpSocket>
#include "NListComp.h"
#include "XDateTime.h"


#define	DFSProviderPort	24600
#define	DFSClientPort	24800

/*
	Operation
		1:Enum files
		2:Enum folders
		3:Load file
		4:Save file
		5:Make folder
		6:Remove file
		7:Remove folder
*/
#define	DFSCmd_ReqEnumFiles			1
#define	DFSCmd_ReqEnumFolders		2
#define	DFSCmd_ReqLoadFile			3
#define	DFSCmd_ReqSaveFile			4
#define	DFSCmd_ReqMakeFolder		5
#define	DFSCmd_ReqRemoveFile		6
#define	DFSCmd_ReqRemoveFolder		7
#define	DFSCmd_ReqFindFile			8

#define	DFSCmd_AckEnumFiles			101
#define	DFSCmd_AckEnumFolders		102
#define	DFSCmd_AckLoadFile			103
#define	DFSCmd_AckSaveFile			104
#define	DFSCmd_AckMakeFolder		105
#define	DFSCmd_AckRemoveFile		106
#define	DFSCmd_AckRemoveFolder		107
#define	DFSCmd_AckFindFile			108

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


	BYTE	*GetClassName(int maxByte);
	BYTE	*GetError(BYTE *fp);

	BYTE	*GetPointerPointer(void){	return(Data);	}
	BYTE	*GetPointer(BYTE *p ,int32 &ret);
	BYTE	*GetPointer(BYTE *p ,WORD &ret );
	BYTE	*GetPointer(BYTE *p ,bool &ret );
	BYTE	*GetPointer(BYTE *p ,BYTE *buff ,int buffByte);
	BYTE	*GetPointer(BYTE *p ,QBuffer &ret);
};


class	DFSSocket : public QObject ,public NPList<DFSSocket>
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

	QMutex		MutexSending;
	bool		Waiting;
	bool		bReceived;
	bool		bAccessed;
	QString		IPAddress;
	int			PortNumber;
	QString		PeerIPAddress;
	int			PeerPort;

public:
	DFSSocket(QObject *parent ,const QString &IPAddress,int PortNumber);
	DFSSocket(QObject *parent ,QTcpSocket *sv);
	virtual	~DFSSocket(void);

	bool	Send(int32 cmd ,QByteArray &Data);
	bool	Send(int32 cmd);

	bool	IsConnected(void);
	bool	WaitReadyRead(int milisec);
	bool	OnWaiting(void)		{	return Waiting;			}
	void	SetReceived(bool b)	{	bReceived=b;			}
	bool	IsReceived(void)	{	return bReceived;		}
	void	SetAccessed(bool b)	{	bAccessed=b;			}
	bool	IsAccessed(void)	{	return bAccessed;		}
		
	QString		GetPeerIPAddress(void)	{	return PeerIPAddress;	}
	int			GetPeerPort(void)		{	return PeerPort;		}

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

//=============================================================================


#endif