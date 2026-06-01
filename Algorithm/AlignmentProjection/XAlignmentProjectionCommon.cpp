/*
 * Copyright (C) 2020
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

#include "XPacketAlignmentProjection.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlignmentProjection.h"


bool	AlignmentProjectionDrawAttr::Save(QIODevice *f)
{
	return true;
}
bool	AlignmentProjectionDrawAttr::Load(QIODevice *f)
{
	return true;
}

//==============================================================================
bool	AlignmentProjectionPointList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Phase)==false)
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
	if(::Load(f,PeakCount)==false)
		return false;
	return true;
}
bool	AlignmentProjectionPointList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Phase)==false)
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
	if(::Save(f,PeakCount)==false)
		return false;
	return true;
}

AlignmentProjectionPointList	&AlignmentProjectionPointList::operator=(AlignmentProjectionPointList &src)
{
	ItemID		=src.ItemID;
	Phase		=src.Phase;
	Page		=src.Page;
	Cx			=src.Cx;
	Cy			=src.Cy;
	XSize		=src.XSize;
	YSize		=src.YSize;
	PeakCount	=src.PeakCount;
	return *this;
}

bool	AlignmentProjectionPointListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentProjectionPointList *p=new AlignmentProjectionPointList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentProjectionPointListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentProjectionPointList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentProjectionPointListPack	&AlignmentProjectionPointListPack::operator=(AlignmentProjectionPointListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentProjectionPointListPack	&AlignmentProjectionPointListPack::operator+=(AlignmentProjectionPointListPack &src)
{
	for(AlignmentProjectionPointList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentProjectionPointList *q=new AlignmentProjectionPointList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}
