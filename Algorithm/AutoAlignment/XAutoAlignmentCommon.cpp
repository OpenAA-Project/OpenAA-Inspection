/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoAlignment\XAutoAlignmentPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XGeneralFunc.h"
#include "XAutoAlignmentCommon.h"

AASheetInfoList::AASheetInfoList(int id ,int picosheet,bool createdManual)
{
	ID				=id;
	PicoShift		=picosheet;
	CreatedManual	=createdManual;
}

bool	AASheetInfoList::Load(QIODevice *f)
{
	if(::Load(f,ID)==false){
		return false;
	}
	if(::Load(f,PicoShift)==false){
		return false;
	}
	if(::Load(f,CreatedManual)==false){
		return false;
	}
	return true;
}
bool	AASheetInfoList::Save(QIODevice *f)
{
	if(::Save(f,ID)==false){
		return false;
	}
	if(::Save(f,PicoShift)==false){
		return false;
	}
	if(::Save(f,CreatedManual)==false){
		return false;
	}
	return true;
}

bool	AASheetInfos::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		AASheetInfoList	*a=new AASheetInfoList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
bool	AASheetInfos::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(AASheetInfoList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}


AAListAttr	&AAListAttr::operator=(AAListAttr &src)
{
	LibID=src.LibID;
	CreatedManual	=src.CreatedManual;
	return *this;
}

bool	AAListAttr::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,CreatedManual)==false)
		return false;
	return true;
}
bool	AAListAttr::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,CreatedManual)==false)
		return false;
	return true;
}

void	AAListAttrContainer::Add(int libID, bool createdManual)
{
	AAListAttr *a=new AAListAttr();
	a->LibID		=libID;
	a->CreatedManual=createdManual;
	AppendList(a);
}

AAListAttrContainer	&AAListAttrContainer::operator=(AAListAttrContainer &src)
{
	RemoveAll();
	for(AAListAttr *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		AAListAttr *d=new AAListAttr();
		*d=*s;
		AppendList(d);
	}
	return *this;
}
bool	AAListAttrContainer::IsInclude(int libID ,bool createdManual)
{
	for(AAListAttr *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibID==libID && a->CreatedManual==createdManual){
			return true;
		}
	}
	return false;
}
bool	AAListAttrContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		AAListAttr *a=new AAListAttr();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
bool	AAListAttrContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(AAListAttr *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
