#include "XContecNC4DPipe.h"
#include <QCoreApplication>
#include <QStringList>
#include <QFileInfo>
#include <QBuffer>
#include "ContecNC4D.h"
#include "XGeneralFunc.h"


ContecNC4DPipeInstance::ContecNC4DPipeInstance(ContecNC4DPipe *parent ,QLocalSocket *s)
	:Parent(parent),Socket(s)
{
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
}

void	ContecNC4DPipeInstance::SlotReadyRead()
{
	QByteArray	R=Socket->readAll();
	QBuffer	Buff(&R);
	Buff.open(QIODevice::ReadOnly);
	QString	Req;
	::Load(&Buff,Req);

	if(Req==QString("StartXY")==true){
		Parent->ExeStartXY();
	}
	else if(Req==QString("StepXY")==true){
		Parent->ExeStepXY();
	}
	else if(Req==QString("GoOrigin")==true){
		Parent->ExeOrigin();
	}
	else if(Req==QString("IsEndXY")==true){
		if(Parent->IsEndXY()==true){
			Socket->write("1");
			Socket->flush();
		}
		else{
			Socket->write("0");
			Socket->flush();
		}
	}
	else if(Req==QString("IsEndZ")==true){
		if(Parent->IsEndZ()==true){
			Socket->write("1");
			Socket->flush();
		}
		else{
			Socket->write("0");
			Socket->flush();
		}
	}
	else if(Req==QString("IsStartButton")==true){
		if(Parent->IsStartButton()==true){
			Socket->write("1");
			Socket->flush();
		}
		else{
			Socket->write("0");
			Socket->flush();
		}
	}
	else if(Req==QString("SetLightGreenON")==true){
		Parent->SetLightGreen(true);
	}
	else if(Req==QString("SetLightGreenOFF")==true){
		Parent->SetLightGreen(false);
	}
	else if(Req==QString("BlinkButton")==true){
		Parent->SetBlink(true);
	}
	else if(Req==QString("BlinkOFF")==true){
		Parent->SetBlink(false);
	}
	else if(Req==QString("MoveZ")==true){
		int	ZMicron;
		::Load(&Buff,ZMicron);
		Parent->ExeStartZ(ZMicron);
	}
	else if(Req==QString("VacuumON")==true){
		Parent->SetVacuum(true);
	}
	else if(Req==QString("VacuumOFF")==true){
		Parent->SetVacuum(false);
	}
	else if(Req==QString("LaserPointerON")==true){
		Parent->SetLaserPointer(true);
	}
	else if(Req==QString("LaserPointerOFF")==true){
		Parent->SetLaserPointer(false);
	}
	else if(Req==QString("MoveVRS")==true){
		int	XPos,YPos;
		::Load(&Buff,XPos);
		::Load(&Buff,YPos);
		Parent->MoveVRS(XPos,YPos);
	}
	else if(Req==QString("IsAreaSensorON")==true){
		if(Parent->IsAreaSensorON()==true){
			Socket->write("1");
			Socket->flush();
		}
		else{
			Socket->write("0");
			Socket->flush();
		}
	}
	else{
		Socket->write("Ack");
	}
	Socket->flush();
}

ContecNC4DPipe::ContecNC4DPipe ( ContecNC4D * parent)
	:QLocalServer(parent)
{
	Parent=parent;
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}
void	ContecNC4DPipe::Start(void)
{
	//QString FileName=QCoreApplication::applicationFilePath ();
	//QFileInfo	Info(FileName);
	QString		Name="ContecNC4D";
	listen(Name);
}

void	ContecNC4DPipe::SlotNewConnection ()
{
	QLocalSocket *s=nextPendingConnection ();
	if(s!=NULL){
		ContecNC4DPipeInstance	*k=new ContecNC4DPipeInstance(this,s);
	}
}

void	ContecNC4DPipe::ExeOrigin(void)
{
	if(Parent!=NULL){
		Parent->ExeOrigin();
	}
}
void	ContecNC4DPipe::ExeStartXY()
{
	if(Parent!=NULL){
		Parent->ExeStartXY();
	}
}
void	ContecNC4DPipe::ExeStepXY()
{
	if(Parent!=NULL){
		Parent->ExeStepXY();
	}
}
bool	ContecNC4DPipe::IsEndXY()
{
	if(Parent!=NULL){
		return Parent->IsEndXY();
	}
	return false;
}
void	ContecNC4DPipe::ExeStartZ(int ZMicron)
{
	if(Parent!=NULL){
		Parent->ExeStartZ(ZMicron);
	}
}
bool	ContecNC4DPipe::IsEndZ()
{
	if(Parent!=NULL){
		return Parent->IsEndZ();
	}
	return false;
}
bool	ContecNC4DPipe::IsStartButton()
{
	if(Parent!=NULL){
		return Parent->IsStartButton();
	}
	return false;
}
bool	ContecNC4DPipe::IsAreaSensorON()
{
	if(Parent!=NULL){
		return Parent->IsAreaSensorON();
	}
	return false;
}

void	ContecNC4DPipe::SetLightGreen(bool b)
{
	if(Parent!=NULL){
		Parent->SetLightGreen(b);
	}
}
void	ContecNC4DPipe::SetBlink(bool b)
{
	if(Parent!=NULL){
		Parent->SetBlink(b);
	}
}
void	ContecNC4DPipe::GoMoveZ(int ZMicron)
{
	if(Parent!=NULL){
		Parent->ExeStartZ(ZMicron);
	}
}

void	ContecNC4DPipe::SetVacuum(bool b)
{
	if(Parent!=NULL){
		Parent->SetVacuum(b);
	}
}
void	ContecNC4DPipe::SetLaserPointer(bool b)
{
	if(Parent!=NULL){
		Parent->SetLaserPointer(b);
	}
}

void	ContecNC4DPipe::MoveVRS(int XPos,int YPos)
{
	if(Parent!=NULL){
		Parent->ExeMoveVRS(XPos,YPos);
	}
}
