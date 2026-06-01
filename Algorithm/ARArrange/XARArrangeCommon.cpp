#include "XGeneralFunc.h"
#include "XARArrange.h"
#include "XLearningRegist.h"
#include "XDateTime.h"

ARItemList::ARItemList(ARArrangeItem *p)
{
	ItemID		=p->GetID();
	CreatedTime	=p->GetIndex()->GetCreatedTime();
	Result		=p->GetARResult();
	p->GetArea().GetCenter(Position);
}

bool	ARItemList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,CreatedTime)==false)
		return false;
	BYTE	d=(BYTE)Result;
	if(::Save(f,d)==false)
		return false;
	if(Position.Save(f)==false)
		return false;
	return true;
}
bool	ARItemList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,CreatedTime)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	Result=(ARArrangeItem::ARResult)d;
	if(Position.Load(f)==false)
		return false;
	return true;
}
ARItemList	&ARItemList::operator=(ARItemList &src)
{
	ItemID		=src.ItemID;
	CreatedTime	=src.CreatedTime;
	Result		=src.Result;
	Position	=src.Position;
	return *this;
}


bool	ARItemListContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(ARItemList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	ARItemListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		ARItemList *a=new ARItemList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}

ARItemListContainer	&ARItemListContainer::operator+=(ARItemListContainer &src)
{
	for(ARItemList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ARItemList *b=new ARItemList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
