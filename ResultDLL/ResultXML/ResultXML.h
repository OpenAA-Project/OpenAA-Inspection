/*
 * Copyright (C) 2023
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