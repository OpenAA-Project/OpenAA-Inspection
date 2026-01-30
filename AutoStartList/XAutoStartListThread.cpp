/*
 * Copyright (C) 2024
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