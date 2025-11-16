/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XFastComm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XFASTCOMM_H
#define XFASTCOMM_H

#include <QtGui>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <time.h>
#include "XTypeDef.h"
#include "NList.h"
#include "XEntryPoint.h"

class	CommBase;
class	ErrorCodeList;

#pragma	pack(push,1)
struct	TxRxLowPacket
{
	int32		NowOnXByte;
	int32		NowCmd;
	int32		ErrorCode;
	int16		GlobalPage;
	int32		IDForUndo;
	int16		ShadowLevel ;
	int16		ShadowNumber;
	BYTE		EmitterRootLen;
	BYTE		EmitterNameLen;
	BYTE		ClassNameLen;
	BYTE		ErrorLevel;
	BYTE		ErrorMessageLen;
	BYTE		ErrorTimeLen;
};

#pragma	pack(pop)

class	RecList : public NPList<RecList>
{
public:
	BYTE		*Data;
	int32		Cmd;
	int32		Len;
	int16		EmitterRootLen;
	int16		EmitterNameLen;
	int16		ClassNameLen;
	int16		GlobalPage;
	int32		IDForUndo;
	int16		ShadowLevel ;
	int16		ShadowNumber;
	int32		ErrorCode;
	BYTE		ErrorLevel;
	BYTE		ErrorMessageLen;
	BYTE		ErrorTimeLen;

	RecList(int len);
	~RecList(void);


	BYTE	*GetClassNamePointer(char CmdEmitterRootBuff[] ,char CmdEmitterNameBuff[] ,char CmdClassBuff[] ,int maxByte);
	BYTE	*GetError(BYTE *fp,ErrorCodeList &ErrorData);

	BYTE	*GetPointer(void){	return(Data);	}
	BYTE	*GetPointer(BYTE *p ,int32 &ret);
	BYTE	*GetPointer(BYTE *p ,WORD &ret );
	BYTE	*GetPointer(BYTE *p ,bool &ret );
	BYTE	*GetPointer(BYTE *p ,BYTE *buff ,int buffByte);
	BYTE	*GetPointer(BYTE *p ,QBuffer &ret);
};

class	TxList : public NPList<TxList>
{
public:
	int32	Len;
	BYTE	*Data;

	TxList(int len , BYTE *data);
	~TxList(void);
};

class	FastCommLeaf : public QObject
{
    Q_OBJECT

	int32				ID;
	QTcpSocket			*Sock;
	bool				Servered;
	QString				IP;
	int32				Port;
	CommBase			*cParent;
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

	NPListPack<TxList>	TxQueueBuff;
	bool		Connected;

public:
	FastCommLeaf(int ID ,CommBase *cparent);
	~FastCommLeaf(void);
	
	int		GetID(void){	return ID;	}

	void	Set(QObject *parent ,const QString &ip ,int port);
	bool	StartConnect(DWORD WaitingTime=1000);
	void	SetServerMode(QTcpSocket *sv);
	bool	IsServerMode(void){	return(Servered);	}
	void	SetCommParent(CommBase *cparent){	cParent=cparent;	}
	bool	IsConnected(void);
	bool	TxData(int32 globalPage 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,BYTE *buff ,int xbyte,ErrorCodeList &ErrorData);
	bool	TxData(int32 globalPage 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QBuffer *f,ErrorCodeList &ErrorData);
	bool	TxData(int32 globalPage 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QByteArray *f,ErrorCodeList &ErrorData);

	void	TxDataQueueStart(void);
	void	TxDataQueuePush(BYTE *data ,int len);
	void	TxDataQueuePush(int32 data);
	void	TxDataQueuePush(WORD data);
	void	TxDataQueuePush(bool data);
	void	TxDataQueuePush(QBuffer *f);
	bool	TxDataQueueFlush(int32 cmd ,int32 globalPage 
							,const QString &EmitterRoot 
							,const QString &EmitterName
							,const QString &CmdClass);

	RecList	*UnpackTopRxBuff(void);
	int		GetQueuedCount(void);
	QTcpSocket	*GetSocket(void){	return Sock;	}
	QString	GetPeerIPAddress(void);
	void	WaitReadyRead(int milisec);
	time_t	GetLastReceivingTime(void){		return LastReceivingTime;	}
signals:
	void	SignalReceived(int ID,int Cmd);
	void	SignalDisconnected(int id);
private slots:
	void	SlotConnected();
	void	SlotDisconnected();
	void	SlotReadyRead();
};

const int	MaxCommLeafNumb=10000;
const int	MaxServerNumb=100;

//===========================================================================
class	CommBase : public QTcpServer
{
    Q_OBJECT
public:
	CommBase(QObject * parent){}
	virtual	~CommBase(void){}

	virtual	void	SetNullInChild(FastCommLeaf *child)=0;

protected slots:
	virtual	void	SlotNewConnection ()	=0;
	virtual	void	SlotReceived(int,int)	=0;
	virtual	void	SlotDisconnected(int id)=0;

};
//===========================================================================

class	FastComm :public CommBase
{
    Q_OBJECT

	//int32			ServerPort;
	FastCommLeaf	*Leaf[MaxCommLeafNumb];

public:
	FastComm(QObject * parent);
	~FastComm(void);

	void	StartServer(int port);
	virtual	void	SetNullInChild(FastCommLeaf *child)	override;

	void	ClearAllReqConnection(void);
	void	AddReqConnection(QObject *parent ,int ID ,const QString &ip ,int Port);
	bool	StartAllReqConnection(DWORD WaitingTime=1000);
	bool	IsConnected(int ID);

	bool	TxData(int32 globalPage 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,int commID ,BYTE *buff ,int xbyte 
					,ErrorCodeList &ErrorData);
	bool	TxData(int32 globalPage 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,int commID ,QBuffer *f
					,ErrorCodeList &ErrorData);
	bool	TxData(int32 globalPage
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,int commID ,QByteArray *f
					,ErrorCodeList &ErrorData);

	FastCommLeaf *GetLeaf(int ID){	return(Leaf[ID]);	}
	int			GetOpenedLeafCount(void);
	QTcpSocket	*GetSocket(int ComNo);
	int		GetFirstCommID(void);
	void	WaitReadyReadAll(int milisec);

	virtual	FastCommLeaf *CreateNewLeaf(int ID){		return new FastCommLeaf(ID ,this);	}
	RecList	*UnpackTopRxBuff(int ID);
	virtual	void	SetConnectedAttr(FastCommLeaf *Leaf){}
	void	SlotNewConnection(int ID);
	void	MiscatchPacket(int GlobalPage ,QString EmitterRoot ,QString EmitterName ,QString CmdClass);

private slots:
	virtual	void	SlotNewConnection ()		override;

protected slots:
	virtual	void	SlotReceived(int,int)		override;
	virtual	void	SlotDisconnected(int id)	override;
};



#endif