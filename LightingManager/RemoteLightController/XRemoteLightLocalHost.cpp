#include "XRemoteLightLocalHost.h"
#include <QStringList>
#include <QCoreApplication>
#include "XTypeDef.h"
#include "RemoteLightController.h"

FromProgramInstance::FromProgramInstance(FromProgram *parent ,QLocalSocket *s)
	:Parent(parent),Socket(s)
{
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	connect(this,SIGNAL(SignalLightID(int )),Parent,SLOT(SlotLightID(int)));
	connect(this,SIGNAL(SignalLightON(bool)),Parent,SLOT(SlotLightON(bool)));
	connect(this,SIGNAL(SignalLightRequest()),Parent,SLOT(SlotLightRequest()));
}

void	FromProgramInstance::SlotReadyRead()
{
	QByteArray	Buff=Socket->readAll();

	QBuffer	RBuff(&Buff);
	RBuff.open(QIODevice::ReadOnly);

	char	Cmd;
	RBuff.read((char *)&Cmd,1);
	short	Len;
	RBuff.read((char *)&Len,sizeof(Len));
	if(Cmd=='A'){
		int32		LightID;
		RBuff.read((char *)&LightID,sizeof(LightID));
		emit	SignalLightID(LightID);
		Socket->write(&Cmd,1);
		Socket->flush();
	}
	else if(Cmd=='B'){
		bool		LightOn;
		RBuff.read((char *)&LightOn,sizeof(LightOn));
		emit	SignalLightON(LightOn);
		Socket->write(&Cmd,1);
		Socket->flush();
	}
	else if(Cmd=='S'){
		if(Parent->ReqData!=NULL){
			delete	[]Parent->ReqData;
		}
		Parent->ReqData			=new BYTE[Len];
		Parent->ReqDataLength	=Len;
		RBuff.read((char *)Parent->ReqData,Len);
		emit	SignalLightRequest();
		Socket->write(&Cmd,1);
		Socket->flush();
	}

}

FromProgram::FromProgram ( RemoteLightController * parent)
	:QLocalServer(parent),RParent(parent)
{
	ReqData			=NULL;
	ReqDataLength	=0;
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}
FromProgram::~FromProgram(void)
{
	if(ReqData!=NULL)
		delete	[]ReqData;
	ReqData=NULL;
	ReqDataLength=0;
}
void	FromProgram::Start(void)
{
	listen(/**/"RemoveLightController");
}

void	FromProgram::SlotNewConnection ()
{
	QLocalSocket *s=nextPendingConnection ();
	if(s!=NULL){
		FromProgramInstance	*k=new FromProgramInstance(this,s);
	}
}

void	FromProgram::SlotLightID(int lightID)
{
	RParent->SetLightID(lightID);
}

void	FromProgram::SlotLightON(bool lightON)
{
	RParent->SetLightOn(lightON);
}

void	FromProgram::SlotLightRequest(void)
{
	RParent->SetLightRequest(ReqData,ReqDataLength);
}

