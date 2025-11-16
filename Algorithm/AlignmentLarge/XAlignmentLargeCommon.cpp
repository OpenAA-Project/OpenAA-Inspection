#include "XPacketAlignmentLarge.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlignmentLarge.h"

//==========================================================================

ReqAlignmentLargeAreaList	&ReqAlignmentLargeAreaList::operator=(ReqAlignmentLargeAreaList &src)
{
	AreaID		=src.AreaID;
	GlobalPage	=src.GlobalPage;
	Layer		=src.Layer;
	return *this;
}

//==========================================================================

bool	ReqAlignmentLargeAreaList::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}
bool	ReqAlignmentLargeAreaList::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
bool	ReqAlignmentLargeAreaListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(ReqAlignmentLargeAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	ReqAlignmentLargeAreaListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		ReqAlignmentLargeAreaList *a=new ReqAlignmentLargeAreaList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
bool	AlignmentLargeDrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&DrawKind,sizeof(DrawKind))!=sizeof(DrawKind))
		return false;
	if(f->write((const char *)&DrawMode,sizeof(DrawMode))!=sizeof(DrawMode))
		return false;
	if(AList.Save(f)==false)
		return false;
	if(Priority.Save(f)==false)
		return false;
	return true;
}
bool	AlignmentLargeDrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&DrawKind,sizeof(DrawKind))!=sizeof(DrawKind))
		return false;
	if(f->read((char *)&DrawMode,sizeof(DrawMode))!=sizeof(DrawMode))
		return false;
	if(AList.Load(f)==false)
		return false;
	if(Priority.Load(f)==false)
		return false;
	return true;
}

//==================================================================================

bool	AlignmentLargeShiftList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,CalcDone)==false)
		return false;
	if(::Save(f,ShiftX)==false)
		return false;
	if(::Save(f,ShiftY)==false)
		return false;
	if(::Save(f,MasterX)==false)
		return false;
	if(::Save(f,MasterY)==false)
		return false;
	return true;
}

bool	AlignmentLargeShiftList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,CalcDone)==false)
		return false;
	if(::Load(f,ShiftX)==false)
		return false;
	if(::Load(f,ShiftY)==false)
		return false;
	if(::Load(f,MasterX)==false)
		return false;
	if(::Load(f,MasterY)==false)
		return false;
	return true;
}

//==================================================================================
ReqAlignmentLargeAreaListPack &ReqAlignmentLargeAreaListPack::operator=(ReqAlignmentLargeAreaListPack &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
ReqAlignmentLargeAreaListPack &ReqAlignmentLargeAreaListPack::operator+=(ReqAlignmentLargeAreaListPack &src)
{
	for(ReqAlignmentLargeAreaList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ReqAlignmentLargeAreaList *b=new ReqAlignmentLargeAreaList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
bool	ReqAlignmentLargeAreaListPack::LayerExists(int page ,int layer)
{
	for(ReqAlignmentLargeAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GlobalPage==page && a->Layer==layer)
			return true;
	}
	return false;
}

bool	ReqAlignmentLargeAreaListPack::ExistsAreaID(int areaID)
{
	for(ReqAlignmentLargeAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID==areaID)
			return true;
	}
	return false;
}
bool	ReqAlignmentLargeAreaListPack::Exists(int page ,int layer,int areaID)
{
	for(ReqAlignmentLargeAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GlobalPage==page && a->Layer==layer && a->AreaID==areaID)
			return true;
	}
	return false;
}
