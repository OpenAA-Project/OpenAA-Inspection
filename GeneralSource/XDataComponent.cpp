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

#include "XDataComponent.h"
#include "XGeneralFunc.h"

RootNameList::RootNameList(const RootNameList &src)
{
	DLLRoot=src.DLLRoot;
	DLLName=src.DLLName;
}
bool	RootNameList::operator==(const RootNameList &s)	const
{
	if(DLLRoot==s.DLLRoot && DLLName==s.DLLName){
		return true;
	}
	return false;
}
bool	RootNameList::operator!=(const RootNameList &s)	const
{
	if(DLLRoot!=s.DLLRoot || DLLName!=s.DLLName){
		return true;
	}
	return false;
}

RootNameList &RootNameList::operator=(const RootNameList &src)
{
	DLLRoot=src.DLLRoot;
	DLLName=src.DLLName;
	return *this;
}
bool	RootNameList::Save(QIODevice *f)
{
	if(::Save(f,DLLRoot)==false){
		return false;
	}
	if(::Save(f,DLLName)==false){
		return false;
	}
	return true;
}
bool	RootNameList::Load(QIODevice *f)
{
	if(::Load(f,DLLRoot)==false){
		return false;
	}
	if(::Load(f,DLLName)==false){
		return false;
	}
	return true;
}

RootNameListContainer::RootNameListContainer(const RootNameListContainer &src)
{
	for(RootNameList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		RootNameList *b=new RootNameList();
		*b=*a;
		AppendList(b);
	}
}

RootNameListContainer	&RootNameListContainer::operator=(const RootNameListContainer &src)
{
	RemoveAll();
	for(RootNameList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		RootNameList *b=new RootNameList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
bool	RootNameListContainer::Exists(const QString &Root ,const QString &Name)
{
	for(RootNameList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->DLLRoot==Root && a->DLLName==Name){
			return true;
		}
	}
	return false;
}
void	RootNameListContainer::Add(const QString &Root ,const QString &Name)
{
	RootNameList	*a=new RootNameList(Root,Name);
	AppendList(a);
}
void	RootNameListContainer::Merge(const QString &Root ,const QString &Name)
{
	for(RootNameList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->DLLRoot==Root && a->DLLName==Name){
			return;
		}
	}
	Add(Root,Name);
}
void	RootNameListContainer::Merge(RootNameList &s)
{
	for(RootNameList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(*a==s){
			return;
		}
	}
	Add(s.DLLRoot,s.DLLName);
}