#include "XGeneralSocket.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "swap.h"


RecList::RecList(int len)
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

RecList::~RecList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

BYTE	*RecList::GetPointer(BYTE *p ,int32 &ret)
{
	if(p==NULL){
		p=GetPointer();
	}
	ret=*((int32 *)p);
	p+=sizeof(int32);
	return(p);
}
BYTE	*RecList::GetPointer(BYTE *p ,WORD &ret)
{
	if(p==NULL){
		p=GetPointer();
	}
	ret=*((WORD *)p);
	p+=sizeof(WORD);
	return(p);
}
BYTE	*RecList::GetPointer(BYTE *p ,bool &ret)
{
	if(p==NULL){
		p=GetPointer();
	}
	ret=*((bool *)p);
	p+=sizeof(bool);
	return(p);
}
BYTE	*RecList::GetPointer(BYTE *p ,BYTE *buff ,int buffByte)
{
	if(p==NULL){
		p=GetPointer();
	}
	memcpy(buff,p,buffByte);
	p+=buffByte;
	return(p);
}

BYTE	*RecList::GetPointer(BYTE *p ,QBuffer &ret)
{
	if(p==NULL){
		p=GetPointer();
	}
	int32	rsize=*((int32 *)p);
	p+=sizeof(int32);
	if(ret.isOpen()){
		ret.close();
	}
	ret.setData((const char *)p,rsize);
	return(p+rsize);
}


BYTE	*RecList::GetPointer(BYTE *p ,QByteArray &ret)
{
	if(p==NULL){
		p=GetPointer();
	}
	int32	rsize=*((int32 *)p);
	p+=sizeof(int32);
	//ret= QByteArray::fromRawData ((const char *)p,rsize);
	QByteArray S=QByteArray::fromRawData ((const char *)p,rsize);
	ret=S;
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

GeneralSocketClient::GeneralSocketClient(QObject *parent)
:QObject(parent)
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
	PacketCounter		=0;
}

GeneralSocketClient::~GeneralSocketClient(void)
{
	if(Sock!=NULL){
		Sock->close();
		Sock->deleteLater();
	}
	Sock=NULL;
	cParent=NULL;
}

void	GeneralSocketClient::Set(QObject *parent ,const QString &ip ,int port)
{
	IP	=ip;
	Port=port;
	Sock=new QTcpSocket(parent);

	connect(Sock ,SIGNAL(connected())	,this ,SLOT(SlotConnected()));
	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));
}


void	GeneralSocketClient::Set(GeneralSocketServer *cparent)
{
	cParent=cparent;
	Sock	=cParent->GetServer().nextPendingConnection();
	Servered=true;	

	connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
	connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));
	ID=cParent->GetTopID();
}


bool	GeneralSocketClient::StartConnect(QObject *parent ,const QString &ip ,int port)
{
	IP	=ip;
	Port=port;
	if(Sock==NULL){
		Sock=new QTcpSocket(parent);

		connect(Sock ,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
		connect(Sock ,SIGNAL(readyRead())	,this ,SLOT(SlotReadyRead()));
	}

	Sock->connectToHost (IP, Port);
	if(Sock->waitForConnected (50000)==false){
		Error=Sock->error ();
		return false;
	}
	if(Sock->open(QIODevice::ReadWrite | QIODevice::Unbuffered)==false){
		return false;
	}
	return(true);
}

bool	GeneralSocketClient::DisconnectFromHost(void)
{
	if(IsConnected()==true){
		Sock->disconnectFromHost();
	}
	return true;
}

bool	GeneralSocketClient::IsConnected(void)
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			return(true);
		}
	}
	return(false);
}

void	GeneralSocketClient::WaitReadyRead(int milisec)
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			Sock->waitForReadyRead(milisec);
		}
	}
}

bool	GeneralSocketClient::TxData(BYTE *buff ,int xbyte)
{
	ErrorCodeList ErrorData;
	return TxData(buff ,xbyte,ErrorData);
}

bool	GeneralSocketClient::TxData(QBuffer *f)
{
	ErrorCodeList ErrorData;
	return TxData(f,ErrorData);
}

bool	GeneralSocketClient::TxData(QByteArray *f)
{
	ErrorCodeList ErrorData;
	return TxData(f,ErrorData);
}

bool	GeneralSocketClient::TxData(BYTE *buff ,int xbyte
								,ErrorCodeList &ErrorData)
{
	if(Sock!=NULL){
		if(IsConnected()==false){
			return false;
		}
		Sock->waitForBytesWritten(5000);

		struct	TxRxLowPacket	Pct;
		Pct.NowOnXByte	=xbyte;
		Pct.ErrorLevel	=(BYTE)ErrorData.GetLevel();

		char	ErrorMessage[1000];
		char	ETime[30];
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			Pct.ErrorCode	=ErrorData.GetErrorCode();
			QString2Char(ErrorData.GetMessage() ,ErrorMessage,sizeof(ErrorMessage));
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
			if(Sock->flush()==false){
				return false;
			}
		}
		return(true);
	}
	return(false);
}

bool	GeneralSocketClient::TxData(QBuffer *f
								,ErrorCodeList &ErrorData)
{
	if(Sock!=NULL){
		if(IsConnected()==false){
			return false;
		}
		Sock->waitForBytesWritten(5000);

		int32	Len=f->size();

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		struct	TxRxLowPacket	Pct;

		Pct.NowOnXByte	=Len+sizeof(Len);
		Pct.ErrorLevel		=(BYTE)ErrorData.GetLevel();
		char	ErrorMessage[1000];
		char	ETime[30];
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			Pct.ErrorCode	=ErrorData.GetErrorCode();
			QString2Char(ErrorData.GetMessage() ,ErrorMessage,sizeof(ErrorMessage));
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

bool	GeneralSocketClient::TxData(QByteArray *f
								,ErrorCodeList &ErrorData)
{
	if(Sock!=NULL){
		if(IsConnected()==false){
			return false;
		}
		Sock->waitForBytesWritten(5000);

		int32	Len=f->size();

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}
		struct	TxRxLowPacket	Pct;
		Pct.NowOnXByte	=Len
						+sizeof(Len);
		Pct.ErrorLevel		=(BYTE)ErrorData.GetLevel();
		char	ErrorMessage[1000];
		char	ETime[30];
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			Pct.ErrorCode	=ErrorData.GetErrorCode();
			QString2Char(ErrorData.GetMessage() ,ErrorMessage,sizeof(ErrorMessage));
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

void	GeneralSocketClient::TxDataQueueStart(void)
{
	TxQueueBuff.RemoveAll();
}
void	GeneralSocketClient::TxDataQueuePush(BYTE *data ,int len)
{
	TxQueueBuff.AppendList(new TxList(len,data));
}
void	GeneralSocketClient::TxDataQueuePush(int32 data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}
void	GeneralSocketClient::TxDataQueuePush(WORD data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}
void	GeneralSocketClient::TxDataQueuePush(bool data)
{
	TxQueueBuff.AppendList(new TxList(sizeof(data),(BYTE *)&data));
}

void	GeneralSocketClient::TxDataQueuePush(QBuffer *f)
{
	int32	rsize=f->size();
	TxQueueBuff.AppendList(new TxList(sizeof(rsize)	,(BYTE *)&rsize));
	TxQueueBuff.AppendList(new TxList(rsize			,(BYTE *)f->buffer().data()));
}
bool	GeneralSocketClient::TxDataQueueFlush(void)
{
	int	XByte=0;
	for(TxList *L=TxQueueBuff.GetFirst();L!=NULL;L=L->GetNext()){
		XByte+=L->Len;
	}
	if(Sock!=NULL){
		if(IsConnected()==false){
			return false;
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

RecList	*GeneralSocketClient::UnpackTopRxBuff(void)
{
	MuteRecData.lock();
	RecList	*R=RecData.GetFirst();
	if(R!=NULL){
		RecData.RemoveList(R);
	}
	MuteRecData.unlock();
	return(R);
}

void	GeneralSocketClient::SlotConnected()
{
}
void	GeneralSocketClient::SlotDisconnected()
{
	if(cParent!=NULL){
		cParent->DisconnectClient(this);
	}
}


RecList	*GeneralSocketClient::WaitForRead(DWORD timeout)
{
	int LastPacketCounter=PacketCounter;
	for(;;){
		Sock->waitForReadyRead(timeout);
		//Sock->waitForReadyRead(100);
		RecList	*R=UnpackTopRxBuff();
		if(R!=NULL){
			return R;
		}
		if(LastPacketCounter==PacketCounter){
			return NULL;
		}
		LastPacketCounter=PacketCounter;
	}
}


void	GeneralSocketClient::SlotReadyRead()
{
	PacketCounter++;
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
			if(OnRBuff->Data!=NULL){
				MuteRecData.lock();
				RecData.AppendList(OnRBuff);
				OnRBuff=NULL;
				MuteRecData.unlock();
				emit	SignalReceived(ID);
			}
			else{
				delete	OnRBuff;
				OnRBuff=NULL;
			}
		}
	}while(Sock->bytesAvailable()!=0);
	FastCommLeafRxReEntrant--;
}


//=======================================================================================================


GeneralSocketServer::GeneralSocketServer(QObject * parent)
:QObject(parent)
{
	TopID=0;
}

GeneralSocketServer::~GeneralSocketServer(void)
{
}


bool	GeneralSocketServer::StartServer(int port)
{
	connect(&Server,SIGNAL(newConnection()),this, SLOT(SlotNewConnection()));
	if(Server.listen ( QHostAddress::Any, port )==false){
		return false;
	}
	return true;
}

int		GeneralSocketServer::GetTopID(void)
{
	return TopID++;
}

void	GeneralSocketServer::DisconnectClient(GeneralSocketClient *s)
{
	for(GeneralSocketClient *a=Leaf.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==s->GetID()){
			LeafAccessor.lock();
			Leaf.RemoveList(a);
			LeafAccessor.unlock();
			a->deleteLater();
		}
	}
	emit	DisconnectClient();
}

void	GeneralSocketServer::SlotNewConnection()
{
	GeneralSocketClient	*a=NewSocket();
	a->Set(this);
	LeafAccessor.lock();
	Leaf.AppendList(a);
	LeafAccessor.unlock();
	emit	ConnectClient();
}

GeneralSocketClient	*GeneralSocketServer::NewSocket(void)
{
	GeneralSocketClient	*a=new GeneralSocketClient();
	return a;
}


//=======================================================================================================

