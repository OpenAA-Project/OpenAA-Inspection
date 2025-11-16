/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\NList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
/*----------------------------------------------------------------------------*/
//
//  äTóv
//
//  çÏê¨é“
//
/*----------------------------------------------------------------------------*/

/*
template<class T>
NPList<T>::~NPList(void)
{
	unsigned long	p;
	NPList<T>	 *n;
	unsigned long	i;

	if(_next!=NULL){
		while((p=this->GetNumberFrom())>RecursiveTurns){
			p-=RecursiveTurns;
			n = this;
			for(i=0;n!=NULL && i!=p;n=n->GetNext(),i++);
			delete	n;
			}
		if(_next!=NULL){
			delete	(NPList<T> *)_next;
			_next=NULL;
			}
		}
	if(_prev!=NULL) ((NPList<T> *)_prev)->SetNext(NULL);
}
*/
#include<stdlib.h>

template<class T>
NPList<T>::~NPList(void)
{
	NPList<T>	*n,*n2;

	if(_next!=NULL){
		for(n=GetLast();n!=this;){
			n2=n->GetPrev();
			delete n;
			n=n2;
			}
		}
	if(_prev!=NULL) ((NPList<T> *)_prev)->SetNext(NULL);
}

template<class T>
T *NPList<T>::GetRoot(void)
{
	NPList<T>	*n;
	for(n=this;n->GetPrev()!=NULL;n=n->GetPrev());
	return((T *)n);
}

template<class T>
T *NPList<T>::GetLast(void)
{
	NPList<T>	 *n;
	for(n=this;n->GetNext()!=NULL;n=n->GetNext());
	return((T *)n);
}

template<class T>
T *NPList<T>::GetFirst(void)
{
	NPList<T>	 *n;
	for(n=this;n->GetPrev()!=NULL;n=n->GetPrev());
	return((T *)n);
}

template<class T>
T *NPList<T>::Dimension(int n)
{
	NPList<T>	 *p;
	int	i;
	for(i=0,p=(T *)this;p->GetNext()!=NULL && i<n;p=p->GetNext(),i++);
	return((T *)p);
}
template<class T>
void NPListPack<T>::AppendListPack(NPListPack<T> &s)
{
    if(s.GetLast()==NULL || s.GetFirst()==NULL)
        return;
	if(Last!=NULL)
		Last->AppendLast( s.Base );
	else	Base=s.Base;
	Last = s.GetLast();

	Count+=s.GetCount();
	s.Base=NULL;
	s.Last=NULL;
	s.Count=0;
}
template<class T>
unsigned long NPList<T>::GetNumber(void)
{
	NPList<T>	 *n;
	unsigned long	i;
	n = GetRoot();
	for(i=0;n!=NULL;n=n->GetNext(),i++);
	return(i);
}

template<class T>
unsigned long NPList<T>::GetNumberFrom(void)
{
	NPList<T>	 *n;
	unsigned long	i;
	n = this;
	for(i=0;n!=NULL;n=n->GetNext(),i++);
	return(i);
}

template<class T>
void	NPListPack<T>::InsertList(long index ,T *additem)
{
	if(Base==NULL && index==0){
		Base=Last=additem;
		Count=1;
	}
	else{
		T	*r=GetItem(index);
        if(r!=NULL){
    		r->Insert(additem);
	    	if(r==Base)
		    	Base=additem;
			Count++;
        }
        else{
            AppendList(additem);
		}
	}
}
template<class T>
unsigned int	NPListPack<T>::GetPointNumber(T *indexitem)
{
	NPList<T>	 *n;
	unsigned long	i;
	n = indexitem;
	for(i=0;n!=NULL;n=n->GetPrev(),i++);
	return(i-1);
}

template<class T>
void	NPListPack<T>::InsertLater(T *indexitem ,T *additem)
{
	if(Base==NULL){
		Base=Last=additem;
		Count=1;
	}
	else{
        T *r=indexitem->GetNext();
        indexitem->SetNext(additem);
        additem  ->SetPrev(indexitem);
        additem  ->SetNext(r);
        if(r!=NULL){
            r->SetPrev(additem);
		}
        if(Last==indexitem){
            Last=additem;
		}
		Count++;
	}
}

template<class T>
void	NPListPack<T>::InsertForward(T *indexitem ,T *additem)
{
	if(Base==NULL){
		Base=Last=additem;
		Count=1;
	}
	else{
        if(indexitem!=NULL){
    		indexitem->Insert(additem);
	    	if(indexitem==Base)
		    	Base=additem;
			Count++;
		}
        else{
            AppendList(additem);
		}
	}
}

template<class T>
void	NPListPack<T>::InsertTop(T *additem)
{
	if(Base==NULL){
		Base=Last=additem;
		Count=1;
	}
	else{
        T	*r=Base;
        Base=additem;
        additem->SetPrev(NULL);
        additem->SetNext(r);
        if(Base!=NULL){
            r->SetPrev(additem);
		}
		Count++;
	}
}

template<class T>
void NPListPack<T>::UpsideDown(void)
{
	for(T *p=GetFirst();p!=NULL;){
		T	*NextP=p->GetNext();
		p->SwapLink();
		p=NextP;
	}
	T	*tmp=Last;
	Last=Base;
	Base=tmp;

}


template<class T>
T *NPListPack<T>::GetItem(unsigned long index)
{
	T	*n=Base;
	for(;index>0 && n!=NULL;index--)
		n = n->GetNext();
	return(n);
}

template<class T>
bool    NPListPack<T>::IsExist(T *point)
{
	NPList<T>	 *n;
	for(n = GetFirst();n!=NULL;n=n->GetNext()){
        if(n==point)
            return(true);
        }
	return(false);
}


template<class T>
NPListPack<T> & NPListPack<T>::operator+=(NPListPack<T> &s1)
{
	T	*n;
	for(T *s=s1.GetFirst() ; s!=NULL ; s=s->GetNext()){
		n = new T(*s);
		_AppendLast(n);
		}
	return(*this);
}

template<class T>
NPListPack<T> & NPListPack<T>::operator<=(NPListPack<T> &s1)
{
    RemoveAll();
    Base=s1.Base;
    Last=s1.Last;
	Count=s1.Count;
    s1.Base=NULL;
    s1.Last=NULL;
	s1.Count=0;
    return(*this);
}

template<class T>
void    NPListPack<T>::Move(NPListPack<T> &src)
{
    RemoveAll();
	Base=src.Base;
	Last=src.Last;
	Count=src.Count;
    src.Base=NULL;
    src.Last=NULL;
	src.Count=0;
}
template<class T>
void    NPListPack<T>::AddMove(NPListPack<T> &src)
{
	if(Base==NULL){
		Base=src.Base;
		Last=src.Last;
		Count=src.Count;
	    src.Base=NULL;
		src.Last=NULL;
		src.Count=0;
	}
	else{
		if(src.Base!=NULL){
			Last->SetNext(src.Base);
			src.Base->SetPrev(Last);
			Last=src.Last;
			Count+=src.Count;
		    src.Base=NULL;
			src.Last=NULL;
			src.Count=0;
		}
	}
}
template<class T>
void    NPListPack<T>::InsertTop(NPListPack<T> &src)
{
	if(src.GetFirst()!=NULL){
		src.GetLast()->SetNext(Base);
		if(Base!=NULL){
			Base->SetPrev(src.GetLast());
		}
		Base=src.GetFirst();
		Last=Base->GetLast();
	}
	Count+=src.Count;
    src.Base=NULL;
    src.Last=NULL;
	src.Count=0;
}

template<class T>
void    NPListPack<T>::Swap(T *sr1 ,T *sr2)
{
    if(Base==sr1)
        Base=sr2;
    else if(Base==sr2)
        Base=sr1;
    if(Last==sr1)
        Last=sr2;
    else if(Last==sr2)
        Last=sr1;
    T   *Prev1=sr1->GetPrev();
    T   *Prev2=sr2->GetPrev();
    T   *Next1=sr1->GetNext();
    T   *Next2=sr2->GetNext();

	T	*pnext=sr1->GetNext();
    T   *pprev=sr1->GetPrev();
    if(sr2->GetNext()!=sr1)
        sr1->SetNext(sr2->GetNext());
    else
        sr1->SetNext(sr2);
    if(sr2->GetPrev()!=sr1)
        sr1->SetPrev(sr2->GetPrev());
    else
        sr1->SetPrev(sr2);
    if(pnext!=sr2)
        sr2->SetNext(pnext);
    else
        sr2->SetNext(sr1);
    if(pprev!=sr2)
        sr2->SetPrev(pprev);
    else
        sr2->SetPrev(sr1);
    if(Prev1!=NULL
    && Prev1!=sr2){
        Prev1->SetNext(sr2);
        }
    if(Prev2!=NULL
    && Prev2!=sr1){
        Prev2->SetNext(sr1);
        }
    if(Next1!=NULL
    && Next1!=sr2){
        Next1->SetPrev(sr2);
        }
    if(Next2!=NULL
    && Next2!=sr1){
        Next2->SetPrev(sr1);
        }
}

template<class T>
int	NPListPack<T>::SortFunc(const void *a ,const void *b)
{
	T	**pa=(T **)a;
	T	**pb=(T **)b;
	int	k=pa[0]->Compare(*pb[0]);
	return k;
}

template<class T>
void	NPListPack<T>::Sort(void)
{
	int		N=GetCount();
	T	**Dim=new T*[N];
	T	*f;
	int	k=0;
	while((f=GetFirst())!=NULL){
		RemoveList(f);
		Dim[k]=f;
		k++;
	}
	qsort(Dim,N,sizeof(T *),(int (*)(const void *a ,const void *b))SortFunc);
	for(int i=0;i<N;i++){
		AppendList(Dim[i]);
	}
	delete	[]Dim;
}

template<class T>
void	NPListPack<T>::Sort(int (*HSortFunc)(const void *,const void *))
{
	int		N=GetCount();
	T	**Dim=new T*[N];
	T	*f;
	int	k=0;
	while((f=GetFirst())!=NULL){
		RemoveList(f);
		Dim[k]=f;
		k++;
	}
	qsort(Dim,N,sizeof(T *),HSortFunc);
	for(int i=0;i<N;i++){
		AppendList(Dim[i]);
	}
	delete	[]Dim;
}

//---------------------------------------------------------------------------------
template<class T>
T *NList<T>::GetLast(void)
{
	NList<T>	*n;
	for(n=this;n->GetNext()!=NULL;n=n->GetNext());
	return((T *)n);
}

template<class T>
T *NList<T>::Dimension(int n)
{
	NList<T>	*p;
	int	i;
	for(i=0,p=(T *)this;p->GetNext()!=NULL && i<n;p=p->GetNext(),i++);
	return((T *)p);
}

template<class T>
unsigned long NList<T>::GetNumber(void)
{
	NList<T>	*n;
	unsigned long	i;
	n = this;
	for(i=0;n!=NULL;n=n->GetNext(),i++);
	return(i);
}

template<class T>
unsigned long NList<T>::GetNumberFrom(void)
{
	NList<T>	*n;
	unsigned long	i;
	n = this;
	for(i=0;n!=NULL;n=n->GetNext(),i++);
	return(i);
}

template<class T>
NList<T>::~NList(void)
{
	if(_next!=NULL){
		unsigned long	p;
		NList<T>	*n;
		unsigned long	i;
		while((p=this->GetNumberFrom())>RecursiveTurns){
			p-=RecursiveTurns;
			n = this;
			for(i=0;n!=NULL && i!=p;n=n->GetNext(),i++);
			delete	n;
			}
		if(_next!=NULL){
			delete	(NList<T> *)_next;
			_next=NULL;
			}
		}
}

template<class T>
T *NListPack<T>::RemoveList(T *point)
{
	T *lastpoint=NULL;
	for(T *n=Base;n!=NULL;n=n->GetNext()){
		if(n==point){
			if(lastpoint!=NULL)
				lastpoint->SetNext(point->GetNext());
			else{
				Base=point->GetNext();
				}
			if(Last==point)
				Last=lastpoint;
			point->SetPrev(NULL);
			point->SetNext(NULL);
			return(point);
			}
		lastpoint=n;
		}
	return(NULL);
}

template<class T>
T *NListPack<T>::GetItem(unsigned long index)
{
	T	*n=Base;
	for(;index>0;index--)
		n = n->GetNext();
	return(n);
}

template<class T>
NListPack<T> & NListPack<T>::operator+=(NListPack<T> &s1)
{
	for(T *s=s1.GetFirst() ; s!=NULL ; s=s->GetNext()){
		_AppendLast(new T(*s));
		}
	return(*this);
}
