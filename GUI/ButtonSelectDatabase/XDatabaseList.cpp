/*
 * Copyright (C) 2017
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

#include "ButtonSelectDatabaseResource.h"
#include "XDatabaseList.h"
#include "XGeneralFunc.h"


bool	DatabaseList::Save(QIODevice *f)
{
	if(::Save(f,Name)==false){
		return false;
	}
	if(::Save(f,IP)==false){
		return false;
	}
	if(::Save(f,FileName)==false){
		return false;
	}
	if(::Save(f,PortNo)==false){
		return false;
	}
	return true;
}

bool	DatabaseList::Load(QIODevice *f)
{
	if(::Load(f,Name)==false){
		return false;
	}
	if(::Load(f,IP)==false){
		return false;
	}
	if(::Load(f,FileName)==false){
		return false;
	}
	if(::Load(f,PortNo)==false){
		return false;
	}
	return true;
}

DatabaseListContainer	&DatabaseListContainer::operator=(DatabaseListContainer &src)
{
	RemoveAll();
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}


bool	DatabaseListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(DatabaseList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	DatabaseListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		DatabaseList *c=new DatabaseList();
		if(c->Load(f)==false){
			return false;
		}
		AppendList(c);
	}
	return true;
}