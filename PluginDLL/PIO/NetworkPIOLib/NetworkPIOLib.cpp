#include "NetworkPIOLib.h"
#include "XPointer.h"
#include "XIntClass.h"

NetworkPIOServerSocket::NetworkPIOServerSocket(QTcpSocket *sock ,NetworkPIOServer *S ,QObject *parent)
	:QObject(parent)
{
	Server	=S;
	Sock	=sock;

	ID		=0;
	InNumb	=0;
	OutNumb	=0;

	for(int i=0;i<sizeof(InData)/sizeof(InData[0]);i++){
		InData[i]=0;
	}
	for(int i=0;i<sizeof(OutData)/sizeof(OutData[0]);i++){
		OutData[i]=0;
	}

	connect(Sock,SIGNAL(readyRead()),this,SLOT(ReadyRead()));
	connect(Sock,SIGNAL(disconnected()),this,SLOT(SlotDisConnected()));
	ErrorCount	=0;
}
NetworkPIOServerSocket::~NetworkPIOServerSocket()
{
}

bool	NetworkPIOServerSocket::IsConnected(void)
{
	if(Sock->state()==QAbstractSocket::ConnectedState){
		return true;
	}
	return false;
}

void	NetworkPIOServerSocket::ReadyRead()
{
	int	N=Sock->bytesAvailable();
	struct	CommandNetworkPIO	RCmd;
	bool	WFlag=false;
	while(N!=0){
		struct	CommandNetworkPIO	tmpRCmd;
		int	RByte=Sock->read((char *)&tmpRCmd,sizeof(tmpRCmd));
		if(RByte==sizeof(tmpRCmd)){
			RCmd	=tmpRCmd;
			ID		=RCmd.ID;
			OutNumb	=RCmd.InNumb;
			InNumb	=RCmd.OutNumb;

			if(RCmd.Cmd==1){
				for(int i=0;i<4;i++){
					InData	[i]=RCmd.OutData[i];
				}
			}
			for(int i=0;i<4;i++){
				RCmd.InData	[i]=OutData[i];
				RCmd.OutData[i]=InData[i];
			}
			WFlag=true;
		}
		N-=RByte;
		if(N!=0){
			ErrorCount++;
		}
	}
	if(WFlag==true){
		Sock->write((const char *)&RCmd,sizeof(RCmd));
		Sock->flush();
	}
}
void	NetworkPIOServerSocket::SlotDisConnected()
{
	for(NetworkPIOServerSocket *s=Server->GetFirst();s!=NULL;s=s->GetNext()){
		if(s==this){
			Server->RemoveList(s);
			s->deleteLater();
			return;
		}
	}
}


NetworkPIOServer::NetworkPIOServer(QObject *Obj)
	:QTcpServer(Obj)
{
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}

void	NetworkPIOServer::Start(int PortNumber)
{
	listen(QHostAddress::Any,PortNumber);
}
bool	NetworkPIOServer::OutByte(int id ,int port ,BYTE data)
{
	for(NetworkPIOServerSocket *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->IsConnected()==true && s->ID==id){
			if(0<=port && port<(s->OutNumb+7)/8){
				s->OutData[port]=data;
			}
			return true;
		}
	}
	return false;
}
bool	NetworkPIOServer::InByte(int id ,int port,BYTE &data)
{
	for(NetworkPIOServerSocket *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->IsConnected()==true && s->ID==id){
			if(0<=port && port<(s->InNumb+7)/8){
				data=s->InData[port];
				return true;
			}
		}
	}
	return false;
}
bool	NetworkPIOServer::OutBit(int id ,int BitIndex ,BYTE data)
{
	for(NetworkPIOServerSocket *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->IsConnected()==true && s->ID==id && 0<=BitIndex && BitIndex<s->OutNumb){
			if(data==0)
				SetBitOnDim0(s->OutData,BitIndex);
			else
				SetBitOnDim1(s->OutData,BitIndex);
			return true;
		}
	}
	return false;
}
bool	NetworkPIOServer::InBit(int id ,int BitIndex,BYTE &data)
{
	for(NetworkPIOServerSocket *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->IsConnected()==true && s->ID==id && 0<=BitIndex && BitIndex<s->InNumb){
			if(GetBitOnDim(s->InData,BitIndex)==0)
				data=0;
			else
				data=1;
			return true;
		}
	}
	return false;
}
bool	NetworkPIOServer::GetOutByte(int id ,int port,BYTE &data)
{
	for(NetworkPIOServerSocket *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->IsConnected()==true && s->ID==id){
			if(0<=port && port<(s->OutNumb+7)/8){
				data=s->OutData[port];
				return true;
			}
		}
	}
	return false;
}
bool	NetworkPIOServer::GetOutBit(int id ,int BitIndex,BYTE &data)
{
	for(NetworkPIOServerSocket *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->IsConnected()==true && s->ID==id && 0<=BitIndex && BitIndex<s->OutNumb){
			if(GetBitOnDim(s->OutData,BitIndex)==0)
				data=0;
			else
				data=1;
			return true;
		}
	}
	return false;
}
void	NetworkPIOServer::GetClientIDList(IntList &IDList)
{
	for(NetworkPIOServerSocket *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(IDList.IsInclude(s->ID)==false){
			IDList.Add(s->ID);
		}
	}
}
int		NetworkPIOServer::GetClientCount(void)
{
	IntList	List;
	for(NetworkPIOServerSocket *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(List.IsInclude(s->ID)==false){
			List.Add(s->ID);
		}
	}
	return List.GetCount();
}
	
int		NetworkPIOServer::GetIOInBitCount (int ID)
{
	for(NetworkPIOServerSocket *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(ID==s->ID){
			return s->InNumb;
		}
	}
	return 0;
}
int		NetworkPIOServer::GetIOOutBitCount(int ID)
{
	for(NetworkPIOServerSocket *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(ID==s->ID){
			return s->OutNumb;
		}
	}
	return 0;
}

void NetworkPIOServer::SlotNewConnection ()
{
	QTcpSocket *sock= nextPendingConnection ();
	NetworkPIOServerSocket	*s=new NetworkPIOServerSocket(sock,this ,this);
	AppendList(s);
}