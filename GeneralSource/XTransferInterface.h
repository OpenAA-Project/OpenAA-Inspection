/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XTransfer.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XTRANSFERINTERFACE_H)
#define	XTRANSFERINTERFACE_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QBuffer>
#include <QMutex>
#include "XTypeDef.h"
#include <time.h>
#include "NListComp.h"
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"

#define	CmdMixTransfer_TxReqGlobalParam					1
#define	CmdMixTransfer_RxReqGlobalParam					101
#define	CmdMixTransfer_TxSndGlobalParam					2
#define	CmdMixTransfer_RxSndGlobalParam					102
#define	CmdMixTransfer_TxReqMasterDataImageCheckByte	3
#define	CmdMixTransfer_RxReqMasterDataImageCheckByte	103
#define	CmdMixTransfer_TxReqMasterDataImage				4
#define	CmdMixTransfer_RxReqMasterDataImage				104
#define	CmdMixTransfer_TxReqTargetDataImageCheckByte	13
#define	CmdMixTransfer_RxReqTargetDataImageCheckByte	113
#define	CmdMixTransfer_TxReqTargetDataImage				14
#define	CmdMixTransfer_RxReqTargetDataImage				114
#define	CmdMixTransfer_TxReqMasterAlgo					15
#define	CmdMixTransfer_RxReqMasterAlgo					115
#define	CmdMixTransfer_TxSndMasterDataImage				6
#define	CmdMixTransfer_RxSndMasterDataImage				106
#define	CmdMixTransfer_TxSndTargetDataImage				16
#define	CmdMixTransfer_RxSndTargetDataImage				116
#define	CmdMixTransfer_TxSndMasterAlgo					7
#define	CmdMixTransfer_RxSndMasterAlgo					107

#define	CmdMixTransfer_TxOperationGUIPush				10
#define	CmdMixTransfer_RxOperationGUIPush				110
#define	CmdMixTransfer_TxOperationGUITranssmitDirectly	11
#define	CmdMixTransfer_RxOperationGUITranssmitDirectly	111
#define	CmdMixTransfer_TxOperationAlgoTranssmitDirectly	12
#define	CmdMixTransfer_RxOperationAlgoTranssmitDirectly	112
#define	CmdMixTransfer_TxReqAck							17
#define	CmdMixTransfer_RxReqAck							117
#define	CmdMixTransfer_TxChangeGUI						20
#define	CmdMixTransfer_RxChangeGUI						120


struct	MixTreansferImagePacketInfo
{
	int32	Phase;
	int32	Page;
	int32	Layer;
	int32	TopY;
	int32	LineCount;
	int32	DotPerLine;
	int32	MaxLines;
};



class	MixTransferComm;
class	ErrorCodeList;

#pragma	pack(push,1)
struct	MixTransferLowPacket
{
	int32		NowOnXByte;
	int32		NowCmd;
	int32		ErrorCode;
	BYTE		ErrorLevel;
	BYTE		ErrorMessageLen;
	BYTE		ErrorTimeLen;
};

#pragma	pack(pop)

class	MixTransferRecList : public NPList<MixTransferRecList>
{
public:
	BYTE		*Data;
	int32		Cmd;
	int32		Len;
	int32		ErrorCode;
	BYTE		ErrorLevel;
	BYTE		ErrorMessageLen;
	BYTE		ErrorTimeLen;

	MixTransferRecList(int len);
	MixTransferRecList(const MixTransferRecList &src);
	~MixTransferRecList(void);

	MixTransferRecList	&operator=(const MixTransferRecList &src);
	BYTE	*GetError(BYTE *fp,ErrorCodeList &ErrorData);

	BYTE	*GetPointer(void){	return(Data);	}
	BYTE	*GetPointer(BYTE *p ,int32 &ret);
	BYTE	*GetPointer(BYTE *p ,WORD &ret );
	BYTE	*GetPointer(BYTE *p ,bool &ret );
	BYTE	*GetPointer(BYTE *p ,BYTE *buff ,int buffByte);
	BYTE	*GetPointer(BYTE *p ,QBuffer &ret);
};

class	MixTransferLeaf : public QObject
{
    Q_OBJECT

	friend	class	MixTransferComm;
	int32				ID;
	QTcpSocket			*Sock;
	bool				Servered;
	QString				IP;
	int32				Port;
	MixTransferComm		*cParent;
	NPListPack<MixTransferRecList>	RecData;
	QMutex				MuteRecData;
	int32				LastPacketLoadedSize;
	struct	MixTransferLowPacket	Pct;
	int32				FastCommLeafRxReEntrant;

	enum	_RxState{
		_NowOnReceiving
		,_NowOnWaiting
		}RxState;
	time_t		LastReceivingTime;
	MixTransferRecList		*OnRBuff;
	int32		NowOnPoint;
	int32		NowOnXByte;
	int32		NowCmd;

	bool		Connected;
	bool		Received;
	bool		ReceivedPiece;
public:
	QByteArray	Data;

	MixTransferLeaf(MixTransferComm *cparent);
	MixTransferLeaf(int ID ,MixTransferComm *cparent);
	~MixTransferLeaf(void);
	
	int		GetID(void){	return ID;	}

	void	Set(QObject *parent ,const QString &ip ,int port);
	bool	StartConnect(DWORD WaitingTime=5000);
	void	SetServerMode(QTcpSocket *sv);
	bool	IsServerMode(void){	return(Servered);	}
	void	SetCommParent(MixTransferComm *cparent){	cParent=cparent;	}
	bool	IsConnected(void);

	bool	TxData(int32 cmd,QBuffer *f,ErrorCodeList &ErrorData);
	bool	TxData(int32 cmd,QByteArray *f,ErrorCodeList &ErrorData);

	MixTransferRecList	*UnpackTopRxBuff(void);
	int		GetQueuedCount(void);
	QTcpSocket	*GetSocket(void){	return Sock;	}
	QString	GetPeerIPAddress(void);
	void	WaitReadyRead(int milisec);
	time_t	GetLastReceivingTime(void){		return LastReceivingTime;	}

	bool	IsReceived(void)		{	return Received;	}
	bool	IsReceivedPiece(void)	{	return ReceivedPiece;	}
	void	ClearReceived(void)		{	Received=false;		}
	int		GetNowCmd(void)			{	return NowCmd;		}

signals:
	void	SignalReceived(int ID,int Cmd);
	void	SignalDisconnected(int id);
private slots:
	void	SlotConnected();
	void	SlotDisconnected();
	void	SlotReadyRead();
	void	SlotReceived(int ID,int Cmd);
};


//------------------------------------------------------------------------------------------------------------

class	PhasePageLayerD : public NPListSaveLoad<PhasePageLayerD>
{
public:
	int		GlobalPage;
	int		Phase;
	int		Layer;
	DWORD	ImageCheckData;

	PhasePageLayerD(void){}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	PhasePageLayerDContainer : public NPListPackSaveLoad<PhasePageLayerD>
{
public:
	virtual	PhasePageLayerD	*Create(void){	return new PhasePageLayerD();	}
	PhasePageLayerD	*Find(int phase ,int layer);
};

class	GUICmdReqImageCheckByte: public GUICmdPacketBase
{
public:
	bool	MasterMode;
	GUICmdReqImageCheckByte(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckImageCheckByte: public GUICmdPacketBase
{
public:
	PhasePageLayerDContainer	CheckData;

	GUICmdAckImageCheckByte(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//-----------------------------------------------------
class	GUICmdReqImageMixTransfer: public GUICmdPacketBase
{
public:
	int		Phase;
	int		Layer;
	int		TopY;
	int		BundleCount;
	bool	MasterMode;

	GUICmdReqImageMixTransfer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckImageMixTransfer: public GUICmdPacketBase
{
public:
	int		BundleCount;
	BYTE	*Data;
	int		Len;

	GUICmdAckImageMixTransfer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckImageMixTransfer(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSndImageMixTransfer: public GUICmdPacketBase
{
public:
	int32	Phase;
	int32	Layer;
	int32	TopY;
	int32	BundleCount;
	int32	DotPerLine	;
	int32	MaxLines	;
	BYTE	*Data;
	int32	Len;
	bool	MasterMode;

	GUICmdSndImageMixTransfer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSndImageMixTransfer(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//-----------------------------------------------------
class	GUICmdReqAlgoDataMixTransfer: public GUICmdPacketBase
{
public:
	QString	AlgoRoot;
	QString	AlgoName;

	GUICmdReqAlgoDataMixTransfer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckAlgoDataMixTransfer: public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdAckAlgoDataMixTransfer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSndAlgoDataMixTransfer: public GUICmdPacketBase
{
public:
	QString	AlgoRoot;
	QString	AlgoName;
	QByteArray	Data;

	GUICmdSndAlgoDataMixTransfer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif
