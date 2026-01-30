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

#include "ClearCacheAndStress.h"
#include<QFile>

ClearCacheAndStress::ClearCacheAndStress(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ThreadStressData=new ThreadStress(this);
	ThreadStressData->start();

	ThreadDiskStressData	=new ThreadDiskStress(this);
	ThreadDiskStressData->start();

	TM.setInterval(100);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

ClearCacheAndStress::~ClearCacheAndStress()
{
	ThreadStressData->FinishMode=true;
	ThreadStressData->wait();
	ThreadStressData->deleteLater();

	ThreadDiskStressData->FinishMode=true;
	ThreadDiskStressData->wait();
	ThreadDiskStressData->deleteLater();
}

void	ClearCacheAndStress::SlotTimeOut()
{
	int	n=ui.progressBar->value()+1;
	ui.progressBar->setValue(n);
	if(n>=ui.progressBar->maximum()){
		ui.progressBar->setValue(0);
	}
}

MemoryLeaf::MemoryLeaf(int id,int len)
{
	ID=id;
	Len=len;
	Pointer=new BYTE [Len];
	AccessMode=Len%4;
}
MemoryLeaf::~MemoryLeaf(void)
{
	delete	[]Pointer;
	Pointer=NULL;
}

void	MemoryLeaf::Access(void)
{
	if((AccessMode%2)==0){
		for(int i=0;i<Len;i++){
			Pointer[i]=(BYTE)i;
		}
	}
	else if((AccessMode%2)==1){
		for(int i=0;i<Len;i++){
			D+=Pointer[i];
		}
	}
	AccessMode++;
}


DiskLeaf::DiskLeaf(int id,int len)
{
	ID=id;
	Len=len;
	Pointer=new BYTE [Len];
	AccessMode=Len%4;
}
DiskLeaf::~DiskLeaf(void)
{
	delete	[]Pointer;
	Pointer=NULL;
}

void	DiskLeaf::Access(void)
{
	if((AccessMode%2)==0){
		QString	FileName=QString("Stressor")
						+QString::number(ID)
						+QString(".dat");

		QFile	File(FileName);
		File.open(QIODevice::WriteOnly);
		File.write((const char *)Pointer,Len);
	}
	else if((AccessMode%2)==1){
		QString	FileName=QString("Stressor")
						+QString::number(ID)
						+QString(".dat");

		QFile	File(FileName);
		File.open(QIODevice::ReadOnly);
		File.read((char *)Pointer,Len);
	}
	AccessMode++;
}
ThreadStress::ThreadStress(QObject *parent)
:QThread(parent)
{
	setPriority(QThread::HighestPriority);
	FinishMode=false;

	for(int i=0;i<10000;i++){
		MemoryLeaf	*a=new MemoryLeaf(i,i*100+i+100000);
		MemoryPack.AppendList(a);
	}
}

void	ThreadStress::run()
{
	while(FinishMode==false){
		for(MemoryLeaf *a=MemoryPack.GetFirst();a!=NULL;a=a->GetNext()){
			if(FinishMode==true){
				return;
			}
			a->Access();
		}
	}
}

ThreadDiskStress::ThreadDiskStress(QObject *parent)
:QThread(parent)
{
	setPriority(QThread::HighestPriority);
	FinishMode=false;

	for(int i=0;i<500;i++){
		DiskLeaf	*a=new DiskLeaf(i,i*1000+i+1000000);
		DiskPack.AppendList(a);
	}
}

void	ThreadDiskStress::run()
{
	while(FinishMode==false){
		for(DiskLeaf *a=DiskPack.GetFirst();a!=NULL;a=a->GetNext()){
			if(FinishMode==true){
				return;
			}
			a->Access();
		}
	}
}

