/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XSyncGUI.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XSYNCGUI_H)
#define	XSYNCGUI_H

#include <QString>
#include <QIODevice>
#include <QByteArray>
#include <QTcpSocket>
#include <QTcpServer>
#include "NList.h"
#include "XTypeDef.h"
#include "XServiceForLayers.h"

#define	DefaultSyncGUIPort	23200

class	LayersBase;
class	SyncGUIPack;

class	SyncGUIPipe : public QObject,public NPList<SyncGUIPipe>,public ServiceForLayers
{
	Q_OBJECT
	
	QTcpSocket	Client;
	QTcpSocket	*Receiver;

	int		RxMode;
	int32	RxByte;
	BYTE	*RxBuff;
	int		CurrentByte;

	QString RxGUIRoot;
	QString RxGUIName;
	QString RxInstName;
	QByteArray	RxData;
	bool	Ack;
	std::shared_ptr<SyncGUIPack>	Parent;

public:
	QString	IPAddress;
	int		Port;

	explicit    SyncGUIPipe(std::shared_ptr<SyncGUIPack> parent ,LayersBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	SetReceiver(QTcpSocket *r);
	void	ConnectToHost(void);
	bool	Send(const QString &GUIRoot,const QString &GUIName,const QString &InstName
				,QByteArray &Data,int SecToWaitForAck);

	bool	IsConnected(void);

signals:
	void	SignalReceive();
private slots:
	void SlotDisconnectedClient();
	void SlotDisconnectedReceiver();
	void SlotReadyReadClient();
	void SlotReadyReadReceiver();
	void SlotReceive();
private:
	void	ExeReadyRead(QTcpSocket *s);
	bool	Send(QTcpSocket *Sock,const QString &GUIRoot,const QString &GUIName,const QString &InstName
				,QByteArray &Data);
};

class	SyncGUIPack : public QObject,public NPListPack<SyncGUIPipe>,public ServiceForLayers
{
	Q_OBJECT
	QTcpServer	Server;
	bool	OnReceiving;
public:
	explicit    SyncGUIPack(LayersBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Start(void);
	bool	Send(const QString &GUIRoot,const QString &GUIName,const QString &InstName
				,QByteArray &Data,int MilisecToWaitForAck=30000);

	void	SetReceived(bool);
	bool	NowOnReceiving(void);
	int		GetConnectedCount(void);

private slots:
	void SlotNewConnection ();
};

#endif
