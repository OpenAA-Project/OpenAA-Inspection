/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XIntClass.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------
#include "XIntClass.h"
#include "XTypeDef.h"
#include "XGeneralFuncCore.h"
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
bool    IntClass::Save(QIODevice *file)
{
	if(file->write((const char *)&Value,sizeof(Value))!=sizeof(Value)){
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
bool    IntClass::Load(QIODevice *file)
{
	if(file->read((char *)&Value,sizeof(Value))!=sizeof(Value)){
        return(false);
	}
    return(true);
}

int	IntClass::Compare(IntClass &src)
{
	int	k=GetValue()-src.GetValue();
	return k;
}
IntClass	IntClass::operator+()	const
{
	IntClass	Ret=*this;
	return Ret;
}
IntClass	IntClass::operator-()	const
{
	IntClass	Ret;
	Ret.Value=-Value;
	return Ret;
}
IntClass	IntClass::operator+(const IntClass &src)	const
{
	IntClass	Ret;
	Ret.Value=Value+src.Value;
	return Ret;
}
IntClass	IntClass::operator-(const IntClass &src)	const
{
	IntClass	Ret;
	Ret.Value=Value-src.Value;
	return Ret;
}
IntClass	IntClass::operator*(const IntClass &src)	const
{
	IntClass	Ret;
	Ret.Value=Value*src.Value;
	return Ret;
}
IntClass	IntClass::operator/(const IntClass &src)	const
{
	IntClass	Ret;
	Ret.Value=Value/src.Value;
	return Ret;
}
IntClass	IntClass::operator*(int m)	const
{
	IntClass	Ret;
	Ret.Value=Value*m;
	return Ret;
}
IntClass	IntClass::operator/(int m)	const
{
	IntClass	Ret;
	Ret.Value=Value/m;
	return Ret;
}
IntClass	IntClass::operator*(double m)	const
{
	IntClass	Ret;
	Ret.Value=Value*m;
	return Ret;
}
IntClass	IntClass::operator/(double m)	const
{
	IntClass	Ret;
	Ret.Value=Value/m;
	return Ret;
}
IntClass	&IntClass::operator+=(const IntClass &src)
{
	Value+=src.Value;
	return *this;
}
IntClass	&IntClass::operator-=(const IntClass &src)
{
	Value-=src.Value;
	return *this;
}
IntClass	&IntClass::operator*=(const IntClass &src)
{
	Value*=src.Value;
	return *this;
}
IntClass	&IntClass::operator/=(const IntClass &src)
{
	Value/=src.Value;
	return *this;
}
IntClass	&IntClass::operator*=(int m)
{
	Value*=m;
	return *this;
}
IntClass	&IntClass::operator/=(int m)
{
	Value/=m;
	return *this;
}
IntClass	&IntClass::operator*=(double m)
{
	Value*=m;
	return *this;
}
IntClass	&IntClass::operator/=(double m)
{
	Value/=m;
	return *this;
}
IntClass	&IntClass::operator++(void)
{
	Value++;
	return *this;
}
IntClass	&IntClass::operator--(void)
{
	Value--;
	return *this;
}

IntList::IntList(void)
{}
IntList::IntList(const IntList &src)
{
	RemoveAll();
	for(IntClass *s=(IntClass *)src.GetFirst();s!=NULL;s=(IntClass *)s->GetNext()){
		//IntClass	*d=new IntClass(s->GetValue());
		//AppendList(d);
		Add(s->GetValue());
	}
}

bool	IntList::IsInclude(int d)	const
{
	for(IntClass *s=(IntClass *)GetFirst();s!=NULL;s=(IntClass *)s->GetNext()){
		if(s->GetValue()==d){
			return true;
		}
	}
	return false;
}

void	IntList::Remove(int d)
{
	for(IntClass *s=(IntClass *)GetFirst();s!=NULL;){
		IntClass *NextS=(IntClass *)s->GetNext();
		if(s->GetValue()==d){
			RemoveList(s);
			//delete	s;
		}
		s=NextS;
	}
}

void	IntList::Merge(const IntList &src)
{
	for(IntClass *s=(IntClass *)src.GetFirst();s!=NULL;s=(IntClass *)s->GetNext()){
		if(IsInclude(s->GetValue())==false){
			Add(s->GetValue());
		}
	}
}
void	IntList::Merge(int d)
{
	for(IntClass *s=(IntClass *)GetFirst();s!=NULL;s=(IntClass *)s->GetNext()){
		if(s->GetValue()==d)
			return;
	}
	Add(d);
}

IntList	&IntList::operator=(IntList &src)
{
	RemoveAll();
	for(IntClass *s=(IntClass *)src.GetFirst();s!=NULL;s=(IntClass *)s->GetNext()){
		//IntClass	*d=new IntClass(s->GetValue());
		//AppendList(d);
		Add(s->GetValue());
	}
	return *this;
}
IntList	&IntList::operator=(const IntList &src)
{
	RemoveAll();
	return operator+=(src);
}

IntList	&IntList::operator+=(const IntList &src)
{
	for(IntClass *s=(IntClass *)src.GetFirst();s!=NULL;s=(IntClass *)s->GetNext()){
		//IntClass	*d=new IntClass(s->GetValue());
		//AppendList(d);
		Add(s->GetValue());
	}
	return *this;
}
bool	IntList::operator==(IntList &src) const
{
	IntClass *d=(IntClass *)GetFirst();
	IntClass *s=(IntClass *)src.GetFirst();
	for(;s!=NULL && d!=NULL;s=(IntClass *)s->GetNext(),d=(IntClass *)d->GetNext()){
		if(*s!=*d){
			return false;
		}
	}
	if(s!=NULL || d!=NULL){
		return false;
	}
	return true;
}
bool	IntList::operator==(const IntList& src) const
{
	IntClass* d = (IntClass *)GetFirst();
	IntClass* s = (IntClass *)src.GetFirst();
	for (; s != NULL && d != NULL; s = (IntClass *)s->GetNext(), d = (IntClass *)d->GetNext()) {
		if (*s != *d) {
			return false;
		}
	}
	if (s != NULL || d != NULL) {
		return false;
	}
	return true;
}
bool	IntList::operator!=(IntList &src) const
{
	return !operator==(src);
}
bool	IntList::operator!=(const IntList& src) const
{
	return !operator==(src);
}

int		IntList::operator[](int n)	const
{
	const IntClass	*c=(const IntClass *)GetItem(n);
	if(c!=NULL){
		return c->GetValue();
	}
	return -1;
}


bool    IntList::Save(QIODevice *file)
{
	int32	N=GetCount();
	if(file->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	for(IntClass *s=(IntClass *)GetFirst();s!=NULL;s=(IntClass *)s->GetNext()){
		if(s->Save(file)==false){
			return false;
		}
	}
	return true;
}
bool    IntList::Load(QIODevice *file)
{
	int32	N;
	if(file->read((char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		IntClass	d;
		if(d.Load(file)==false){
			return false;
		}
		Add(d.GetValue());
	}
	return true;
}

IntList	IntList::operator+()	const
{
	IntList	Ret=*this;
	return Ret;
}
IntList	IntList::operator-()	const
{
	IntList	Ret;
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		Ret.Add(-d->GetValue());
	}
	return Ret;
}
IntList	IntList::operator+(const IntList &src)	const
{
	IntList	Ret;
	IntClass *s=(IntClass *)src.GetFirst();
	IntClass *d=(IntClass *)GetFirst();
	for(;d!=NULL && s!=NULL;d=(IntClass *)d->GetNext(),s=(IntClass *)s->GetNext()){
		Ret.Add(s->GetValue()+d->GetValue());
	}
	for(;d!=NULL;d=(IntClass *)d->GetNext()){
		Ret.Add(d->GetValue());
	}
	for(;s!=NULL;s=(IntClass *)s->GetNext()){
		Ret.Add(s->GetValue());
	}
	return Ret;
}
IntList	IntList::operator-(const IntList &src)	const
{
	IntList	Ret;
	IntClass *s=(IntClass *)src.GetFirst();
	IntClass *d=(IntClass *)GetFirst();
	for(;d!=NULL && s!=NULL;d=(IntClass *)d->GetNext(),s=(IntClass *)s->GetNext()){
		Ret.Add(d->GetValue()-s->GetValue());
	}
	for(;d!=NULL;d=(IntClass *)d->GetNext()){
		Ret.Add(d->GetValue());
	}
	for(;s!=NULL;s=(IntClass *)s->GetNext()){
		Ret.Add(-s->GetValue());
	}
	return Ret;
}
IntList	IntList::operator*(const IntList &src)	const
{
	IntList	Ret;
	IntClass *s=(IntClass *)src.GetFirst();
	IntClass *d=(IntClass *)GetFirst();
	for(;d!=NULL && s!=NULL;d=(IntClass *)d->GetNext(),s=(IntClass *)s->GetNext()){
		Ret.Add(s->GetValue()*d->GetValue());
	}
	for(;d!=NULL;d=(IntClass *)d->GetNext()){
		Ret.Add(0);
	}
	for(;s!=NULL;s=(IntClass *)s->GetNext()){
		Ret.Add(0);
	}
	return Ret;
}
IntList	IntList::operator/(const IntList &src)	const
{
	IntList	Ret;
	IntClass *s=(IntClass *)src.GetFirst();
	IntClass *d=(IntClass *)GetFirst();
	for(;d!=NULL && s!=NULL;d=(IntClass *)d->GetNext(),s=(IntClass *)s->GetNext()){
		Ret.Add(d->GetValue()/s->GetValue());
	}
	for(;d!=NULL;d=(IntClass *)d->GetNext()){
		Ret.Add(0);
	}
	for(;s!=NULL;s=(IntClass *)s->GetNext()){
		Ret.Add(0);
	}
	return Ret;
}
IntList	IntList::operator*(int m)	const
{
	IntList	Ret;
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		Ret.Add(d->GetValue()*m);
	}

	return Ret;
}
IntList	IntList::operator/(int m)	const
{
	IntList	Ret;
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		Ret.Add(d->GetValue()/m);
	}

	return Ret;
}

IntList	IntList::operator*(double m)	const
{
	IntList	Ret;
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		Ret.Add(d->GetValue()*m);
	}

	return Ret;
}
IntList	IntList::operator/(double m)	const
{
	IntList	Ret;
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		Ret.Add(d->GetValue()/m);
	}

	return Ret;
}
IntList	&IntList::operator-=(const IntList &src)
{
	IntClass *s=(IntClass *)src.GetFirst();
	IntClass *d=(IntClass *)GetFirst();
	for(;d!=NULL && s!=NULL;d=(IntClass *)d->GetNext(),s=(IntClass *)s->GetNext()){
		d->SetValue(d->GetValue()-s->GetValue());
	}
	return *this;
}
IntList	&IntList::operator*=(const IntList &src)
{
	IntClass *s=(IntClass *)src.GetFirst();
	IntClass *d=(IntClass *)GetFirst();
	for(;d!=NULL && s!=NULL;d=(IntClass *)d->GetNext(),s=(IntClass *)s->GetNext()){
		d->SetValue(d->GetValue()*s->GetValue());
	}
	return *this;
}
IntList	&IntList::operator/=(const IntList &src)
{
	IntClass *s=(IntClass *)src.GetFirst();
	IntClass *d=(IntClass *)GetFirst();
	for(;d!=NULL && s!=NULL;d=(IntClass *)d->GetNext(),s=(IntClass *)s->GetNext()){
		d->SetValue(d->GetValue()/s->GetValue());
	}
	return *this;
}
IntList	&IntList::operator*=(int m)
{
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		d->SetValue(d->GetValue()*m);
	}
	return *this;
}
IntList	&IntList::operator/=(int m)
{
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		d->SetValue(d->GetValue()/m);
	}
	return *this;
}
IntList	&IntList::operator*=(double m)
{
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		d->SetValue(d->GetValue()*m);
	}
	return *this;
}
IntList	&IntList::operator/=(double m)
{
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		d->SetValue(d->GetValue()/m);
	}
	return *this;
}
IntList	&IntList::operator++(void)
{
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		d->SetValue(d->GetValue()+1);
	}
	return *this;
}
IntList	&IntList::operator--(void)
{
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext()){
		d->SetValue(d->GetValue()-1);
	}
	return *this;
}

int		IntList::GetMaxValue(int *Point)	const
{
	int	MaxValue=INT_MIN;
	int	n=0;
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext(),n++){
		if(MaxValue<d->GetValue()){
			MaxValue=d->GetValue();
			if(Point!=NULL){
				*Point=n;
			}
		}
	}
	return MaxValue;
}
int		IntList::GetMinValue(int *Point)	const
{
	int	MinValue=INT_MAX;
	int	n=0;
	for(IntClass *d=(IntClass *)GetFirst();d!=NULL;d=(IntClass *)d->GetNext(),n++){
		if(MinValue>d->GetValue()){
			MinValue=d->GetValue();
			if(Point!=NULL){
				*Point=n;
			}
		}
	}
	return MinValue;
}

IntListPointer::IntListPointer(void)
{}

IntListPointer::IntListPointer(const IntList &src)
	:IntList(src)
{}

IntListContainer::IntListContainer(void)
{}
IntListContainer::IntListContainer(const IntListContainer &src)
{
	RemoveAll();
	for(IntListPointer *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		IntListPointer	*d=new IntListPointer(*L);
		AppendList(d);
	}
}
void	IntListContainer::Add(const IntList &d)
{
	IntListPointer	*t=new IntListPointer(d);
	AppendList(t);
}
bool	IntListContainer::IsInclude(const IntList &d)
{
	for(IntListPointer *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(*L==d){
			return true;
		}
	}
	return false;
}
IntListContainer	&IntListContainer::operator=(IntListContainer &src)
{
	RemoveAll();
	for(IntListPointer *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		IntListPointer	*d=new IntListPointer(*L);
		AppendList(d);
	}
	return *this;
}
IntListContainer	&IntListContainer::operator=(const IntListContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
IntListContainer	&IntListContainer::operator+=(const IntListContainer &src)
{
	for(IntListPointer *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		IntListPointer	*d=new IntListPointer(*L);
		AppendList(d);
	}
	return *this;
}
bool	IntListContainer::operator==(IntListContainer &src) const
{
	IntListPointer *d=GetFirst();
	IntListPointer *s=src.GetFirst();
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
bool	IntListContainer::operator==(const IntListContainer& src) const
{
	IntListPointer *d=GetFirst();
	IntListPointer *s=src.GetFirst();
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
bool	IntListContainer::operator!=(IntListContainer &src) const
{
	return !operator==(src);
}
bool	IntListContainer::operator!=(const IntListContainer& src) const
{
	return !operator==(src);
}

bool    IntListContainer::Save(QIODevice *file)
{
	int32	N=GetNumber();
	if(file->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	for(IntListPointer *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(file)==false){
			return false;
		}
	}
	return true;
}
bool    IntListContainer::Load(QIODevice *file)
{
	int32	N;
	if(file->read((char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		IntListPointer	*d=new IntListPointer();
		if(d->Load(file)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}

IntListContainer	IntListContainer::operator+()	const
{
	IntListContainer	Ret=*this;
	return Ret;
}
IntListContainer	IntListContainer::operator-()	const
{
	IntListContainer	Ret;
	for(IntListPointer *d=GetFirst();d!=NULL;d=d->GetNext()){
		Ret.Add(-(*d));
	}
	return Ret;
}
IntListContainer	IntListContainer::operator+(const IntListContainer &src)	const
{
	IntListContainer	Ret;
	IntListPointer *s=src.GetFirst();
	IntListPointer *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		Ret.Add(*s+*d);
	}
	for(;d!=NULL;d=d->GetNext()){
		Ret.Add(*d);
	}
	for(;s!=NULL;s=s->GetNext()){
		Ret.Add(*s);
	}
	return Ret;
}
IntListContainer	IntListContainer::operator-(const IntListContainer &src)	const
{
	IntListContainer	Ret;
	IntListPointer *s=src.GetFirst();
	IntListPointer *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		Ret.Add(*d-*s);
	}
	for(;d!=NULL;d=d->GetNext()){
		Ret.Add(*d);
	}
	for(;s!=NULL;s=s->GetNext()){
		Ret.Add(-*s);
	}
	return Ret;
}
IntListContainer	IntListContainer::operator*(const IntListContainer &src)	const
{
	IntListContainer	Ret;
	IntListPointer *s=src.GetFirst();
	IntListPointer *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		Ret.Add((*s)*(*d));
	}
	for(;d!=NULL;d=d->GetNext()){
		Ret.AppendList(new IntListPointer());
	}
	for(;s!=NULL;s=s->GetNext()){
		Ret.AppendList(new IntListPointer());
	}
	return Ret;
}
IntListContainer	IntListContainer::operator/(const IntListContainer &src)	const
{
	IntListContainer	Ret;
	IntListPointer *s=src.GetFirst();
	IntListPointer *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		Ret.Add((*d)/(*s));
	}
	for(;d!=NULL;d=d->GetNext()){
		Ret.AppendList(new IntListPointer());
	}
	for(;s!=NULL;s=s->GetNext()){
		Ret.AppendList(new IntListPointer());
	}
	return Ret;
}
IntListContainer	IntListContainer::operator*(int m)	const
{
	IntListContainer	Ret;
	for(IntListPointer *d=GetFirst();d!=NULL;d=d->GetNext()){
		Ret.Add((*d)*m);
	}

	return Ret;
}
IntListContainer	IntListContainer::operator/(int m)	const
{
	IntListContainer	Ret;
	for(IntListPointer *d=GetFirst();d!=NULL;d=d->GetNext()){
		Ret.Add((*d)/m);
	}

	return Ret;
}

IntListContainer	IntListContainer::operator*(double m)	const
{
	IntListContainer	Ret;
	for(IntListPointer *d=GetFirst();d!=NULL;d=d->GetNext()){
		Ret.Add((*d)*m);
	}

	return Ret;
}
IntListContainer	IntListContainer::operator/(double m)	const
{
	IntListContainer	Ret;
	for(IntListPointer *d=GetFirst();d!=NULL;d=d->GetNext()){
		Ret.Add((*d)/m);
	}

	return Ret;
}
IntListContainer	&IntListContainer::operator-=(const IntListContainer &src)
{
	IntListPointer *s=src.GetFirst();
	IntListPointer *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		*d=((*d)-(*s));
	}
	return *this;
}
IntListContainer	&IntListContainer::operator*=(const IntListContainer &src)
{
	IntListPointer *s=src.GetFirst();
	IntListPointer *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		*d=((*d)*(*s));
	}
	return *this;
}
IntListContainer	&IntListContainer::operator/=(const IntListContainer &src)
{
	IntListPointer *s=src.GetFirst();
	IntListPointer *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		*d=((*d)/(*s));
	}
	return *this;
}
IntListContainer	&IntListContainer::operator*=(int m)
{
	for(IntListPointer *d=GetFirst();d!=NULL;d=d->GetNext()){
		*d=((*d)*m);
	}
	return *this;
}
IntListContainer	&IntListContainer::operator/=(int m)
{
	for(IntListPointer *d=GetFirst();d!=NULL;d=d->GetNext()){
		*d=((*d)/m);
	}
	return *this;
}
IntListContainer	&IntListContainer::operator*=(double m)
{
	for(IntListPointer *d=GetFirst();d!=NULL;d=d->GetNext()){
		*d=((*d)*m);
	}
	return *this;
}
IntListContainer	&IntListContainer::operator/=(double m)
{
	for(IntListPointer *d=GetFirst();d!=NULL;d=d->GetNext()){
		*d=((*d)/m);
	}
	return *this;
}


//===========================================================================
bool    IntDimClass::Save(QIODevice *file)
{
	return ::Save(file,d);
}

bool    IntDimClass::Load(QIODevice *file)
{
	return ::Load(file,d);
}


bool    IntDimClassPack::Save(QIODevice *file)
{
	int32	N=GetCount();
	if(::Save(file,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(GetItem(i)->Save(file)==false)
			return false;
	}
	return true;
}
bool    IntDimClassPack::Load(QIODevice *file)
{
	int32	N;
	if(::Load(file,N)==false)
		return false;
	RemoveAll();
	Allocate(N);
	for(int i=0;i<N;i++){
		if(GetItem(i)->Load(file)==false)
			return false;
	}
	return true;
}
//===========================================================

ListLayerAndID	&ListLayerAndID::operator=(const ListLayerAndID &src)
{
	Layer	=src.Layer;
	ID		=src.ID;
	return *this;
}
ListLayerAndID	&ListLayerAndID::operator=(const ListLayerIDLibName &src)
{
	Layer	=src.Layer;
	ID		=src.ID;
	return *this;
}

ListLayerAndID::ListLayerAndID(const ListLayerAndID &src)
{
	Layer	=src.Layer;
	ID		=src.ID;
}
ListLayerAndID::ListLayerAndID(const ListLayerIDLibName &src)
{
	operator=(src);
}
bool	ListLayerAndID::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ID)==false){
		return false;
	}
	return true;
}
bool	ListLayerAndID::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ID)==false){
		return false;
	}
	return true;
}

ListLayerAndIDPack::ListLayerAndIDPack(const ListLayerAndIDPack &src)
{
	for(ListLayerAndID *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListLayerAndID	*d=new ListLayerAndID(*s);
		AppendList(d);
	}
}

ListLayerAndIDPack	&ListLayerAndIDPack::operator=(const ListLayerAndIDPack &src)
{
	RemoveAll();
	return operator+=(src);
}

ListLayerAndIDPack	&ListLayerAndIDPack::operator+=(const ListLayerAndIDPack &src)
{
	for(ListLayerAndID *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListLayerAndID	*d=new ListLayerAndID(*s);
		AppendList(d);
	}
	return *this;
}
ListLayerAndIDPack	&ListLayerAndIDPack::operator=(const ListLayerIDLibNamePack &src)
{
	RemoveAll();
	for(ListLayerIDLibName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListLayerAndID	*d=new ListLayerAndID();
		d->Layer=s->Layer;
		d->ID	=s->ID;
		AppendList(d);
	}
	return *this;
}
bool	ListLayerAndIDPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ListLayerAndID *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ListLayerAndIDPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ListLayerAndID	*d=new ListLayerAndID();
		if(d->Load(f)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}
void	ListLayerAndIDPack::MakeIDList(int Layer ,IntList &IDList)
{
	IDList.RemoveAll();
	for(ListLayerAndID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Layer==Layer){
			IDList.Add(a->ID);
		}
	}
}

//===========================================================
ListPageLayerID::ListPageLayerID(const ListPageLayerID &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
	ID		=src.ID;
}
ListPageLayerID &ListPageLayerID::operator=(ListPageLayerID &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
	ID		=src.ID;
	return *this;
}
bool	ListPageLayerID::Save(QIODevice *f)
{
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ID)==false){
		return false;
	}
	return true;
}
bool	ListPageLayerID::Load(QIODevice *f)
{
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ID)==false){
		return false;
	}
	return true;
}


ListPageLayerIDPack::ListPageLayerIDPack(const ListPageLayerIDPack &src)
{
	Table=NULL;
	for(ListPageLayerID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPageLayerID	*b=new ListPageLayerID(*a);
		AppendList(b);
	}
}
ListPageLayerIDPack::~ListPageLayerIDPack(void)
{
	if(Table!=NULL){
		delete	[]Table;
		Table=NULL;
	}
}
ListPageLayerIDPack	&ListPageLayerIDPack::operator=(ListPageLayerIDPack &src)
{
	RemoveAll();
	return operator+=(src);
}
ListPageLayerIDPack	&ListPageLayerIDPack::operator+=(ListPageLayerIDPack &src)
{
	for(ListPageLayerID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPageLayerID	*b=new ListPageLayerID(*a);
		AppendList(b);
	}
	return *this;
}
bool	ListPageLayerIDPack::IsInclude(int Page, int Layer ,int ID)
{
	for(ListPageLayerID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==Page && a->Layer==Layer && a->ID==ID){
			return true;
		}
	}
	return false;
}
	
void	ListPageLayerIDPack::Add		(int page ,int Layer ,int id)
{
	ListPageLayerID	*a=new ListPageLayerID(page,Layer,id);
	AppendList(a);
}

void	ListPageLayerIDPack::Merge	(int page ,int Layer ,int id)
{
	for(ListPageLayerID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==page && a->Layer==Layer && a->ID==id){
			return;
		}
	}
	ListPageLayerID	*a=new ListPageLayerID(page,Layer,id);
	AppendList(a);
}
void	ListPageLayerIDPack::Merge	(const ListPageLayerIDPack &src)
{
	for(ListPageLayerID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		bool	Found=false;
		for(ListPageLayerID *b=GetFirst();b!=NULL;b=b->GetNext()){
			if(a->Page==b->Page && a->Layer==b->Layer && a->ID==b->ID){
				Found=true;
				break;
			}
		}
		if(Found==false){
			ListPageLayerID	*b=new ListPageLayerID(a->Page,a->Layer,a->ID);
			AppendList(b);
		}
	}
}
void	ListPageLayerIDPack::Merge	(const ListPageLayerID &src)
{
	for(ListPageLayerID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==src.Page && a->Layer==src.Layer && a->ID==src.ID){
			return;
		}
	}
	ListPageLayerID	*a=new ListPageLayerID(src.Page,src.Layer,src.ID);
	AppendList(a);
}
void	ListPageLayerIDPack::Move(ListPageLayerIDPack &src)
{
	NPListPack<ListPageLayerID>::Move(src);
	MaxPage	=src.MaxPage;
	MaxLayer=src.MaxLayer;
	MaxID	=src.MaxID;
	MinPage	=src.MinPage;
	MinLayer=src.MinLayer;
	MinID	=src.MinID;
}
void	ListPageLayerIDPack::MakeIDList(int Layer ,IntList &IDList)
{
	IDList.RemoveAll();
	for(ListPageLayerID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Layer==Layer){
			IDList.Add(a->ID);
		}
	}
}
void	ListPageLayerIDPack::MakeIDList(int Page,int Layer ,IntList &IDList)
{
	IDList.RemoveAll();
	for(ListPageLayerID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==Page && a->Layer==Layer){
			IDList.Add(a->ID);
		}
	}
}

bool	ListPageLayerIDPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ListPageLayerID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ListPageLayerIDPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ListPageLayerID *a=new ListPageLayerID();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

void	ListPageLayerIDPack::MakeLinearDim(void)
{
	if(GetCount()==0)
		return;
	MaxPage	=0;
	MaxLayer=0;
	MaxID	=0;
	MinPage	=99999999;
	MinLayer=99999999;
	MinID	=99999999;
	for(ListPageLayerID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page>MaxPage)
			MaxPage=a->Page;
		if(a->Page<MinPage)
			MinPage=a->Page;
		if(a->Layer>MaxLayer)
			MaxLayer=a->Layer;
		if(a->Layer<MinLayer)
			MinLayer=a->Layer;
		if(a->ID>MaxID)
			MaxID=a->ID;
		if(a->ID<MinID)
			MinID=a->ID;
	}
	int	N=(MaxPage-MinPage+1)*(MaxLayer-MinLayer+1)*(MaxID-MinLayer+1);
	if(N<=0)
		return;
	if(Table!=NULL){
		delete	[]Table;
	}
	Table=new bool[N];
	for(int i=0;i<N;i++){
		Table[i]=false;
	}

	for(ListPageLayerID *a=GetFirst();a!=NULL;a=a->GetNext()){
		int	Index=(a->Page-MinPage)*(MaxLayer-MinLayer+1)*(MaxID-MinLayer+1)
				+ (a->Layer-MinLayer)*(MaxID-MinLayer+1)
				+ (a->ID-MinID);
		Table[Index]=true;
	}
}

bool	ListPageLayerIDPack::IsIncludeByLinear(int Page, int Layer ,int ID)
{
	if(Page>MaxPage || Layer>MaxLayer || ID>MaxID)
		return false;
	if(Page<MinPage || Layer<MinLayer || ID<MinID)
		return false;

	int	Index=(Page-MinPage)*(MaxLayer-MinLayer+1)*(MaxID-MinLayer+1)
			+ (Layer-MinLayer)*(MaxID-MinLayer+1)
			+ (ID-MinID);
	return Table[Index];
}


//===========================================================
ListPageLayer::ListPageLayer(const ListPageLayer &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
}
ListPageLayer &ListPageLayer::operator=(const ListPageLayer &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
	return *this;
}
bool	ListPageLayer::Save(QIODevice *f)
{
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}
bool	ListPageLayer::Load(QIODevice *f)
{
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}

ListPageLayerPack::ListPageLayerPack(const ListPageLayerPack &src)
{
	for(ListPageLayer *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPageLayer	*b=new ListPageLayer(*a);
		AppendList(b);
	}
}

ListPageLayerPack	&ListPageLayerPack::operator=(const ListPageLayerPack &src)
{
	RemoveAll();
	return operator+=(src);
}
ListPageLayerPack	&ListPageLayerPack::operator+=(const ListPageLayerPack &src)
{
	for(ListPageLayer *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPageLayer	*b=new ListPageLayer(*a);
		AppendList(b);
	}
	return *this;
}
bool	ListPageLayerPack::IsInclude(int Page, int Layer)
{
	for(ListPageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==Page && a->Layer==Layer){
			return true;
		}
	}
	return false;
}
	
void	ListPageLayerPack::Add		(int page ,int Layer)
{
	ListPageLayer	*a=new ListPageLayer(page,Layer);
	AppendList(a);
}

void	ListPageLayerPack::Merge	(int page ,int Layer)
{
	for(ListPageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==page && a->Layer==Layer){
			return;
		}
	}
	ListPageLayer	*a=new ListPageLayer(page,Layer);
	AppendList(a);
}
void	ListPageLayerPack::Merge	(const ListPageLayerPack &src)
{
	for(ListPageLayer *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		bool	Found=false;
		for(ListPageLayer *b=GetFirst();b!=NULL;b=b->GetNext()){
			if(a->Page==b->Page && a->Layer==b->Layer){
				Found=true;
				break;
			}
		}
		if(Found==false){
			ListPageLayer	*b=new ListPageLayer(a->Page,a->Layer);
			AppendList(b);
		}
	}
}
void	ListPageLayerPack::Merge	(const ListPageLayer &src)
{
	for(ListPageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==src.Page && a->Layer==src.Layer){
			return;
		}
	}
	ListPageLayer	*a=new ListPageLayer(src.Page,src.Layer);
	AppendList(a);
}
bool	ListPageLayerPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ListPageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ListPageLayerPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ListPageLayer *a=new ListPageLayer();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
void	ListPageLayerPack::GetPageList(IntList &PageList)
{
	for(ListPageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		PageList.Merge(a->Page);
	}
}
void	ListPageLayerPack::GetLayer(int page ,IntList &LayerList)
{
	for(ListPageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==page){
			LayerList.Merge(a->Layer);
		}
	}
}
//===========================================================
ListPageID::ListPageID(const ListPageLayerID &src)
{
	Page	=src.Page;
	ID		=src.ID;
}
ListPageID::ListPageID(const ListPageID &src)
{
	Page	=src.Page;
	ID		=src.ID;
}
ListPageID &ListPageID::operator=(const ListPageID &src)
{
	Page	=src.Page;
	ID		=src.ID;
	return *this;
}
bool	ListPageID::Save(QIODevice *f)
{
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,ID)==false){
		return false;
	}
	return true;
}
bool	ListPageID::Load(QIODevice *f)
{
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,ID)==false){
		return false;
	}
	return true;
}


ListPageIDPack::ListPageIDPack(const ListPageIDPack &src)
{
	for(ListPageID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPageID	*b=new ListPageID();
		*b=*a;
		AppendList(b);
	}
}

ListPageIDPack	&ListPageIDPack::operator=(const ListPageIDPack &src)
{
	RemoveAll();
	return operator+=(src);
}
ListPageIDPack	&ListPageIDPack::operator+=(const ListPageIDPack &src)
{
	for(ListPageID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPageID	*b=new ListPageID();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
bool	ListPageIDPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ListPageID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ListPageIDPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ListPageID *a=new ListPageID();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
bool	ListPageIDPack::IsInclude(int page,int id)
{
	for(ListPageID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==page && a->ID==id)
			return true;
	}
	return false;
}
void	ListPageIDPack::Add(int page ,int id)
{
	ListPageID	*a=new ListPageID(page,id);
	AppendList(a);
}
void	ListPageIDPack::Merge	(int page ,int id)
{
	for(ListPageID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==page && a->ID==id)
			return;
	}
	ListPageID	*a=new ListPageID(page,id);
	AppendList(a);
}
void	ListPageIDPack::Merge	(const ListPageIDPack &src)
{
	for(ListPageID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		bool	Found=false;
		for(ListPageID *b=GetFirst();b!=NULL;b=b->GetNext()){
			if(a->Page==b->Page && a->ID==b->ID){
				Found=true;
				break;
			}
		}
		if(Found==false){
			ListPageID	*b=new ListPageID(a->Page,a->ID);
			AppendList(b);
		}
	}
}
void	ListPageIDPack::Merge	(const ListPageID &src)
{
	for(ListPageID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==src.Page && a->ID==src.ID)
			return;
	}
	ListPageID	*a=new ListPageID(src.Page,src.ID);
	AppendList(a);
}
void	ListPageIDPack::MakeIDList(int page ,IntList &IDList)
{
	IDList.RemoveAll();
	for(ListPageID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==page){
			IDList.Add(a->ID);
		}
	}
}

//===========================================================
ListPhasePageID::ListPhasePageID(const ListPageLayerID &src)
{
	Phase	=0;
	Page	=src.Page;
	ID		=src.ID;
}
ListPhasePageID::ListPhasePageID(const ListPhasePageID &src)
{
	Phase	=src.Phase;
	Page	=src.Page;
	ID		=src.ID;
}
ListPhasePageID &ListPhasePageID::operator=(const ListPhasePageID &src)
{
	Phase	=src.Phase;
	Page	=src.Page;
	ID		=src.ID;
	return *this;
}
bool	ListPhasePageID::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,ID)==false){
		return false;
	}
	return true;
}
bool	ListPhasePageID::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,ID)==false){
		return false;
	}
	return true;
}


ListPhasePageIDPack::ListPhasePageIDPack(const ListPhasePageIDPack &src)
{
	for(ListPhasePageID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPhasePageID	*b=new ListPhasePageID();
		*b=*a;
		AppendList(b);
	}
}

ListPhasePageIDPack	&ListPhasePageIDPack::operator=(const ListPhasePageIDPack &src)
{
	RemoveAll();
	return operator+=(src);
}
ListPhasePageIDPack	&ListPhasePageIDPack::operator+=(const ListPhasePageIDPack &src)
{
	for(ListPhasePageID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPhasePageID	*b=new ListPhasePageID();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
bool	ListPhasePageIDPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ListPhasePageID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ListPhasePageIDPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ListPhasePageID *a=new ListPhasePageID();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
bool	ListPhasePageIDPack::IsInclude(int phase ,int page,int id)
{
	for(ListPhasePageID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Phase==phase && a->Page==page && a->ID==id)
			return true;
	}
	return false;
}
void	ListPhasePageIDPack::Add(int phase,int page ,int id)
{
	ListPhasePageID	*a=new ListPhasePageID(phase,page,id);
	AppendList(a);
}
void	ListPhasePageIDPack::Merge	(int phase ,int page ,int id)
{
	for(ListPhasePageID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==page && a->ID==id)
			return;
	}
	ListPhasePageID	*a=new ListPhasePageID(phase,page,id);
	AppendList(a);
}
void	ListPhasePageIDPack::Merge	(const ListPhasePageIDPack &src)
{
	for(ListPhasePageID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		bool	Found=false;
		for(ListPhasePageID *b=GetFirst();b!=NULL;b=b->GetNext()){
			if(a->Phase==b->Phase && a->Page==b->Page && a->ID==b->ID){
				Found=true;
				break;
			}
		}
		if(Found==false){
			ListPhasePageID	*b=new ListPhasePageID(a->Phase,a->Page,a->ID);
			AppendList(b);
		}
	}
}
void	ListPhasePageIDPack::Merge	(const ListPhasePageID &src)
{
	for(ListPhasePageID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Page==src.Page && a->ID==src.ID)
			return;
	}
	ListPhasePageID	*a=new ListPhasePageID(src.Phase,src.Page,src.ID);
	AppendList(a);
}
void	ListPhasePageIDPack::MakeIDList(int Phase,int page ,IntList &IDList)
{
	IDList.RemoveAll();
	for(ListPhasePageID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Phase==Phase && a->Page==page){
			IDList.Add(a->ID);
		}
	}
}

//==============================================================

IntListFast::IntListFast(void)
{
	Dim				=NULL;
	AllocatedByte	=0;
}
IntListFast::IntListFast(const IntListFast &src)
	:IntList(*((const IntList *)&src))
{
	AllocatedByte=src.AllocatedByte;
	Dim=new BYTE[AllocatedByte];
	memcpy(Dim,src.Dim,src.AllocatedByte);
	memset(&Dim[src.AllocatedByte],0,AllocatedByte-src.AllocatedByte);
}
IntListFast::~IntListFast(void)
{
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	AllocatedByte	=0;
}

bool	IntListFast::IsInclude(int d)	const
{
	if(d<0)
		return false;
	int	n=d>>3;
	if(n>=AllocatedByte)
		return false;
	if((Dim[n] & (0x01<<(d&7)))==0)
		return false;
	return true;
}
void	IntListFast::Add(int d)
{
	if(d<0){
		return;
	}
	IntList::Add(d);
	if(AllocatedByte<=((d+7)>>3)){
		int		tAllocatedByte=((d+7)>>3)+100;
		BYTE	*tDim=new BYTE[tAllocatedByte];
		if(Dim!=NULL){
			memcpy(tDim,Dim,AllocatedByte);
			delete	[]Dim;
		}
		memset(&tDim[AllocatedByte],0,tAllocatedByte-AllocatedByte);
		Dim=tDim;
		AllocatedByte=tAllocatedByte;
	}
	Dim[d>>3] |= 0x01<<(d&7);
}

IntListFast	&IntListFast::operator=(const IntList &src)
{
	if(this!=&src){
		RemoveAll();
		for(IntClass *v=(IntClass *)src.GetFirst();v!=NULL;v=(IntClass *)v->GetNext()){
			Add(v->GetValue());
		}
	}
	return *this;
}

IntListFast	&IntListFast::operator=(const IntListFast &src)
{
	if(this!=&src){
		IntList::operator=(*((IntList *)&src));
		if(AllocatedByte<src.AllocatedByte){
			delete	[]Dim;
			AllocatedByte=src.AllocatedByte;
			Dim=new BYTE[AllocatedByte];
		}
		memcpy(Dim,src.Dim,src.AllocatedByte);
		memset(&Dim[src.AllocatedByte],0,AllocatedByte-src.AllocatedByte);
	}
	return *this;
}
IntListFast	&IntListFast::operator+=(const IntListFast &src)
{
	IntList::operator+=(*((IntList *)&src));
	if(AllocatedByte<src.AllocatedByte){
		delete	[]Dim;
		AllocatedByte=src.AllocatedByte;
		Dim=new BYTE[AllocatedByte];
	}
	memcpy(Dim,src.Dim,src.AllocatedByte);
	memset(&Dim[src.AllocatedByte],0,AllocatedByte-src.AllocatedByte);
	return *this;
}
bool	IntListFast::operator==(IntListFast &src) const
{
	int	i;
	for(i=0;i<AllocatedByte && i<src.AllocatedByte;i++){
		if(Dim[i]!=src.Dim[i])
			return false;
	}
	for(;i<AllocatedByte;i++){
		if(Dim[i]!=0)
			return false;
	}
	for(;i<src.AllocatedByte;i++){
		if(src.Dim[i]!=0)
			return false;
	}
	return true;
}
bool	IntListFast::operator!=(IntListFast &src) const
{
	return !operator==(src);
}


bool    IntListFast::Save(QIODevice *file)
{
	if(IntList::Save(file)==false)
		return false;
	if(::Save(file,AllocatedByte)==false)
		return false;
	if(file->write((const char *)Dim,AllocatedByte)!=AllocatedByte)
		return false;
	return true;
}
bool    IntListFast::Load(QIODevice *file)
{
	if(IntList::Load(file)==false)
		return false;
	int32	tAllocatedByte;
	if(::Load(file,tAllocatedByte)==false)
			return false;
	if(tAllocatedByte>AllocatedByte){
		delete	[]Dim;
		Dim=new BYTE[tAllocatedByte];
	}
	AllocatedByte=tAllocatedByte;
	if(file->read((char *)Dim,AllocatedByte)!=AllocatedByte)
		return false;
	return true;
}
//===========================================================

ListLayerIDLibName	&ListLayerIDLibName::operator=(const ListLayerIDLibName &src)
{
	Layer	=src.Layer;
	ID		=src.ID;
	LibID	=src.LibID;
	ItemName=src.ItemName;
	return *this;
}

ListLayerIDLibName::ListLayerIDLibName(const ListLayerIDLibName &src)
{
	Layer	=src.Layer;
	ID		=src.ID;
	LibID	=src.LibID;
	ItemName=src.ItemName;
}
bool	ListLayerIDLibName::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ID)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,ItemName)==false){
		return false;
	}
	return true;
}
bool	ListLayerIDLibName::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ID)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,ItemName)==false){
		return false;
	}
	return true;
}

ListLayerIDLibNamePack::ListLayerIDLibNamePack(const ListLayerIDLibNamePack &src)
{
	for(ListLayerIDLibName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListLayerIDLibName	*d=new ListLayerIDLibName(*s);
		AppendList(d);
	}
}

ListLayerIDLibNamePack	&ListLayerIDLibNamePack::operator=(const ListLayerIDLibNamePack &src)
{
	RemoveAll();
	for(ListLayerIDLibName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListLayerIDLibName	*d=new ListLayerIDLibName(*s);
		AppendList(d);
	}
	return *this;
}

ListLayerIDLibNamePack	&ListLayerIDLibNamePack::operator+=(const ListLayerIDLibNamePack &src)
{
	for(ListLayerIDLibName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListLayerIDLibName	*d=new ListLayerIDLibName(*s);
		AppendList(d);
	}
	return *this;
}

bool	ListLayerIDLibNamePack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ListLayerIDLibName *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ListLayerIDLibNamePack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ListLayerIDLibName	*d=new ListLayerIDLibName();
		if(d->Load(f)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}

//===========================================================

ListPageLayerIDLibName	&ListPageLayerIDLibName::operator=(const ListPageLayerIDLibName &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
	ID		=src.ID;
	LibID	=src.LibID;
	ItemName=src.ItemName;
	return *this;
}

ListPageLayerIDLibName::ListPageLayerIDLibName(const ListPageLayerIDLibName &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
	ID		=src.ID;
	LibID	=src.LibID;
	ItemName=src.ItemName;
}
bool	ListPageLayerIDLibName::Save(QIODevice *f)
{
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ID)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,ItemName)==false){
		return false;
	}
	return true;
}
bool	ListPageLayerIDLibName::Load(QIODevice *f)
{
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ID)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,ItemName)==false){
		return false;
	}
	return true;
}

ListPageLayerIDLibNamePack::ListPageLayerIDLibNamePack(const ListPageLayerIDLibNamePack &src)
{
	for(ListPageLayerIDLibName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListPageLayerIDLibName	*d=new ListPageLayerIDLibName(*s);
		AppendList(d);
	}
}

ListPageLayerIDLibNamePack	&ListPageLayerIDLibNamePack::operator=(const ListPageLayerIDLibNamePack &src)
{
	RemoveAll();
	for(ListPageLayerIDLibName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListPageLayerIDLibName	*d=new ListPageLayerIDLibName(*s);
		AppendList(d);
	}
	return *this;
}

ListPageLayerIDLibNamePack	&ListPageLayerIDLibNamePack::operator+=(const ListPageLayerIDLibNamePack &src)
{
	for(ListPageLayerIDLibName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListPageLayerIDLibName	*d=new ListPageLayerIDLibName(*s);
		AppendList(d);
	}
	return *this;
}

bool	ListPageLayerIDLibNamePack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ListPageLayerIDLibName *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ListPageLayerIDLibNamePack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ListPageLayerIDLibName	*d=new ListPageLayerIDLibName();
		if(d->Load(f)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}

//===========================================================

ListPhasePageLayer::ListPhasePageLayer(const ListPhasePageLayer &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
	Phase	=src.Phase;
}
ListPhasePageLayer &ListPhasePageLayer::operator=(const ListPhasePageLayer &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
	Phase	=src.Phase;
	return *this;
}
bool	ListPhasePageLayer::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}
bool	ListPhasePageLayer::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}


ListPhasePageLayerPack::ListPhasePageLayerPack(const ListPhasePageLayerPack &src)
{
	for(ListPhasePageLayer *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPhasePageLayer	*b=new ListPhasePageLayer(*a);
		AppendList(b);
	}
}

ListPhasePageLayerPack	&ListPhasePageLayerPack::operator=(const ListPhasePageLayerPack &src)
{
	RemoveAll();
	return operator+=(src);
}
ListPhasePageLayerPack	&ListPhasePageLayerPack::operator+=(const ListPhasePageLayerPack &src)
{
	for(ListPhasePageLayer *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPhasePageLayer	*b=new ListPhasePageLayer(*a);
		AppendList(b);
	}
	return *this;
}
bool	ListPhasePageLayerPack::IsInclude(int Phase,int Page, int Layer)
{
	for(ListPhasePageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Phase==Phase && a->Page==Page && a->Layer==Layer){
			return true;
		}
	}
	return false;
}
	
void	ListPhasePageLayerPack::Add	(int Phase ,int page ,int Layer)
{
	ListPhasePageLayer	*a=new ListPhasePageLayer(Phase,page,Layer);
	AppendList(a);
}

void	ListPhasePageLayerPack::Merge	(int Phase ,int page ,int Layer)
{
	for(ListPhasePageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Phase==Phase && a->Page==page && a->Layer==Layer){
			return;
		}
	}
	ListPhasePageLayer	*a=new ListPhasePageLayer(Phase,page,Layer);
	AppendList(a);
}
void	ListPhasePageLayerPack::Merge	(const ListPhasePageLayerPack &src)
{
	for(ListPhasePageLayer *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		bool	Found=false;
		for(ListPhasePageLayer *b=GetFirst();b!=NULL;b=b->GetNext()){
			if(a->Phase==b->Phase && a->Page==b->Page && a->Layer==b->Layer){
				Found=true;
				break;
			}
		}
		if(Found==false){
			ListPhasePageLayer	*b=new ListPhasePageLayer(a->Phase,a->Page,a->Layer);
			AppendList(b);
		}
	}
}

void	ListPhasePageLayerPack::Merge	(const ListPhasePageLayer &src)
{
	for(ListPhasePageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Phase==src.Phase && a->Page==src.Page && a->Layer==src.Layer){
			return;
		}
	}
	ListPhasePageLayer	*a=new ListPhasePageLayer(src.Phase,src.Page,src.Layer);
	AppendList(a);
}
bool	ListPhasePageLayerPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ListPhasePageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ListPhasePageLayerPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ListPhasePageLayer *a=new ListPhasePageLayer();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
void	ListPhasePageLayerPack::GetPhaseList(IntList &PhaseList)
{
	for(ListPhasePageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		PhaseList.Merge(a->Phase);
	}
}
void	ListPhasePageLayerPack::GetPageLayer(int Phase,ListPageLayerPack &PageLayer)
{
	for(ListPhasePageLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Phase==Phase){
			PageLayer.Merge(a->Page,a->Layer);
		}
	}
}
//===========================================================

ListPhasePageLayerItem::ListPhasePageLayerItem(const ListPhasePageLayerItem &src)
{
	Data	=src.Data;
}
ListPhasePageLayerItem &ListPhasePageLayerItem::operator=(const ListPhasePageLayerItem &src)
{
	Data	=src.Data;
	return *this;
}
bool	ListPhasePageLayerItem::operator==(const ListPhasePageLayerItem &src)	const
{
	if(Data.Phase ==src.Data.Phase
	&& Data.Page  ==src.Data.Page
	&& Data.Layer ==src.Data.Layer
	&& Data.ItemID==src.Data.ItemID){
		return true;
	}
	return false;
}
bool	ListPhasePageLayerItem::operator!=(const ListPhasePageLayerItem &src)	const
{
	return !operator==(src);
}
bool	ListPhasePageLayerItem::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	return true;
}
bool	ListPhasePageLayerItem::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	return true;
}


ListPhasePageLayerItemPack::ListPhasePageLayerItemPack(const ListPhasePageLayerItemPack &src)
{
	for(ListPhasePageLayerItem *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPhasePageLayerItem	*b=new ListPhasePageLayerItem(*a);
		AppendList(b);
	}
}

ListPhasePageLayerItemPack	&ListPhasePageLayerItemPack::operator=(const ListPhasePageLayerItemPack &src)
{
	RemoveAll();
	return operator+=(src);
}
ListPhasePageLayerItemPack	&ListPhasePageLayerItemPack::operator+=(const ListPhasePageLayerItemPack &src)
{
	for(ListPhasePageLayerItem *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPhasePageLayerItem	*b=new ListPhasePageLayerItem(*a);
		AppendList(b);
	}
	return *this;
}
bool	ListPhasePageLayerItemPack::IsInclude(int Phase,int Page, int Layer,int ItemID)
{
	for(ListPhasePageLayerItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Data.Phase==Phase && a->Data.Page==Page && a->Data.Layer==Layer && a->Data.ItemID==ItemID){
			return true;
		}
	}
	return false;
}
	
void	ListPhasePageLayerItemPack::Add	(int Phase ,int page ,int Layer ,int ItemID)
{
	ListPhasePageLayerItem	*a=new ListPhasePageLayerItem(Phase,page,Layer,ItemID);
	AppendList(a);
}

void	ListPhasePageLayerItemPack::Merge	(int Phase ,int page ,int Layer ,int ItemID)
{
	for(ListPhasePageLayerItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Data.Phase==Phase && a->Data.Page==page && a->Data.Layer==Layer && a->Data.ItemID==ItemID){
			return;
		}
	}
	ListPhasePageLayerItem	*a=new ListPhasePageLayerItem(Phase,page,Layer,ItemID);
	AppendList(a);
}
void	ListPhasePageLayerItemPack::Merge	(const ListPhasePageLayerItemPack &src)
{
	for(ListPhasePageLayerItem *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		bool	Found=false;
		for(ListPhasePageLayerItem *b=GetFirst();b!=NULL;b=b->GetNext()){
			if(a->Data.Phase==b->Data.Phase && a->Data.Page==b->Data.Page && a->Data.Layer==b->Data.Layer && a->Data.ItemID==b->Data.ItemID){
				Found=true;
				break;
			}
		}
		if(Found==false){
			ListPhasePageLayerItem	*b=new ListPhasePageLayerItem(a->Data.Phase,a->Data.Page,a->Data.Layer,a->Data.ItemID);
			AppendList(b);
		}
	}
}
void	ListPhasePageLayerItemPack::Merge	(const ListPhasePageLayerItem &src)
{
	for(ListPhasePageLayerItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Data.Phase==src.Data.Phase 
		&& a->Data.Page==src.Data.Page
		&& a->Data.Layer==src.Data.Layer
		&& a->Data.ItemID==src.Data.ItemID){
			return;
		}
	}
	ListPhasePageLayerItem	*a=new ListPhasePageLayerItem(src.Data.Phase,src.Data.Page,src.Data.Layer,src.Data.ItemID);
	AppendList(a);
}
bool	ListPhasePageLayerItemPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ListPhasePageLayerItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ListPhasePageLayerItemPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ListPhasePageLayerItem *a=new ListPhasePageLayerItem();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
void	ListPhasePageLayerItemPack::GetPhaseList(IntList &PhaseList)
{
	for(ListPhasePageLayerItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		PhaseList.Merge(a->Data.Phase);
	}
}
void	ListPhasePageLayerItemPack::GetPageLayer(int Phase,ListPageLayerPack &PageLayer)
{
	for(ListPhasePageLayerItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Data.Phase==Phase){
			PageLayer.Merge(a->Data.Page,a->Data.Layer);
		}
	}
}


//===========================================================

ListPhasePageLayerLibID::ListPhasePageLayerLibID(const ListPhasePageLayerLibID &src)
{
	Data	=src.Data;
	ItemIDs	=src.ItemIDs;
}
ListPhasePageLayerLibID &ListPhasePageLayerLibID::operator=(const ListPhasePageLayerLibID &src)
{
	Data	=src.Data;
	ItemIDs	=src.ItemIDs;
	return *this;
}
bool	ListPhasePageLayerLibID::operator==(const ListPhasePageLayerLibID &src)	const
{
	if(Data.Phase ==src.Data.Phase
	&& Data.Page  ==src.Data.Page
	&& Data.Layer ==src.Data.Layer
	&& Data.LibID ==src.Data.LibID
	&& ItemIDs	  ==src.ItemIDs){
		return true;
	}
	return false;
}
bool	ListPhasePageLayerLibID::operator!=(const ListPhasePageLayerLibID &src)	const
{
	return !operator==(src);
}
bool	ListPhasePageLayerLibID::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	if(ItemIDs.Save(f)==false){
		return false;
	}
	return true;
}
bool	ListPhasePageLayerLibID::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	if(ItemIDs.Load(f)==false){
		return false;
	}
	return true;
}


ListPhasePageLayerLibIDPack::ListPhasePageLayerLibIDPack(const ListPhasePageLayerLibIDPack &src)
{
	for(ListPhasePageLayerLibID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPhasePageLayerLibID	*b=new ListPhasePageLayerLibID(*a);
		AppendList(b);
	}
}

ListPhasePageLayerLibIDPack	&ListPhasePageLayerLibIDPack::operator=(const ListPhasePageLayerLibIDPack &src)
{
	RemoveAll();
	return operator+=(src);
}
ListPhasePageLayerLibIDPack	&ListPhasePageLayerLibIDPack::operator+=(const ListPhasePageLayerLibIDPack &src)
{
	for(ListPhasePageLayerLibID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListPhasePageLayerLibID	*b=new ListPhasePageLayerLibID(*a);
		AppendList(b);
	}
	return *this;
}
bool	ListPhasePageLayerLibIDPack::IsInclude(int Phase,int Page, int Layer,int LibID)
{
	for(ListPhasePageLayerLibID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Data.Phase==Phase && a->Data.Page==Page && a->Data.Layer==Layer && a->Data.LibID==LibID){
			return true;
		}
	}
	return false;
}
	
void	ListPhasePageLayerLibIDPack::Add	(int Phase ,int page ,int Layer ,int LibID)
{
	ListPhasePageLayerLibID	*a=new ListPhasePageLayerLibID(Phase,page,Layer,LibID);
	AppendList(a);
}

void	ListPhasePageLayerLibIDPack::Merge	(int Phase ,int page ,int Layer ,int LibID)
{
	for(ListPhasePageLayerLibID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Data.Phase==Phase && a->Data.Page==page && a->Data.Layer==Layer && a->Data.LibID==LibID){
			return;
		}
	}
	ListPhasePageLayerLibID	*a=new ListPhasePageLayerLibID(Phase,page,Layer,LibID);
	AppendList(a);
}
void	ListPhasePageLayerLibIDPack::Merge	(ListPhasePageLayerLibIDPack &src)
{
	for(ListPhasePageLayerLibID *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		bool	Found=false;
		for(ListPhasePageLayerLibID *b=GetFirst();b!=NULL;b=b->GetNext()){
			if(a->Data.Phase==b->Data.Phase && a->Data.Page==b->Data.Page && a->Data.Layer==b->Data.Layer && a->Data.LibID==b->Data.LibID){
				Found=true;
				break;
			}
		}
		if(Found==false){
			ListPhasePageLayerLibID	*b=new ListPhasePageLayerLibID(a->Data.Phase,a->Data.Page,a->Data.Layer,a->Data.LibID);
			AppendList(b);
		}
	}
}
bool	ListPhasePageLayerLibIDPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ListPhasePageLayerLibID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ListPhasePageLayerLibIDPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ListPhasePageLayerLibID *a=new ListPhasePageLayerLibID();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
void	ListPhasePageLayerLibIDPack::GetPhaseList(IntList &PhaseList)
{
	for(ListPhasePageLayerLibID *a=GetFirst();a!=NULL;a=a->GetNext()){
		PhaseList.Merge(a->Data.Phase);
	}
}
void	ListPhasePageLayerLibIDPack::GetPageLayer(int Phase,ListPageLayerPack &PageLayer)
{
	for(ListPhasePageLayerLibID *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Data.Phase==Phase){
			PageLayer.Merge(a->Data.Page,a->Data.Layer);
		}
	}
}