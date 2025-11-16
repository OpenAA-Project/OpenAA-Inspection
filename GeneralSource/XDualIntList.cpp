/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDualIntList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------
#include "XDualIntList.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"



/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    file
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    DualIntClass::Save(QIODevice *file)
{
	if(::Save(file,D[0])==false){
		return false;
	}
	if(::Save(file,D[1])==false){
		return false;
	}
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    file
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    DualIntClass::Load(QIODevice *file)
{
	if(::Save(file,D[0])==false){
		return false;
	}
	if(::Save(file,D[1])==false){
		return false;
	}
    return(true);
}


DualIntList::DualIntList(const DualIntList &src)
{
	RemoveAll();
	for(DualIntClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		DualIntClass	*d=new DualIntClass(*s);
		AppendList(d);
	}
}

bool	DualIntList::IsInclude(int d1, int d2)
{
	for(DualIntClass *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->GetValue(0)==d1 && s->GetValue(1)==d2){
			return true;
		}
	}
	return false;
}

DualIntList	&DualIntList::operator=(const DualIntList &src)
{
	RemoveAll();
	for(DualIntClass *s=((DualIntList *)&src)->GetFirst();s!=NULL;s=s->GetNext()){
		DualIntClass	*d=new DualIntClass(*s);
		AppendList(d);
	}
	return *this;
}
bool	DualIntList::operator==(const DualIntList &src)	const
{
	DualIntClass *d=GetFirst();
	DualIntClass *s=src.GetFirst();
	for(;s!=NULL && d!=NULL;s=s->GetNext(),d=d->GetNext()){
		if(*s!=*d){
			return false;
		}
	}
	if(s!=NULL || d!=NULL){
		return false;
	}
	return true;
}
bool	DualIntList::operator!=(const DualIntList &src)	const
{
	return !operator==(src);
}
void	DualIntList::Merge	(int d1, int d2)
{
	for(DualIntClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(d->GetX()==d1 && d->GetY()==d2){
			return;
		}
	}
	DualIntClass	*k=new DualIntClass(d1,d2);
	AppendList(k);
}

void	DualIntList::Merge	(const DualIntList &src)
{
	for(DualIntClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		bool	Found=false;
		for(DualIntClass *d=GetFirst();d!=NULL;d=d->GetNext()){
			if(*d==*s){
				Found=true;
				break;
			}
		}
		if(Found==false){
			DualIntClass	*k=new DualIntClass(*s);
			AppendList(k);
		}
	}
}
void	DualIntList::Merge	(const DualIntClass &src)
{
	for(DualIntClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(*d==src){
			return;
		}
	}
	DualIntClass	*k=new DualIntClass(src);
	AppendList(k);
}

bool    DualIntList::Save(QIODevice *file)
{
	int32	N=GetNumber();
	if(::Save(file,N)==false){
		return false;
	}
	for(DualIntClass *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(file)==false){
			return false;
		}
	}
	return true;
}
bool    DualIntList::Load(QIODevice *file)
{
	int32	N;
	if(::Load(file,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		DualIntClass	*d=new DualIntClass();
		if(d->Load(file)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}
