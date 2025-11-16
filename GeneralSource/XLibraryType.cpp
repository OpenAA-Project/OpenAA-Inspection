/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XLibraryType.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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