/*
 * Copyright (C) 2016
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

#include "XDistinguishPixCommon.h"
#include "XGeneralFunc.h"

FileListLeaf::FileListLeaf(void)
{
	Judgement=0;
}

bool	FileListLeaf::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,UFolderName)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Judgement)==false)
		return false;
	return true;
}
bool	FileListLeaf::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,UFolderName)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Judgement)==false)
		return false;
	return true;
}

FileListLeaf	*FileListContainer::Find(const QString &UFolderName,const QString &FileName)
{
	for(FileListLeaf *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->UFolderName==UFolderName && a->FileName==FileName){
			return a;
		}
	}
	return NULL;
}

bool	FileListContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;

	for(FileListLeaf *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	FileListContainer::Load(QIODevice *f)
{
	RemoveAll();
	int32	N=GetCount();
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		FileListLeaf	*a=new FileListLeaf();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}