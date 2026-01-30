/*
 * Copyright (C) 2023
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



#include "XAutoStartThread.h"
#include <QString>
#include "XDateTime.h"
#include <QDir>
#include <QProcess>
#include <QApplication>
#include "XGeneralFuncCore.h"

ThreadAutoStart::ThreadAutoStart( QObject * parent)
:QThread (parent)
{	
	SpareSec=20;	
	StartExecMode	=false;
	StopMode		=false;
	OnExecuting		=false;
}

void	ThreadAutoStart::run()
{
	QString	SPath=QCoreApplication::applicationDirPath();
	for(;;){
		StartExecMode	=false;
		StopMode		=false;
		OnExecuting		=false;
		emit	OnLoop(0);
		for(int N=0;N<SpareSec;N++){
			do{
				msleep(1000);
				emit	OnLoop(N);
				if(StartExecMode==true)
					goto	NextP;
			}while(StopMode==true);
		}
NextP:;
		emit	OnLoop(SpareSec);
		QDir::setCurrent (SPath);

		OnExecuting=true;
		if(SArg.isEmpty()==true)
			QProcess::execute ( SPath+::GetSeparator()+PlayerExe);
		else
			QProcess::execute ( SPath+::GetSeparator()+PlayerExe+QString(" ")+SArg);
		OnExecuting=false;
	}
}
void	ThreadAutoStart::SetExec()
{
	StartExecMode=true;
}

void	ThreadAutoStart::SetStop()
{
	StopMode=true;
}
void	ThreadAutoStart::SetRestart()
{
	StopMode=false;
}