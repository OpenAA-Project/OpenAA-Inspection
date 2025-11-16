#include "PIODevicer.h"
#include "NetworkPIO.h"
#include "windows.h"
#include "CDio.h"


ClientSocket::ClientSocket(PIODevicer *parent)
:Parent(parent)
{
	Client=NULL;
}

void	ClientSocket::SetClient(QTcpSocket *client)
{	
	Client=client;	
	connect(Client,SIGNAL(readyRead()),this,SLOT(ReadyRead()));
}

void	ClientSocket::ReadyRead()
{
	int	N;
	do{
		N=Client->bytesAvailable();
		if(N!=0){
			char	buff[10000];
			if(N>=10000){
				N=10000;
			}
			Client->read(buff,N);
			Parent->OutPort((BYTE *)buff);
		}
	}while(N!=0);
}

void	ClientSocket::Disconnected()
{
	Parent->DeleteClient(this);
}

bool	ClientSocket::Send(BYTE *data,int len)
{
	if(Client->write((const char *)data,len)==len){
		Client->flush();
		return true;
	}
	return false;
}



//==============================================================


PIODevicer::PIODevicer(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	CameNew=false;
	for(int i=0;i<sizeof(Client)/sizeof(Client[0]);i++){
		Client[i]=NULL;
	}

	Server.setParent(this);
	connect(&Server,SIGNAL(newConnection()),this,SLOT(NewConnection()));
	Server.listen(QHostAddress::Any,NetworkPIOPort);

	TM.setInterval(1);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(TimeOut()));
	TM.start();

	char DeviceName[256];
	char Device[256];
	for(int i=0;i<256;i++){
		long	Ret = DioQueryDeviceName ( i , DeviceName , Device );
		if(Ret==DIO_ERR_SUCCESS){
			Ret = DioInit ( DeviceName , &BoardId );
			if(Ret == 0){
				break;
			}
		}
	}

	if(strcmp(PIO_NAME,"IOLIB_PIO16")==0){
		InportBitCount=16;
		OutportBitCount=16;
	}
	else if(strcmp(PIO_NAME,"IOLIB_PIO32")==0){
		InportBitCount=32;
		OutportBitCount=32;
	}
	else if(strcmp(PIO_NAME,"IOLIB_PIO64")==0){
		InportBitCount=64;
		OutportBitCount=64;
	}
}

PIODevicer::~PIODevicer()
{

}

void PIODevicer::NewConnection ()
{
	for(int i=0;i<sizeof(Client)/sizeof(Client[0]);i++){
		if(Client[i]==NULL){
			ClientSocket	*c=new ClientSocket(this);
			c->SetClient(Server.nextPendingConnection ());
			Client[i]=c;
			CameNew=true;
			break;
		}
	}
}

void	PIODevicer::DeleteClient(ClientSocket *c)
{
	for(int i=0;i<sizeof(Client)/sizeof(Client[0]);i++){
		if(Client[i]==c){
			Client[i]->deleteLater();
			Client[i]=NULL;
		}
	}
}

void PIODevicer::TimeOut()
{
	bool	Changed=false;
	for(int i=0;i<InportBitCount;i++){
		BYTE	data;
		InPort(i,data);
		if(InData[i]!=data){
			Changed=true;
			InData[i]=data;
		}
	}

	if(Changed==true || CameNew==true){
		for(int i=0;i<sizeof(Client)/sizeof(Client[0]);i++){
			if(Client[i]!=NULL){
				Client[i]->Send(InData,InportBitCount/8);
			}
		}
		CameNew=false;
	}
}

void	PIODevicer::OutPort(BYTE data[])
{
	for(int i=0;i<OutportBitCount/8;i++){
		OutPort(i,data[i]);
	}
}

void	PIODevicer::OutPort(int port ,BYTE data)
{
	long Ret;

	Ret = DioOutByte ( BoardId , port , data );
}

void	PIODevicer::InPort(int port ,BYTE &data)
{
	long Ret;
	BYTE InData;

	Ret = DioInpByte ( BoardId , port , &InData );
	data=InData;
}
