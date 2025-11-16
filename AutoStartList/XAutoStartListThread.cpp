/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\XAutoStartThread.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XAutoStartListThread.h"
#include <QString>
#include <QDir>
#include <QProcess>
#include <QApplication>
#include "AutoStartList.h"

ThreadAutoStartList::ThreadAutoStartList(AutoStartList *aparent, QObject * parent)
:QThread (parent),Parent(aparent)
{	
	OnExecuting		=false;
	Terminated		=false;
}

void	ThreadAutoStartList::run()
{
	while(Terminated==false){
		OnExecuting		=false;

		while(Parent->Counting==true){
			if(Terminated==true)
				return;
			msleep(300);
		}

		OnExecuting=true;
		Parent->ExecuteAll();

		do{
			while(Parent->AllFinished==false){
				if(Terminated==true)
					return;
				msleep(300);
			}
			msleep(1500);
		}while(Parent->AllFinished==false);

		Parent->AutoStartExeListData.CloseAll();
		OnExecuting=false;

		msleep(3000);
	}
}
