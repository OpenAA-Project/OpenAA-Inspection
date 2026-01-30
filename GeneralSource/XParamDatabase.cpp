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


#include "XTypeDef.h"
#include "XParamDatabase.h"
#include "XGeneralFunc.h"


bool	ParamDatabaseLeaf::Save(QIODevice *f)
{
	if(::Save(f,IDName)==false){
		return false;
	}
	if(::Save(f,Data)==false){
		return false;
	}
	return true;
}
	
bool	ParamDatabaseLeaf::Load(QIODevice *f)
{
	if(::Load(f,IDName)==false){
		return false;
	}
	if(::Load(f,Data)==false){
		return false;
	}
	return true;
}


ParamDatabase::ParamDatabase(const QString &FileName)
{
	ParamDatabaseFileName=FileName;
}

QIODevice	*ParamDatabase::CreateIODevice(const QString &IDName)
{
	for(ParamDatabaseLeaf *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->IDName==IDName){
			QBuffer	*Buff=new QBuffer(&L->Data);
			Buff->open(QIODevice::ReadWrite);
			return Buff;
		}
	}
	ParamDatabaseLeaf	*P=new ParamDatabaseLeaf();
	P->IDName=IDName;
	AppendList(P);
	QBuffer	*Buff=new QBuffer(&P->Data);
	Buff->open(QIODevice::ReadWrite);
	return Buff;
}
void		ParamDatabase::DeleteIODevice(QIODevice *f)
{
	delete	f;
	Save();
}

bool	ParamDatabase::Save(void)
{
	QFile	FL(ParamDatabaseFileName);

	if(FL.open(QIODevice::WriteOnly)==false){
		return false;
	}

	int32	N=GetNumber();
	if(::Save(&FL,N)==false){
		return false;
	}
	for(ParamDatabaseLeaf *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(&FL)==false){
			return false;
		}
	}
	return true;
}
	
bool	ParamDatabase::Load(void)
{
	int32	N;

	QFile	FL(ParamDatabaseFileName);

	if(FL.open(QIODevice::ReadOnly)==false){
		return false;
	}
	if(::Load(&FL,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ParamDatabaseLeaf *L=new ParamDatabaseLeaf();
		if(L->Load(&FL)==false){
			return false;
		}
		AppendList(L);
	}
	return true;
}