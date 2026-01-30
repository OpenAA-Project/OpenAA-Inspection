/*
 * Copyright (C) 2015
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "XContecNC3DPipe.h"
#include <QCoreApplication>
#include <QStringList>
#include <QFileInfo>
#include <QBuffer>
#include "ContecNC3D.h"
#include "XGeneralFunc.h"


ContecNC3DPipeInstance::ContecNC3DPipeInstance(ContecNC3DPipe *parent ,QLocalSocket *s)
	:Parent(parent),Socket(s)
{
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
}

void	ContecNC3DPipeInstance::SlotReadyRead()
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
	else{
		Socket->write("Ack");
	}
	Socket->flush();
}

ContecNC3DPipe::ContecNC3DPipe ( ContecNC3D * parent)
	:QLocalServer(parent)
{
	Parent=parent;
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}
void	ContecNC3DPipe::Start(void)
{
	//QString FileName=QCoreApplication::applicationFilePath ();
	//QFileInfo	Info(FileName);
	QString		Name="ContecNC3D";
	listen(Name);
}

void	ContecNC3DPipe::SlotNewConnection ()
{
	QLocalSocket *s=nextPendingConnection ();
	if(s!=NULL){
		ContecNC3DPipeInstance	*k=new ContecNC3DPipeInstance(this,s);
	}
}

void	ContecNC3DPipe::ExeOrigin(void)
{
	if(Parent!=NULL){
		Parent->ExeOrigin();
	}
}
void	ContecNC3DPipe::ExeStartXY()
{
	if(Parent!=NULL){
		Parent->ExeStartXY();
	}
}
void	ContecNC3DPipe::ExeStepXY()
{
	if(Parent!=NULL){
		Parent->ExeStepXY();
	}
}
bool	ContecNC3DPipe::IsEndXY()
{
	if(Parent!=NULL){
		return Parent->IsEndXY();
	}
	return false;
}
void	ContecNC3DPipe::ExeStartZ(int ZMicron)
{
	if(Parent!=NULL){
		Parent->ExeStartZ(ZMicron);
	}
}
bool	ContecNC3DPipe::IsEndZ()
{
	if(Parent!=NULL){
		return Parent->IsEndZ();
	}
	return false;
}
bool	ContecNC3DPipe::IsStartButton()
{
	if(Parent!=NULL){
		return Parent->IsStartButton();
	}
	return false;
}

void	ContecNC3DPipe::SetLightGreen(bool b)
{
	if(Parent!=NULL){
		Parent->SetLightGreen(b);
	}
}
void	ContecNC3DPipe::SetBlink(bool b)
{
	if(Parent!=NULL){
		Parent->SetBlink(b);
	}
}
void	ContecNC3DPipe::GoMoveZ(int ZMicron)
{
	if(Parent!=NULL){
		Parent->ExeStartZ(ZMicron);
	}
}

void	ContecNC3DPipe::SetVacuum(bool b)
{
	if(Parent!=NULL){
		Parent->SetVacuum(b);
	}
}