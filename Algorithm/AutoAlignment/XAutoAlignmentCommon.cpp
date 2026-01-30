/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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