#include "XGeneralFunc.h"
#include "XAlignment.h"

//==============================================================================
bool	AlignmentPointList::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	if(::Load(f,XSize)==false)
		return false;
	if(::Load(f,YSize)==false)
		return false;
	if(::Load(f,AlignmentOnOutline)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,Threshold)==false)
		return false;
	return true;
}
bool	AlignmentPointList::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	if(::Save(f,XSize)==false)
		return false;
	if(::Save(f,YSize)==false)
		return false;
	if(::Save(f,AlignmentOnOutline)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,Threshold)==false)
		return false;
	return true;
}

AlignmentPointList	&AlignmentPointList::operator=(AlignmentPointList &src)
{
	ID			=src.ID;
	AreaID		=src.AreaID;
	ItemID		=src.ItemID;
	GroupNumber	=src.GroupNumber;
	Layer		=src.Layer;
	Page		=src.Page;
	Cx			=src.Cx;
	Cy			=src.Cy;
	XSize		=src.XSize;
	YSize		=src.YSize;
	AlignmentOnOutline	=src.AlignmentOnOutline;
	SearchDot	=src.SearchDot;
	Threshold	=src.Threshold;
	return *this;
}

bool	AlignmentPointListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentPointList *p=new AlignmentPointList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentPointListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentPointList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentPointListPack	&AlignmentPointListPack::operator=(AlignmentPointListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentPointListPack	&AlignmentPointListPack::operator+=(AlignmentPointListPack &src)
{
	for(AlignmentPointList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentPointList *q=new AlignmentPointList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}

//-----------------------------------------------------------------------------

bool	AlignmentAreaList::Load(QIODevice *f)
{
	if(::Load(f,Number)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,XSize)==false)
		return false;
	if(::Load(f,YSize)==false)
		return false;
	return true;
}
bool	AlignmentAreaList::Save(QIODevice *f)
{
	if(::Save(f,Number)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,XSize)==false)
		return false;
	if(::Save(f,YSize)==false)
		return false;
	return true;
}

AlignmentAreaList	&AlignmentAreaList::operator=(AlignmentAreaList &src)
{
	Number		=src.Number;
	AreaID		=src.AreaID;
	AreaName	=src.AreaName;
	Layer		=src.Layer;
	GlobalPage	=src.GlobalPage;
	XSize		=src.XSize;
	YSize		=src.YSize;
	return *this;
}

bool	AlignmentAreaListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentAreaList *p=new AlignmentAreaList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentAreaListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentAreaList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentAreaListPack	&AlignmentAreaListPack::operator=(AlignmentAreaListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentAreaListPack	&AlignmentAreaListPack::operator+=(AlignmentAreaListPack &src)
{
	for(AlignmentAreaList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentAreaList *q=new AlignmentAreaList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}
