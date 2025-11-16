#include "XTypeDef.h"
#include "PropertyAlignmentLargePacket.h"
#include "XGeneralFunc.h"
#include "XAlignmentLarge.h"
#include "XDisplayImagePacket.h"
#include "XPropertyAlignmentLargeCommon.h"

//==============================================================================
AlignmentLargePointList::AlignmentLargePointList(const AlignmentLargePointList &src)
{
	ID				=src.ID;
	AreaID			=src.AreaID;
	ItemID			=src.ItemID;
	GroupNumber		=src.GroupNumber;
	Phase			=src.Phase;
	Layer			=src.Layer;
	Page			=src.Page;
	Cx				=src.Cx;
	Cy				=src.Cy;
	XSize			=src.XSize;
	YSize			=src.YSize;
	MoveDotX		=src.MoveDotX;
	MoveDotY		=src.MoveDotY;
	MoveDotX2		=src.MoveDotX2;
	MoveDotY2		=src.MoveDotY2;
	SearchAround	=src.SearchAround;
	UsageGlobal		=src.UsageGlobal;
	JudgeWithBrDif	=src.JudgeWithBrDif	;
	CharacterMode	=src.CharacterMode	;
	Threshold		=src.Threshold;
	UseLayer		=src.UseLayer		;
	ThresholdColor	=src.ThresholdColor	;
}
bool	AlignmentLargePointList::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,Phase)==false)
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
	if(::Load(f,MoveDotX)==false)
		return false;
	if(::Load(f,MoveDotY)==false)
		return false;
	if(::Load(f,MoveDotX2)==false)
		return false;
	if(::Load(f,MoveDotY2)==false)
		return false;
	if(::Load(f,SearchAround)==false)
		return false;
	if(::Load(f,UsageGlobal)==false)
		return false;
	if(::Load(f,JudgeWithBrDif)==false)
		return false;
	if(::Load(f,CharacterMode)==false)
		return false;
	if(::Load(f,Threshold)==false)
		return false;
	if(::Load(f,UseLayer)==false)
		return false;
	if(::Load(f,ThresholdColor)==false)
		return false;
	return true;
}
bool	AlignmentLargePointList::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,Phase)==false)
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
	if(::Save(f,MoveDotX)==false)
		return false;
	if(::Save(f,MoveDotY)==false)
		return false;
	if(::Save(f,MoveDotX2)==false)
		return false;
	if(::Save(f,MoveDotY2)==false)
		return false;
	if(::Save(f,SearchAround)==false)
		return false;
	if(::Save(f,UsageGlobal)==false)
		return false;
	if(::Save(f,JudgeWithBrDif)==false)
		return false;
	if(::Save(f,CharacterMode)==false)
		return false;
	if(::Save(f,Threshold)==false)
		return false;
	if(::Save(f,UseLayer)==false)
		return false;
	if(::Save(f,ThresholdColor)==false)
		return false;
	return true;
}

AlignmentLargePointList	&AlignmentLargePointList::operator=(AlignmentLargePointList &src)
{
	ID				=src.ID;
	AreaID			=src.AreaID;
	ItemID			=src.ItemID;
	GroupNumber		=src.GroupNumber;
	Phase			=src.Phase;
	Layer			=src.Layer;
	Page			=src.Page;
	Cx				=src.Cx;
	Cy				=src.Cy;
	XSize			=src.XSize;
	YSize			=src.YSize;
	MoveDotX		=src.MoveDotX;
	MoveDotY		=src.MoveDotY;
	MoveDotX2		=src.MoveDotX2;
	MoveDotY2		=src.MoveDotY2;
	SearchAround	=src.SearchAround;
	UsageGlobal		=src.UsageGlobal;
	JudgeWithBrDif	=src.JudgeWithBrDif	;
	CharacterMode	=src.CharacterMode	;
	Threshold		=src.Threshold	;
	UseLayer		=src.UseLayer	;
	ThresholdColor	=src.ThresholdColor;
	return *this;
}

bool	AlignmentLargePointListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentLargePointList *p=new AlignmentLargePointList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentLargePointListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentLargePointList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentLargePointListPack	&AlignmentLargePointListPack::operator=(AlignmentLargePointListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentLargePointListPack	&AlignmentLargePointListPack::operator+=(AlignmentLargePointListPack &src)
{
	for(AlignmentLargePointList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentLargePointList *q=new AlignmentLargePointList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}
