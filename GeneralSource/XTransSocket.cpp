#include "XTypeDef.h"
#include <cmath>
#include "XTransSocket.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "swap.h"


TrSocketClient::RecList::RecList(int len)
{
	Len=len;
	if(Len!=0){
		if(Len<16384){
			Data=DataBuff;
		}
		else{
			Data=new BYTE[Len];
		}
	}
	else{
		Data=NULL;
	}
	ErrorCode		=0;
	ErrorLevel		=0;
	ErrorMessageLen	=0;
	ErrorTimeLen	=0;
}

TrSocketClient::RecList::~RecList(void)
{
	if(Data!=NULL){
		if(Data!=DataBuff){
			delete	[]Data;
		}
		Data=NULL;
	}
}

BYTE	*TrSocketClient::RecList::GetPointer(BYTE *p ,int32 &ret)
{
	ret=*((int32 *)p);
	p+=sizeof(int32);
	return(p);
}
BYTE	*TrSocketClient::RecList::GetPointer(BYTE *p ,qint64 &ret)
{
	ret=*((qint64 *)p);
	p+=sizeof(qint64);
	return(p);
}
BYTE	*TrSocketClient::RecList::GetPointer(BYTE *p ,WORD &ret)
{
	ret=*((WORD *)p);
	p+=sizeof(WORD);
	return(p);
}
BYTE	*TrSocketClient::RecList::GetPointer(BYTE *p ,bool &ret)
{
	ret=*((bool *)p);
	p+=sizeof(bool);
	return(p);
}
BYTE	*TrSocketClient::RecList::GetPointer(BYTE *p ,BYTE *buff ,int buffByte)
{
	memcpy(buff,p,buffByte);
	p+=buffByte;
	return(p);
}

BYTE	*TrSocketClient::RecList::GetPointer(BYTE *p ,QBuffer &ret)
{
	int32	rsize=*((int32 *)p);
	p+=sizeof(int32);
	if(ret.isOpen()){
		ret.close();
	}
	ret.setData((const char *)p,rsize);
	return(p+rsize);
}

BYTE	*TrSocketClient::RecList::GetError(BYTE *fp,ErrorCodeList &ErrorData)
{
	char	CmdErrorMessage[1000];
	char	CmdErrorTime[1000];

	CmdErrorMessage[sizeof(CmdErrorMessage)-1]=0;
	CmdErrorTime[sizeof(CmdErrorTime)-1]=0;

	strncpy(CmdErrorMessage,(char *)fp,sizeof(CmdErrorMessage)-1);
	fp+=ErrorMessageLen+1;
	if(strlen(CmdErrorMessage)!=ErrorMessageLen){
		return NULL;
	}

	strncpy(CmdErrorTime,(char *)fp,sizeof(CmdErrorTime)-1);
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

TrSocketClient::TxList::TxList(int len , BYTE *data)
{
	Len=len;
	Data=new BYTE[Len];
	memcpy(Data,data,Len);
}

TrSocketClient::TxList::~TxList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

//==================================================================================

TrSocketClient::TrSocketClient(void)
{
	ID			=0;
	cParent		=NULL;
	Servered	=false;
	Sock		=NULL;
	OnRBuff				=NULL;
	LastReceivingTime	=0;
	NowOnPoint			=0;
	RxState				=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant=0;
	CreatedTime			=XDateTime::currentDateTime();
	DataIn				=false;
}

TrSocketClient::~TrSocketClient(void)
{
	if(Sock!=NULL){
		Sock->close();
		Sock->deleteLater();
	}
	Sock=NULL;
	cParent=NULL;
}

void	TrSocketClient::Set(QObject *parent ,const QString &ip ,int port)
{
	IP	=ip;
	Port=port;
	Sock=new QTcpSocket(parent);
	Sock->setSocketOption(QAbstractSocket::LowDelayOption,1);
	PeerIP=Sock->peerAddress().toString();
	connect(Sock ,SIGNAL(connected())	,this ,SLOT(SlotConnected()));
	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));
}

void	TrSocketClient::Set(QObject *parent ,const QString &ip ,int port) const
{
	IP	=ip;
	Port=port;
	Sock=new QTcpSocket(parent);
	Sock->setSocketOption(QAbstractSocket::LowDelayOption,1);
	PeerIP=Sock->peerAddress().toString();
	connect(Sock ,SIGNAL(connected())	,this ,SLOT(SlotConnected()));
	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));
}

void	TrSocketClient::Set(TrSocketServer *cparent)
{
	cParent=cparent;
	Sock	=cParent->GetServer().nextPendingConnection();
	Sock->setSocketOption(QAbstractSocket::LowDelayOption,1);
	Servered=true;	
	PeerIP=Sock->peerAddress().toString();
	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));
	ID=cParent->GetTopID();
}


bool	TrSocketClient::StartConnect(void) const
{
	if(Sock!=NULL){
		Sock->connectToHost (IP, Port);
		PeerIP=IP;
		if(Sock->waitForConnected (500)==false){
			return false;
		}
		if(Sock->open(QIODevice::ReadWrite | QIODevice::Unbuffered)==false){
			return false;
		}
		return(true);
	}
	return(false);
}

bool	TrSocketClient::IsConnected(void) const
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			return(true);
		}
	}
	return(false);
}

void	TrSocketClient::WaitReadyRead(int milisec) const
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			Sock->waitForReadyRead(milisec);
		}
	}
}

void	TrSocketClient::FlushRead(void) const
{
	//if(DataIn==true){
	//	while(DataIn==true){
	//		DataIn=false;
	//		WaitReadyRead(1);
	//	}
	//}
	//do{
	//	DataIn=false;
	//	WaitReadyRead(1);
	//}while(DataIn==true);
}

bool	TrSocketClient::TxData(BYTE *buff ,int xbyte) const
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
		Pct.NowOnXByte	=xbyte;
		Pct.ErrorLevel	=ErrorCodeList::_None;

		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return false;
		}
		if(xbyte!=0){
			if(Sock->write((char *)buff,xbyte)!=xbyte){
				return(false);
			}
			if(Sock->flush()==false){
				return false;
			}
		}
		return(true);
	}
	return(false);
}

bool	TrSocketClient::TxData(QBuffer *f) const
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

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		struct	TxRxLowPacket	Pct;

		Pct.NowOnXByte	=Len+sizeof(Len);
		Pct.ErrorLevel		=ErrorCodeList::_None;

		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return(false);
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

bool	TrSocketClient::TxData(QByteArray *f) const
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

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		struct	TxRxLowPacket	Pct;
		Pct.NowOnXByte	=Len
						+sizeof(Len);
		Pct.ErrorLevel		=ErrorCodeList::_None;

		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return(false);
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

bool	TrSocketClient::TxData(BYTE Cmd ,QByteArray *f) const
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

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		struct	TxRxLowPacket	Pct;
		Pct.NowOnXByte	=1+Len
						+sizeof(Len);
		Pct.ErrorLevel		=ErrorCodeList::_None;

		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return(false);
		}
		if(Sock->write((const char *)&Cmd,1)!=1){
			return(false);
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


bool	TrSocketClient::TxData(BYTE Cmd ,qint64 d) const
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

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		struct	TxRxLowPacket	Pct;
		Pct.NowOnXByte	=1+sizeof(d);
		Pct.ErrorLevel		=ErrorCodeList::_None;

		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return(false);
		}
		if(Sock->write((const char *)&Cmd,1)!=1){
			return(false);
		}
		if(Sock->write((char *)&d,sizeof(d))!=sizeof(d)){
			return(false);
		}
		if(Sock->flush()==false){
			return false;
		}
		return(true);
	}
	return(false);
}

bool	TrSocketClient::TxData(BYTE Cmd ,int32 d) const
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

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		struct	TxRxLowPacket	Pct;
		Pct.NowOnXByte	=1+sizeof(d);
		Pct.ErrorLevel		=ErrorCodeList::_None;

		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return(false);
		}
		if(Sock->write((const char *)&Cmd,1)!=1){
			return(false);
		}
		if(Sock->write((char *)&d,sizeof(d))!=sizeof(d)){
			return(false);
		}
		if(Sock->flush()==false){
			return false;
		}
		return(true);
	}
	return(false);
}

bool	TrSocketClient::TxData(BYTE Cmd ,bool d) const
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

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		struct	TxRxLowPacket	Pct;
		Pct.NowOnXByte	=1+sizeof(d);
		Pct.ErrorLevel		=ErrorCodeList::_None;

		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return(false);
		}
		if(Sock->write((const char *)&Cmd,1)!=1){
			return(false);
		}
		if(Sock->write((char *)&d,sizeof(d))!=sizeof(d)){
			return(false);
		}
		if(Sock->flush()==false){
			return false;
		}
		return(true);
	}
	return(false);
}

bool	TrSocketClient::TxData(BYTE Cmd,BYTE *buff ,int xbyte) const
{
	if(Sock!=NULL){
		/*
		if(IsConnected()==false){
			if(StartConnect()==false){
				return false;
			}
			if(IsConnected()==false){
				return false;
			}
		}
		Sock->waitForBytesWritten(5000);
		*/
		struct	TxRxLowPacket	Pct;
		Pct.NowOnXByte	=1+xbyte+sizeof(xbyte);
		Pct.ErrorLevel	=ErrorCodeList::_None;

		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return false;
		}
		if(Sock->write((const char *)&Cmd,1)!=1){
			return(false);
		}
		if(Sock->write((const char *)&xbyte,sizeof(xbyte))!=sizeof(xbyte)){
			return(false);
		}
		if(xbyte!=0){
			if(Sock->write((char *)buff,xbyte)!=xbyte){
				return(false);
			}
			//if(Sock->flush()==false){
			//	return false;
			//}
		}
		return(true);
	}
	return(false);
}

void	TrSocketClient::TxDataQueueStart(void)
{
	TxQueueBuff.RemoveAll();
}
void	TrSocketClient::TxDataQueuePush(BYTE *data ,int len)
{
	TxQueueBuff.AppendList(new TxList(len,data));
}
void	TrSocketClient::TxDataQueuePush(int32 data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}
void	TrSocketClient::TxDataQueuePush(WORD data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}
void	TrSocketClient::TxDataQueuePush(bool data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}

void	TrSocketClient::TxDataQueuePush(QBuffer *f)
{
	int32	rsize=f->size();
	TxQueueBuff.AppendList(new TxList(sizeof(rsize)	,(BYTE *)&rsize));
	TxQueueBuff.AppendList(new TxList(rsize			,(BYTE *)f->buffer().data()));
}
bool	TrSocketClient::TxDataQueueFlush(void)
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
		Pct.NowOnXByte	=XByte;
		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return(false);
		}
		if(XByte!=0){
			for(TxList *L=TxQueueBuff.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->Len!=0){
					if(Sock->write((char *)L->Data,L->Len)!=L->Len){
						return(false);
					}
				if(Sock->flush()==false)
					return false;
				}
			}
		}
		TxQueueBuff.RemoveAll();
		return(true);
	}
	TxQueueBuff.RemoveAll();
	return(false);

}

TrSocketClient::RecList	*TrSocketClient::UnpackTopRxBuff(void)
{
	MuteRecData.lock();
	RecList	*R=RecData.GetFirst();
	if(R!=NULL){
		RecData.RemoveList(R);
	}
	MuteRecData.unlock();
	return(R);
}

void	TrSocketClient::SlotConnected()
{
}
void	TrSocketClient::SlotDisconnected()
{
	if(cParent!=NULL){
		cParent->DisconnectClient(this);
	}
}

void	TrSocketClient::SlotReadyRead()
{
	DataIn=true;
	FastCommLeafRxReEntrant++;
	do{
		if(RxState==_NowOnWaiting || (RxState==_NowOnReceiving && (LastReceivingTime-time(NULL)>10))){
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
			if(OnRBuff!=NULL){
				delete	OnRBuff;
			}
			OnRBuff=new RecList(NowOnXByte);
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
			OnRBuff->Client=this;
			MuteRecData.lock();
			RecData.AppendList(OnRBuff);
			OnRBuff=NULL;
			MuteRecData.unlock();
			emit	SignalReceived(ID);
		}
	}while(Sock->bytesAvailable()!=0);
	FastCommLeafRxReEntrant--;
}

QString	TrSocketClient::GetPartnerIP(void) const
{
	return PeerIP;
}

//=======================================================================================================


TrSocketServer::TrSocketServer(QObject * parent)
:QObject(parent),Server(parent)
{
	TopID=0;
}

TrSocketServer::~TrSocketServer(void)
{
}


void	TrSocketServer::StartServer(int port)
{
	connect(&Server,SIGNAL(newConnection()),this, SLOT(SlotNewConnection()));
	Server.listen ( QHostAddress::Any, port );
}

int		TrSocketServer::GetTopID(void)
{
	return TopID++;
}

void	TrSocketServer::DisconnectClient(TrSocketClient *s)
{
	for(TrSocketClient *a=Leaf.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==s->GetID()){
			LeafAccessor.lock();
			Leaf.RemoveList(a);
			LeafAccessor.unlock();
			a->deleteLater();
		}
	}
	emit	DisconnectClient();
}

void	TrSocketServer::SlotNewConnection()
{
	TrSocketClient	*a=NewSocket();
	a->Set(this);
	LeafAccessor.lock();
	Leaf.AppendList(a);
	LeafAccessor.unlock();
	emit	ConnectClient();
}

TrSocketClient	*TrSocketServer::NewSocket(void)
{
	TrSocketClient	*a=new TrSocketClient();
	return a;
}
	
bool	TrSocketServer::TxAllData(BYTE *buff ,int xbyte)
{
	bool	Ret=true;
	for(TrSocketClient *a=Leaf.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsConnected()==true){
			if(a->TxData(buff,xbyte)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

bool	TrSocketServer::TxAllData(QBuffer *f)
{
	bool	Ret=true;
	for(TrSocketClient *a=Leaf.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsConnected()==true){
			if(a->TxData(f)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

bool	TrSocketServer::TxAllData(QByteArray *f)
{
	bool	Ret=true;
	for(TrSocketClient *a=Leaf.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsConnected()==true){
			if(a->TxData(f)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

//=======================================================================================================

