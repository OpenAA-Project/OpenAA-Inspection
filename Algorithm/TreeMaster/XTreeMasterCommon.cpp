/*
 * Copyright (C) 2013
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

#include "XTreeMasterCommon.h"
#include "XGeneralFunc.h"


bool	AreaWithColor::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(Color.Save(f)==false)
		return false;
	return true;
}

bool	AreaWithColor::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(Color.Load(f)==false)
		return false;
	return true;
}

void	AreaWithColor::MoveTo(int dx ,int dy)
{
	Area.MoveToNoClip(dx,dy);
}

//====================================================

void	AreaWithColorContainer::MoveTo(int dx ,int dy)
{
	for(AreaWithColor *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveTo(dx,dy);
	}
}
//========================================================================================

TreeMasterResultList	&TreeMasterResultList::operator=(TreeMasterResultList &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Save(&Buff)==false){
		return *this;
	}
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

bool	TreeMasterResultList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,CatName)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,ResultE)==false)
		return false;
	return true;
}

bool	TreeMasterResultList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,CatName)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,ResultE)==false)
		return false;
	return true;
}

TreeMasterResultList	*TreeMasterResultListForPacketPack::FindByItemID(int TMItemID)
{
	for(TreeMasterResultList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ItemID==TMItemID){
			return (c);
		}
	}
	return NULL;
}

//==========================================================================================

bool	TreeMasterList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,CatName)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,MasterName)==false)
		return false;
	if(::Load(f,AlertMask)==false)
		return false;
	return true;
}

bool	TreeMasterList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,CatName)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,MasterName)==false)
		return false;
	if(::Save(f,AlertMask)==false)
		return false;
	return true;
}

TreeMasterList	&TreeMasterList::operator=(TreeMasterList &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

TreeMasterList	*TreeMasterListForPacketPack::FindByItemID(int TMItemID)
{
	for(TreeMasterList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ItemID==TMItemID){
			return (c);
		}
	}
	return NULL;
}

TreeMasterList	*TreeMasterListForPacketPack::FindByMasterCode(int MasterCode)
{
	for(TreeMasterList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->MasterCode==MasterCode){
			return (c);
		}
	}
	return NULL;
}

void TreeMasterListForPacketPack::decreaseID(int BaseID){
	for(TreeMasterList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ItemID>BaseID){
			c->ItemID--;
		}
	}
}

TreeMasterListForPacketPack	&TreeMasterListForPacketPack::operator+=(TreeMasterListForPacketPack &src)
{
	for(TreeMasterList *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		TreeMasterList *d=new TreeMasterList();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		c->Save(&Buff);
		Buff.seek(0);
		d->Load(&Buff);
		AppendList(d);
	}
	return *this;
}
bool	TreeMasterListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		TreeMasterList *c=new TreeMasterList();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}
bool	TreeMasterListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(TreeMasterList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
