#include "XAlignmentBlockCommon.h"
#include "XGeneralFunc.h"

AlignmentBlockItemList::AlignmentBlockItemList(const AlignmentBlockItemList &src)
{
	ItemID						=src.ItemID						;
	X1							=src.X1							;
	Y1							=src.Y1							;
	X2							=src.X2							;
	Y2							=src.Y2							;
	CurrentRotationPatternNo	=src.CurrentRotationPatternNo	;
	ResultRadian				=src.ResultRadian				;
	ResultDx					=src.ResultDx					;
	ResultDy					=src.ResultDy					;
}

AlignmentBlockItemList	&AlignmentBlockItemList::operator=(const AlignmentBlockItemList &src)
{
	ItemID						=src.ItemID						;
	X1							=src.X1							;
	Y1							=src.Y1							;
	X2							=src.X2							;
	Y2							=src.Y2							;
	CurrentRotationPatternNo	=src.CurrentRotationPatternNo	;
	ResultRadian				=src.ResultRadian				;
	ResultDx					=src.ResultDx					;
	ResultDy					=src.ResultDy					;
	return *this;
}

bool	AlignmentBlockItemList::Save(QIODevice *f)
{
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,X1		)==false)	return false;
	if(::Save(f,Y1		)==false)	return false;
	if(::Save(f,X2		)==false)	return false;
	if(::Save(f,Y2		)==false)	return false;
	if(::Save(f,CurrentRotationPatternNo	)==false)	return false;
	if(::Save(f,ResultRadian	)==false)	return false;
	if(::Save(f,ResultDx	)==false)	return false;
	if(::Save(f,ResultDy	)==false)	return false;
	return true;
}
bool	AlignmentBlockItemList::Load(QIODevice *f)
{
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,X1		)==false)	return false;
	if(::Load(f,Y1		)==false)	return false;
	if(::Load(f,X2		)==false)	return false;
	if(::Load(f,Y2		)==false)	return false;
	if(::Load(f,CurrentRotationPatternNo	)==false)	return false;
	if(::Load(f,ResultRadian	)==false)	return false;
	if(::Load(f,ResultDx	)==false)	return false;
	if(::Load(f,ResultDy	)==false)	return false;
	return true;
}

AlignmentBlockItemListContainer::AlignmentBlockItemListContainer(const AlignmentBlockItemListContainer &src)
{
	for(AlignmentBlockItemList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		AlignmentBlockItemList *d=new AlignmentBlockItemList(*s);
		AppendList(d);
	}
}

AlignmentBlockItemListContainer	&AlignmentBlockItemListContainer::operator=(const AlignmentBlockItemListContainer &src)
{
	RemoveAll();
	for(AlignmentBlockItemList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		AlignmentBlockItemList *d=new AlignmentBlockItemList(*s);
		AppendList(d);
	}
	return *this;
}
AlignmentBlockItemList	*AlignmentBlockItemListContainer::Create(void)
{
	return new AlignmentBlockItemList();
}