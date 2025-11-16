/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\NList.h
** Author : YYYYYYYYYY
****************************************************************************-**/
/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
#if	!defined(NLIST_DEF)
#define	NLIST_DEF

#include<stdio.h>

#define	RecursiveTurns	30

template<class T>
/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class	NPList
{
	/*----------------------------------------------------------------------------*/
	//  1.日本語名
	//
	//  2.概要
	//
	//  3.機能説明
	//
	//  4.備考
	//
	/*----------------------------------------------------------------------------*/
private:
	T	*_next;
	T	*_prev;
public:
	NPList(void){		_next = NULL;
				_prev = NULL;		}
	virtual ~NPList(void);
	inline T *GetNext(void){	return(_next);	}
	inline T *GetPrev(void){	return(_prev);	}

	void SetNext(T *next){	_next = next;	}
	void SetPrev(T *prev){	_prev = prev;	}
	T *Append(T *child);

    public:
	T *GetRoot(void);
	T *GetLast(void);
	T *GetFirst(void);
	T *AppendLast(T *child);
	T *Insert(T *child);
	T *Remove(void);
	T *Dimension(int n);
	unsigned long GetNumber(void);
	void	SwapLink(void){	T	*p=_next;	_next=_prev;	_prev=p;	}
	virtual	int	Compare(T &src)	{	return 0;	}

private:
	unsigned long GetNumberFrom(void);
};

template<class T>
inline T *NPList<T>::Append(T *child)
{
	if(child==NULL) return(NULL);
	SetNext(child);
	((NPList<T> *)child)->SetPrev((T *)this);
	return((T *)this);
}



template<class T>
inline T *NPList<T>::AppendLast(T *child)
{
	if(child==NULL){ return(NULL);	}
	T	*n;
	n = this->GetLast();
	((NPList<T> *)n)->SetNext(child);
	((NPList<T> *)child)->SetPrev((T *)n);
	return((T *)this);
}

template<class T>
inline T *NPList<T>::Insert(T *child)
{
	if(child!=NULL){
		((NPList<T> *)child)->SetNext((T *)this);
		((NPList<T> *)child)->SetPrev(_prev);
		if(((NPList<T> *)child)->GetPrev()!=NULL)
			((NPList<T> *)(((NPList<T> *)child)->GetPrev()))->SetNext(child);
		}
	_prev=child;
	return((T *)this);
}

template<class T>
inline T *NPList<T>::Remove(void)
{
	if(_prev!=NULL) ((NPList<T> *)_prev)->SetNext(_next);
	if(_next!=NULL) ((NPList<T> *)_next)->SetPrev(_prev);
	_prev=_next=NULL;
	return((T *)this);
}


template<class T>
/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class	NPListPack
{
	T	*Base;
	T	*Last;
	int	Count;
    public:
	NPListPack(void){
		Base = Last = NULL;	Count=0;
		}
	virtual ~NPListPack(void){	delete	Base;	Base=Last=NULL; }

	inline T *GetFirst(void) const{
		return(Base);
		}
	inline T *GetLast(void) const{
		return(Last);
		}
	inline T *GetRingNext(T *p){
		T	*a;
		if((a=p->GetNext())==NULL)
			a=GetFirst();
		return(a);
		}
	inline T *GetRingPrev(T *p){
		T	*a;
		if((a=p->GetPrev())==NULL)
			a=GetLast();
		return(a);
		}
	void	AppendList(T *additem){
		if(Base==NULL){	Base=Last=additem;	}
		else{	Last->AppendLast(additem);	}
		Last=additem->NPList<T>::GetLast();
		//Last=additem->GetLast();
		Count++;
		}
	void	InsertList(long index ,T *additem);
	void	InsertLater(T *indexitem ,T *additem);
	void	InsertForward(T *indexitem ,T *additem);

	void	InsertTop(T *additem);
	T *AppendList(T &additem){
		T	*r = new T(additem);
		AppendList(r);
		return(r);
		}
	void AppendListPack(NPListPack<T> &s1);
    void UpsideDown(void);
	unsigned int	GetPointNumber(T *indexitem);

	void	RemoveList(T *point){
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
		/*
		if(Base!=NULL){
			if(Base->GetNext()==NULL){
				return(1);
			}
			return(Base->NPList<T>::GetNumber());
		}
		return(0);
		*/
	}
	unsigned long GetNumber(void) const{
		return Count;
		/*
		if(Base!=NULL){
			if(Base->GetNext()==NULL){
				return(1);
			}
			return(Base->NPList<T>::GetNumber());
		}
		return(0);
		*/
	}
	unsigned long count(void)			{	return GetNumber();	}
	unsigned long count(void) const		{	return GetNumber();	}
	unsigned long GetCount(void) 		{	return GetNumber();	}
	unsigned long GetCount(void) const	{	return GetNumber();	}

	T *GetItem(unsigned long index);
	T *operator[](unsigned long index){	return GetItem(index);	}
    bool    IsExist(T *point);
	bool	IsEmpty(void)		{	return (GetFirst()==NULL)?true:false;	}
	bool	IsEmpty(void) const	{	return (GetFirst()==NULL)?true:false;	}
	bool	IsNull(void)		{	return IsEmpty();	}
	bool	IsNull(void) const	{	return IsEmpty();	}

    
    void    Move(NPListPack<T> &src);
    void    AddMove(NPListPack<T> &src);
	void	InsertTop(NPListPack<T> &src);
	void    Swap(T *sr1 ,T *sr2);

	NPListPack<T> & operator+=(NPListPack<T> &s1);
	NPListPack<T> & operator<=(NPListPack<T> &s1);

	void	Sort(void);		//Use Compare function
	void	Sort(int (*SortFunc)(const void *,const void *));

private:
	void _AppendLast(T *additem){
		if(Base==NULL){
			Base=Last=additem;
			Base->SetPrev(NULL);
			}
		else	Last->Append(additem);
		Last=additem;
		Last->SetNext(NULL);
		Count++;
		}
	static	int	SortFunc(const void *a ,const void *b);
};


/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
template<class T>
class	NList
{
	/*----------------------------------------------------------------------------*/
	//  1.日本語名
	//
	//  2.概要
	//
	//  3.機能説明
	//
	//  4.備考
	//
	/*----------------------------------------------------------------------------*/

    private:
	T	*_next;
    public:
	NList(void){		_next = NULL;		}
	inline T *GetNext(void){	return(_next);	}
	virtual ~NList(void);

    protected:
	void SetNext(T *next){	_next = next;	}
	T *Append(T *child);

    public:
	T *GetLast(void);
	T *AppendLast(T *child);
	T *Insert(T *child);
	T *Dimension(int n);
	unsigned long GetNumber(void);

    private:
	unsigned long GetNumberFrom(void);
};

template<class T>
inline T *NList<T>::Append(T *child)
{
	if(child==NULL) return(NULL);
	SetNext(child);
	return((T *)this);
}

template<class T>
inline T *NList<T>::AppendLast(T *child)
{
	if(child==NULL) return(NULL);
	T	*n;
	n = this->GetLast();
	((NList<T> *)n)->SetNext(child);
	return((T *)this);
}
template<class T>
inline T *NList<T>::Insert(T *child)
{
	if(child!=NULL){
		((NList<T> *)child)->SetNext((T *)_next);
		}
	_next=child;
	return((T *)this);
}



template<class T>
/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class	NListPack
{
    private:
	T	*Base;
	T	*Last;

    public:
	NListPack(void){
		Base = Last = NULL;
		}
	virtual ~NListPack(void){	delete	Base;	Base=Last=NULL; }

	T *GetFirst(void){
		return(Base);
		}
	inline T *GetLast(void){
		return(Last);
		}
	T *AppendList(T *additem){
		if(Base==NULL)	Base=Last=additem;
		else	Last->AppendLast(additem);
		Last=additem->GetLast();
		return(additem);
		}
	T *AppendList(T &additem){
		T	*r = new T(additem);
		if(Base==NULL)	Base=Last=r;
		else{
			Last->AppendLast(r);
			Last=r;
			}
		return(r);
		}
	T *RemoveList(T *point);
	void RemoveAll(void){
		delete  Base;
		Base=Last=NULL;
		}
	unsigned long GetNumber(void){
		if(Base==NULL)	return(0);
		return(Base->GetNumber());
		}
	T *GetItem(unsigned long index);

	NListPack<T> & operator+=(NListPack<T> &s1);
   private:
	void _AppendLast(T *additem){
		if(Base==NULL){
			Base=Last=additem;
			}
		else	Last->Append(additem);
		Last=additem;
		Last->SetNext(NULL);
		}
};
#include"NList.cpp"

#endif
