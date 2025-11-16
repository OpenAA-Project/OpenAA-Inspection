/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ResultDLL\ResultXML\ResultXML.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef RESULTXML_H
#define RESULTXML_H

#include "resultxml_global.h"

#include "XResult.h"
#include "XResultDLL.h"
#include "XDataInLayer.h"
#include "clientmain.h"

class	ResultClient : public ResultDLLBaseRoot
{
//	ClientMain	*Client;
	ClientMain	*ClientMaster;
	ClientMain	*ClientSleave;
	ClientMain	*ClientMasterBoth;
	ClientMain	*ClientSleaveBoth;
public:
	ResultClient(LayersBase *Base);
	~ResultClient(void);	
	
	QString	HostName;
	int32	Port;
	QString	DBName;
	QByteArray sMsg;
	QString SubMasterDBN;
	QString SubSleaveDBN;
	QString	DatabasePath;
	QByteArray LotID;
	QByteArray LotName;
	QStringList	ErrorMessage;

	virtual	QString	GetDataText(void);
	virtual	QString	GetDefaultFileName(void);

	bool	OpenXML(QByteArray &Target, QByteArray &DBN, QByteArray &LotID, QByteArray &LotName ,QStringList &ErrorMessage,int Page=0);

	bool	OutputCommon(bool HostOk,ResultInspection &Res);
	bool	OutputResult(bool HostOk,int32 MachineID ,const QDateTime &InspectedTime ,ResultInspection *Res ,int localPage);
	bool	RemoveResult(int32 MachineID ,const QDateTime &ResultTime,	int64 InspectionID);
	bool	GetLastInspectionID(int MasterID, QString LotID ,int64 &InspectionID);

	bool	OutputInLotChangedSlave(int LocalPage);
	bool	OutputInLib(int LocalPage);
};
#endif // RESULTXML_H
