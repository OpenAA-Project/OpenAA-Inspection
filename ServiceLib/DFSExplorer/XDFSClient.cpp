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

#include <cmath>
#include "XDFSClient.h"

DFSClient::DFSClient(QObject *parent ,const QString &IPAddress,int PortNumber)
	:DFSSocket(parent ,IPAddress,PortNumber)
{
}


void	DFSClient::Received(int cmd ,QByteArray &data)
{
	if(cmd==DFSCmd_AckEnumFolders){
		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		Folders.Load(&RBuff);
		SetReceived(true);
		emit	SignalShowFolders();
	}
	else if(cmd==DFSCmd_AckEnumFiles){
		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		FileNames.Load(&RBuff);
		SetReceived(true);
		emit	SignalShowFiles();
	}
	else if(cmd==DFSCmd_AckSaveFile){
		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		::Load(&RBuff,DestNetwordFolder);
		SetReceived(true);
	}
	else if(cmd==DFSCmd_AckLoadFile){
		QBuffer	RBuff(&data);
		RBuff.open(QIODevice::ReadOnly);
		::Load(&RBuff,DestNetworkFile);
		SetReceived(true);
	}
	else if(cmd==DFSCmd_AckRemoveFile){
		SetReceived(true);
	}
	else if(cmd==DFSCmd_AckMakeFolder){
		SetReceived(true);
	}
}