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

#include "XTypeDef.h"
#include "XGUILanguage.h"
#include "XGeneralFunc.h"

LanguageStringList::LanguageStringList(const LanguageStringList &src)
{
	LanguageCode=src.LanguageCode;
	Text		=src.Text		 ;
	TextList	=src.TextList	 ;
}
bool	LanguageStringList::Save(QIODevice *f)
{
	if(::Save(f,LanguageCode)==false)	return false;
	if(::Save(f,Text		)==false)	return false;
	if(::Save(f,TextList	)==false)	return false;
	return true;
}
bool	LanguageStringList::Load(QIODevice *f)
{
	if(::Load(f,LanguageCode)==false)	return false;
	if(::Load(f,Text		)==false)	return false;
	if(::Load(f,TextList	)==false)	return false;
	return true;
}

LanguageStringList	&LanguageStringList::operator=(const LanguageStringList &src)
{
	LanguageCode=src.LanguageCode;
	Text		=src.Text		 ;
	TextList	=src.TextList	 ;
	return *this;
}
LanguageStringContainer::LanguageStringContainer(const LanguageStringContainer &src)
{
	for(LanguageStringList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		LanguageStringList	*d=new LanguageStringList(*s);
		AppendList(d);
	}
}

LanguageStringList	*LanguageStringContainer::Create(void)
{
	return new LanguageStringList();
}

LanguageStringContainer	&LanguageStringContainer::operator=(const LanguageStringContainer &src)
{
	NPListPackSaveLoad<LanguageStringList>::operator=(src);
	return *this;
}

LanguageStringList	*LanguageStringContainer::FindLanguage(int LanguageCode)	const
{
	for(LanguageStringList *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->LanguageCode==LanguageCode)
			return s;
	}
	return NULL;
}

//===================================================================
GUILanguageList::GUILanguageList(const GUILanguageList &src)
{
	DLLRoot			=src.DLLRoot;
	DLLName			=src.DLLName;
	InstName		=src.InstName;
	MemberName		=src.MemberName;
	LanguageText	=src.LanguageText;
}
bool	GUILanguageList::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver			)==false)	return false;
	if(::Save(f,DLLRoot		)==false)	return false;
	if(::Save(f,DLLName		)==false)	return false;
	if(::Save(f,InstName	)==false)	return false;
	if(::Save(f,MemberName	)==false)	return false;
	if(LanguageText.Save(f)==false)		return false;
	return true;
}
bool	GUILanguageList::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver			)==false)	return false;
	if(::Load(f,DLLRoot		)==false)	return false;
	if(::Load(f,DLLName		)==false)	return false;
	if(::Load(f,InstName	)==false)	return false;
	if(::Load(f,MemberName	)==false)	return false;
	if(LanguageText.Load(f)==false)		return false;
	return true;
}

GUILanguageList	&GUILanguageList::operator=(const GUILanguageList &src)
{
	DLLRoot		=src.DLLRoot	;	
	DLLName		=src.DLLName	;	
	InstName	=src.InstName	;
	MemberName	=src.MemberName	;
	LanguageText=src.LanguageText;
	return *this;
}

GUILanguageList	*GUILanguageContainer::Create(void)
{
	return new GUILanguageList();
}

GUILanguageContainer::GUILanguageContainer(const GUILanguageContainer &src)
{
	for(GUILanguageList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		GUILanguageList	*d=new GUILanguageList(*s);
		AppendList(d);
	}
}
GUILanguageContainer	&GUILanguageContainer::operator=(const GUILanguageContainer &src)
{
	NPListPackSaveLoad<GUILanguageList>::operator=(src);
	return *this;
}

GUILanguageList	*GUILanguageContainer::Find(const QString &FormRoot 
											,const QString &FormName
											,const QString &InstName
											,const QString &MemberName)	const
{
	for(GUILanguageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->DLLRoot==FormRoot
		&& a->DLLName==FormName
		&& a->InstName==InstName
		&& a->MemberName==MemberName){
			return a;
		}
	}
	return NULL;
}