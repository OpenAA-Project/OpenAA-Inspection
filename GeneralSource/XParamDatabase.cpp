/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XParamDatabase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
