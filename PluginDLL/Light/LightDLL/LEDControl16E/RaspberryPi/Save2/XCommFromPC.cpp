/*
 * Copyright (C) 2020
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

#include "XCommFromPC.h"
#include "mainwindow.h"


TriggerClient::TriggerClient(TriggerServer *p ,QTcpSocket *s)
:Sock(s),Parent(p)
{
	connect(Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	connect(Sock,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
}

void	TriggerClient::SlotReadyRead()
{
	unsigned char	Cmd;
	if(Sock->read((char *)&Cmd,1)!=1)
		return;
	if(Cmd==0x1A){
		struct	TriggerInfo	Data;
		if(Sock->read((char *)&Data,sizeof(Data))!=sizeof(Data))
			return;
		Parent->SetData(Data);
	}
	else if(Cmd==0x1B){
		struct	TriggerInfo	Data;
		Parent->ReqData(Data);
		unsigned char	Ack=0x1E;
		
		if(Sock->write((const char *)&Ack,1)!=1)
			return;
		if(Sock->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
			return;
		Sock->flush();
	}
	int	N=Sock->bytesAvailable();
	if(N>0){
        QByteArray	Dummy=Sock->readAll();
	}
}

void	TriggerClient::SlotDisconnected()
{
	deleteLater();
}


TriggerServer::TriggerServer(MainWindow *p)
:Parent(p)
{
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}
void	TriggerServer::StartListen(void)
{
    listen(QHostAddress::Any,TriggerControllerPort);
}
void	TriggerServer::SetData(struct	TriggerInfo &Data)
{
	Parent->EIOData.DelayFrameTriggerA	=Data.TriggerTiming1;
	Parent->EIOData.DelayFrameTriggerB	=Data.TriggerTiming2;
	Parent->EIOData.DropLength			=Data.DropTiming;
    Parent->ShowEIO();
	Parent->WriteEIO();
}
void	TriggerServer::ReqData(struct	TriggerInfo &Data)
{
	Data.TriggerTiming1	=Parent->EIOData.DelayFrameTriggerA;
	Data.TriggerTiming2	=Parent->EIOData.DelayFrameTriggerB;
	Data.DropTiming		=Parent->EIOData.DropLength;
}
	
void	TriggerServer::SlotNewConnection()
{
	QTcpSocket	*s=nextPendingConnection ();
	new TriggerClient(this,s);
}
	
