/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XTransfer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "XTransferInterface.h"
#include "XTransfer.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "swap.h"
#include "XDateTime.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XGUIFormBase.h"
#include "XDataAlgorithm.h"
#include <QHostAddress>
#include <QCoreApplication>
#include "SelectTransferHostDialog.h"

#define	LocalHostName	"localhost"

MixTransferRecList::MixTransferRecList(int len)
{
	Len=len;
	if(Len!=0){
		Data=new BYTE[Len];
	}
	else{
		Data=NULL;
	}
	ErrorCode		=0;
	ErrorLevel		=0;
	ErrorMessageLen	=0;
	ErrorTimeLen	=0;
}

MixTransferRecList::MixTransferRecList(const MixTransferRecList &src)
{
	Len=src.Len;
	if(Len!=0){
		Data=new BYTE[Len];
		memcpy(Data,src.Data,Len);
	}
	else{
		Data=NULL;
	}
	ErrorCode		=src.ErrorCode		;
	ErrorLevel		=src.ErrorLevel		;
	ErrorMessageLen	=src.ErrorMessageLen;
	ErrorTimeLen	=src.ErrorTimeLen	;
}

MixTransferRecList::~MixTransferRecList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}
MixTransferRecList	&MixTransferRecList::operator=(const MixTransferRecList &src)
{
	if(this!=&src){
		Len=src.Len;
		if(Len!=0){
			Data=new BYTE[Len];
			memcpy(Data,src.Data,Len);
		}
		else{
			Data=NULL;
		}
		ErrorCode		=src.ErrorCode		;
		ErrorLevel		=src.ErrorLevel		;
		ErrorMessageLen	=src.ErrorMessageLen;
		ErrorTimeLen	=src.ErrorTimeLen	;
	}
	return *this;
}

BYTE	*MixTransferRecList::GetPointer(BYTE *p ,int32 &ret)
{
	if(p==NULL){
		p=Data;
	}
	ret=*((int32 *)p);
	p+=sizeof(int32);
	return(p);
}
BYTE	*MixTransferRecList::GetPointer(BYTE *p ,WORD &ret)
{
	if(p==NULL){
		p=Data;
	}
	ret=*((WORD *)p);
	p+=sizeof(WORD);
	return(p);
}
BYTE	*MixTransferRecList::GetPointer(BYTE *p ,bool &ret)
{
	if(p==NULL){
		p=Data;
	}
	ret=*((bool *)p);
	p+=sizeof(bool);
	return(p);
}
BYTE	*MixTransferRecList::GetPointer(BYTE *p ,BYTE *buff ,int buffByte)
{
	if(p==NULL){
		p=Data;
	}
	memcpy(buff,p,buffByte);
	p+=buffByte;
	return(p);
}

BYTE	*MixTransferRecList::GetPointer(BYTE *p ,QBuffer &ret)
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

BYTE	*MixTransferRecList::GetError(BYTE *fp,ErrorCodeList &ErrorData)
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

MixTransferLeaf::MixTransferLeaf(MixTransferComm *cparent)
{
	ID=cparent->GetEmptyCommID();
	cParent=cparent;
	Servered=false;
	Sock=NULL;
	OnRBuff=NULL;
	LastReceivingTime=0;
	NowOnPoint		=0;
	RxState=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant	=0;
	Received				=false;
	Connected=false;
}

MixTransferLeaf::MixTransferLeaf(int id ,MixTransferComm *cparent)
{
	ID=id;
	cParent=cparent;
	Servered=false;
	Sock=NULL;
	OnRBuff=NULL;
	LastReceivingTime=0;
	NowOnPoint		=0;
	RxState=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant	=0;
	Received				=false;
	Connected=false;
}

MixTransferLeaf::~MixTransferLeaf(void)
{
	cParent->SetDisconnect(this);
	if(Sock!=NULL){
		Sock->close();
		delete	Sock;
	}
	Sock=NULL;
	cParent=NULL;
}

void	MixTransferLeaf::Set(QObject *parent ,const QString &ip ,int port)
{
	IP	=ip;
	Port=port;
	Sock=new QTcpSocket(parent);

	connect(Sock ,SIGNAL(connected())	,this ,SLOT(SlotConnected()));
	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));

	connect(this ,SIGNAL(SignalReceived(int,int)),this ,SLOT(SlotReceived(int,int)),Qt::QueuedConnection);
}

void	MixTransferLeaf::SetServerMode(QTcpSocket *sv)
{	
	Sock=sv;	
	Servered=true;	

	connect(Sock ,SIGNAL(connected())	,this ,SLOT(SlotConnected()));
	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));

	connect(this ,SIGNAL(SignalReceived(int,int)),this ,SLOT(SlotReceived(int,int)),Qt::QueuedConnection);
}

bool	MixTransferLeaf::StartConnect(DWORD WaitingTime)
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

bool	MixTransferLeaf::IsConnected(void)
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			return(true);
		}
	}
	return(false);
}

void	MixTransferLeaf::WaitReadyRead(int milisec)
{
	if(Sock!=NULL){
		ReceivedPiece=false;
		if(Sock->state()==QAbstractSocket::ConnectedState){
			Sock->waitForReadyRead(milisec);
		}
	}
}

bool	MixTransferLeaf::TxData(int32 cmd 
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

		int64	Len=f->size();

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		struct	MixTransferLowPacket	Pct;
		Pct.NowOnXByte	=Len
						+sizeof(Len);
		Pct.NowCmd			=cmd;

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
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			if(Sock->write((char *)ErrorMessage	,Pct.ErrorMessageLen+1)!=(Pct.ErrorMessageLen+1)){
				return(false);
			}
			if(Sock->write((char *)ETime		,Pct.ErrorTimeLen+1)!=(Pct.ErrorTimeLen+1)){
				return(false);
			}
		}
		if(::Save(Sock,f->buffer())==false){
			return(false);
		}
		if(Sock->flush()==false){
			return false;
		}
		return(true);
	}
	return(false);
}

bool	MixTransferLeaf::TxData(int32 cmd 
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

		int64	Len=f->size();

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		struct	MixTransferLowPacket	Pct;
		Pct.NowOnXByte	=Len
						+sizeof(Len);
		Pct.NowCmd			=cmd;

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
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			if(Sock->write((char *)ErrorMessage	,Pct.ErrorMessageLen+1)!=(Pct.ErrorMessageLen+1)){
				return(false);
			}
			if(Sock->write((char *)ETime		,Pct.ErrorTimeLen+1)!=(Pct.ErrorTimeLen+1)){
				return(false);
			}
		}
		if(::Save(Sock,*f)==false){
			return(false);
		}
		if(Sock->flush()==false){
			return false;
		}
		return(true);
	}
	return(false);
}

MixTransferRecList	*MixTransferLeaf::UnpackTopRxBuff(void)
{
	MuteRecData.lock();
	MixTransferRecList	*R=RecData.GetFirst();
	if(R!=NULL){
		RecData.RemoveList(R);
	}
	MuteRecData.unlock();
	return(R);
}

int		MixTransferLeaf::GetQueuedCount(void)
{
	MuteRecData.lock();
	int	Ret=RecData.GetCount();
	MuteRecData.unlock();
	return(Ret);
}

QString	MixTransferLeaf::GetPeerIPAddress(void)
{
	if(IsConnected()==true){
		return Sock->peerAddress ().toString();
	}
	return /**/"";
}

void	MixTransferLeaf::SlotConnected()
{
}
void	MixTransferLeaf::SlotDisconnected()
{
	cParent->SetDisconnect(this);
	deleteLater();
}

const	int		MaxWaitingSecondInPacketReceive=30;

void	MixTransferLeaf::SlotReadyRead()
{
	ReceivedPiece=true;
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
			OnRBuff=new MixTransferRecList(NowOnXByte);
			OnRBuff->Cmd			=NowCmd;
			OnRBuff->ErrorCode		=Pct.ErrorCode;
			OnRBuff->ErrorLevel		=Pct.ErrorLevel;
			OnRBuff->ErrorMessageLen=Pct.ErrorMessageLen;
			OnRBuff->ErrorTimeLen	=Pct.ErrorTimeLen;

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
			Received=true;
			emit	SignalReceived(ID ,NowCmd);
		}
	}while(Sock->bytesAvailable()!=0);
	FastCommLeafRxReEntrant--;
}

//==================================================================================

MixTransferComm::MixTransferComm(LayersBase *base ,QObject * parent)
	:QTcpServer(parent),ServiceForLayers(base)
{
	for(int i=0;i<MaxMixTransferCommLeafNumb;i++){
		LeafClient[i]=NULL;
		LeafServer[i]=NULL;
	}
	ServerPort=-1;
	FixedPort=-1;
}

MixTransferComm::~MixTransferComm(void)
{
	ClearAllReqConnection();
}

void	MixTransferComm::StartMixTransferServer(void)
{
	int	StartPort=GetParamGlobal()->TransterPortNumber;
	int	PortCount=GetParamGlobal()->TransterPortCount;
	int	TransterWaitingMilisec=GetParamGlobal()->TransterWaitingMilisec;

	QTcpSocket *Sock=new QTcpSocket();
	for(int port=StartPort;port<(StartPort +PortCount);port++){
		Sock->connectToHost(LocalHostName, port);
		if(Sock->waitForConnected(TransterWaitingMilisec) == false) {
			ServerPort=port;
			break;
		}
		LocalPort.Merge(port);
		Sock->disconnectFromHost();
	}
	delete	Sock;

	listen ( QHostAddress::Any, ServerPort);
	connect(this,SIGNAL(newConnection()),this, SLOT(SlotNewConnection()));
}

void	MixTransferComm::SetDisconnect(MixTransferLeaf *leaf)
{
	if(leaf->IP.toLower()==LocalHostName || leaf->IP=="127.0.0.0" || leaf->IP == "127.1.1.1"){
		LocalPort.Remove(leaf->Port);
	}
	for(int i=0;i < MaxMixTransferCommLeafNumb;i++) {
		if(LeafServer[i]==leaf){
			LeafServer[i]=NULL;
		}
		if(LeafClient[i]==leaf){
			LeafClient[i]=NULL;
		}
	}
}

void	MixTransferComm::SlotNewConnection ()
{
	int	ID=0;
	for(int i=0;i<MaxMixTransferCommLeafNumb;i++){
		if(LeafServer[i]==NULL){
			ID=i;
			break;
		}
	}

	if(ID<MaxMixTransferCommLeafNumb){
		SlotNewConnection(ID);
	}
}

void	MixTransferComm::SlotNewConnection(int ID)
{
	LeafServer[ID]=CreateNewLeaf(ID);
	LeafServer[ID]->SetCommParent(this);
	QTcpSocket	*sv=nextPendingConnection ();
	if(sv!=NULL){
		LeafServer[ID]->SetServerMode(sv);
		connect(LeafServer[ID] ,SIGNAL(SignalDisconnected(int)),this ,SLOT(SlotDisconnected(int)));
		SetConnectedAttr(LeafServer[ID]);
	}
}

void	MixTransferComm::ClearAllReqConnection(void)
{
	for(int i=0;i<MaxMixTransferCommLeafNumb;i++){
		if(LeafServer[i]!=NULL){
			delete	LeafServer[i];
		}
		LeafServer[i]=NULL;
	}
	for(int i=0;i < MaxMixTransferCommLeafNumb;i++) {
		if(LeafClient[i] != NULL) {
			delete	LeafClient[i];
		}
		LeafClient[i]=NULL;
	}
}

int		MixTransferComm::GetFirstCommID(void)
{
	for(int i=0;i<MaxMixTransferCommLeafNumb;i++){
		if(LeafClient[i]!=NULL){
			return i;
		}
	}
	return -1;
}
int		MixTransferComm::GetEmptyCommID(void)
{
	for(int i=0;i<MaxMixTransferCommLeafNumb;i++){
		if(LeafClient[i]==NULL){
			return i;
		}
	}
	return -1;
}
MixTransferLeaf	*MixTransferComm::AddReqConnection(QObject *parent ,const QString &ip ,int Port)
{
	int ID;
	for(ID=0;ID<MaxMixTransferCommLeafNumb;ID++){
		if(LeafClient[ID]==NULL){
			break;
		}
	}
	if(ID<MaxMixTransferCommLeafNumb){
		LeafClient[ID]=new MixTransferLeaf(ID,this);
		LeafClient[ID]->Set(parent ,ip ,Port);
		QHostAddress	Host(ip);
		if(Host.isGlobal()==false){
			LocalPort.Merge(Port);
		}
		return LeafClient[ID];
	}
	return NULL;
}

bool	MixTransferComm::IsConnected(int ID)
{
	if(LeafClient[ID]!=NULL){
		if(LeafClient[ID]->IsConnected()==true){
			return(true);
		}
	}
	return(false);
}

bool	MixTransferComm::TxData(int32 cmd 
						 ,int commID ,QBuffer *f
						 ,ErrorCodeList &ErrorData)
{
	if(commID==-2){
		commID=GetFirstCommID();
	}
	if(LeafClient[commID]==NULL){
		commID=0;
		if(LeafClient[commID]==NULL){
			return false;
		}
	}
	return(LeafClient[commID]->TxData(cmd,f,ErrorData));
}
bool	MixTransferComm::TxData(int32 cmd 
						 ,int commID ,QByteArray *f
						 ,ErrorCodeList &ErrorData)
{
	if(commID==-2){
		commID=GetFirstCommID();
	}
	if(LeafClient[commID]==NULL){
		return false;
	}
	return(LeafClient[commID]->TxData(cmd,f,ErrorData));
}
QTcpSocket	*MixTransferComm::GetSocket(int ComNo)
{
	if(LeafClient[ComNo]==NULL){
		return NULL;
	}
	return LeafClient[ComNo]->GetSocket();
}


int		MixTransferComm::GetOpenedLeafCount(void)
{
	int	Ret=0;
	for(int i=0;i<MaxMixTransferCommLeafNumb;i++){
		if(LeafClient[i]!=NULL){
			Ret++;
		}
	}
	return Ret;
}

bool	MixTransferComm::ExistHost(const QString &IP, int port, QString &RetName)
{
	ErrorCodeList	ErrorData;
	for(int i=0;i < MaxMixTransferCommLeafNumb;i++) {
		if(LeafClient[i]!=NULL && LeafClient[i]->IP==IP && LeafClient[i]->Port==port) {
			QByteArray	Dummy;
			LeafClient[i]->TxData(CmdMixTransfer_TxReqAck ,&Dummy,ErrorData);
			LeafClient[i]->WaitReadyRead(1000);
			QCoreApplication::processEvents();
			if(LeafClient[i]->IsReceived()==true){
				QBuffer	Buff(&LeafClient[i]->Data);
				Buff.open(QIODevice::ReadOnly);
				if(::Load(&Buff,RetName)==true){
					return true;
				}
			}
		}
	}
	for(int i=0;i < MaxMixTransferCommLeafNumb;i++) {
		if(LeafServer[i]!=NULL && LeafServer[i]->IP==IP && LeafServer[i]->Port==port) {
			QByteArray	Dummy;
			LeafServer[i]->TxData(CmdMixTransfer_TxReqAck ,&Dummy,ErrorData);
			LeafServer[i]->WaitReadyRead(1000);
			QCoreApplication::processEvents();
			if(LeafServer[i]->IsReceived()==true){
				QBuffer	Buff(&LeafServer[i]->Data);
				Buff.open(QIODevice::ReadOnly);
				if(::Load(&Buff,RetName)==true){
					return true;
				}
			}
		}
	}
	MixTransferLeaf	*R=AddReqConnection(NULL,IP ,port);
	if(R->StartConnect()==true){
		QByteArray	Dummy;
		R->TxData(CmdMixTransfer_TxReqAck ,&Dummy,ErrorData);
		R->WaitReadyRead(1000);
		QCoreApplication::processEvents();
		if(R->IsReceived()==true){
			QBuffer	Buff(&R->Data);
			Buff.open(QIODevice::ReadOnly);
			if(::Load(&Buff,RetName)==true){
				return true;
			}
		}
	}
	else{
		delete	R;
	}
	return false;
}

int	MixTransferComm::GetRemoteTransferList(RemoteTransferList List[])
{
	QString	RetName;
	int	Row=0;

	for(IntClass	*c=GetLocalPort().GetFirst();c!=NULL;c=c->GetNext()){
		if(ExistHost(LocalHostName,c->GetValue(), RetName)==true){
			List[Row].Name		=RetName;
			List[Row].IPAddress	=LocalHostName;
			List[Row].Port		=c->GetValue();
			Row++;
		}
	}

	int	N=GetParamGlobal()->GetRemoteTransferCount();
	for(int i=0;i < N;i++) {
		RemoteTransferList *L=GetParamGlobal()->GetRemoteTransfer(i);
		if(ExistHost(L->IPAddress, L->Port, RetName) == true) {
			List[Row].Name		=RetName;
			List[Row].IPAddress	=L->IPAddress;
			List[Row].Port		=L->Port;
			Row++;
		}
	}

	int	StartPort=GetParamGlobal()->TransterPortNumber;
	int	PortCount=GetParamGlobal()->TransterPortCount;
	int	TransterWaitingMilisec=GetParamGlobal()->TransterWaitingMilisec;
	ErrorCodeList	ErrorData;

	QTcpSocket *Sock=new QTcpSocket();
	for(int port=StartPort;port<(StartPort +PortCount);port++){
		if(GetLocalPort().IsInclude(port)==false
		&& ServerPort!=port){
			Sock->connectToHost(LocalHostName, port);
			if(Sock->waitForConnected(TransterWaitingMilisec) == true) {
				LocalPort.Merge(port);
				Sock->disconnectFromHost();

				QString	RetName;
				if(ExistHost(LocalHostName ,port, RetName)==true){
					List[Row].Name		=RetName;
					List[Row].IPAddress	=LocalHostName;
					List[Row].Port		=port;
					Row++;
				}
			}
		}
	}
	delete	Sock;

	return Row;
}

bool	MixTransferComm::ReqHost(QString &_FixedAddress ,int32 &_FixedPort)
{
	QString	RetName;
	if(FixedPort<=0 || ExistHost(FixedAddress ,FixedPort ,RetName)==false){
		RemoteTransferList List[MaxRemoteTransferListDimNumb];
		int	RemoteTransferListNumb=GetRemoteTransferList(List);
		if(RemoteTransferListNumb==0){
			return false;
		}
		else
		if(RemoteTransferListNumb==1){
			_FixedAddress=List[0].IPAddress;
			_FixedPort	 =List[0].Port;
			FixedAddress =_FixedAddress;
			FixedPort	 =_FixedPort;
			return true;
		}
		else
		if(RemoteTransferListNumb>1){
			GetLayersBase()->CloseProcessingForm ();
			SelectTransferHostDialog	D(GetLayersBase());
			if(D.exec()==(int)true){
				FixedAddress =D.Selected.IPAddress;
				FixedPort	 =D.Selected.Port;
				_FixedAddress=FixedAddress;
				_FixedPort	 =FixedPort;
				return true;
			}
			return false;
		}
	}
	if(FixedPort>0){
		_FixedAddress=FixedAddress;
		_FixedPort	 =FixedPort;
		return true;
	}
	return false;
}

MixTransferLeaf	*MixTransferComm::FindLeaf(const QString &IP ,int port)
{
	for(int i=0;i<MaxMixTransferCommLeafNumb;i++){
		if(LeafClient[i]!=NULL && LeafClient[i]->IP==IP && LeafClient[i]->Port==port){
			return LeafClient[i];
		}
		if(LeafServer[i]!=NULL && LeafServer[i]->IP==IP && LeafServer[i]->Port==port){
			return LeafServer[i];
		}
	}
	return NULL;
}

void	MixTransferComm::ResetFixedHost(void)
{
	FixedPort=-1;
}

//===========================================================================================

bool	PhasePageLayerD::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ImageCheckData)==false)
		return false;
	return true;
}

bool	PhasePageLayerD::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ImageCheckData)==false)
		return false;
	return true;
}

PhasePageLayerD	*PhasePageLayerDContainer::Find(int phase ,int layer)
{
	for(PhasePageLayerD *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(d->Layer==layer && d->Phase==phase)
			return d;
	}
	return NULL;
}

