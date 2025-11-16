#include "XPieceForReview.h"
#include "XResult.h"
#include "XPieceForReviewPacket.h"
#include "XGeneralFunc.h"

ItemsListPieceForReview::ItemsListPieceForReview(void)
{
	GlobalPage	=-1;
	ItemID		=0;
	AreaNumber	=0;
	SysRegNumber=0;
	X1	=0;
	Y1	=0;
	X2	=0;
	Y2	=0;
}

ItemsListPieceForReview	&ItemsListPieceForReview::operator=(ItemsListPieceForReview &src)
{
	GlobalPage	=src.GlobalPage;
	ItemID		=src.ItemID;
	AreaNumber	=src.AreaNumber;
	AreaName	=src.AreaName;
	SysRegNumber=src.SysRegNumber;
	X1			=src.X1;
	Y1			=src.Y1;
	X2			=src.X2;
	Y2			=src.Y2;
	return *this;
}

bool	ItemsListPieceForReview::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,AreaNumber)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,SysRegNumber)==false)
		return false;
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	return true;
}
	
bool	ItemsListPieceForReview::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,AreaNumber)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,SysRegNumber)==false)
		return false;
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	return true;
}



ItemsContainerPieceForReview	&ItemsContainerPieceForReview::operator+=(ItemsContainerPieceForReview &src)
{
	for(ItemsListPieceForReview *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ItemsListPieceForReview *d=new ItemsListPieceForReview();
		*d=*s;
		AppendList(d);
	}
	return *this;
}
ItemsContainerPieceForReview	&ItemsContainerPieceForReview::operator=(ItemsContainerPieceForReview &src)
{
	RemoveAll();
	for(ItemsListPieceForReview *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ItemsListPieceForReview *d=new ItemsListPieceForReview();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

bool	ItemsContainerPieceForReview::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(ItemsListPieceForReview *r=GetFirst();r!=NULL;r=r->GetNext()){
		if(r->Save(f)==false)
			return false;
	}
	return true;
}
bool	ItemsContainerPieceForReview::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		ItemsListPieceForReview *r=new ItemsListPieceForReview();
		if(r->Load(f)==false)
			return false;
		AppendList(r);
	}
	return true;
}