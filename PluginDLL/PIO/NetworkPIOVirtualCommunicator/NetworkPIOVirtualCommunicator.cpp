#include "NetworkPIOVirtualCommunicator.h"
#include "NetworkPIOVirtual.h"
#include "NetworkPIOLib.h"

ThreadIOClass::ThreadIOClass(NetworkPIOVirtualCommunicator *p,QObject *parent)
	:QThread(parent),MemMap(/**/"NetworkPIOVirtual"),Parent(p)
{
	MemMap.create(sizeof(struct	NetworkPIOVirtualPacket));
	Pointer=(struct	NetworkPIOVirtualPacket *)MemMap.data();
	Terminated=false;
}

void	ThreadIOClass::run()
{
	while(Terminated==false){
		msleep(2);
		MemMap.lock();
		if(Pointer->Cmd==1){
			Parent->NetworkPIOClientInst->OutData[0]=Pointer->OutData[0];
			Parent->NetworkPIOClientInst->OutData[1]=Pointer->OutData[1];
			Parent->NetworkPIOClientInst->OutData[2]=Pointer->OutData[2];
			Parent->NetworkPIOClientInst->OutData[3]=Pointer->OutData[3];
			Pointer->Cmd=0;
			MemMap.unlock();
			emit	SignalTransfer();
		}
		else if(Pointer->Cmd==2){
			Pointer->InData[0]=Parent->NetworkPIOClientInst->InData[0];
			Pointer->InData[1]=Parent->NetworkPIOClientInst->InData[1];
			Pointer->InData[2]=Parent->NetworkPIOClientInst->InData[2];
			Pointer->InData[3]=Parent->NetworkPIOClientInst->InData[3];
			Pointer->Cmd=0;
			MemMap.unlock();
			emit	SignalRequest();
		}
		else{
			MemMap.unlock();
		}
	}
}

//=============================================================================
NetworkPIOClient::NetworkPIOClient(QObject *parent)
:QTcpSocket(parent)
{
	QWidget	*p=dynamic_cast<QWidget *>(parent);
	connect(this,SIGNAL(readyRead()),this,SLOT(ReadyRead()));
	connect(this,SIGNAL(readyRead()),this,SLOT(ReadyRead()));

	for(int i=0;i<sizeof(InData)/sizeof(InData[0]);i++){
		InData[i]=0;
	}
	for(int i=0;i<sizeof(OutData)/sizeof(OutData[0]);i++){
		OutData[i]=0;
	}
	WaitToReceive	=false;
	InNumb=0;
	OutNumb=0;
	setSocketOption(QAbstractSocket::LowDelayOption,1);
}

NetworkPIOClient::~NetworkPIOClient()
{
}

void	NetworkPIOClient::Initial(int _ID ,const QString &Address,int port ,int _InNumb ,int _OutNumb)
{
	ID		=_ID;
	IPAddress=Address;
	Port	=port;
	InNumb	=_InNumb;
	OutNumb	=_OutNumb;

	OpenSocket();
}
void	NetworkPIOClient::Initial(const QString &Something)
{
	QStringList	List=Something.split(',');
	if(List.count()>=1)
		ID		=List[0].toInt();
	if(List.count()>=2)
		IPAddress=List[1];
	if(List.count()>=3)
		Port	=List[2].toInt();
	if(List.count()>=4)
		InNumb=List[3].toInt();
	if(List.count()>=5)
		OutNumb=List[4].toInt();

	OpenSocket();
}

bool	NetworkPIOClient::OpenSocket(void)
{
	if(state()!=QAbstractSocket::ConnectedState){
		AccessMutex.lock();
		connectToHost (IPAddress, Port, QIODevice::ReadWrite );
		waitForConnected(2000);
		AccessMutex.unlock();
		if(state()==QAbstractSocket::ConnectedState){
			ReqData(false);
			return true;
		}
	}
	else{
		return true;
	}
	return false;
}

void NetworkPIOClient::ReadyRead()
{
	AccessMutex.lock();
	int	N=bytesAvailable();
	while(N!=0){
		struct	CommandNetworkPIO	RCmd;
		int	RByte=read((char *)&RCmd,sizeof(RCmd));
		if(RByte==sizeof(RCmd)){
			if(RCmd.Cmd==1){
				for(int i=0;i<4;i++){
					InData	[i]=RCmd.InData[i];
				}
			}
			else if(RCmd.Cmd==2){
				for(int i=0;i<4;i++){
					InData	[i]=RCmd.InData[i];
					OutData	[i]=RCmd.OutData[i];
				}
			}
			WaitToReceive=false;
		}
		N-=RByte;
	}
	AccessMutex.unlock();
}

void	NetworkPIOClient::ReqData(bool SendOutData)
{
	if(WaitToReceive==true){
		return;
	}
	struct	CommandNetworkPIO	RCmd;
	RCmd.ID=ID;
	RCmd.InNumb	=InNumb;
	RCmd.OutNumb=OutNumb;

	if(SendOutData==true){
		RCmd.Cmd	=1;
		for(int i=0;i<4;i++){
			RCmd.OutData[i]=OutData[i];
		}
	}
	else{
		RCmd.Cmd	=2;
	}
	AccessMutex.lock();
	if(OpenSocket()==true){
		WaitToReceive=true;
		if(write((const char *)&RCmd,sizeof(RCmd))==sizeof(RCmd)){
			flush();
		}
	}
	AccessMutex.unlock();
}
//=============================================================================
NetworkPIOVirtualCommunicator::NetworkPIOVirtualCommunicator(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	NetworkPIOClientInst=new NetworkPIOClient(this);

	ThreadIOInst=new ThreadIOClass(this,this);
	connect(ThreadIOInst,SIGNAL(SignalTransfer()),this,SLOT(SlotTransfer()),Qt::QueuedConnection);
	connect(ThreadIOInst,SIGNAL(SignalRequest()) ,this,SLOT(SlotRequest()) ,Qt::QueuedConnection);
	ThreadIOInst->start();
}

NetworkPIOVirtualCommunicator::~NetworkPIOVirtualCommunicator()
{
	ThreadIOInst->Terminated=true;
	ThreadIOInst->wait(1000);
}

void	NetworkPIOVirtualCommunicator::Initial(int _ID ,const QString &Address,int port ,int _InNumb ,int _OutNumb)
{
	NetworkPIOClientInst->Initial(_ID ,Address,port ,_InNumb ,_OutNumb);
}

void	NetworkPIOVirtualCommunicator::SlotTransfer()
{
	NetworkPIOClientInst->ReqData(true);
}

void	NetworkPIOVirtualCommunicator::SlotRequest()
{
	NetworkPIOClientInst->ReqData(false);
}