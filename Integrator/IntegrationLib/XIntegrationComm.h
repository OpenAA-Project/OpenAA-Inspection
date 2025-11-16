/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Integrator\IntegrationLib\XIntegrationComm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XIntegrationComm_H)
#define	XIntegrationComm_H

#include <QString>
#include <QIODevice>
#include <QByteArray>
#include <QTcpSocket>
#include <QTcpServer>
#include <QBuffer>
#include <QMutex>
#include <QTimer>
#include "NList.h"
#include "XTypeDef.h"
#include "XServiceForLayers.h"
#include "XEntryPoint.h"

#define	DefaultIntegrationCommPort				23210

class	LayersBase;
class	IntegrationCommPack;
class	ErrorCodeList;

class	IntegrationRecList : public NPList<IntegrationRecList>
{
public:
	BYTE		*Data;
	int32		Cmd;
	int32		Len;
	int32		SlaveNo;
	int16		EmitterRootLen;
	int16		EmitterNameLen;
	int16		ClassNameLen;
	int32		IDForUndo;
	int32		ErrorCode;
	BYTE		ErrorLevel;
	BYTE		ErrorMessageLen;
	BYTE		ErrorTimeLen;
	int16		ShadowLevel ;
	int16		ShadowNumber;

	IntegrationRecList(int len);
	IntegrationRecList(const IntegrationRecList &src);
	~IntegrationRecList(void);

	IntegrationRecList	&operator=(const IntegrationRecList &src);
	BYTE	*GetClassNamePointer(char CmdEmitterRootBuff[] ,char CmdEmitterNameBuff[] ,char CmdClassBuff[] ,int maxByte)	const;
	BYTE	*GetError(BYTE *fp,ErrorCodeList &ErrorData)	const;

	BYTE	*GetPointer(void)	const	{	return(Data);	}
	BYTE	*GetPointer(BYTE *p ,int32 &ret)	const;
	BYTE	*GetPointer(BYTE *p ,WORD &ret )	const;
	BYTE	*GetPointer(BYTE *p ,bool &ret )	const;
	BYTE	*GetPointer(BYTE *p ,BYTE *buff ,int buffByte)	const;
	BYTE	*GetPointer(BYTE *p ,QBuffer &ret)	const;
};

#pragma	pack(push,1)
struct	IntegrationTxRxLowPacket
{
	int32		NowOnXByte;
	int32		NowCmd;
	int32		ErrorCode;
	int32		IDForUndo;
	BYTE		EmitterRootLen;
	BYTE		EmitterNameLen;
	BYTE		ClassNameLen;
	BYTE		ErrorLevel;
	BYTE		ErrorMessageLen;
	BYTE		ErrorTimeLen;
	int16		ShadowLevel ;
	int16		ShadowNumber;
};
#pragma	pack(pop)


class	IntegrationCommPipe : public QObject,public NPList<IntegrationCommPipe>,public ServiceForLayers
{
	Q_OBJECT

	friend	class	IntegrationCommPack;

	int32		SlaveNo;
	NPListPack<IntegrationRecList>	RecData;

	QTcpSocket	Client;
	QTcpSocket	*Receiver;

	IntegrationRecList		*OnRBuff;
	struct	IntegrationTxRxLowPacket	Pct;
	int32	NowOnPoint;
	int32	NowOnXByte;
	int32	NowCmd;
	QMutex		MuteRecData;
	bool	Ack;
	IntegrationCommPack	*Parent;
	int32	LastPacketLoadedSize;
	int32	RxReEntrant;
	enum	_RxState{
		_NowOnReceiving
		,_NowOnWaiting
		}RxState;
	time_t		LastReceivingTime;
	DWORD		LastConnectingTime;
	QTimer		OneShotTimerForConnection;
public:
	QString	IPAddress;
	int		Port;

	IntegrationCommPipe(int slaveNo ,IntegrationCommPack *parent ,LayersBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	SetReceiver(QTcpSocket *r);
	bool	ConnectToHost(const QString &ipaddress , int port);
	bool	Send(struct EntryPointBase::EntryPointPacketInfo &IndoPacket
				,QByteArray &Data		
				,ErrorCodeList &ErrorData
				,int MilisecToWaitForAck=30000);

	bool	IsConnected(void);
	IntegrationRecList	*UnpackTopRxBuff(void);
	QTcpSocket	*GetSocket(void)	const	{	return (Receiver!=NULL)?Receiver:(QTcpSocket *)&Client;	}
signals:
	void	SignalReceived(int SlaveNo,int Cmd);
private slots:
	void	SlotOneShotTimerForConnection();
	void	SlotDisconnectedClient();
	void	SlotDisconnectedReceiver();
	void	SlotReadyReadClient();
	void	SlotReadyReadReceiver();
private:
	void	ExeReadyRead(QTcpSocket *s);
	bool	Send(QTcpSocket *Sock,const QString &GUIRoot,const QString &GUIName,const QString &InstName
				,QByteArray &Data);
};

class	IntegrationCommPack : public QObject,public NPListPack<IntegrationCommPipe>,public ServiceForLayers
{
	Q_OBJECT

	friend	class	IntegrationCommPipe;

	QTcpServer			*MasterServer		;
	QTcpServer			*SlaveServer		;	//for knocking
	IntegrationCommPipe	*CommInSlave;
	bool	OnReceiving;
	QTimer	TimerCheckConnection;		// IntegrationMaster runs this
	bool	ReEntrantTimer;
	QTcpSocket *SlaveSocket;
	QByteArray	RData;
public:
	IntegrationCommPack(LayersBase *Base);
	~IntegrationCommPack(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Start(void);
	bool	Send(int slaveNo
				,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
				,QByteArray &Data		
				,ErrorCodeList &ErrorData
				,int MilisecToWaitForAck=30000);

	void	SetReceived(bool);
	bool	NowOnReceiving(void);
	int		GetConnectedCount(void);
	void	RemoveCommPipe(IntegrationCommPipe *s);
	IntegrationCommPipe	*GetSocket(int SlaveNo)		const;
	IntegrationRecList	*UnpackTopRxBuff(int SlaveNo);
private slots:
	void	SlotNewConnection ();
	void	SlotNewSlaveConnection();
	virtual	void	SlotReceived(int,int){};
	void	SlotTimeOut();
private:
	void	ReConnectToHost(void);
};

#endif
