/*
 * Copyright (C) 2015
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

#include "XAutoSaveImage.h"
#include "XGeneralFunc.h"
#include <QBuffer>

bool	BandImageFileList::Load(QIODevice *f)
{
	if(::Load(f,BaseFileName)==false)
		return false;
	if(::Load(f,EachFileNames)==false)
		return false;
	return true;
}
bool	BandImageFileList::Save(QIODevice *f)
{
	if(::Save(f,BaseFileName)==false)
		return false;
	if(::Save(f,EachFileNames)==false)
		return false;
	return true;
}

BandImageFileList	&BandImageFileList::operator=(BandImageFileList &src)
{
	BaseFileName	=src.BaseFileName;
	EachFileNames	=src.EachFileNames;
	return *this;
}

bool	BandImageFileContainer::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		BandImageFileList	*L=new BandImageFileList();
		if(L->Load(f)==false)
			return false;
		AppendList(L);
	}
	return true;
}
bool	BandImageFileContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(BandImageFileList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false)
			return false;
	}
	return true;
}

BandImageFileContainer	&BandImageFileContainer::operator=(BandImageFileContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}