#include "NetworkSIOClientLib.h"
#include <QThread>

class	TmpThread : public QThread
{
public:
	void run (){}

	static	void	TmpGSleep(unsigned int milisec){	msleep(milisec);	}
};


void	GSleep(unsigned int milisec)
{
	TmpThread::TmpGSleep(milisec);
}


SocketInClient::SocketInClient(NetworkSIOClientLib *parent ,const QString &_IPAddress,int _PortNumber)
	:SoESocket(parent,_IPAddress,_PortNumber)
	,Parent(parent)
{
	RxCmd=CmdComm_None;
}
	
void	SocketInClient::Clear(void)
{
	RxCmd=CmdComm_None;
	RxData.clear();
}
void	SocketInClient::Received(int cmd ,QByteArray &data)
{
	RxData	=data;
	RxCmd	=cmd;
}
void	SocketInClient::SlotDisconnected()
{
	SoESocket::SlotDisconnected();
	deleteLater();
}

//--------------------------------------------------------------------------------
	
NetworkSIOClientLib::NetworkSIOClientLib(QObject *parent)
	:QObject(parent)
{
	Client=NULL;
}
	
NetworkSIOClientLib::~NetworkSIOClientLib()
{
	if(Client!=NULL){
		delete	Client;
		Client=NULL;
	}
}

	
bool	NetworkSIOClientLib::StartConnection(const QString &IPAddress ,int PortNumber)
{
	if(Client!=NULL){
		delete	Client;
	}
	Client=new SocketInClient(this,IPAddress ,PortNumber);
	return Client->ConnectToHost();
}

	
bool	NetworkSIOClientLib::OpenPort(int BaudRate ,int Character ,int Parity ,int StopBit)
{
	struct	CommOpenInfo	Data;
	Data.BaudRate	=BaudRate;
	Data.Character	=Character;
	Data.Parity		=Parity;
	Data.StopBit	=StopBit;

	QBuffer	Buff;
	Buff.open(QIODevice::WriteOnly);
	Buff.write((const char *)&Data,sizeof(Data));
	if(Client==NULL || Client->IsConnected()==false)
		return false;
	Client->RxData.clear();
	bool	Ret=Client->Send(CmdComm_Open ,Buff.buffer());
	if(Ret==false)
		return false;
	while(Client->RxCmd==CmdComm_None){
		Client->WaitReadyRead(1);
	}
	if(Client->RxCmd==CmdComm_Ack_OK)
		return true;
	else
		return false;
}
	
bool	NetworkSIOClientLib::SendData(char *fp ,int Len)
{
	QByteArray	Array(fp,Len);

	if(Client==NULL || Client->IsConnected()==false)
		return false;
	Client->RxData.clear();
	bool	Ret=Client->Send(CmdComm_Tx,Array);
	if(Ret==false)
		return false;
	while(Client->RxCmd==CmdComm_None){
		Client->WaitReadyRead(1);
	}
	if(Client->RxCmd==CmdComm_Ack_OK)
		return true;
	else
		return false;
}
	
bool	NetworkSIOClientLib::GetReceivedByte(int &RxLen)
{
	QByteArray	Array;

	if(Client==NULL || Client->IsConnected()==false)
		return false;
	Client->RxData.clear();
	bool	Ret=Client->Send(CmdComm_RxByte,Array);
	if(Ret==false)
		return false;
	while(Client->RxCmd==CmdComm_None){
		Client->WaitReadyRead(1);
	}
	if(Client->RxCmd==CmdComm_Ack_RxByte){
		int	Count=Client->RxData.count();
		char	*fp=Client->RxData.data();
		if(Count>=sizeof(int32)){
			RxLen=*((int32 *)fp);
			return true;
		}
	}
	return false;
}
	
bool	NetworkSIOClientLib::ReceiveData(char *fp ,int &RxLen ,int MaxLen)
{
	QByteArray	Array((char *)&MaxLen,sizeof(MaxLen));

	if(Client==NULL || Client->IsConnected()==false)
		return false;
	Client->RxData.clear();
	bool	Ret=Client->Send(CmdComm_Rx,Array);
	if(Ret==false)
		return false;
	while(Client->RxCmd==CmdComm_None){
		Client->WaitReadyRead(1);
	}
	if(Client->RxCmd==CmdComm_Ack_Received){
		RxLen=Client->RxData.count();
		memcpy(fp,Client->RxData.data(),RxLen);
		return true;
	}
	return false;
}