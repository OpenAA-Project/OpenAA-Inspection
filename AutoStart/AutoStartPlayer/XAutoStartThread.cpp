/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\XAutoStartThread.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


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