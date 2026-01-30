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
#include <QSqlQuery>
#include "XLibraryType.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XDatabaseLoader.h"

void	LibTypeListContainer::LoadFromDatabase(LayersBase *Base)
{
	if(Base->GetDatabaseLoader()){
		RemoveAll();
		QSqlQuery	*query=Base->GetDatabaseLoader()->S_GetLibraryTypeFirst(Base->GetDatabase());
		if(Base->GetDatabaseLoader()->S_FindNext(query)==true){
			do{
				int		LibType;
				QString	LibName;
				Base->GetDatabaseLoader()->S_GetLibraryTypeData(query,LibType,LibName);
				LibraryTypeList	*L=new LibraryTypeList();
				L->SetLibType(LibType);
				L->SetLibName(LibName);
				AppendList(L);
			}while(Base->GetDatabaseLoader()->S_FindNext(query)==true);
		}
		Base->GetDatabaseLoader()->S_DeleteLibraryType(query);
	}
}
void	LibTypeListContainer::LoadFromDatabaseInstalled(LayersBase *Base ,LogicDLLBaseClass *LContainer)
{
	if(Base->GetDatabaseLoader()){
		RemoveAll();
		QSqlQuery	*query=Base->GetDatabaseLoader()->S_GetLibraryTypeFirst(Base->GetDatabase());
		if(Base->GetDatabaseLoader()->S_FindNext(query)==true){
			do{
				int		LibType;
				QString	LibName;
				Base->GetDatabaseLoader()->S_GetLibraryTypeData(query,LibType,LibName);
				LogicDLL	*L=LContainer->SearchByLibType(LibType);
				if(L!=NULL){
					LibraryTypeList	*L=new LibraryTypeList();
					L->SetLibType(LibType);
					L->SetLibName(LibName);
					AppendList(L);
				}
			}while(Base->GetDatabaseLoader()->S_FindNext(query)==true);
		}
		Base->GetDatabaseLoader()->S_DeleteLibraryType(query);
	}
}


LibraryTypeList	*LibTypeListContainer::FindLibraryType(int LibType)
{
	for(LibraryTypeList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==LibType){
			return a;
		}
	}
	return NULL;
}

QString	LibTypeListContainer::FindLibraryTypeName(int LibType)
{
	LibraryTypeList	*s=FindLibraryType(LibType);
	if(s==NULL){
		return /**/"";
	}
	return	s->GetLibName();
}