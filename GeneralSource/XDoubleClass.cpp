/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDoubleClass.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------
#include "XDoubleClass.h"
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
bool    DoubleClass::Save(QIODevice *file)
{
	if(file->write((const char *)&d,sizeof(d))!=sizeof(d)){
        return(false);
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
bool    DoubleClass::Load(QIODevice *file)
{
	if(file->read((char *)&d,sizeof(d))!=sizeof(d)){
        return(false);
	}
    return(true);
}
int	DoubleClass::Compare(DoubleClass &src)
{
	if(GetValue()<src.GetValue())
		return 1;
	if(GetValue()>src.GetValue())
		return -1;
	return 0;
}

DoubleList::DoubleList(void)
{}
DoubleList::DoubleList(const DoubleList &src)
{
	RemoveAll();
	for(DoubleClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		DoubleClass	*d=new DoubleClass(s->GetValue());
		AppendList(d);
	}
}

bool	DoubleList::IsInclude(double d)
{
	for(DoubleClass *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->GetValue()==d){
			return true;
		}
	}
	return false;
}

DoubleList	&DoubleList::operator=(const DoubleList &src)
{
	RemoveAll();
	return operator+=(src);
}
DoubleList	&DoubleList::operator+=(const DoubleList &src)
{
	for(DoubleClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		DoubleClass	*d=new DoubleClass(s->GetValue());
		AppendList(d);
	}
	return *this;
}
bool	DoubleList::operator==(const DoubleList &src)	const
{
	DoubleClass *d=GetFirst();
	DoubleClass *s=src.GetFirst();
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
bool	DoubleList::operator!=(const DoubleList &src)	const
{
	return !operator==(src);
}
void	DoubleList::Merge	(double D)
{
	for(DoubleClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(d->GetValue()==D){
			return;
		}
	}
	DoubleClass	*k=new DoubleClass(D);
	AppendList(k);
}
void	DoubleList::Merge	(const DoubleList &src)
{
	for(DoubleClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		bool	Found=false;
		for(DoubleClass *d=GetFirst();d!=NULL;d=d->GetNext()){
			if(*d==*s){
				Found=true;
				break;
			}
		}
		if(Found==false){
			DoubleClass	*k=new DoubleClass(*s);
			AppendList(k);
		}
	}
}
void	DoubleList::Merge	(const DoubleClass &src)
{
	for(DoubleClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(*d==src){
			return;
		}
	}
	DoubleClass	*k=new DoubleClass(src);
	AppendList(k);
}

bool    DoubleList::Save(QIODevice *file)
{
	int32	N=GetNumber();
	if(file->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	for(DoubleClass *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(file)==false){
			return false;
		}
	}
	return true;
}
bool    DoubleList::Load(QIODevice *file)
{
	int32	N;
	if(file->read((char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		DoubleClass	*d=new DoubleClass();
		if(d->Load(file)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}

DoubleList	DoubleList::operator+()	const
{
	DoubleList	Ret=*this;
	return Ret;
}
DoubleList	DoubleList::operator-()	const
{
	DoubleList	Ret;
	for(DoubleClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		Ret.Add(-d->GetValue());
	}
	return Ret;
}
DoubleList	DoubleList::operator+(const DoubleList &src)	const
{
	DoubleList	Ret;
	DoubleClass *s=src.GetFirst();
	DoubleClass *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		Ret.Add(s->GetValue()+d->GetValue());
	}
	for(;d!=NULL;d=d->GetNext()){
		Ret.Add(d->GetValue());
	}
	for(;s!=NULL;s=s->GetNext()){
		Ret.Add(s->GetValue());
	}
	return Ret;
}
DoubleList	DoubleList::operator-(const DoubleList &src)	const
{
	DoubleList	Ret;
	DoubleClass *s=src.GetFirst();
	DoubleClass *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		Ret.Add(d->GetValue()-s->GetValue());
	}
	for(;d!=NULL;d=d->GetNext()){
		Ret.Add(d->GetValue());
	}
	for(;s!=NULL;s=s->GetNext()){
		Ret.Add(-s->GetValue());
	}
	return Ret;
}
DoubleList	DoubleList::operator*(const DoubleList &src)	const
{
	DoubleList	Ret;
	DoubleClass *s=src.GetFirst();
	DoubleClass *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		Ret.Add(s->GetValue()*d->GetValue());
	}
	for(;d!=NULL;d=d->GetNext()){
		Ret.Add(0);
	}
	for(;s!=NULL;s=s->GetNext()){
		Ret.Add(0);
	}
	return Ret;
}
DoubleList	DoubleList::operator/(const DoubleList &src)	const
{
	DoubleList	Ret;
	DoubleClass *s=src.GetFirst();
	DoubleClass *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		Ret.Add(d->GetValue()/s->GetValue());
	}
	for(;d!=NULL;d=d->GetNext()){
		Ret.Add(0);
	}
	for(;s!=NULL;s=s->GetNext()){
		Ret.Add(0);
	}
	return Ret;
}
DoubleList	DoubleList::operator*(float m)	const
{
	DoubleList	Ret;
	for(DoubleClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		Ret.Add(d->GetValue()*m);
	}

	return Ret;
}
DoubleList	DoubleList::operator/(float m)	const
{
	DoubleList	Ret;
	for(DoubleClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		Ret.Add(d->GetValue()/m);
	}

	return Ret;
}
DoubleList	&DoubleList::operator-=(const DoubleList &src)
{
	DoubleClass *s=src.GetFirst();
	DoubleClass *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		d->SetValue(d->GetValue()-s->GetValue());
	}
	return *this;
}
DoubleList	&DoubleList::operator*=(const DoubleList &src)
{
	DoubleClass *s=src.GetFirst();
	DoubleClass *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		d->SetValue(d->GetValue()*s->GetValue());
	}
	return *this;
}
DoubleList	&DoubleList::operator/=(const DoubleList &src)
{
	DoubleClass *s=src.GetFirst();
	DoubleClass *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		d->SetValue(d->GetValue()/s->GetValue());
	}
	return *this;
}
DoubleList	&DoubleList::operator*=(float m)
{
	for(DoubleClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		d->SetValue(d->GetValue()*m);
	}
	return *this;
}
DoubleList	&DoubleList::operator/=(float m)
{
	for(DoubleClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		d->SetValue(d->GetValue()/m);
	}
	return *this;
}
