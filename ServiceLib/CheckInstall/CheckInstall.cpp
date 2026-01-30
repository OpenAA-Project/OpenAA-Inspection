/*
 * Copyright (C) 2022
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

#include "CheckInstall.h"

CheckInstall::CheckInstall(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Thread=NULL;
}
   
void    CheckInstall::StartThread(void)
{
    Thread=new CheckInstall(this);
    Thread->start();
}
    
void    CheckInstall::StopThread(void)
{
    if(Thread!=NULL){
        Thread->SetTerminate(true);
        Thread->wait(5000);
        delete  Thread;
        Thread=NULL;
    }
}

//===========================================
CheckThread::CheckThread(CheckInstall *p)
    :QThread(p),Parent(p)
{
    Terminated=false;
}
CheckThread::~CheckThread(void)
{
}

void    CheckThread::SetTerminate(bool b)
{
    Terminated=true;
}

void    CheckThread::run()
{
}
