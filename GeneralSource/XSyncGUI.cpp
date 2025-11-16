/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XSyncGUI.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "XSyncGUI.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "swap.h"


SyncGUIPipe::SyncGUIPipe(std::shared_ptr<SyncGUIPack> parent ,LayersBase *Base)
:ServiceForLayers(Base),Parent(parent)
{
	Receiver=NULL;
	RxMode	=0;
	RxBuff	=NULL;
	RxByte	=0;
	CurrentByte	=0;

	IPAddress="localhost";
	Port	=DefaultSyncGUIPort;

	connect(this,SIGNAL(SignalReceive()),this,SLOT(SlotReceive()),Qt::QueuedConnection);
}

bool	SyncGUIPipe::Save(QIODevice *f)
{
	if(::Save(f,IPAddress)==false){
		return false;
	}
	if(::Save(f,Port)==false){
		return false;
	}
	return true;
}
bool	SyncGUIPipe::Load(QIODevice *f)
{
	if(::Load(f,IPAddress)==false){
		return false;
	}
	if(::Load(f,Port)==false){
		return false;
	}
	return true;
}

void	SyncGUIPipe::SetReceiver(QTcpSocket *r)
{
	if(Client.state()==QAbstractSocket::ConnectedState){
		Client.disconnectFromHost();
		Client.waitForDisconnected();
	}
	Receiver=r;
	connect(Receiver,SIGNAL(disconnected()),this,SLOT(SlotDisconnectedReceiver()));
	connect(Receiver,SIGNAL(readyRead()),this,SLOT(SlotReadyReadReceiver()));
}

void	SyncGUIPipe::ConnectToHost(void)
{
	if(Client.state()!=QAbstractSocket::ConnectedState){
		Client.setParent(GetLayersBase()->GetMainWidget());
		connect(&Client,SIGNAL(disconnected()),this,SLOT(SlotDisconnectedClient()));
		connect(&Client,SIGNAL(readyRead()),this,SLOT(SlotReadyReadClient()));
		Client.connectToHost(IPAddress, Port);
		Client.waitForConnected(2000);
	}
}


void SyncGUIPipe::SlotDisconnectedClient()
{
}
void SyncGUIPipe::SlotDisconnectedReceiver()
{
	Receiver=NULL;
}
bool	SyncGUIPipe::Send(const QString &GUIRoot,const QString &GUIName,const QString &InstName
			,QByteArray &Data ,int MilisecToWaitForAck)
{
	QTcpSocket	*s=NULL;
	if(Receiver!=NULL && Receiver->state()==QAbstractSocket::ConnectedState){
		s=Receiver;
	}
	else{
		s=&Client;
		ConnectToHost();
	}
	Ack=false;
	Send(s,GUIRoot,GUIName,InstName,Data);
	int	N=MilisecToWaitForAck/10;
	for(int i=0;i<=N;i++){
		s->waitForReadyRead(10);
		if(Ack==true){
			return true;
		}
	}
	return false;
}
bool	SyncGUIPipe::Send(QTcpSocket *Sock,const QString &GUIRoot,const QString &GUIName,const QString &InstName
			,QByteArray &Data)
{
	if(Sock->state()==QAbstractSocket::ConnectedState){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,GUIRoot);
		::Save(&Buff,GUIName);
		::Save(&Buff,InstName);
		::Save(&Buff,Data);
		int32	Len=Buff.size();
		
		Sock->write((const char *)&Len,sizeof(Len));
		Sock->write(Buff.buffer());
		Sock->flush();
		return true;
	}
	return false;
}
void SyncGUIPipe::SlotReadyReadClient()
{
	ExeReadyRead(&Client);
}
void SyncGUIPipe::SlotReadyReadReceiver()
{
	ExeReadyRead(Receiver);
}
void SyncGUIPipe::ExeReadyRead(QTcpSocket *Sock)
{
	char	LBuff[10000];

	Parent->SetReceived(true);
	for(;;){
		int Len=Sock->read(LBuff,sizeof(LBuff));
		if(Len==0)
			break;
		if(RxMode==0){
			char	*fp=LBuff;
			RxByte=*((int32 *)fp);
			fp+=sizeof(int32);
			Len-=sizeof(int32);
			if(RxBuff!=NULL){
				delete	[]RxBuff;
				RxBuff = NULL;
			}
			if(0<=RxByte && Len>=0 && Len<100000 && RxByte>=Len){
				RxBuff=new BYTE[RxByte+100000];
				memcpy(RxBuff,fp,Len);
				CurrentByte=Len;
				RxMode=1;
			}
			else{
				Len=Sock->read(LBuff,sizeof(LBuff));
				CurrentByte=0;
				RxMode=0;
			}
		}
		else{
			int	LeftByte=RxByte-CurrentByte;
			int	MinLen=min(LeftByte,Len);
			if(0<=MinLen && MinLen<=10000){
				memcpy(&RxBuff[CurrentByte],LBuff,MinLen);
				CurrentByte+=MinLen;
			}
			else{
				Len=Sock->read(LBuff,sizeof(LBuff));
				CurrentByte=0;
				RxMode=0;
			}
		}
		if(CurrentByte==RxByte){
			RxMode=0;
			QByteArray	HBuffArray((const char *)RxBuff,RxByte);
			QBuffer	HBuff(&HBuffArray);
			HBuff.open(QIODevice::ReadWrite);
			::Load(&HBuff,RxGUIRoot);
			::Load(&HBuff,RxGUIName);
			::Load(&HBuff,RxInstName);
			::Load(&HBuff,RxData);
			if(RxGUIRoot=="ANY" && RxGUIName=="ANY"){
				Ack=true;
			}
			else{
				emit	SignalReceive();
				QByteArray TmpData;
				Send(Sock,"ANY","ANY","",TmpData);
			}
		}
	}
	Parent->SetReceived(false);
}

void SyncGUIPipe::SlotReceive()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(RxGUIRoot,RxGUIName,RxInstName);
	if(f!=NULL){
		f->RxSync(RxData);
	}
}

bool	SyncGUIPipe::IsConnected(void)
{
	if(Receiver!=NULL && Receiver->state()==QAbstractSocket::ConnectedState){
		return true;
	}
	else{
		if(Client.state()==QAbstractSocket::ConnectedState){
			return true;
		}
		ConnectToHost();
		if(Client.state()==QAbstractSocket::ConnectedState){
			return true;
		}
	}
	return false;	
}


//----------------------------------------------------------
SyncGUIPack::SyncGUIPack(LayersBase *Base)
:ServiceForLayers(Base)
{
	OnReceiving=false;
}

bool	SyncGUIPack::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(SyncGUIPipe *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	SyncGUIPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		SyncGUIPipe *a=new SyncGUIPipe(std::shared_ptr<SyncGUIPack>(this),GetLayersBase());
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

void	SyncGUIPack::Start(void)
{
	if(Server.isListening()==false){
		Server.setParent(GetLayersBase()->GetMainWidget());
		connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
		Server.listen(QHostAddress::Any, GetParamGlobal()->SyncGUIPort);
	}
}

void SyncGUIPack::SlotNewConnection()
{
	QTcpSocket *s=Server.nextPendingConnection();
	QString	Addr=s->peerAddress().toString();
	for(SyncGUIPipe *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IPAddress==Addr || (a->IPAddress.toLower()==/**/"localhost" && Addr=="127.0.0.1")){
			a->SetReceiver(s);
		}
	}
}

bool	SyncGUIPack::Send(const QString &GUIRoot,const QString &GUIName,const QString &InstName
			,QByteArray &Data,int SecToWaitForAck)
{
	if(NowOnReceiving()==false){
		for(SyncGUIPipe *a=GetFirst();a!=NULL;a=a->GetNext()){
			//for(int i=0;i<5;i++){
				if(a->Send(GUIRoot,GUIName,InstName,Data,SecToWaitForAck)==true){
					return true;
				}
			//}
		}
	}
	return false;
}

void	SyncGUIPack::SetReceived(bool b)
{
	OnReceiving=b;
}
bool	SyncGUIPack::NowOnReceiving(void)
{
	return OnReceiving;
}

int		SyncGUIPack::GetConnectedCount(void)
{
	int	Count=0;
	for(SyncGUIPipe *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsConnected()==true){
			Count++;
		}
	}
	return Count;
}

