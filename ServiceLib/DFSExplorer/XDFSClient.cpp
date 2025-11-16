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