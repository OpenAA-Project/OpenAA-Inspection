#include "XVirtualPIOCommon.h"
#include "swap.h"
#include <time.h>
#include <QThread>
#include <QApplication>
#include "XGeneralFunc.h"

RecList::RecList(int len)
{
	Len=len;
	if(Len!=0){
		Data=new BYTE[Len];
	}
	else{
		Data=NULL;
	}
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

//==================================================================================

PIOSocket::PIOSocket(QObject *parent ,const QString &_IPAddress,int _PortNumber)
{
	OnRBuff=NULL;
	LastReceivingTime=0;
	NowOnPoint		=0;
	RxState=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant=0;

	Sock=new QTcpSocket(parent);
	IPAddress	=_IPAddress;
	PortNumber	=_PortNumber;
	ConnectToHost();

	connect(Sock,SIGNAL(readyRead()),this,SLOT(ReadyRead()));
	connect(Sock,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
	connect(this,SIGNAL(SignalReceived(int)),this,SLOT(SlotReceived(int)),Qt::QueuedConnection);
}
PIOSocket::PIOSocket(QObject *parent ,QTcpSocket *sv)
	:QObject(parent),Sock(sv)
{
	OnRBuff=NULL;
	LastReceivingTime=0;
	NowOnPoint		=0;
	RxState=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant=0;

	connect(Sock,SIGNAL(readyRead()),this,SLOT(ReadyRead()));
	connect(Sock,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
	connect(this,SIGNAL(SignalReceived(int)),this,SLOT(SlotReceived(int)),Qt::QueuedConnection);
}

PIOSocket::~PIOSocket(void)
{
	if(Sock!=NULL){
		//Sock->close();
		//Sock->deleteLater();
		Sock=NULL;
	}
}

bool	PIOSocket::IsConnected(void)
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			return(true);
		}
	}
	return(false);
}
bool	PIOSocket::ConnectToHost(void)
{
	Sock->connectToHost(IPAddress,PortNumber);
	return Sock->waitForConnected(5000);
}

void	PIOSocket::WaitReadyRead(int milisec)
{
	if(Sock!=NULL){
		if(Sock->state()==QAbstractSocket::ConnectedState){
			if(qApp->thread()==QThread::currentThread()){
				Sock->waitForReadyRead(milisec);
			}
			else{
				GSleep(milisec);
			}
		}
	}
}


bool	PIOSocket::Send(int32 cmd ,QByteArray &Data)
{
	if(Sock!=NULL){
		Sock->waitForBytesWritten(5000);

		int32	Len=Data.size();

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}

		Pct.NowOnXByte	=Len+sizeof(Len);
		Pct.NowCmd			=cmd;

		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return(false);
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


void	PIOSocket::ReadyRead ()
{
	FastCommLeafRxReEntrant++;
	do{
		if(RxState==_NowOnWaiting || (RxState==_NowOnReceiving && (time(NULL)-LastReceivingTime>5))
		&& Sock->bytesAvailable()>0){
			int	NByte=sizeof(Pct)-LastPacketLoadedSize;
			int Len=Sock->read(((char *)&Pct)+LastPacketLoadedSize, NByte);
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
			emit	SignalReceived(NowCmd);
		}
	}while(Sock->bytesAvailable()!=0);
	FastCommLeafRxReEntrant--;
}

void	PIOSocket::SlotReceived(int Cmd)
{
	RecList	*r=RecData.GetFirst();
	if(r!=NULL){
		RecData.RemoveList(r);
		int32	ArrayByte;
		BYTE	*p=r->GetPointer(NULL,ArrayByte);
		QByteArray	Array((const char *)p,ArrayByte);
		Received(Cmd ,Array);
		delete	r;
	}
}

void	PIOSocket::SlotDisconnected()
{
	if(Sock!=NULL){
		//delete	Sock;
		Sock->deleteLater();
	}
	Sock=NULL;
}