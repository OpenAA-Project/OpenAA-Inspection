#include "XLightDLLRemoteController.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include <XGeneralFunc.h>
#include "SelectListDialog.h"

XLightDLLRemoteController::XLightDLLRemoteController(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	Socket	=new QLocalSocket(base->GetMainWidget());
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	LightID=-1;
}
XLightDLLRemoteController::~XLightDLLRemoteController(void)
{
	if(Socket!=NULL){
		delete	Socket;
		Socket=NULL;
	}
}

bool	XLightDLLRemoteController::Save(QIODevice *f)
{
	if(::Save(f,LightID)==false)
		return false;
	return true;
}
bool	XLightDLLRemoteController::Load(QIODevice *f)
{
	if(::Load(f,LightID)==false)
		return false;
	return true;
}

bool	XLightDLLRemoteController::ShowSettingDialog(void)
{
	SelectListDialog	*H=new SelectListDialog(GetLayersBase(),NULL);
	H->Initial(LightID);
	if(H->exec()==(int)true){
		LightID=H->LightID;
		delete	H;
		return true;
	}
	delete	H;
	return false;
}
	//Don't call directly
bool	XLightDLLRemoteController::InitialPhysical(const QString &Param)
{
	if(Socket!=NULL && Socket->isValid()==false){
		Socket->connectToServer (/**/"RemoveLightController");
		if(Socket->waitForConnected (3000)==false){
			Socket->deleteLater();
			Socket=NULL;
			return false;
		}
	}
	return true;
}

bool	XLightDLLRemoteController::ReflectPhysical(void)
{
	if(Socket!=NULL && Socket->isValid()==true){
		for(int i=0;i<3;i++){
			QBuffer	Buff;
			Buff.open(QIODevice::WriteOnly);

			Buff.write("A",1);
			short	Len=sizeof(LightID);
			Buff.write((const char *)&Len,sizeof(Len));
			Buff.write((const char *)&LightID,sizeof(LightID));

			Socket->write(Buff.buffer());
			Socket->flush();
			QElapsedTimer	Timer;
			Timer.start();
			while(Timer.hasExpired(1000)==false){
				QString	Str(Received);
				if(Str=="A"){
					return true;
				}
				Socket->waitForReadyRead(10);
			}
		}
	}
	return false;
}

bool	XLightDLLRemoteController::ReflectPhysicalTurnOn(bool LightOn)
{
	if(Socket!=NULL && Socket->isValid()==true){
		for(int i=0;i<3;i++){
			Received.clear();
			QBuffer	Buff;
			Buff.open(QIODevice::WriteOnly);

			Buff.write("B",1);
			short	Len=sizeof(LightOn);
			Buff.write((const char *)&Len,sizeof(Len));
			Buff.write((const char *)&LightOn,sizeof(LightOn));

			Socket->write(Buff.buffer());
			Socket->flush();
			QElapsedTimer	Timer;
			Timer.start();
			while(Timer.hasExpired(1000)==false){
				QString	Str(Received);
				if(Str=="B"){
					return true;
				}
				Socket->waitForReadyRead(10);
			}
		}
	}
	return false;
}

void	XLightDLLRemoteController::SlotReadyRead()
{
	if(Socket!=NULL){
		Received=Socket->readAll();
	}
}

void	XLightDLLRemoteController::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSendRequestLight	*CmdSendRequestLightVar=dynamic_cast<CmdSendRequestLight *>(packet);
	if(CmdSendRequestLightVar!=NULL){
		Received.clear();
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);

		Buff.write("S",1);
		short	Len=sizeof(CmdSendRequestLightVar->BytesOfAnyData);
		Buff.write((const char *)&Len,sizeof(Len));
		Buff.write((const char *)CmdSendRequestLightVar->AnyData,CmdSendRequestLightVar->BytesOfAnyData);

		Socket->write(Buff.buffer());
		Socket->flush();
		QElapsedTimer	Timer;
		Timer.start();
		while(Timer.hasExpired(1000)==false){
			QString	Str(Received);
			if(Str=="S"){
				break;
			}
			Socket->waitForReadyRead(10);
		}
		return;
	}
}