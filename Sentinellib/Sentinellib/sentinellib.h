/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinellib\Sentinellib\Sentinellib.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SENTINELLIB_H
#define SENTINELLIB_H

#include "spromeps.h"
#include <QStringList>
#include <QByteArray>

//#include "sentinellib_global.h"

//class SENTINELLIB_EXPORT Sentinellib
class Sentinellib
{
public:
	Sentinellib();
	~Sentinellib();
	bool SentinelExecute(QStringList &Ret);

private:
	RB_BYTE IsInitialized;			/* Will help to release the Memory if the pkt has been initialized. */
	RB_SPRO_APIPACKET ApiPack;		/* SuperPro packet      */
	RBP_SPRO_APIPACKET ApiPacket;
	bool bFirstSession;
	int SerialNumber;
	RB_WORD MemCell[56];
	QByteArray ReadArray;

	bool SentinelLogin();
	bool Session();
	bool ReadSentinel();
	void Return(QStringList &RetData);
};

#endif // SENTINELLIB_H
