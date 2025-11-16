#pragma once

#include "XDataAlgorithm.h"

template<class T>
class PointerList
{
private:
	PointerList	*_next;
	PointerList	*_prev;
	T	*Pointer;
public:
	PointerList()		{	_next = NULL;	_prev = NULL;	Pointer=NULL;	}
	PointerList(T *s)	{	_next = NULL;	_prev = NULL;	Pointer=s;		}
	virtual	~PointerList(void);

	T		*Get(void)	{	return Pointer;	}
	void	Set(T *s)	{	Pointer=s;		}


	inline PointerList *GetNext(void){	return(_next);	}
	inline PointerList *GetPrev(void){	return(_prev);	}

	void SetNext(PointerList *next){	_next = next;	}
	void SetPrev(PointerList *prev){	_prev = prev;	}
	PointerList *Append(PointerList *child);

public:
	PointerList *GetRoot(void);
	PointerList *GetLast(void);
	PointerList *GetFirst(void);
	PointerList *AppendLast(PointerList *child);
	PointerList *Insert(PointerList *child);
	PointerList *Remove(void);
	PointerList *Dimension(int n);
	unsigned long GetNumber(void);
	void	SwapLink(void){	PointerList	*p=_next;	_next=_prev;	_prev=p;	}
	virtual	int	Compare(PointerList &src)	{	return 0;	}

private:
	unsigned long GetNumberFrom(void);
};


template<class T>
inline PointerList<T>::~PointerList<T>(void)
{
	PointerList<T>	*n,*n2;

	if(_next!=NULL){
		for(n=GetLast();n!=this;){
			n2=n->GetPrev();
			delete n;
			n=n2;
		}
	}
	if(_prev!=NULL) _prev->SetNext(NULL);
}

template<class T>
inline PointerList<T> *PointerList<T>::GetRoot(void)
{
	PointerList<T>	*n;
	for(n=this;n->GetPrev()!=NULL;n=n->GetPrev());
	return(n);
}

template<class T>
inline PointerList<T>	*PointerList<T>::GetLast(void)
{
	PointerList<T>	 *n;
	for(n=this;n->GetNext()!=NULL;n=n->GetNext());
	return(n);
}

template<class T>
inline PointerList<T>	*PointerList<T>::GetFirst(void)
{
	PointerList<T>	 *n;
	for(n=this;n->GetPrev()!=NULL;n=n->GetPrev());
	return(n);
}

template<class T>
inline PointerList<T> *PointerList<T>::Dimension(int n)
{
	PointerList<T>	 *p;
	int	i;
	for(i=0,p=(T *)this;p->GetNext()!=NULL && i<n;p=p->GetNext(),i++);
	return(p);
}

template<class T>
inline PointerList<T> *PointerList<T>::Append(PointerList<T> *child)
{
	if(child==NULL) return(NULL);
	SetNext(child);
	child->SetPrev(this);
	return(this);
}

template<class T>
inline PointerList<T> *PointerList<T>::AppendLast(PointerList<T> *child)
{
	if(child==NULL){ return(NULL);	}
	PointerList<T>	*n;
	n = this->GetLast();
	n	 ->SetNext(child);
	child->SetPrev(n);
	return(this);
}

template<class T>
inline PointerList<T> *PointerList<T>::Insert(PointerList<T> *child)
{
	if(child!=NULL){
		child->SetNext(this);
		child->SetPrev(_prev);
		if(child->GetPrev()!=NULL){
			((child->GetPrev()))->SetNext(child);
		}
	}
	_prev=child;
	return(this);
}

template<class T>
inline PointerList<T> *PointerList<T>::Remove(void)
{
	if(_prev!=NULL) _prev->SetNext(_next);
	if(_next!=NULL) _next->SetPrev(_prev);
	_prev=_next=NULL;
	return(this);
}

template<class T>
class PointerListContainer 
{
	PointerList<T>	*Base;
	PointerList<T>	*Last;
	int	Count;

public:
	PointerListContainer(void){
		Base = Last = NULL;	Count=0;
		}
	PointerListContainer(PointerListContainer<T> &src){
		Base = Last = NULL;	Count=0;
		//static_assert(false,"No copy-constructor");
	}
	virtual ~PointerListContainer(void){	delete	Base;	Base=Last=NULL; }

	inline PointerList<T> *GetFirst(void) const{
		return(Base);
		}
	inline PointerList<T> *GetLast(void) const{
		return(Last);
		}
	inline PointerList<T> *GetRingNext(T *p){
		PointerList<T>	*a;
		if((a=p->GetNext())==NULL)
			a=GetFirst();
		return(a);
		}
	inline PointerList<T> *GetRingPrev(T *p){
		PointerList<T>	*a;
		if((a=p->GetPrev())==NULL)
			a=GetLast();
		return(a);
		}
	void	AppendList(T *t){
		PointerList<T>	*additem=new PointerList<T>(t);
		if(Base==NULL){	Base=Last=additem;	}
		else{	Last->AppendLast(additem);	}
		Last=additem->PointerList<T>::GetLast();
		Count++;
		}

	void	RemoveList(PointerList<T> *point){
		if(Base==NULL){  return;	}
		if(point==Last){ Last=point->GetPrev();	}
		if(point==Base){ Base=point->GetNext();	}
		point->Remove();
		Count--;
		}
	void InitialList(void){
		Base=Last=NULL;
		Count=0;
		}
	void RemoveAll(void){
		delete  Base;
		Base=Last=NULL;
		Count=0;
		}
	void RemoveHead(int n){
		for(int i=0;i<n;i++){
			T *p=GetFirst();
			if(p==NULL)
				break;
			RemoveList(p);
			delete	p;
		}
	}
	unsigned long GetNumber(void){
		return Count;
	}
	unsigned long GetNumber(void) const{
		return Count;
	}
	unsigned long count(void)			{	return GetNumber();	}
	unsigned long count(void) const		{	return GetNumber();	}
	unsigned long GetCount(void) 		{	return GetNumber();	}
	unsigned long GetCount(void) const	{	return GetNumber();	}

	T *GetItem(unsigned long index)
	{
		PointerList<T>	*n=Base;
		for(;index>0 && n!=NULL;index--)
			n = n->GetNext();
		return(n->Get());
	}
	T *operator[](unsigned long index){	return GetItem(index);	}

	bool	IsEmpty(void)		{	return (GetFirst()==NULL)?true:false;	}
	bool	IsEmpty(void) const	{	return (GetFirst()==NULL)?true:false;	}
	bool	IsNull(void)		{	return IsEmpty();	}
	bool	IsNull(void) const	{	return IsEmpty();	}

};