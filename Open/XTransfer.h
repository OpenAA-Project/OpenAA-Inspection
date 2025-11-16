/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XTransfer.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XTRANSFER_H)
#define	XTRANSFER_H

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
#include "XIntClass.h"

class	MixTransferLeaf;
class	MixTransferRecList;
class	RemoteTransferList;


const int	MaxMixTransferCommLeafNumb=100;

class	MixTransferComm :public QTcpServer , public ServiceForLayers
{
    Q_OBJECT

	friend	class	MixTransferLeaf;

	IntList			LocalPort;
	int32			ServerPort;
	MixTransferLeaf	*LeafClient[MaxMixTransferCommLeafNumb];
	MixTransferLeaf *LeafServer[MaxMixTransferCommLeafNumb];

	QString		FixedAddress;
	int32		FixedPort;
public:
	MixTransferComm(LayersBase *base ,QObject * parent);
	~MixTransferComm(void);

	void	StartMixTransferServer(void);

	void	ClearAllReqConnection(void);
	MixTransferLeaf	*AddReqConnection(QObject *parent ,const QString &ip ,int Port);
	bool	IsConnected(int ID);
	void	SetDisconnect(MixTransferLeaf *leaf);

	bool	TxData(int32 cmd 
					,int commID ,QBuffer *f
					,ErrorCodeList &ErrorData);
	bool	TxData(int32 cmd
					,int commID ,QByteArray *f
					,ErrorCodeList &ErrorData);

	int			GetOpenedLeafCount(void);
	QTcpSocket	*GetSocket(int ComNo);
	int		GetFirstCommID(void);
	int		GetEmptyCommID(void);

	IntList	&GetLocalPort(void)	{	return LocalPort;	}
	bool	ExistHost(const QString &IP ,int port ,QString &RetName);

	bool	ReqHost(QString	&_FixedAddress ,int32 &_FixedPort);
	void	ResetFixedHost(void);

	virtual	MixTransferLeaf *CreateNewLeaf(int ID);
	MixTransferLeaf	*FindLeaf(const QString &IP ,int port);
	virtual	void	SetConnectedAttr(MixTransferLeaf *Leaf){}
	void	SlotNewConnection(int ID);

	bool	ReqGlobalParam(ParamGlobal &TmpGlobalParam ,DWORD WaitingTime=5000);
	bool	SndGlobalParam(DWORD WaitingTime=5000);
	bool	ReqMasterData(DWORD WaitingTime=5000);
	bool	SndMasterData(DWORD WaitingTime=5000);
	bool	ReqImageData(bool SrcMasterImage ,bool DstMasterImage ,bool ChangeXY ,DWORD WaitingTime=5000);
	bool	SndImageData(bool SrcMasterImage ,bool DstMasterImage ,bool ChangeXY ,DWORD WaitingTime=5000);
	bool	OperationGUIPush				(const QString &GUIRoot ,const QString &GUIName ,const QString &GUIInst,DWORD WaitingTime=5000);
	bool	OperationGUITranssmitDirectly	(const QString &GUIRoot ,const QString &GUIName ,const QString &GUIInst ,QByteArray &Data,DWORD WaitingTime=5000);
	bool	OperationAlgoTranssmitDirectly	(const QString &AlgoRoot ,const QString &AlgoName ,QByteArray &Data,DWORD WaitingTime=5000);
	bool	ChangeGUI(const QString &GUIFileName ,DWORD WaitingTime=5000);

	int		GetRemoteTransferList(RemoteTransferList List[]);

private slots:
	void	SlotNewConnection ();
};



#endif
