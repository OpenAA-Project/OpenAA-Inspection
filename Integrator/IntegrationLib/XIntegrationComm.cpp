/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\IntegrationLib\XIntegrationComm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "XIntegrationComm.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "XIntegrationBase.h"
#include "XParamIntegrationMaster.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XDateTime.h"

IntegrationRecList::IntegrationRecList(int len)
{
	Len=len;
	if(Len!=0){
		Data=new BYTE[Len];
	}
	else{
		Data=NULL;
	}
	EmitterRootLen	=0;
	EmitterNameLen	=0;
	ClassNameLen	=0;
	ErrorCode		=0;
	ErrorLevel		=0;
	ErrorMessageLen	=0;
	ErrorTimeLen	=0;
	ShadowLevel		=0;
	ShadowNumber	=0;
}
IntegrationRecList::IntegrationRecList(const IntegrationRecList &src)
{
	Len=src.Len;
	if(Len!=0){
		Data=new BYTE[Len];
		memcpy(Data,src.Data,Len);
	}
	else{
		Data=NULL;
	}
	EmitterRootLen	=src.EmitterRootLen	;
	EmitterNameLen	=src.EmitterNameLen	;
	ClassNameLen	=src.ClassNameLen	;
	ErrorCode		=src.ErrorCode		;
	ErrorLevel		=src.ErrorLevel		;
	ErrorMessageLen	=src.ErrorMessageLen;
	ErrorTimeLen	=src.ErrorTimeLen	;
	ShadowLevel		=src.ShadowLevel	;
	ShadowNumber	=src.ShadowNumber	;
}
IntegrationRecList::~IntegrationRecList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}
IntegrationRecList	&IntegrationRecList::operator=(const IntegrationRecList &src)
{
	if(this!=&src){
		Len=src.Len;
		if(Data!=NULL){
			delete	[]Data;
		}
		if(Len!=0){
			Data=new BYTE[Len];
			memcpy(Data,src.Data,Len);
		}
		else{
			Data=NULL;
		}
		EmitterRootLen	=src.EmitterRootLen	;
		EmitterNameLen	=src.EmitterNameLen	;
		ClassNameLen	=src.ClassNameLen	;
		ErrorCode		=src.ErrorCode		;
		ErrorLevel		=src.ErrorLevel		;
		ErrorMessageLen	=src.ErrorMessageLen;
		ErrorTimeLen	=src.ErrorTimeLen	;
		ShadowLevel		=src.ShadowLevel	;
		ShadowNumber	=src.ShadowNumber	;
	}
	return *this;
}
BYTE	*IntegrationRecList::GetClassNamePointer(char EmitterRoot[] ,char EmitterName[],char CmdClassBuff[] ,int maxByte)	const
{
	CmdClassBuff[maxByte-1]=0;
	EmitterRoot[maxByte-1]=0;
	EmitterName[maxByte-1]=0;
	if(Data==NULL)
		return NULL;
	BYTE	*p=Data;
	strncpy(EmitterRoot,(char *)p,maxByte-1);
	p+=EmitterRootLen+1;
	if(strlen(EmitterRoot)!=EmitterRootLen){
		return NULL;
	}
	strncpy(EmitterName,(char *)p,maxByte-1);
	p+=EmitterNameLen+1;
	if(strlen(EmitterName)!=EmitterNameLen){
		return NULL;
	}
	strncpy(CmdClassBuff,(char *)p,maxByte-1);
	p+=ClassNameLen+1;
	if(strlen(CmdClassBuff)!=ClassNameLen){
		return NULL;
	}
	return(p);
}

BYTE	*IntegrationRecList::GetPointer(BYTE *p ,int32 &ret)	const
{
	if(p==NULL){
		p=Data;
	}
	ret=*((int32 *)p);
	p+=sizeof(int32);
	return(p);
}
BYTE	*IntegrationRecList::GetPointer(BYTE *p ,WORD &ret)	const
{
	if(p==NULL){
		p=Data;
	}
	ret=*((WORD *)p);
	p+=sizeof(WORD);
	return(p);
}
BYTE	*IntegrationRecList::GetPointer(BYTE *p ,bool &ret)	const
{
	if(p==NULL){
		p=Data;
	}
	ret=*((bool *)p);
	p+=sizeof(bool);
	return(p);
}
BYTE	*IntegrationRecList::GetPointer(BYTE *p ,BYTE *buff ,int buffByte)	const
{
	if(p==NULL){
		p=Data;
	}
	memcpy(buff,p,buffByte);
	p+=buffByte;
	return(p);
}

BYTE	*IntegrationRecList::GetPointer(BYTE *p ,QBuffer &ret)	const
{
	if(p==NULL){
		p=Data;
	}
	int32	rsize=*((int32 *)p);
	p+=sizeof(int32);
	if(ret.isOpen()){
		ret.close();
	}
	ret.setData((const char *)p,rsize);
	return(p+rsize);
}

BYTE	*IntegrationRecList::GetError(BYTE *fp,ErrorCodeList &ErrorData)	const
{
	char	CmdErrorMessage[1000];
	char	CmdErrorTime[1000];

	strncpy(CmdErrorMessage,(char *)fp,sizeof(CmdErrorMessage)-1);
	CmdErrorMessage[sizeof(CmdErrorMessage)-1]=0;
	fp+=ErrorMessageLen+1;
	if(strlen(CmdErrorMessage)!=ErrorMessageLen){
		return NULL;
	}

	strncpy(CmdErrorTime,(char *)fp,sizeof(CmdErrorTime)-1);
	CmdErrorTime[sizeof(CmdErrorTime)-1]=0;
	fp+=ErrorTimeLen+1;
	if(strlen(CmdErrorTime)!=ErrorTimeLen){
		return NULL;
	}
	ErrorData.SetError(ErrorCode
					,CmdErrorMessage
					,(ErrorCodeList::CautionLevel)ErrorLevel
					,XDateTime::fromString(QString(CmdErrorTime),"d/M/yy h:m:s.z"));
	return fp;
}

//==================================================================================
IntegrationCommPipe::IntegrationCommPipe(int slaveNo ,IntegrationCommPack *parent ,LayersBase *Base)
:ServiceForLayers(Base),Parent(parent)
{
	SlaveNo				=slaveNo;
	Receiver			=NULL;

	NowOnXByte			=0;
	NowCmd				=0;
	RxReEntrant			=0;
	OnRBuff				=NULL;
	LastReceivingTime	=0;
	NowOnPoint			=0;
	RxState				=_NowOnWaiting;
	LastPacketLoadedSize=0;
	LastConnectingTime	=0;

	IPAddress			="localhost";
	Port				=DefaultIntegrationCommPort;

	connect(this,SIGNAL(SignalReceived(int,int)),parent,SLOT(SlotReceived(int,int)));
}

bool	IntegrationCommPipe::Save(QIODevice *f)
{
	if(::Save(f,IPAddress)==false){
		return false;
	}
	if(::Save(f,Port)==false){
		return false;
	}
	if(::Save(f,SlaveNo)==false){
		return false;
	}
	return true;
}
bool	IntegrationCommPipe::Load(QIODevice *f)
{
	if(::Load(f,IPAddress)==false){
		return false;
	}
	if(::Load(f,Port)==false){
		return false;
	}
	if(::Load(f,SlaveNo)==false){
		return false;
	}
	return true;
}

void	IntegrationCommPipe::SetReceiver(QTcpSocket *r)
{
	if(Client.state()==QAbstractSocket::ConnectedState){
		Client.disconnectFromHost();
		Client.waitForDisconnected();
	}
	Receiver=r;
	connect(Receiver,SIGNAL(disconnected()),this,SLOT(SlotDisconnectedReceiver()));
	connect(Receiver,SIGNAL(readyRead()),this,SLOT(SlotReadyReadReceiver()));
}

bool	IntegrationCommPipe::ConnectToHost(const QString &ipaddress , int port)
{
	if(Client.state()==QAbstractSocket::ConnectedState){
		return true;
	}
	IPAddress=ipaddress;
	Port=port;
	Client.setParent(GetLayersBase()->GetMainWidget());
	
	if(OneShotTimerForConnection.interval()!=1000){
		OneShotTimerForConnection.setSingleShot(true);
		OneShotTimerForConnection.setInterval(1000);
		connect(&OneShotTimerForConnection,SIGNAL(timeout()),this,SLOT(SlotOneShotTimerForConnection()));

		connect(&Client,SIGNAL(disconnected()),this,SLOT(SlotDisconnectedClient()));
		connect(&Client,SIGNAL(readyRead()),this,SLOT(SlotReadyReadClient()));
		
		Client.connectToHost(IPAddress, Port);
		LastConnectingTime	=::GetComputerMiliSec();
	}
	OneShotTimerForConnection.start();

	return false;
}
void	IntegrationCommPipe::SlotOneShotTimerForConnection()
{
	LayersBase	*LBase=GetLayersBase();
	if(Client.state()==QAbstractSocket::ConnectedState){
		QByteArray Data;
		ErrorCodeList ErrorData;
		struct EntryPointBase::EntryPointPacketInfo	Info(LBase->GetIntegrationBasePointer()->GetParamIntegrationMaster()->OwnSlaveNo
														,LBase->GetShadowLevel()
														,LBase->GetShadowNumber()
														,0
														,/**/""
														,/**/"" 
														,/**/"SetSlaveNo");
		Send(Info,Data,ErrorData);
		LastConnectingTime	=::GetComputerMiliSec();
	}
	else{
		Client.connectToHost(IPAddress, Port);
		LastConnectingTime	=::GetComputerMiliSec();
		OneShotTimerForConnection.start();
	}
}
void IntegrationCommPipe::SlotDisconnectedClient()
{
}
void IntegrationCommPipe::SlotDisconnectedReceiver()
{
	Receiver=NULL;
	Parent->RemoveCommPipe(this);
}



bool	IntegrationCommPipe::Send(struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QByteArray &Data			
								,ErrorCodeList &ErrorData
								,int MilisecToWaitForAck)
{
	QTcpSocket	*Sock=NULL;
	if(Receiver!=NULL && Receiver->state()==QAbstractSocket::ConnectedState){
		Sock=Receiver;
	}
	else if(Client.state()==QAbstractSocket::ConnectedState){
		Sock=&Client;
	}
	else{
		return false;
	}
	Ack=false;

	if(Sock!=NULL){
		if(IsConnected()==false){
			return false;
		}

		Sock->waitForBytesWritten(5000);

		int32	Len=Data.size();
		char	EmitterRoot[1000];
		QString2Char(IndoPacket.EmitterRoot ,EmitterRoot,sizeof(EmitterRoot));
		char	EmitterName[1000];
		QString2Char(IndoPacket.EmitterName ,EmitterName,sizeof(EmitterName));
		char	CmdClass[1000];
		QString2Char(IndoPacket.CmdClass ,CmdClass,sizeof(CmdClass));

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		int32	EmitterRootLen	=strlen(EmitterRoot);	
		int32	EmitterNameLen	=strlen(EmitterName);	
		int32	CmdClassLen		=strlen(CmdClass);	
		struct	IntegrationTxRxLowPacket	LPct;
		LPct.NowOnXByte	=Len+CmdClassLen+1
							+EmitterRootLen+1
							+EmitterNameLen+1
						+sizeof(Len);
		LPct.NowCmd			=IndoPacket.cmd;
		LPct.EmitterRootLen	=EmitterRootLen;
		LPct.EmitterNameLen	=EmitterNameLen;
		LPct.ClassNameLen	=CmdClassLen;
		LPct.IDForUndo		=IndoPacket.IDForUndo;
		LPct.ShadowLevel 	=IndoPacket.ShadowLevel ;
		LPct.ShadowNumber	=IndoPacket.ShadowNumber;

		LPct.ErrorLevel		=(BYTE)ErrorData.GetLevel();
		char	ErrorMessage[1000];
		char	ETime[30];
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			LPct.ErrorCode	=ErrorData.GetErrorCode();
			QString2Char(ErrorData.GetMessageStr() ,ErrorMessage,sizeof(ErrorMessage));
			LPct.ErrorMessageLen	=strlen(ErrorMessage);
			LPct.NowOnXByte +=LPct.ErrorMessageLen+1;
			QString	t=ErrorData.GetErrorTime().toString("d/M/yy h:m:s.z");
			QString2Char(t,ETime,sizeof(ErrorMessage));
			LPct.ErrorTimeLen=strlen(ETime);
			LPct.NowOnXByte +=LPct.ErrorTimeLen+1;
		}
		if(Sock->write((char *)&LPct,sizeof(LPct))!=sizeof(LPct)){
			return(false);
		}
		if(Sock->write((char *)EmitterRoot,EmitterRootLen+1)!=(EmitterRootLen+1)){
			return(false);
		}
		if(Sock->write((char *)EmitterName,EmitterNameLen+1)!=(EmitterNameLen+1)){
			return(false);
		}
		if(Sock->write((char *)CmdClass,CmdClassLen+1)!=(CmdClassLen+1)){
			return(false);
		}
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			if(Sock->write((char *)ErrorMessage	,LPct.ErrorMessageLen+1)!=(LPct.ErrorMessageLen+1)){
				return(false);
			}
			if(Sock->write((char *)ETime		,LPct.ErrorTimeLen+1)!=(LPct.ErrorTimeLen+1)){
				return(false);
			}
		}
		if(Sock->write((char *)&Len,sizeof(Len))!=sizeof(Len)){
			return(false);
		}
		if(Sock->write(Data)!=Len){
			return(false);
		}
		if(Sock->flush()==false){
			return false;
		}
		return(true);
	}
	return(false);
}

void IntegrationCommPipe::SlotReadyReadClient()
{
	ExeReadyRead(&Client);
}
void IntegrationCommPipe::SlotReadyReadReceiver()
{
	ExeReadyRead(Receiver);
}

bool	IntegrationCommPipe::IsConnected(void)
{
	if(Receiver!=NULL && Receiver->state()==QAbstractSocket::ConnectedState){
		return true;
	}
	else{
		if(Client.state()==QAbstractSocket::ConnectedState){
			return true;
		}
		ConnectToHost(GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->MasterIPAddress
					, GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->IntegrationPortNo);
		if(Client.state()==QAbstractSocket::ConnectedState){
			return true;
		}
	}
	return false;	
}
IntegrationRecList	*IntegrationCommPipe::UnpackTopRxBuff(void)
{
	MuteRecData.lock();
	IntegrationRecList	*R=RecData.GetFirst();
	if(R!=NULL){
		RecData.RemoveList(R);
	}
	MuteRecData.unlock();
	return(R);
}

//----------------------------------------------------------
IntegrationCommPack::IntegrationCommPack(LayersBase *Base)
:ServiceForLayers(Base)
{
	MasterServer	=NULL;
	SlaveServer		=NULL;
	CommInSlave		=NULL;
	OnReceiving		=false;
	ReEntrantTimer	=false;
	SlaveSocket		=NULL;
}
IntegrationCommPack::~IntegrationCommPack(void)
{
	if(MasterServer!=NULL){
		delete	MasterServer;
		MasterServer=NULL;
	}
	if(SlaveServer!=NULL){
		delete	SlaveServer;
		SlaveServer=NULL;
	}
	if(CommInSlave!=NULL){
		delete	CommInSlave;
		CommInSlave=NULL;
	}
	if(SlaveSocket!=NULL){
		delete	SlaveSocket;
		SlaveSocket=NULL;
	}
}
bool	IntegrationCommPack::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(IntegrationCommPipe *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	IntegrationCommPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		IntegrationCommPipe *a=new IntegrationCommPipe(0,this,GetLayersBase());
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

void	IntegrationCommPack::Start(void)
{
	bool	Effective=false;
	QMetaObject::Connection	ConRet;
	bool	Ret;
	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL){
		if(IBase->GetParamIntegrationMaster()->IsIntegrationMaster()==true
		&& IBase->GetIntegrationSlaveCount()>0){
			if(MasterServer==NULL){
				MasterServer=new QTcpServer(parent());
			}
			if(MasterServer->isListening()==false){
				MasterServer->setParent(GetLayersBase()->GetMainWidget());
				ConRet=connect(MasterServer,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
				Ret=MasterServer->listen(QHostAddress::Any, IBase->GetParamIntegrationMaster()->IntegrationPortNo);
			}
			ConRet=connect(&TimerCheckConnection,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
			TimerCheckConnection.setInterval(3000);
			TimerCheckConnection.setSingleShot(false);
			TimerCheckConnection.start();

			Effective=true;
		}
		else 
		if(IBase->GetParamIntegrationMaster()->IsIntegrationMaster()==false
		&& IBase->GetParamIntegrationMaster()->GetOwnSlaveNo()>=0){
			if(SlaveServer==NULL){
				SlaveServer=new QTcpServer(parent());
			}
			if(SlaveServer->isListening()==false){
				SlaveServer->setParent(GetLayersBase()->GetMainWidget());
				ConRet=connect(SlaveServer,SIGNAL(newConnection()),this,SLOT(SlotNewSlaveConnection()));
				if(((bool)ConRet)==false){
					Ret=false;
					qDebug()<<Ret;
				}
				int	SlavePortNo=IBase->GetParamIntegrationMaster()->IntegrationPortNo
								+1
								+IBase->GetParamIntegrationMaster()->GetOwnSlaveNo();
				Ret=SlaveServer->listen(QHostAddress::Any
									,SlavePortNo );
			}

			if(CommInSlave==NULL){
				CommInSlave=new IntegrationCommPipe(IBase->GetParamIntegrationMaster()->OwnSlaveNo
													,this,GetLayersBase());
			}
			QString ipaddress	=IBase->GetParamIntegrationMaster()->MasterIPAddress;
			int		port		=IBase->GetParamIntegrationMaster()->IntegrationPortNo;
			Ret=CommInSlave->ConnectToHost(ipaddress ,port);
			AppendList(CommInSlave);

			Effective=true;
		}

		if(Effective==true){
			if(IBase->GetParamIntegrationMaster()->SharedFolderForSlaveIntegration.isEmpty()==false){
				::ForceDirectories(IBase->GetParamIntegrationMaster()->SharedFolderForSlaveIntegration);
			}
		}
	}
}

void IntegrationCommPack::SlotNewConnection()
{
	QTcpSocket *s=MasterServer->nextPendingConnection();
	QString	Addr=s->peerAddress().toString();
	IntegrationCommPipe	*Pipe=new IntegrationCommPipe(0,this,GetLayersBase());
	Pipe->IPAddress=Addr;
	Pipe->SetReceiver(s);
	AppendList(Pipe);

	//GetLayersBase()->GetIntegrationBasePointer()->SlaveConnected();
}
void	IntegrationCommPack::SlotNewSlaveConnection()
{
	SlaveSocket=SlaveServer->nextPendingConnection();
	ReConnectToHost();
}

void	IntegrationCommPack::SlotTimeOut()
{
	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL
	&& IBase->GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		int	N=IBase->GetParamIntegrationMaster()->GetIntegrationSlaveCount();
		for(int i=0;i<N;i++){
			IntegrationCommPipe	*s=GetSocket(i);
			if(s==NULL){
				IntegrationSlave	*L=IBase->GetParamIntegrationMaster()->Slaves[i];
				QTcpSocket	ToClient;
				ToClient.setParent(GetLayersBase()->GetMainWidget());
				const	int	SlavePortNo=IBase->GetParamIntegrationMaster()->IntegrationPortNo
								+1
								+i;
				ToClient.connectToHost(L->SlaveAddress, SlavePortNo);
				for(int k=0;k<10;k++){
					ToClient.waitForConnected(100);
					//QAbstractSocket::SocketState	tState=ToClient.state();
				}
			}
		}
	}
}
void	IntegrationCommPack::ReConnectToHost(void)
{
	if(ReEntrantTimer==true)
		return;

	ReEntrantTimer=true;
	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL
	&& IBase->GetParamIntegrationMaster()->IsIntegrationMaster()==false
	&& IBase->GetParamIntegrationMaster()->GetOwnSlaveNo()>=0){
		if(CommInSlave!=NULL && CommInSlave->IsConnected()==false){
			QString ipaddress	=IBase->GetParamIntegrationMaster()->MasterIPAddress;
			int		port		=IBase->GetParamIntegrationMaster()->IntegrationPortNo;
			CommInSlave->ConnectToHost(ipaddress ,port);
		}
	}
	ReEntrantTimer=false;
}

bool	IntegrationCommPack::Send(int slaveNo 	
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QByteArray &Data		
								,ErrorCodeList &ErrorData
								,int MilisecToWaitForAck)
{
	if(NowOnReceiving()==false){
		if(GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->IsIntegrationMaster()==true){
			IntegrationCommPipe *a=GetSocket(slaveNo);
			if(a!=NULL){
				bool	Ret=a->Send(IndoPacket
									,Data	
									,ErrorData
									,MilisecToWaitForAck);
				return Ret;
			}
		}
		else{
			if(CommInSlave!=NULL){
				bool	Ret=CommInSlave->Send(IndoPacket
									,Data		
									,ErrorData
									,MilisecToWaitForAck);
				return Ret;
			}
		}
	}
	return false;
}

void	IntegrationCommPack::SetReceived(bool b)
{
	OnReceiving=b;
}
bool	IntegrationCommPack::NowOnReceiving(void)
{
	return OnReceiving;
}

int		IntegrationCommPack::GetConnectedCount(void)
{
	int	Count=0;
	for(IntegrationCommPipe *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsConnected()==true){
			Count++;
		}
	}
	return Count;
}

IntegrationCommPipe	*IntegrationCommPack::GetSocket(int SlaveNo)	const
{
	for(IntegrationCommPipe *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->SlaveNo==SlaveNo)
			return a;
	}
	return NULL;
}

void	IntegrationCommPack::RemoveCommPipe(IntegrationCommPipe *s)
{
	RemoveList(s);
	s->deleteLater();
	GetLayersBase()->GetIntegrationBasePointer()->SlaveDisconnected();
}

IntegrationRecList	*IntegrationCommPack::UnpackTopRxBuff(int SlaveNo)
{
	IntegrationCommPipe	*c=IntegrationCommPack::GetSocket(SlaveNo);
	if(c!=NULL){
		return(c->UnpackTopRxBuff());
	}
	return NULL;
}
//==================================================================================================
