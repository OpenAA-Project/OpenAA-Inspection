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
#include "XTypeDef.h"

#define	RecursiveTurns	30

template<class T>
class	NPList
{
private:
	T	*_next;
	T	*_prev;
public:
	NPList(void){		_next = NULL;
				_prev = NULL;		}
	virtual ~NPList(void);

	inline T *GetNext(void)	const	{	return(_next);	}
	inline T *GetPrev(void)	const	{	return(_prev);	}

	void SetNext(T *next){	_next = next;	}
	void SetPrev(T *prev){	_prev = prev;	}
	T *Append(T *child);

	virtual	bool	operator=(T *s)	{	return true;	}

public:
	T *GetRoot(void)	const;
	T *GetLast(void)	const;
	T *GetLastEnd(void)	const;
	T *GetFirst(void)	const;
	T *AppendLast(T *child);
	T *Insert(T *child);
	bool	Remove(void);
	T *Dimension(int n);
	unsigned long GetNumber(void)	const;
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
inline bool NPList<T>::Remove(void)
{
	if((_prev==NULL) && (_next==NULL)){
		return false;
	}
	if(_prev!=NULL) ((NPList<T> *)_prev)->SetNext(_next);
	if(_next!=NULL) ((NPList<T> *)_next)->SetPrev(_prev);
	_prev=_next=NULL;
	return(true);
}

template<class T>
class	NPListPack
{
	T	*Base;
	T	*Last;
	int	Count;

public:
	NPListPack(void){
		Base = Last = NULL;	Count=0;
		}
	NPListPack(const NPListPack<T> &src);

	virtual ~NPListPack(void){	delete	Base;	Base=Last=NULL; }

	inline T *GetFirst(void) const{
		return(Base);
		}
	inline T *GetLast(void) const{
		return(Last);
		}
	inline T *GetRingNext(T *p)	const{
		T	*a;
		if(p==NULL){
			return NULL;
		}
		if((a=p->GetNext())==NULL)
			a=GetFirst();
		return(a);
		}
	inline T *GetRingPrev(T *p)	const{
		T	*a;
		if(p==NULL){
			return NULL;
		}
		if((a=p->GetPrev())==NULL)
			a=GetLast();
		return(a);
		}
	bool	IsValid(void) const{
		if(Base!=NULL && Last==NULL)	return false;
		if(Base==NULL && Last!=NULL)	return false;
		if(Base==NULL && Last!=NULL && Count==0)	return false;
		return true;
	}
	void	AppendList(T *additem){
		if(Base==NULL){	Base=Last=additem;	}
		else{	Last->AppendLast(additem);	}
		//Last=additem->NPList<T>::GetLast();
		Last=(T *)additem->GetLastEnd();
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
	unsigned int	GetPointNumber(T *indexitem)	const;

	void	RemoveList(T *point){
		if(Base==NULL){  return;	}
		bool	LastBase=false;
		if(point==Last){ Last=point->GetPrev();	LastBase=true;	}
		if(point==Base){ Base=point->GetNext();	LastBase=true;	}
		if((point->Remove()==true) || (LastBase==true)){
			Count--;
		}
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
	unsigned long GetNumber(void) const{
		return Count;
	}
	unsigned long count(void)	const	{	return GetNumber();	}
	unsigned long GetCount(void) const	{	return GetNumber();	}

	T *GetItem(unsigned long index)		const;
	T *operator[](unsigned long index)	const	{	return GetItem(index);	}
    bool    IsExist(T *point)	const;
	bool	IsEmpty(void) const	{	return (GetFirst()==NULL)?true:false;	}
	bool	IsNull(void) const	{	return IsEmpty();	}
   
    void    Move(NPListPack<T> &src);
    void    AddMove(NPListPack<T> &src);
	void	InsertTop(NPListPack<T> &src);
	void    Swap(T *sr1 ,T *sr2);
	void    Swap(NPListPack<T> &s1);

	NPListPack<T> & operator=(const NPListPack<T> &src);
	NPListPack<T> & operator+=(const NPListPack<T> &s1);
	NPListPack<T> & operator<=(const NPListPack<T> &s1);

	void	Sort(void);		//Use Compare function
	void	Sort(int (*SortFunc)(const void *,const void *));
	void	Sort(int (*SortFunc)(const T **,const T **));

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
    private:
	T	*_next;
    public:
	NList(void){		_next = NULL;		}
	inline T *GetNext(void)	const	{	return(_next);	}
	virtual ~NList(void);

    protected:
	void SetNext(T *next){	_next = next;	}
	T *Append(T *child);

    public:
	T *GetLast(void)	const;
	T *AppendLast(T *child);
	T *Insert(T *child);
	T *Dimension(int n);
	unsigned long GetNumber(void)	const;

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
	T *GetItem(unsigned long index)	const;

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

//===============================================================================


template<class T>
class	DimList
{
	int	ID;
public:
	DimList(void){	ID=-1;	}
	virtual ~DimList(void){}

	int		GetID(void)	const	{	return ID;	}
	void	SetID(int id)		{	ID=id;		}
	virtual	int	Compare(T &src)	{	return 0;	}
	virtual	DimList<T> &operator=(const DimList<T> &src)	{	ID=src.ID;	return *this;	}
};


template<class T>
class	DimListPack
{
	T	*Base;
	int	AllocatedCount;
	int	Count;
    int	BaseID;
public:
	DimListPack(void){		Base=NULL;	Count=0;	AllocatedCount=0;	BaseID=0;	}
	DimListPack(const DimListPack<T> &src){
		AllocatedCount=src.AllocatedCount;
		Base=new T[AllocatedCount]; 
		BaseID=0;
		for(int i=0;i<src.Count;i++){
			Base[i]=src.Base[i];
			Base[i].SetID(BaseID++);
		}
		Count=src.Count;
	}

	virtual ~DimListPack(void){	delete	[]Base;	Base=NULL; Count=0;	AllocatedCount=0;	}

	virtual	int	GetAllocationBlockCount(void)	{	return ((4096/sizeof(T))>=10)?((4096/sizeof(T))>=10):10;	}

	void	Allocate(int n){
		int	tAllocatedCount=(n+GetAllocationBlockCount()-1)/GetAllocationBlockCount();
		if(tAllocatedCount>AllocatedCount){
			AllocatedCount=tAllocatedCount;
			T *Tmp=new T[AllocatedCount];
			for(int i=0;i<Count;i++){
				Tmp[i]=Base[i];
			}
			delete	[]Base;
			Base=Tmp;
		}
	}

	inline T *GetFirst(void)	const	{	return(Base);	}
	inline T *GetLast(void)		const	{	return (Base!=NULL)?&Base[Count-1]:NULL;	}

	void	Append(T &additem){
		if(Count>=AllocatedCount){
			AllocatedCount+=GetAllocationBlockCount();
			T *Tmp=new T[AllocatedCount];
			for(int i=0;i<Count;i++){
				Tmp[i]=Base[i];
			}
			delete	[]Base;
			Base=Tmp;
		}
		Base[Count]=additem;
		Base[Count].SetID(BaseID++);
		Count++;
	}
	void	Insert(long index ,T &additem){
		if(Count>=AllocatedCount){
			AllocatedCount+=GetAllocationBlockCount();
			T *Tmp=new T[AllocatedCount];
			for(int i=0;i<Count;i++){
				Tmp[i]=Base[i];
			}
			delete	[]Base;
			Base=Tmp;
		}
		if((0<=index) && (index<Count)){
			for(int i=Count-1;i>=index;i--){
				Base[i+1]=Base[i];
			}
		}
		Base[index]=additem;
		Base[index].SetID(BaseID++);
		Count++;
	}
	
	int	GetPointNumber(T *indexitem){
		if(Base==NULL){  return -1;	}
		int	ID=indexitem->GetID();
		for(int i=0;i<Count;i++){
			if(Base[i].GetID()==ID){
				return i;
			}
		}
		return -1;
	}
	void	RemoveItem(int index){
		if((0<=index) && (index<Count)){
			for(int i=index;i<Count-1;i++){
				Base[i]=Base[i+1];
			}
			Count--;
		}
	}

	void	RemoveItem(T *point){
		if(Base==NULL){  return;	}
		int	ID=point->GetID();
		for(int i=0;i<Count;i++){
			if(Base[i].GetID()==ID){
				RemoveItem(i);
				return;
			}
		}
	}
	void RemoveAll(void){
		delete  []Base;
		Base=NULL;
		Count=0;
		AllocatedCount=0;
		}
	unsigned long count(void)	const	{	return Count;	}
	unsigned long GetCount(void) const	{	return Count;	}

	T *GetItem(unsigned long index)		const	{	return (0<=index && index<Count)?&Base[index]:NULL;	}
	T *operator[](unsigned long index)	const	{	return GetItem(index);	}
    bool    IsExist(T *point)	const
	{
		if(Base==NULL){  return false;	}
		int	ID=point->GetID();
		for(int i=0;i<Count;i++){
			if(Base[i].GetID()==ID){
				return true;
			}
		}
		return false;
	}
	bool	IsEmpty(void) const	{	return (Count==0)?true:false;	}
	bool	IsNull(void) const	{	return IsEmpty();	}
   
    void    Append(DimListPack<T> &src);
	void	Move(DimListPack<T> &src);
	DimListPack<T> & operator=(DimListPack<T> &src);
	DimListPack<T> & operator+=(DimListPack<T> &s1);

	void	Sort(void);		//Use Compare function
	void	Sort(int (*SortFunc)(const void *,const void *));

	static	int	SortFunc(const void *a ,const void *b);
};

//========================================================================
class	NPListPointerForCompare : public NPList<NPListPointerForCompare>
{
	void	*Pointer;
public:
	bool	Equal;
	NPListPointerForCompare(void *a)	{	Pointer=a;	Equal=false;	}

	void	*GetPointer(void)	const	{	return Pointer;	}
};

template<class T>
class	NPListPointerForComparePack : public NPListPack<NPListPointerForCompare>
{
public:
	NPListPointerForComparePack(void){}

	void	Set(const NPListPack<T> &src);
	bool	operator==(NPListPointerForComparePack<T> &src);
	bool	operator!=(NPListPointerForComparePack<T> &src);
private:
	void	ClearFlag(void);
};


//========================================================================

template<class U>
class DataValueDimBase;
template<class T,int MaxDimN>
class DataValueDim;
template<class T>
class DataValueDimContainer;


template<class U>
class DataList
{
public:
	U	Value;

	bool			Effective;
	int				Index;
	DataValueDimBase<U>	*DPoint;

	DataList(void)	{	Effective=true;	}
	DataList(const U &s){	Effective=true;	Value=s;	}
	virtual	~DataList(void){}

	const	U	&GetValue(void)	const		{	return Value;	}
	void	SetValue(const U &d)			{	Value=d;		}

	const	DataList	*GetNext(void)	const	;
	const	DataList	*GetPrev(void)	const	;
};

template<class U>
class DataValueDimBase :public NPList<DataValueDimBase<U> >
{
public:
	DataValueDimContainer<U>	*Parent;
	int				AddedCount;
	int				EffectiveCount;
public:
	DataValueDimBase(DataValueDimContainer<U> *p):Parent(p)
	{
		AddedCount=EffectiveCount=0;
	}
	virtual	~DataValueDimBase(void){}

	int				GetAddedCount(void)	const		{	return AddedCount;	}
	void			SetAddedCount(int d)			{	AddedCount=d;		}
	int				GetEffectiveCount(void)	const	{	return EffectiveCount;	}
	void			SetEffectiveCount(int d)		{	EffectiveCount=d;		}

	virtual	const	DataList<U>	*GetFirstList(void)	const	=0;
	virtual	const	DataList<U>	*GetLastList(void)	const	=0;
	virtual	const	DataList<U>	*GetItemList(int Index)	const	=0;

	virtual	bool	Add(const U &s)	=0;

	virtual	DataList<U>	*GetNextPoint(int index)	=0;
	virtual	DataList<U>	*GetPrevPoint(int index)	=0;
};


template<class U ,int MaxDimN=100>
class DataValueDim :public DataValueDimBase<U>
{
public:
	DataList<U>		Dim[MaxDimN];


	DataValueDim(DataValueDimContainer<U> *p):DataValueDimBase<U>(p){}
	virtual	~DataValueDim(void){}

	const	DataList<U>	*GetFirstList(void)	const{
		for(int i=0;i<GetAddedCount();i++){
			if(Dim[i].Effective==true){
				return &Dim[i];
			}
		}
		return NULL;
	}
	const	DataList<U>	*GetLastList(void)	const{
		for (int i=GetAddedCount()-1;i>=0;i--) {
			if(Dim[i].Effective==true){
				return &Dim[i];
			}
		}
		return NULL;
	}
	const	DataList<U>	*GetItemList(int Index)	const{
		for(int i=0;i<GetAddedCount();i++){
			if(Dim[i].Effective==true){
				if(Index==0){
					return &Dim[i];
				}
				Index--;
			}
		}
		return NULL;
	}

	bool	Add(const U &s){
		int	iAddedCount=GetAddedCount();
		if(iAddedCount<MaxDimN){
			Dim[iAddedCount]=DataList<U>(s);
			Dim[iAddedCount].DPoint=this;
			Dim[iAddedCount].Index=iAddedCount;
			SetAddedCount(iAddedCount+1);
			SetEffectiveCount(GetEffectiveCount()+1);
			return true;
		}
		return false;
	}

	DataList<U>	*GetNextPoint(int index)
	{
		for(int i=index;i<GetAddedCount();i++){
			if(Dim[i].Effective==true){
				return &Dim[i];
			}
		}
		return NULL;
	}
	DataList<U>	*GetPrevPoint(int index)
	{
		for(int i=index;i>=0;i--){
			if(Dim[i].Effective==true){
				return &Dim[i];
			}
		}
		return NULL;
	}
};

template<class T>
class DataValueDimContainer
{
	DataValueDim<T,5>					Dim0;
	NPListPack<DataValueDim<T,100> >	Dim ;
	int		EffectiveCount;
public:
	DataValueDimContainer(void):Dim0(this){
		EffectiveCount=0;
	}
	virtual	~DataValueDimContainer(void){}

	int		GetCount(void)	const	{	return EffectiveCount;	}
	bool	IsEmpty(void)	const	{	return (EffectiveCount==0)?true:false;	}

	const	DataList<T>	*GetFirst(void)	const{
		if(Dim0.GetAddedCount()>0){
			const	DataList<T>	*p=Dim0.GetFirstList();
			if(p!=NULL){
				return p;
			}
		}
		for(DataValueDimBase<T> *L=Dim.GetFirst();L!=NULL;L=L->GetNext()){
			const	DataList<T>	*p=L->GetFirstList();
			if(p!=NULL){
				return p;
			}
		}
		return NULL;
	}
	const	DataList<T>	*GetLast(void)	const{
		for(DataValueDimBase<T> *L=Dim.GetLast();L!=NULL;L=L->GetPrev()){
			const	DataList<T>	*p=L->GetLastList();
			if(p!=NULL){
				return p;
			}
		}
		return Dim0.GetLastList();
	}
	const	DataList<T>	*GetItem(int Index)	const{
		if(Index<Dim0.GetEffectiveCount()){
			return Dim0.GetItemList(Index);
		}
		Index-=Dim0.GetEffectiveCount();
		for(DataValueDimBase<T> *L=Dim.GetFirst();L!=NULL;L=L->GetNext()){
			if(Index<L->GetEffectiveCount()){
				return L->GetItemList(Index);
			}
			Index-=L->GetEffectiveCount();
		}
		return NULL;
	}

	void	Add(const T &s){
		DataValueDimBase<T>	*p=Dim.GetLast();
		if(p==NULL){
			p=&Dim0;
		}
		if(p->Add(s)==false){
			DataValueDim<T,100>	*pp=new DataValueDim<T,100>(this);
			p=pp;
			p->Add(s);
			Dim.AppendList(pp);
		}
		EffectiveCount++;
	}
	DataValueDimBase<T>	*GetNextDim(DataValueDimBase<T> *DPoint){
		if(DPoint==&Dim0){
			return Dim.GetFirst();
		}
		return DPoint->GetNext();
	}
	DataValueDimBase<T>	*GetPrevDim(DataValueDimBase<T> *DPoint){
		if(DPoint==&Dim0){
			return NULL;
		}
		DataValueDimBase<T>	*p=DPoint->GetPrev();
		if(p!=NULL){
			return p;
		}
		return &Dim0;
	}
	void	RemoveList(DataList<T> *p){
		if(p!=NULL){
			p->Effective=false;
			p->DPoint->EffectiveCount--;
			EffectiveCount--;
		}
	}
	void	RemoveAll(void){
		Dim.RemoveAll();
		Dim0.SetAddedCount(0);
		Dim0.SetEffectiveCount(0);
		EffectiveCount=0;
	}
};


template<class T>
inline	const	DataList<T>	*DataList<T>::GetNext(void)	const	
{
	if(DPoint!=NULL){
		DataList<T>	*p=DPoint->GetNextPoint(Index+1);
		if(p!=NULL){
			return p;
		}
		DataValueDimBase<T>	*d=DPoint->Parent->GetNextDim(DPoint);
		if(d!=NULL){
			return d->GetFirstList();
		}
	}
	return NULL;
}
template<class T>
inline	const		DataList<T>	*DataList<T>::GetPrev(void)	const
{
	if(DPoint!=NULL){
		DataList<T>	*p=DPoint->GetPrevPoint(Index-1);
		if(p!=NULL){
			return p;
		}
		DataValueDimBase<T>	*d=DPoint->Parent->GetPrevDim(DPoint);
		if(d!=NULL){
			return d->GetLastList();
		}
	}
	return NULL;
}

template<class T>
class	NPListPointer: public NPList<NPListPointer<T> >
{
	T	*Pointer;
public:
	NPListPointer(T *t):Pointer(t){}

	T	*GetPointer(void){	return Pointer;	}
};


#include"NList.cpp"

#endif
