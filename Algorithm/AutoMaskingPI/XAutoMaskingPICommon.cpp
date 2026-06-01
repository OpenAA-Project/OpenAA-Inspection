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
#include "XAutoMaskingPI.h"


bool	AutoMaskingPIListForPacket::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
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
	if(::Save(f,Effective)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	return true;
}
bool	AutoMaskingPIListForPacket::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
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
	if(::Load(f,Effective)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	return true;
}
AutoMaskingPIListForPacket	&AutoMaskingPIListForPacket::operator=(AutoMaskingPIListForPacket &src)
{
	ItemID	=src.ItemID;
	Page	=src.Page;
	x1		=src.x1;
	y1		=src.y1;
	x2		=src.x2;
	y2		=src.y2;
	Effective	=src.Effective;
	LimitedLib	=src.LimitedLib;
	return *this;
}


bool	AutoMaskingPIListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AutoMaskingPIListForPacket *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
bool	AutoMaskingPIListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		AutoMaskingPIListForPacket	*c=new AutoMaskingPIListForPacket();
		if(c->Load(f)==false)
			return false;
	}
	return true;
}

AutoMaskingPIListForPacketPack	&AutoMaskingPIListForPacketPack::operator=(AutoMaskingPIListForPacketPack &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
AutoMaskingPIListForPacketPack	&AutoMaskingPIListForPacketPack::operator+=(AutoMaskingPIListForPacketPack &src)
{
	for(AutoMaskingPIListForPacket *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		AutoMaskingPIListForPacket *d=new AutoMaskingPIListForPacket();
		*d=*c;
		AppendList(d);
	}
	return *this;
}
