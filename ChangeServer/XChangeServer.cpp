/*
 * Copyright (C) 2012
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

#include "XChangeServer.h"
#include "XGeneralFunc.h"
#include "XTypeDef.h"
#include <QProcess>

bool	ChangeServerItem::Save(QIODevice *f)
{
	int32	Ver=ChangeServerVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,ServerName)==false)
		return false;
	if(::Save(f,Remark)==false)
		return false;
	if(::Save(f,ExecuteBatMode)==false)
		return false;
	if(::Save(f,ExeFilePath)==false)
		return false;
	if(::Save(f,DirectCommandLine)==false)
		return false;

	return true;
}
bool	ChangeServerItem::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,ServerName)==false)
		return false;
	if(::Load(f,Remark)==false)
		return false;
	if(::Load(f,ExecuteBatMode)==false)
		return false;
	if(::Load(f,ExeFilePath)==false)
		return false;
	if(::Load(f,DirectCommandLine)==false)
		return false;

	return true;
}

bool	ChangeServerItem::Execute(void)
{
	if(ExecuteBatMode==true){
		QProcess	QP;
		QP.start(ExeFilePath);
		QP.waitForStarted(3000);
		QP.waitForFinished (2000000000);
	}
	else{
		QString	Current=QDir::currentPath();
		QString	FileName="TmpCmd.bat";
		MakeTmpFile(FileName);

		QProcess	QP;
		QP.start(FileName);
		QP.waitForStarted(3000);
		QP.waitForFinished (2000000000);

		QDir::setCurrent(Current);
		QFile::remove(FileName);
	}
	return true;
}

void	ChangeServerItem::MakeTmpFile(QString &FileName)
{
	QFile	F(FileName);
	F.open(QIODevice::WriteOnly);

	QTextStream	FTxt(&F);
	for(int i=0;i<DirectCommandLine.count();i++){
		FTxt<<DirectCommandLine[i];
		FTxt<<QString("\n");
	}
}

//==================================================================

ChangeServerItem	*ChangeServerContainer::SearchByID(int id)
{
	for(ChangeServerItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ID==id){
			return a;
		}
	}
	return NULL;
}

bool	ChangeServerContainer::Save(QIODevice *f)
{
	int32	Ver=ChangeServerVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,CurrentID)==false)
		return false;

	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(ChangeServerItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	ChangeServerContainer::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,CurrentID)==false)
		return false;

	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		ChangeServerItem *a=new ChangeServerItem();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}