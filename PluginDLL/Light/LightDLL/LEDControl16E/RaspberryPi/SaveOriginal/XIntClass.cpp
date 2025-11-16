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
bool    IntClass::Save(QIODevice *file)
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
bool    IntClass::Load(QIODevice *file)
{
	if(file->read((char *)&d,sizeof(d))!=sizeof(d)){
        return(false);
	}
    return(true);
}

int	IntClass::Compare(IntClass &src)
{
	int	k=GetValue()-src.GetValue();
	return k;
}

IntList::IntList(void)
{}
IntList::IntList(IntList &src)
{
	RemoveAll();
	for(IntClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		IntClass	*d=new IntClass(s->GetValue());
		AppendList(d);
	}
}

bool	IntList::IsInclude(int d)
{
	for(IntClass *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->GetValue()==d){
			return true;
		}
	}
	return false;
}

void	IntList::Remove(int d)
{
	for(IntClass *s=GetFirst();s!=NULL;){
		IntClass *NextS=s->GetNext();
		if(s->GetValue()==d){
			RemoveList(s);
			delete	s;
		}
		s=NextS;
	}
}

void	IntList::Merge(IntList &src)
{
	for(IntClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		if(IsInclude(s->GetValue())==false){
			Add(s->GetValue());
		}
	}
}

IntList	&IntList::operator=(IntList &src)
{
	RemoveAll();
	for(IntClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		IntClass	*d=new IntClass(s->GetValue());
		AppendList(d);
	}
	return *this;
}
IntList	&IntList::operator=(const IntList &src)
{
	RemoveAll();
	for(IntClass *s=((IntList *)&src)->GetFirst();s!=NULL;s=s->GetNext()){
		IntClass	*d=new IntClass(s->GetValue());
		AppendList(d);
	}
	return *this;
}
bool	IntList::operator==(IntList &src) const
{
	IntClass *d=GetFirst();
	IntClass *s=src.GetFirst();
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
bool	IntList::operator!=(IntList &src) const
{
	return !operator==(src);
}

int		IntList::operator[](int n)
{
	IntClass	*c=GetItem(n);
	if(c!=NULL){
		return c->GetValue();
	}
	return -1;
}


bool    IntList::Save(QIODevice *file)
{
	int32	N=GetNumber();
	if(file->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return false;
	}
	for(IntClass *s=GetFirst();s!=NULL;s=s->GetNext()){
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
		IntClass	*d=new IntClass();
		if(d->Load(file)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}

//===========================================================

ListLayerAndID	&ListLayerAndID::operator=(ListLayerAndID &src)
{
	Layer	=src.Layer;
	ID		=src.ID;
	return *this;
}
ListLayerAndID	&ListLayerAndID::operator=(ListLayerIDLibName &src)
{
	Layer	=src.Layer;
	ID		=src.ID;
	return *this;
}

ListLayerAndID::ListLayerAndID(ListLayerAndID &src)
{
	operator=(src);
}
ListLayerAndID::ListLayerAndID(ListLayerIDLibName &src)
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

ListLayerAndIDPack::ListLayerAndIDPack(ListLayerAndIDPack &src)
{
	operator=(src);
}

ListLayerAndIDPack	&ListLayerAndIDPack::operator=(ListLayerAndIDPack &src)
{
	RemoveAll();
	for(ListLayerAndID *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListLayerAndID	*d=new ListLayerAndID(*s);
		AppendList(d);
	}
	return *this;
}

ListLayerAndIDPack	&ListLayerAndIDPack::operator+=(ListLayerAndIDPack &src)
{
	for(ListLayerAndID *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListLayerAndID	*d=new ListLayerAndID(*s);
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

//===========================================================
ListPageLayerID::ListPageLayerID(ListPageLayerID &src)
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


ListPageLayerIDPack::ListPageLayerIDPack(ListPageLayerIDPack &src)
{
	Table=NULL;
	operator=(src);
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
ListPageID::ListPageID(const ListPageLayerID &src)
{
	Page	=src.Page;
	ID		=src.ID;
}
ListPageID &ListPageID::operator=(ListPageID &src)
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


ListPageIDPack::ListPageIDPack(ListPageIDPack &src)
{
	operator=(src);
}

ListPageIDPack	&ListPageIDPack::operator=(ListPageIDPack &src)
{
	RemoveAll();
	return operator+=(src);
}
ListPageIDPack	&ListPageIDPack::operator+=(ListPageIDPack &src)
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
void	ListPageIDPack::Merge	(ListPageIDPack &src)
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

//==============================================================

IntListFast::IntListFast(void)
{
	Dim				=NULL;
	AllocatedByte	=0;
}
IntListFast::~IntListFast(void)
{
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	AllocatedByte	=0;
}

bool	IntListFast::IsInclude(int d)
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

IntList	&IntListFast::operator=(IntListFast &src)
{
	IntList::operator=(*((IntList *)&src));
	if(AllocatedByte<src.AllocatedByte){
		delete	[]Dim;
		AllocatedByte=src.AllocatedByte;
		Dim=new BYTE[AllocatedByte];
	}
	memcpy(Dim,src.Dim,src.AllocatedByte);
	memset(&Dim[src.AllocatedByte],0,AllocatedByte-src.AllocatedByte);
	return *this;
}
IntList	&IntListFast::operator=(const IntListFast &src)
{
	IntList::operator=(*((IntList *)&src));
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

ListLayerIDLibName	&ListLayerIDLibName::operator=(ListLayerIDLibName &src)
{
	Layer	=src.Layer;
	ID		=src.ID;
	LibID	=src.LibID;
	ItemName=src.ItemName;
	return *this;
}

ListLayerIDLibName::ListLayerIDLibName(ListLayerIDLibName &src)
{
	operator=(src);
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

ListLayerIDLibNamePack::ListLayerIDLibNamePack(ListLayerIDLibNamePack &src)
{
	operator=(src);
}

ListLayerIDLibNamePack	&ListLayerIDLibNamePack::operator=(ListLayerIDLibNamePack &src)
{
	RemoveAll();
	for(ListLayerIDLibName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListLayerIDLibName	*d=new ListLayerIDLibName(*s);
		AppendList(d);
	}
	return *this;
}

ListLayerIDLibNamePack	&ListLayerIDLibNamePack::operator+=(ListLayerIDLibNamePack &src)
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

ListPageLayerIDLibName	&ListPageLayerIDLibName::operator=(ListPageLayerIDLibName &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
	ID		=src.ID;
	LibID	=src.LibID;
	ItemName=src.ItemName;
	return *this;
}

ListPageLayerIDLibName::ListPageLayerIDLibName(ListPageLayerIDLibName &src)
{
	operator=(src);
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

ListPageLayerIDLibNamePack::ListPageLayerIDLibNamePack(ListPageLayerIDLibNamePack &src)
{
	operator=(src);
}

ListPageLayerIDLibNamePack	&ListPageLayerIDLibNamePack::operator=(ListPageLayerIDLibNamePack &src)
{
	RemoveAll();
	for(ListPageLayerIDLibName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListPageLayerIDLibName	*d=new ListPageLayerIDLibName(*s);
		AppendList(d);
	}
	return *this;
}

ListPageLayerIDLibNamePack	&ListPageLayerIDLibNamePack::operator+=(ListPageLayerIDLibNamePack &src)
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