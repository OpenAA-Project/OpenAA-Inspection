#include "XSocketClient.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "swap.h"


SocketClient::RecList::RecList(int len)
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

SocketClient::RecList::~RecList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

BYTE	*SocketClient::RecList::GetPointer(BYTE *p ,int32 &ret)
{
	ret=*((int32 *)p);
	p+=sizeof(int32);
	return(p);
}
BYTE	*SocketClient::RecList::GetPointer(BYTE *p ,WORD &ret)
{
	ret=*((WORD *)p);
	p+=sizeof(WORD);
	return(p);
}
BYTE	*SocketClient::RecList::GetPointer(BYTE *p ,bool &ret)
{
	ret=*((bool *)p);
	p+=sizeof(bool);
	return(p);
}
BYTE	*SocketClient::RecList::GetPointer(BYTE *p ,BYTE *buff ,int buffByte)
{
	memcpy(buff,p,buffByte);
	p+=buffByte;
	return(p);
}

BYTE	*SocketClient::RecList::GetPointer(BYTE *p ,QBuffer &ret)
{
	int32	rsize=*((int32 *)p);
	p+=sizeof(int32);
	if(ret.isOpen()){
		ret.close();
	}
	ret.setData((const char *)p,rsize);
	return(p+rsize);
}

BYTE	*SocketClient::RecList::GetError(BYTE *fp,ErrorCodeList &ErrorData)
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

SocketClient::TxList::TxList(int len , BYTE *data)
{
	Len=len;
	Data=new BYTE[Len];
	memcpy(Data,data,Len);
}

SocketClient::TxList::~TxList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

//==================================================================================

SocketClient::SocketClient(void)
{
	ID=0;
	cParent=NULL;
	Servered=false;
	Sock=NULL;
	OnRBuff				=NULL;
	LastReceivingTime	=0;
	NowOnPoint			=0;
	RxState=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant=0;
	CreatedTime			=XDateTime::currentDateTime();
}

SocketClient::~SocketClient(void)
{
	if(Sock!=NULL){
		Sock->close();
		Sock->deleteLater();
	}
	Sock=NULL;
	cParent=NULL;
}

void	SocketClient::Set(QObject *parent ,const QString &ip ,int port)
{
	IP	=ip;
	Port=port;
	Sock=new QTcpSocket(parent);

	connect(Sock ,SIGNAL(connected())	,this ,SLOT(SlotConnected()));
	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));
}

void	SocketClient::Set(SocketServer *cparent)
{
	cParent=cparent;
	Sock	=cParent->GetServer().nextPendingConnection();
	Servered=true;	

	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));
	ID=cParent->GetTopID();
}


bool	SocketClient::StartConnect(void)
{
	if(Sock!=NULL){
		Sock->connectToHost (IP, Port);
		if(Sock->waitForConnected (10000)==false){
			return false;
		}
		if(Sock->open(QIODevice::ReadWrite | QIODevice::Unbuffered)==false){
			return false;
		}
		return(true);
	}
	return(false);
}

bool	SocketClient::IsConnected(void)
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			return(true);
		}
	}
	return(false);
}

void	SocketClient::WaitReadyRead(int milisec)
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			Sock->waitForReadyRead(milisec);
		}
	}
}

bool	SocketClient::TxData(BYTE *buff ,int xbyte)
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

bool	SocketClient::TxData(QBuffer *f)
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

bool	SocketClient::TxData(QByteArray *f)
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

void	SocketClient::TxDataQueueStart(void)
{
	TxQueueBuff.RemoveAll();
}
void	SocketClient::TxDataQueuePush(BYTE *data ,int len)
{
	TxQueueBuff.AppendList(new TxList(len,data));
}
void	SocketClient::TxDataQueuePush(int32 data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}
void	SocketClient::TxDataQueuePush(WORD data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}
void	SocketClient::TxDataQueuePush(bool data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}

void	SocketClient::TxDataQueuePush(QBuffer *f)
{
	int32	rsize=f->size();
	TxQueueBuff.AppendList(new TxList(sizeof(rsize)	,(BYTE *)&rsize));
	TxQueueBuff.AppendList(new TxList(rsize			,(BYTE *)f->buffer().data()));
}
bool	SocketClient::TxDataQueueFlush(void)
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

SocketClient::RecList	*SocketClient::UnpackTopRxBuff(void)
{
	MuteRecData.lock();
	RecList	*R=RecData.GetFirst();
	if(R!=NULL){
		RecData.RemoveList(R);
	}
	MuteRecData.unlock();
	return(R);
}

void	SocketClient::SlotConnected()
{
}
void	SocketClient::SlotDisconnected()
{
	if(cParent!=NULL){
		cParent->DisconnectClient(this);
	}
}

void	SocketClient::SlotReadyRead()
{
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


//=======================================================================================================


SocketServer::SocketServer(QObject * parent)
:QObject(parent),Server(parent)
{
	TopID=0;
}

SocketServer::~SocketServer(void)
{
}


void	SocketServer::StartServer(int port)
{
	connect(&Server,SIGNAL(newConnection()),this, SLOT(SlotNewConnection()));
	Server.listen ( QHostAddress::Any, port );
}

int		SocketServer::GetTopID(void)
{
	return TopID++;
}

void	SocketServer::DisconnectClient(SocketClient *s)
{
	for(SocketClient *a=Leaf.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==s->GetID()){
			LeafAccessor.lock();
			Leaf.RemoveList(a);
			LeafAccessor.unlock();
			a->deleteLater();
		}
	}
	emit	DisconnectClient();
}

void	SocketServer::SlotNewConnection()
{
	SocketClient	*a=NewSocket();
	a->Set(this);
	LeafAccessor.lock();
	Leaf.AppendList(a);
	LeafAccessor.unlock();
	emit	ConnectClient();
}

SocketClient	*SocketServer::NewSocket(void)
{
	SocketClient	*a=new SocketClient();
	return a;
}
	
bool	SocketServer::TxAllData(BYTE *buff ,int xbyte)
{
	bool	Ret=true;
	for(SocketClient *a=Leaf.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsConnected()==true){
			if(a->TxData(buff,xbyte)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

bool	SocketServer::TxAllData(QBuffer *f)
{
	bool	Ret=true;
	for(SocketClient *a=Leaf.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsConnected()==true){
			if(a->TxData(f)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

bool	SocketServer::TxAllData(QByteArray *f)
{
	bool	Ret=true;
	for(SocketClient *a=Leaf.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsConnected()==true){
			if(a->TxData(f)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

//=======================================================================================================

