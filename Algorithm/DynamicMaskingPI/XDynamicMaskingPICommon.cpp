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
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XDynamicMaskingPI.h"



bool    DynamicMaskingPIInfoList::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,AbsLR)==false)
		return false;
	if(::Save(f,AbsHR)==false)
		return false;
	if(::Save(f,AbsLG)==false)
		return false;
	if(::Save(f,AbsHG)==false)
		return false;
	if(::Save(f,AbsLB)==false)
		return false;
	if(::Save(f,AbsHB)==false)
		return false;
	if(::Save(f,EnlargeDot)==false)
		return false;
	if(::Save(f,EnsmallDot)==false)
		return false;
	if(::Save(f,BlockWidth)==false)
		return false;
	if(::Save(f,BlockHeight)==false)
		return false;	
	if(::Save(f,Cx)==false)
		return false;	
	if(::Save(f,Cy)==false)
		return false;	
	if(::Save(f,Page)==false)
		return false;	
	BYTE	D=(BYTE)OpeType;
	if(::Save(f,D)==false)
		return false;
	if(::Save(f,DrawColR)==false)
		return false;
	if(::Save(f,DrawColG)==false)
		return false;
	if(::Save(f,DrawColB)==false)
		return false;

	if(::Save(f,AbsLR2)==false)
		return false;
	if(::Save(f,AbsHR2)==false)
		return false;
	if(::Save(f,AbsLG2)==false)
		return false;
	if(::Save(f,AbsHG2)==false)
		return false;
	if(::Save(f,AbsLB2)==false)
		return false;
	if(::Save(f,AbsHB2)==false)
		return false;
	if(::Save(f,EnlargeDot2)==false)
		return false;
	if(::Save(f,EnsmallDot2)==false)
		return false;
	if(::Save(f,DrawColR2)==false)
		return false;
	if(::Save(f,DrawColG2)==false)
		return false;
	if(::Save(f,DrawColB2)==false)
		return false;
	if(::Save(f,Mergin)==false)
		return false;
	if(MaskingColor.Save(f)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,MinSize)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(AdaptedPickupLayers.Save(f)==false)
		return false;
	return(true);
}

bool    DynamicMaskingPIInfoList::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,AbsLR)==false)
		return false;
	if(::Load(f,AbsHR)==false)
		return false;
	if(::Load(f,AbsLG)==false)
		return false;
	if(::Load(f,AbsHG)==false)
		return false;
	if(::Load(f,AbsLB)==false)
		return false;
	if(::Load(f,AbsHB)==false)
		return false;
	if(::Load(f,EnlargeDot)==false)
		return false;
	if(::Load(f,EnsmallDot)==false)
		return false;	
	if(::Load(f,BlockWidth)==false)
		return false;
	if(::Load(f,BlockHeight)==false)
		return false;	
	if(::Load(f,Cx)==false)
		return false;	
	if(::Load(f,Cy)==false)
		return false;	
	if(::Load(f,Page)==false)
		return false;	
	BYTE	D;
	if(::Load(f,D)==false)
		return false;
	OpeType=(DynamicMaskingPIThreshold::OperationType)D;
	if(::Load(f,DrawColR)==false)
		return false;
	if(::Load(f,DrawColG)==false)
		return false;
	if(::Load(f,DrawColB)==false)
		return false;

	if(::Load(f,AbsLR2)==false)
		return false;
	if(::Load(f,AbsHR2)==false)
		return false;
	if(::Load(f,AbsLG2)==false)
		return false;
	if(::Load(f,AbsHG2)==false)
		return false;
	if(::Load(f,AbsLB2)==false)
		return false;
	if(::Load(f,AbsHB2)==false)
		return false;
	if(::Load(f,EnlargeDot2)==false)
		return false;
	if(::Load(f,EnsmallDot2)==false)
		return false;	
	if(::Load(f,DrawColR2)==false)
		return false;
	if(::Load(f,DrawColG2)==false)
		return false;
	if(::Load(f,DrawColB2)==false)
		return false;
	if(::Load(f,Mergin)==false)
		return false;
	if(MaskingColor.Load(f)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,MinSize)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(AdaptedPickupLayers.Load(f)==false)
		return false;
	return(true);
}


bool    DynamicMaskingPIInfoListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(DynamicMaskingPIInfoList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}

bool    DynamicMaskingPIInfoListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		DynamicMaskingPIInfoList *c=new DynamicMaskingPIInfoList();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}

DynamicMaskingPIInfoListContainer	&DynamicMaskingPIInfoListContainer::operator+=(DynamicMaskingPIInfoListContainer &src)
{
	for(DynamicMaskingPIInfoList *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(c->Save(&Buff)==false)
			return *this;
		Buff.seek(0);
		DynamicMaskingPIInfoList *d=new DynamicMaskingPIInfoList();
		if(d->Load(&Buff)==false)
			return *this;
		AppendList(d);
	}
	return *this;
}



