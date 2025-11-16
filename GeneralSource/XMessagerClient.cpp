#include "XMessagerClient.h"
#include "XDataInLayer.h"
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
}

RecList::~RecList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

BYTE	*RecList::GetPointer(BYTE *p ,QByteArray &ret)
{
	if(p==NULL){
		p=Data;
	}
	QBuffer	Buff;
	Buff.setData((const char *)p,Len);
	Buff.open(QIODevice::ReadOnly);
	ret=Buff.readAll();
	p+=ret.size();
	return(p);
}

MessagerClient::MessagerClient(QObject * parent)
{
	ThreadMessage=new ThreadMessageList(parent);
	connect(ThreadMessage,SIGNAL(SignalReceived()),this,SLOT(SlotReceived()));
}

MessagerClient::~MessagerClient(void)
{
	Close();
}
void	MessagerClient::Close(void)
{
	if(ThreadMessage!=NULL && ThreadMessage->isFinished()==false){
		ThreadMessage->CloseMode=true;
		//ThreadMessage->terminate();
		ThreadMessage->wait(1000);
		ThreadMessage->deleteLater();
		ThreadMessage=NULL;
	}
}
void	MessagerClient::Start(void)
{
	if(ThreadMessage!=NULL){
		ThreadMessage->start();
	}
}

bool	MessagerClient::Initial(const QString &_IPAddress,int _Port)
{
	if(ThreadMessage!=NULL){
		if(ThreadMessage->Initial(_IPAddress,_Port)==false){
			return false;
		}
	}

	return true;
}

bool	MessagerClient::Send(int MType,int GlobalPage,const QString &Message)
{
	if(ThreadMessage!=NULL){
		ThreadMessage->Send(MType,GlobalPage,Message);
		return true;
	}
	return false;
}

bool	MessagerClient::Send(int MType,QByteArray &Data)
{
	if(ThreadMessage!=NULL){
		ThreadMessage->Send(MType,Data);
		return true;
	}
	return false;
}

void	MessagerClient::SlotReceived()
{
	if(ThreadMessage!=NULL){
		RecList	*r=ThreadMessage->UnpackTopRxBuff();
		if(r!=NULL){
			BYTE	*p=r->GetPointer();
			r->GetPointer(p,ReceivedData);
			emit	SignalReceived();
			delete	r;
		}
	}
}
//----------------------------------------------------------------------
ThreadMessageList::ThreadMessageList(QObject *parent)
:QThread(parent),Socket(parent)
{
	CloseMode=false;
	LastReceivingTime=0;
	NowOnPoint		=0;
	RxState=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant=0;
	PctLen			=0;
	LastPacketLoadedSize	=0;
	OnRBuff			=NULL;
}

ThreadMessageList::~ThreadMessageList(void)
{
	Socket.disconnectFromHost ();
	if(Socket.state() == QAbstractSocket::UnconnectedState || Socket.waitForDisconnected(1000)){
		qDebug("Disconnected!");
	}
}

bool	ThreadMessageList::Initial(const QString &_IPAddress,int _Port)
{
	IPAddress	=_IPAddress;
	Port		=_Port;

	Socket.connectToHost (IPAddress, Port);
	if(Socket.waitForConnected (5000)==false){
		return false;
	}
	if(Socket.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Unbuffered)==false){
		return false;
	}
	connect(&Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()),Qt::QueuedConnection);
	return true;
}

void ThreadMessageList::run()
{
	for(;;){
		MutexMessageList.lock();
		MessageList	*r=MessageListContainer.GetFirst();
		MutexMessageList.unlock();

		if(r!=NULL){
			if(Socket.state()!=QAbstractSocket::ConnectedState){
				if(Initial(IPAddress,Port)==false){
					goto	ReTry;
				}
			}
			if(Socket.isTextModeEnabled()==true){
				Socket.setTextModeEnabled(false);
			}
			QBuffer	SBuff;
			SBuff.open(QIODevice::WriteOnly);
			
			if(r!=NULL){
				::Save(&SBuff,r->MType);
				::Save(&SBuff,r->GlobalPage);
				::Save(&SBuff,r->Message);
				::Save(&SBuff,r->ArrayData);

				int32	Len=SBuff.buffer().size();
				if(Socket.write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
					goto	ReTry;
				}
				if(Socket.write(SBuff.buffer())<=0){
					goto	ReTry;
				}
			}

			Socket.flush();
			if(r!=NULL){
				MutexMessageList.lock();
				MessageListContainer.RemoveList(r);
				delete	r;
				MutexMessageList.unlock();
			}
		}
ReTry:
		//if(GetLayersBase()->GetOnTerminating()==true){
		//	return;
		//}
		msleep(100);
		if(CloseMode==true){
			break;
		}
	}
}

void	ThreadMessageList::SlotReadyRead()
{
	FastCommLeafRxReEntrant++;
	do{
		if(RxState==_NowOnWaiting || (RxState==_NowOnReceiving && (time(NULL)-LastReceivingTime>5))){
			int Len=Socket.read(((char *)&PctLen)+LastPacketLoadedSize, sizeof(PctLen)-LastPacketLoadedSize);
			if(Len<0){
				FastCommLeafRxReEntrant--;
				return;
			}
			if(Len+LastPacketLoadedSize!=sizeof(PctLen)){
				LastPacketLoadedSize+=Len;
				FastCommLeafRxReEntrant--;
				return;
			}
			LastPacketLoadedSize=0;
			NowOnXByte	=PctLen	;

			if(OnRBuff!=NULL){
				delete	OnRBuff;
			}
			OnRBuff=new RecList(NowOnXByte);
			NowOnPoint=0;
		
			int	N=Socket.bytesAvailable();
			if(N!=0){
				if(NowOnXByte>=N){
					Len=Socket.read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
					if(Len<0){
						FastCommLeafRxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
				else if(NowOnXByte!=0){
					Len=Socket.read((char *)(OnRBuff->GetPointer()+NowOnPoint), NowOnXByte);
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
			int	N=Socket.bytesAvailable();
			int	RByte=min(OnRBuff->Len-NowOnPoint,N);
			int	Len=Socket.read((char *)(OnRBuff->GetPointer()+NowOnPoint),RByte);
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
			emit	SignalReceived();
		}
	}while(Socket.bytesAvailable()!=0);
	FastCommLeafRxReEntrant--;
}

void	ThreadMessageList::Send(int MType,int GlobalPage,const QString &Message)
{
	MutexMessageList.lock();
	MessageListContainer.AppendList(new MessageList(MType,GlobalPage,Message));
	MutexMessageList.unlock();
}

bool	ThreadMessageList::Send(int MType,QByteArray &Data)
{
	MutexMessageList.lock();
	MessageListContainer.AppendList(new MessageList(MType,Data));
	MutexMessageList.unlock();
	return true;
}

RecList	*ThreadMessageList::UnpackTopRxBuff(void)
{
	MuteRecData.lock();
	RecList	*R=RecData.GetFirst();
	if(R!=NULL){
		RecData.RemoveList(R);
	}
	MuteRecData.unlock();
	return(R);
}

int		ThreadMessageList::GetQueuedCount(void)
{
	MuteRecData.lock();
	int	Ret=RecData.GetCount();
	MuteRecData.unlock();
	return(Ret);
}
