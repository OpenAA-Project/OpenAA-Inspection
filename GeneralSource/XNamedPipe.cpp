/*
 * Copyright (C) 2021
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

#include "XNamedPipe.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QStringList>
#include "XGeneralFunc.h"

WatchdogInstance::WatchdogInstance(WatchdogInProgram *parent ,QLocalSocket *s)
	:Parent(parent),Socket(s)
{
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
}

void	WatchdogInstance::SlotReadyRead()
{
	QByteArray	R=Socket->readAll();
	QString	Req(R);
	if(Req==QString("ARG")==true){
		QStringList	q=QCoreApplication::arguments();
		QString	arg;
		for(int i=1;i<q.count();i++){
			arg+=q[i];
			if((i+1)<q.count()){
				arg+=" ";
			}
		}
		char	Buff[10000];
		::QString2Char(arg, Buff, sizeof(Buff));
		Socket->write(Buff);
	}
	else{
		Socket->write("Ack");
	}
	Socket->flush();
}

//======================================================

WatchdogInProgram::WatchdogInProgram ( QObject * parent)
	:QLocalServer(parent)
{
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}

void	WatchdogInProgram::Start(void)
{
	qint64	pid=QCoreApplication::applicationPid (); 
	QString FileName=QCoreApplication::applicationFilePath ();
	QFileInfo	Info(FileName);
	QString		Name=Info.baseName()+QString::number(pid);
	listen(Name);
}

void	WatchdogInProgram::SlotNewConnection ()
{
	QLocalSocket *s=nextPendingConnection ();
	if(s!=NULL){
		WatchdogInstance	*k=new WatchdogInstance(this,s);
	}
}