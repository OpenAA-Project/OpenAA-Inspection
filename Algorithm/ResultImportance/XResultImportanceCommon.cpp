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
#include "XResultImportance.h"


bool	ResultImportanceList::Load(QIODevice *f)
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
	if(::Load(f,ImportanceLevel)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;

	return true;
}

bool	ResultImportanceList::Save(QIODevice *f)
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
	if(::Save(f,ImportanceLevel)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;

	return true;
}

ResultImportanceListForPacketPack	&ResultImportanceListForPacketPack::operator+=(ResultImportanceListForPacketPack &src)
{
	for(ResultImportanceList *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		ResultImportanceList *d=new ResultImportanceList();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		c->Save(&Buff);
		Buff.seek(0);
		d->Load(&Buff);
		AppendList(d);
	}
	return *this;
}
bool	ResultImportanceListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		ResultImportanceList *c=new ResultImportanceList();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}
bool	ResultImportanceListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(ResultImportanceList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
