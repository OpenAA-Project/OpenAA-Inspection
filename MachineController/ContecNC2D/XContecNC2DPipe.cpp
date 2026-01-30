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

#include "XContecNC2DPipe.h"
#include <QCoreApplication>
#include <QStringList>
#include <QFileInfo>
#include "ContecNC2D.h"

ContecNC2DPipeInstance::ContecNC2DPipeInstance(ContecNC2DPipe *parent ,QLocalSocket *s)
	:Parent(parent),Socket(s)
{
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
}

void	ContecNC2DPipeInstance::SlotReadyRead()
{
	QByteArray	R=Socket->readAll();
	QString	Req(R);
	if(Req==QString("Start")==true){
		Parent->ExeStart();
	}
	else if(Req==QString("Step")==true){
		Parent->ExeStep();
	}
	else if(Req==QString("IsEnd")==true){
		if(Parent->IsEnd()==true){
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
	else{
		Socket->write("Ack");
	}
	Socket->flush();
}

ContecNC2DPipe::ContecNC2DPipe ( ContecNC2D * parent)
	:QLocalServer(parent)
{
	Parent=parent;
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}
void	ContecNC2DPipe::Start(void)
{
	//QString FileName=QCoreApplication::applicationFilePath ();
	//QFileInfo	Info(FileName);
	QString		Name="ContecNC2D";
	listen(Name);
}

void	ContecNC2DPipe::SlotNewConnection ()
{
	QLocalSocket *s=nextPendingConnection ();
	if(s!=NULL){
		ContecNC2DPipeInstance	*k=new ContecNC2DPipeInstance(this,s);
	}
}


void	ContecNC2DPipe::ExeStart()
{
	Parent->ExeStart();
}
void	ContecNC2DPipe::ExeStep()
{
	Parent->ExeStep();
}
bool	ContecNC2DPipe::IsEnd()
{
	return Parent->IsEnd();
}
bool	ContecNC2DPipe::IsStartButton()
{
	return Parent->IsStartButton();
}
