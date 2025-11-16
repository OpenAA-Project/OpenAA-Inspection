/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\SeqFor64Connector\SeqFor64Connector.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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
