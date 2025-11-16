/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBoolList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------
#include "XBoolList.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"


bool    BoolClass::Save(QIODevice *file)
{
	if(file->write((const char *)&d,sizeof(d))!=sizeof(d)){
        return(false);
	}
    return(true);
}

bool    BoolClass::Load(QIODevice *file)
{
	if(file->read((char *)&d,sizeof(d))!=sizeof(d)){
        return(false);
	}
    return(true);
}

BoolList::BoolList(void)
{}
BoolList::BoolList(const BoolList &src)
{
	RemoveAll();
	for(BoolClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BoolClass	*d=new BoolClass(s->GetValue());
		AppendList(d);
	}
}

bool	BoolList::IsInclude(bool d)
{
	for(BoolClass *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->GetValue()==d){
			return true;
		}
	}
	return false;
}

BoolList	&BoolList::operator=(BoolList &src)
{
	RemoveAll();
	for(BoolClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BoolClass	*d=new BoolClass(s->GetValue());
		AppendList(d);
	}
	return *this;
}
BoolList	&BoolList::operator=(const BoolList &src)
{
	RemoveAll();
	return operator+=(src);
}
BoolList	&BoolList::operator+=(const BoolList &src)
{
	for(BoolClass *s=((BoolList *)&src)->GetFirst();s!=NULL;s=s->GetNext()){
		BoolClass	*d=new BoolClass(s->GetValue());
		AppendList(d);
	}
	return *this;
}
bool	BoolList::operator==(const BoolList &src)	const
{
	BoolClass *d=GetFirst();
	BoolClass *s=src.GetFirst();
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
bool	BoolList::operator!=(const BoolList &src)	const
{
	return !operator==(src);
}
bool	BoolList::operator[](int n)	const
{
	BoolClass	*b=GetItem(n);
	if(b!=NULL){
		return b->GetValue();
	}
	return false;
}
void	BoolList::Merge(const BoolList &src)
{
	for(BoolClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		bool	Found=false;
		for(BoolClass *d=GetFirst();d!=NULL;d=d->GetNext()){
			if(*s==*d){
				Found=true;
				break;
			}
		}
		if(Found==false){
			BoolClass	*k=new BoolClass(*s);
			AppendList(k);
		}
	}
}
void	BoolList::Merge(const BoolClass &src)
{
	for(BoolClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(*d==src){
			return;
		}
	}
	BoolClass	*k=new BoolClass(src);
	AppendList(k);
}
void	BoolList::Merge(bool s)
{
	for(BoolClass *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(*d==s){
			return;
		}
	}
	BoolClass	*k=new BoolClass(s);
	AppendList(k);
}
bool    BoolList::Save(QIODevice *file)
{
	int32	N=GetNumber();
	if(file->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	for(BoolClass *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(file)==false){
			return false;
		}
	}
	return true;
}
bool    BoolList::Load(QIODevice *file)
{
	int32	N;
	if(file->read((char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		BoolClass	*d=new BoolClass();
		if(d->Load(file)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}

//===============================================================================

bool    Bool3Class::Save(QIODevice *file)
{
	if(file->write((const char *)&d,sizeof(d))!=sizeof(d)){
        return(false);
	}
    return(true);
}

bool    Bool3Class::Load(QIODevice *file)
{
	if(file->read((char *)&d,sizeof(d))!=sizeof(d)){
        return(false);
	}
    return(true);
}

Bool3List::Bool3List(void)
{}
Bool3List::Bool3List(const Bool3List &src)
{
	for(Bool3Class *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		Bool3Class	*d=new Bool3Class(s->GetValue());
		AppendList(d);
	}
}

bool	Bool3List::IsInclude(bool3 d)
{
	for(Bool3Class *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->GetValue()==d){
			return true;
		}
	}
	return false;
}

Bool3List	&Bool3List::operator=(Bool3List &src)
{
	RemoveAll();
	for(Bool3Class *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		Bool3Class	*d=new Bool3Class(s->GetValue());
		AppendList(d);
	}
	return *this;
}
Bool3List	&Bool3List::operator=(const Bool3List &src)
{
	RemoveAll();
	return operator+=(src);
}
Bool3List	&Bool3List::operator+=(const Bool3List &src)
{
	for(Bool3Class *s=((Bool3List *)&src)->GetFirst();s!=NULL;s=s->GetNext()){
		Bool3Class	*d=new Bool3Class(s->GetValue());
		AppendList(d);
	}
	return *this;
}
bool	Bool3List::operator==(const Bool3List &src)	const
{
	Bool3Class *d=GetFirst();
	Bool3Class *s=src.GetFirst();
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
bool	Bool3List::operator!=(const Bool3List &src)	const
{
	return !operator==(src);
}
bool3	Bool3List::operator[](int n)	const
{
	Bool3Class	*b=GetItem(n);
	if(b!=NULL){
		return b->GetValue();
	}
	return false3;
}
void	Bool3List::Merge(const Bool3List &src)
{
	for(Bool3Class *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		bool	Found=false;
		for(Bool3Class *d=GetFirst();d!=NULL;d=d->GetNext()){
			if(*s==*d){
				Found=true;
				break;
			}
		}
		if(Found==false){
			Bool3Class	*k=new Bool3Class(*s);
			AppendList(k);
		}
	}
}
void	Bool3List::Merge(const Bool3Class &src)
{
	for(Bool3Class *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(*d==src){
			return;
		}
	}
	Bool3Class	*k=new Bool3Class(src);
	AppendList(k);
}
void	Bool3List::Merge(bool3 s)
{
	for(Bool3Class *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(*d==s){
			return;
		}
	}
	Bool3Class	*k=new Bool3Class(s);
	AppendList(k);
}
bool    Bool3List::Save(QIODevice *file)
{
	int32	N=GetNumber();
	if(file->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	for(Bool3Class *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(file)==false){
			return false;
		}
	}
	return true;
}
bool    Bool3List::Load(QIODevice *file)
{
	int32	N;
	if(file->read((char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		Bool3Class	*d=new Bool3Class();
		if(d->Load(file)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}

