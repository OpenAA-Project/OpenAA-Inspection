/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFastComm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XFastComm.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "swap.h"
#include "XDateTime.h"
#include "XDataInLayer.h"

RecList::RecList(int len)
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
	ShadowLevel		=0;
	ShadowNumber	=0;
	GlobalPage		=0;
	ErrorCode		=0;
	ErrorLevel		=0;
	ErrorMessageLen	=0;
	ErrorTimeLen	=0;
}

RecList::~RecList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

BYTE	*RecList::GetClassNamePointer(char EmitterRoot[] ,char EmitterName[],char CmdClassBuff[] ,int maxByte)
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

BYTE	*RecList::GetPointer(BYTE *p ,int32 &ret)
{
	if(p==NULL){
		p=Data;
	}
	ret=*((int32 *)p);
	p+=sizeof(int32);
	return(p);
}
BYTE	*RecList::GetPointer(BYTE *p ,WORD &ret)
{
	if(p==NULL){
		p=Data;
	}
	ret=*((WORD *)p);
	p+=sizeof(WORD);
	return(p);
}
BYTE	*RecList::GetPointer(BYTE *p ,bool &ret)
{
	if(p==NULL){
		p=Data;
	}
	ret=*((bool *)p);
	p+=sizeof(bool);
	return(p);
}
BYTE	*RecList::GetPointer(BYTE *p ,BYTE *buff ,int buffByte)
{
	if(p==NULL){
		p=Data;
	}
	memcpy(buff,p,buffByte);
	p+=buffByte;
	return(p);
}

BYTE	*RecList::GetPointer(BYTE *p ,QBuffer &ret)
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

BYTE	*RecList::GetError(BYTE *fp,ErrorCodeList &ErrorData)
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

TxList::TxList(int len , BYTE *data)
{
	Len=len;
	Data=new BYTE[Len];
	memcpy(Data,data,Len);
}

TxList::~TxList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

//==================================================================================

FastCommLeaf::FastCommLeaf(int id ,CommBase *cparent)
{
	ID=id;
	cParent=cparent;
	Servered=false;
	Sock=NULL;
	OnRBuff=NULL;
	LastReceivingTime	=0;
	NowOnPoint			=0;
	NowOnXByte			=0;
	NowCmd				=0;
	RxState				=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant=0;
	Connected=false;
}

FastCommLeaf::~FastCommLeaf(void)
{
	cParent->SetNullInChild(this);
	if(Sock!=NULL){
		Sock->close();
		delete	Sock;
	}
	Sock=NULL;
	cParent=NULL;
}

void	FastCommLeaf::Set(QObject *parent ,const QString &ip ,int port)
{
	IP	=ip;
	Port=port;
	Sock=new QTcpSocket(parent);

	connect(Sock ,SIGNAL(connected())	,this ,SLOT(SlotConnected()));
	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));

	connect(this ,SIGNAL(SignalReceived(int,int)),cParent ,SLOT(SlotReceived(int,int)));
}

void	FastCommLeaf::SetServerMode(QTcpSocket *sv)
{	
	Sock=sv;	
	Servered=true;	

	connect(Sock ,SIGNAL(connected())	,this ,SLOT(SlotConnected()));
	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));

	connect(this ,SIGNAL(SignalReceived(int,int)),cParent ,SLOT(SlotReceived(int,int)));
}

bool	FastCommLeaf::StartConnect(DWORD WaitingTime)
{
	if(Sock!=NULL){
		Connected=false;
		Sock->connectToHost (IP, Port);
		if(Sock->waitForConnected (WaitingTime)==false){
			return false;
		}
		if(Sock->open(QIODevice::ReadWrite | QIODevice::Unbuffered)==false){
			return false;
		}
		Connected=true;
		return(true);
	}
	return(false);
}

bool	FastCommLeaf::IsConnected(void)
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			return(true);
		}
	}
	return(false);
}

void	FastCommLeaf::WaitReadyRead(int milisec)
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			Sock->waitForReadyRead(milisec);
		}
	}
}

bool	FastCommLeaf::TxData(int32 globalPage 
							 ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
							 ,BYTE *buff ,int xbyte
							 ,ErrorCodeList &ErrorData)
{
	if(Sock!=NULL){
		if(IsConnected()==false){
			if(StartConnect()==false){
				return false;
			}
			if(IsConnected()==false){
				return false;
			}
		}
		Sock->waitForBytesWritten(5000);

		struct	TxRxLowPacket	Pct;
		char	EmitterRoot[1000];
		QString2Char(IndoPacket.EmitterRoot ,EmitterRoot,sizeof(EmitterRoot));
		char	EmitterName[1000];
		QString2Char(IndoPacket.EmitterName ,EmitterName,sizeof(EmitterName));
		char	CmdClass[1000];
		QString2Char(IndoPacket.CmdClass ,CmdClass,sizeof(CmdClass));
		int32	EmitterRootLen=strlen(EmitterRoot);	
		int32	EmitterNameLen=strlen(EmitterName);	
		int32	CmdClassLen=strlen(CmdClass);
		Pct.NowOnXByte	=xbyte+EmitterRootLen+1
							  +EmitterNameLen+1
							  +CmdClassLen+1;
		Pct.NowCmd			=IndoPacket.cmd;
		Pct.EmitterRootLen	=EmitterRootLen;
		Pct.EmitterNameLen	=EmitterNameLen;
		Pct.ClassNameLen	=CmdClassLen;
		Pct.GlobalPage		=globalPage;
		Pct.IDForUndo		=IndoPacket.IDForUndo;
		Pct.ShadowLevel		=IndoPacket.ShadowLevel ;
		Pct.ShadowNumber	=IndoPacket.ShadowNumber;

		Pct.ErrorLevel		=(BYTE)ErrorData.GetLevel();
		char	ErrorMessage[1000];
		char	ETime[30];
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			Pct.ErrorCode	=ErrorData.GetErrorCode();
			QString2Char(ErrorData.GetMessageStr() ,ErrorMessage,sizeof(ErrorMessage));
			Pct.ErrorMessageLen	=strlen(ErrorMessage);
			Pct.NowOnXByte +=Pct.ErrorMessageLen+1;
			QString	t=ErrorData.GetErrorTime().toString("d/M/yy h:m:s.z");
			QString2Char(t,ETime,sizeof(ErrorMessage));
			Pct.ErrorTimeLen=strlen(ETime);
			Pct.NowOnXByte +=Pct.ErrorTimeLen+1;
		}

		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return false;
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
			if(Sock->write((char *)ErrorMessage	,Pct.ErrorMessageLen+1)!=(Pct.ErrorMessageLen+1)){
				return(false);
			}
			if(Sock->write((char *)ETime		,Pct.ErrorTimeLen+1)!=(Pct.ErrorTimeLen+1)){
				return(false);
			}
		}

		if(xbyte!=0){
			if(Sock->write((char *)buff,xbyte)!=xbyte){
				return(false);
			}
		}
		if(Sock->flush()==false){
			return false;
		}
		return(true);
	}
	return(false);
}

bool	FastCommLeaf::TxData(int32 globalPage 
							 ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
							 ,QBuffer *f
							 ,ErrorCodeList &ErrorData)
{
	if(Sock!=NULL){
		if(IsConnected()==false){
			if(StartConnect()==false){
				return false;
			}
			if(IsConnected()==false){
				return false;
			}
		}
		Sock->waitForBytesWritten(5000);

		int32	Len=f->size();
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
		struct	TxRxLowPacket	Pct;
		Pct.NowOnXByte	=Len+CmdClassLen+1
							+EmitterRootLen+1
							+EmitterNameLen+1
						+sizeof(Len);
		Pct.NowCmd			=IndoPacket.cmd;
		Pct.EmitterRootLen	=EmitterRootLen;
		Pct.EmitterNameLen	=EmitterNameLen;
		Pct.ClassNameLen	=CmdClassLen;
		Pct.GlobalPage		=globalPage;
		Pct.IDForUndo		=IndoPacket.IDForUndo;
		Pct.ShadowLevel		=IndoPacket.ShadowLevel ;
		Pct.ShadowNumber	=IndoPacket.ShadowNumber;

		Pct.ErrorLevel		=(BYTE)ErrorData.GetLevel();
		char	ErrorMessage[1000];
		char	ETime[30];
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			Pct.ErrorCode	=ErrorData.GetErrorCode();
			QString2Char(ErrorData.GetMessageStr() ,ErrorMessage,sizeof(ErrorMessage));
			Pct.ErrorMessageLen	=strlen(ErrorMessage);
			Pct.NowOnXByte +=Pct.ErrorMessageLen+1;
			QString	t=ErrorData.GetErrorTime().toString("d/M/yy h:m:s.z");
			QString2Char(t,ETime,sizeof(ErrorMessage));
			Pct.ErrorTimeLen=strlen(ETime);
			Pct.NowOnXByte +=Pct.ErrorTimeLen+1;
		}
		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
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
			if(Sock->write((char *)ErrorMessage	,Pct.ErrorMessageLen+1)!=(Pct.ErrorMessageLen+1)){
				return(false);
			}
			if(Sock->write((char *)ETime		,Pct.ErrorTimeLen+1)!=(Pct.ErrorTimeLen+1)){
				return(false);
			}
		}
		if(Sock->write((char *)&Len,sizeof(Len))!=sizeof(Len)){
			return(false);
		}
		if(Sock->write(f->buffer().data(),Len)!=Len){
			return(false);
		}
		if(Sock->flush()==false){
			return false;
		}
		return(true);
	}
	return(false);
}

bool	FastCommLeaf::TxData(int32 globalPage 
							 ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
							 ,QByteArray *f
							 ,ErrorCodeList &ErrorData)
{
	if(Sock!=NULL){
		if(IsConnected()==false){
			if(StartConnect()==false){
				return false;
			}
			if(IsConnected()==false){
				return false;
			}
		}
		Sock->waitForBytesWritten(5000);

		int32	Len=f->size();
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
		struct	TxRxLowPacket	Pct;
		Pct.NowOnXByte	=Len+CmdClassLen+1
							+EmitterRootLen+1
							+EmitterNameLen+1
						+sizeof(Len);
		Pct.NowCmd			=IndoPacket.cmd;
		Pct.EmitterRootLen	=EmitterRootLen;
		Pct.EmitterNameLen	=EmitterNameLen;
		Pct.ClassNameLen	=CmdClassLen;
		Pct.GlobalPage		=globalPage;
		Pct.IDForUndo		=IndoPacket.IDForUndo;
		Pct.ShadowLevel		=IndoPacket.ShadowLevel ;
		Pct.ShadowNumber	=IndoPacket.ShadowNumber;

		Pct.ErrorLevel		=(BYTE)ErrorData.GetLevel();
		char	ErrorMessage[1000];
		char	ETime[30];
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			Pct.ErrorCode	=ErrorData.GetErrorCode();
			QString2Char(ErrorData.GetMessageStr() ,ErrorMessage,sizeof(ErrorMessage));
			Pct.ErrorMessageLen	=strlen(ErrorMessage);
			Pct.NowOnXByte +=Pct.ErrorMessageLen+1;
			QString	t=ErrorData.GetErrorTime().toString("d/M/yy h:m:s.z");
			QString2Char(t,ETime,sizeof(ErrorMessage));
			Pct.ErrorTimeLen=strlen(ETime);
			Pct.NowOnXByte +=Pct.ErrorTimeLen+1;
		}
		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
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
			if(Sock->write((char *)ErrorMessage	,Pct.ErrorMessageLen+1)!=(Pct.ErrorMessageLen+1)){
				return(false);
			}
			if(Sock->write((char *)ETime		,Pct.ErrorTimeLen+1)!=(Pct.ErrorTimeLen+1)){
				return(false);
			}
		}
		if(Sock->write((char *)&Len,sizeof(Len))!=sizeof(Len)){
			return(false);
		}
		if(Sock->write(*f)!=Len){
			return(false);
		}
		if(Sock->flush()==false){
			return false;
		}
		return(true);
	}
	return(false);
}

void	FastCommLeaf::TxDataQueueStart(void)
{
	TxQueueBuff.RemoveAll();
}
void	FastCommLeaf::TxDataQueuePush(BYTE *data ,int len)
{
	TxQueueBuff.AppendList(new TxList(len,data));
}
void	FastCommLeaf::TxDataQueuePush(int32 data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}
void	FastCommLeaf::TxDataQueuePush(WORD data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}
void	FastCommLeaf::TxDataQueuePush(bool data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}

void	FastCommLeaf::TxDataQueuePush(QBuffer *f)
{
	int32	rsize=f->size();
	TxQueueBuff.AppendList(new TxList(sizeof(rsize)	,(BYTE *)&rsize));
	TxQueueBuff.AppendList(new TxList(rsize			,(BYTE *)f->buffer().data()));
}
bool	FastCommLeaf::TxDataQueueFlush(int32 cmd ,int32 globalPage 
									  ,const QString &EmitterRootString 
									  ,const QString &EmitterNameString
									  ,const QString &CmdClassString)
{
	int	XByte=0;
	for(TxList *L=TxQueueBuff.GetFirst();L!=NULL;L=L->GetNext()){
		XByte+=L->Len;
	}
	if(Sock!=NULL){
		if(IsConnected()==false){
			if(StartConnect()==false){
				return false;
			}
			if(IsConnected()==false){
				return false;
			}
		}
		Sock->waitForBytesWritten(5000);

		struct	TxRxLowPacket	Pct;
		char	EmitterRoot[1000];
		QString2Char(EmitterRootString ,EmitterRoot,sizeof(EmitterRoot));
		char	EmitterName[1000];
		QString2Char(EmitterNameString ,EmitterName,sizeof(EmitterName));
		char	CmdClass[1000];
		QString2Char(CmdClassString ,CmdClass,sizeof(CmdClass));

		int32	EmitterRootLen	=strlen(EmitterRoot);	
		int32	EmitterNameLen	=strlen(EmitterName);	
		int32	CmdClassLen		=strlen(CmdClass);	
		Pct.NowOnXByte	=XByte+CmdClassLen+1
							  +EmitterRootLen+1
							  +EmitterNameLen+1;
		Pct.NowCmd		=cmd;
		Pct.EmitterRootLen	=EmitterRootLen;
		Pct.EmitterNameLen	=EmitterNameLen;
		Pct.ClassNameLen	=CmdClassLen;
		Pct.GlobalPage		=globalPage;
		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
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
		if(XByte!=0){
			for(TxList *L=TxQueueBuff.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->Len!=0){
					if(Sock->write((char *)L->Data,L->Len)!=L->Len){
						return(false);
					}
			}
		}
		if(Sock->flush()==false)
			return false;
		}
		TxQueueBuff.RemoveAll();
		return(true);
	}
	TxQueueBuff.RemoveAll();
	return(false);

}

RecList	*FastCommLeaf::UnpackTopRxBuff(void)
{
	MuteRecData.lock();
	RecList	*R=RecData.GetFirst();
	if(R!=NULL){
		RecData.RemoveList(R);
	}
	MuteRecData.unlock();
	return(R);
}

int		FastCommLeaf::GetQueuedCount(void)
{
	MuteRecData.lock();
	int	Ret=RecData.GetCount();
	MuteRecData.unlock();
	return(Ret);
}

QString	FastCommLeaf::GetPeerIPAddress(void)
{
	if(IsConnected()==true){
		return Sock->peerAddress ().toString();
	}
	return /**/"";
}

void	FastCommLeaf::SlotConnected()
{
}
void	FastCommLeaf::SlotDisconnected()
{
	emit	SignalDisconnected(ID);
	deleteLater();
}

const	int		MaxWaitingSecondInPacketReceive=30;

void	FastCommLeaf::SlotReadyRead()
{
	FastCommLeafRxReEntrant++;
	do{
		if(RxState==_NowOnWaiting || (RxState==_NowOnReceiving && (time(NULL)-LastReceivingTime>MaxWaitingSecondInPacketReceive))){
			int Len=Sock->read(((char *)&Pct)+LastPacketLoadedSize, sizeof(Pct)-LastPacketLoadedSize);
			if(Len<0){
				FastCommLeafRxReEntrant--;
				return;
			}
			if((Len+LastPacketLoadedSize)!=sizeof(Pct)){
				LastPacketLoadedSize+=Len;
				FastCommLeafRxReEntrant--;
				return;
			}
			LastPacketLoadedSize=0;

			NowOnXByte	=Pct.NowOnXByte	;
			NowCmd		=Pct.NowCmd		;
			if(OnRBuff!=NULL){
				delete	OnRBuff;
			}
			OnRBuff=new RecList(NowOnXByte);
			OnRBuff->Cmd			=NowCmd;
			OnRBuff->EmitterRootLen	=Pct.EmitterRootLen;
			OnRBuff->EmitterNameLen	=Pct.EmitterNameLen;
			OnRBuff->ClassNameLen	=Pct.ClassNameLen;
			OnRBuff->GlobalPage		=Pct.GlobalPage	;
			OnRBuff->ErrorCode		=Pct.ErrorCode;
			OnRBuff->ErrorLevel		=Pct.ErrorLevel;
			OnRBuff->ErrorMessageLen=Pct.ErrorMessageLen;
			OnRBuff->ErrorTimeLen	=Pct.ErrorTimeLen;
			OnRBuff->IDForUndo		=Pct.IDForUndo;
			OnRBuff->ShadowLevel 	=Pct.ShadowLevel ;
			OnRBuff->ShadowNumber	=Pct.ShadowNumber;

			NowOnPoint=0;
		
			int	N=Sock->bytesAvailable();
			if(N!=0){
				if(NowOnXByte>=N){
					Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
					if(Len<0){
						FastCommLeafRxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
				else if(NowOnXByte!=0){
					Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), NowOnXByte);
					if(Len<0){
						FastCommLeafRxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
			}
			RxState=_NowOnReceiving;
		}
		else{
			//qint64	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), NowOnXByte-NowOnPoint);
			int	N=Sock->bytesAvailable();
			int	RByte=min(OnRBuff->Len-NowOnPoint,N);
			int	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint),RByte);
			//int	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
			if(Len<0){
				FastCommLeafRxReEntrant--;
				return;
			}
			NowOnPoint+=Len;
		}

		LastReceivingTime=time(NULL);
		if(NowOnXByte<=NowOnPoint){
			RxState=_NowOnWaiting;
			MuteRecData.lock();
			RecData.AppendList(OnRBuff);
			OnRBuff=NULL;
			MuteRecData.unlock();
			emit	SignalReceived(ID ,NowCmd);
		}
	}while(Sock->bytesAvailable()!=0);
	FastCommLeafRxReEntrant--;
}


//==================================================================================

FastComm::FastComm(QObject * parent)
:CommBase(parent)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		Leaf[i]=NULL;
	}
}

FastComm::~FastComm(void)
{
	ClearAllReqConnection();
}


void	FastComm::StartServer(int port)
{
	listen ( QHostAddress::Any, port );
	connect(this,SIGNAL(newConnection()),this, SLOT(SlotNewConnection()));
}

void	FastComm::SlotNewConnection ()
{
	int	ID=0;
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]==NULL){
			ID=i;
			break;
		}
	}

	if(ID<MaxCommLeafNumb){
		SlotNewConnection(ID);
	}
}

void	FastComm::SlotNewConnection(int ID)
{
	Leaf[ID]=CreateNewLeaf(ID);
	Leaf[ID]->SetCommParent(this);
	QTcpSocket	*sv=nextPendingConnection ();
	if(sv!=NULL){
		Leaf[ID]->SetServerMode(sv);
		connect(Leaf[ID] ,SIGNAL(SignalDisconnected(int)),this ,SLOT(SlotDisconnected(int)));
		SetConnectedAttr(Leaf[ID]);
	}
}

void	FastComm::SetNullInChild(FastCommLeaf *child)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]==child){
			Leaf[i]=NULL;
		}
	}
}

void	FastComm::ClearAllReqConnection(void)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]!=NULL){
			delete	Leaf[i];
		}
		Leaf[i]=NULL;
	}

}
void	FastComm::WaitReadyReadAll(int milisec)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]!=NULL){
			Leaf[i]->WaitReadyRead(milisec);
		}
	}
}

int		FastComm::GetFirstCommID(void)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]!=NULL){
			return i;
		}
	}
	return -1;
}
void	FastComm::AddReqConnection(QObject *parent ,int ID ,const QString &ip ,int Port)
{
	if(Leaf[ID]!=NULL){
		delete	Leaf[ID];
	}
	Leaf[ID]=new FastCommLeaf(ID,this);
	Leaf[ID]->Set(parent ,ip ,Port);
}
bool	FastComm::StartAllReqConnection(DWORD WaitingTime)
{
	bool	Ret=true;
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]!=NULL){
			if(Leaf[i]->IsConnected()==false){
				if(Leaf[i]->StartConnect(WaitingTime)==false){
					Ret=false;
				}
			}
		}
	}
	return Ret;
}
bool	FastComm::IsConnected(int ID)
{
	if(Leaf[ID]!=NULL){
		if(Leaf[ID]->IsConnected()==true){
			return(true);
		}
	}
	return(false);
}
bool	FastComm::TxData(int32 globalPage 
						 ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket 
						 ,int commID ,BYTE *buff ,int xbyte
						 ,ErrorCodeList &ErrorData)
{
	if(commID==-2){
		commID=GetFirstCommID();
	}
	if(Leaf[commID]==NULL){
		return false;
	}
	return(Leaf[commID]->TxData(globalPage ,IndoPacket ,buff ,xbyte,ErrorData));
}

bool	FastComm::TxData(int32 globalPage 
						 ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
						 ,int commID ,QBuffer *f
						 ,ErrorCodeList &ErrorData)
{
	if(commID==-2){
		commID=GetFirstCommID();
	}
	if(Leaf[commID]==NULL){
		commID=0;
		if(Leaf[commID]==NULL){
			return false;
		}
	}
	return(Leaf[commID]->TxData(globalPage ,IndoPacket,f,ErrorData));
}
bool	FastComm::TxData(int32 globalPage 
						 ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
						 ,int commID ,QByteArray *f
						 ,ErrorCodeList &ErrorData)
{
	if(commID==-2){
		commID=GetFirstCommID();
	}
	if(Leaf[commID]==NULL){
		return false;
	}
	return(Leaf[commID]->TxData(globalPage ,IndoPacket,f,ErrorData));
}
QTcpSocket	*FastComm::GetSocket(int ComNo)
{
	if(Leaf[ComNo]==NULL){
		return NULL;
	}
	return Leaf[ComNo]->GetSocket();
}


int		FastComm::GetOpenedLeafCount(void)
{
	int	Ret=0;
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]!=NULL){
			Ret++;
		}
	}
	return Ret;
}

void	FastComm::SlotDisconnected(int id)
{
	Leaf[id]=NULL;
}


RecList	*FastComm::UnpackTopRxBuff(int ID)
{
	if(Leaf[ID]==NULL){
		return NULL;
	}
	return(Leaf[ID]->UnpackTopRxBuff());
}

void	FastComm::SlotReceived(int ID ,int Cmd)
{
}

void	FastComm::MiscatchPacket(int GlobalPage ,QString EmitterRoot ,QString EmitterName ,QString CmdClass)
{
	QString	FileName="MiscatchPacket.txt";
	QFileInfo LInfo(FileName);
	if(LInfo.size()<10000000){
		QFile	F(FileName);

		if(F.open(QIODevice::Append)==true){
			QTextStream	LF(&F);
			LF<<"GlobalPage=";
			LF<<GlobalPage;
			LF<<"  Root:";
			LF<<EmitterRoot;
			LF<<"  Name:";
			LF<<EmitterName;
			LF<<"  CmdClass:";
			LF<<CmdClass;
			LF<<"\n";
		}
	}
}

//=======================================================================================================
