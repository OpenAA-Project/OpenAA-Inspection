/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RegulusWorld\XRWAlgorithmInterface.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XRWAlgorithmInterface.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include "XDatabase.h"
#include "XDatabaseLoader.h"
#include "XErrorCode.h"
#include "XGUIFormBase.h"
#include "XFileRegistry.h"
#include "XMapBuffer.h"
#include "XDataComponent.h"

RWAlgorithmDLLList::RWAlgorithmDLLList(RegulusWorld *base)
	:Base(base)
{
	DLL_GetDLLType				=NULL;
	DLL_GetOrganization			=NULL;
	DLL_GetName					=NULL;
	DLL_GetVersion				=NULL;

	DLL_InitialAlloc			=NULL;
	DLL_Close					=NULL;
	DLL_ReleaseAlgorithmBase	=NULL;
	DLL_CheckCopyright			=NULL;
	DLL_AssociateComponent		=NULL;

	DLL_GetExplain				=NULL;
	DLL_SetLanguage				=NULL;
	DLL_SetLanguageCommon		=NULL;

	DLL_RegistMacroFunction			=NULL;
}
RWAlgorithmDLLList::~RWAlgorithmDLLList(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;

	if(DLL_Close!=NULL){
		InFunc=true;
		DLL_Close();
		InFunc=false;
	}

	if(DllLib.isLoaded()==true){
		DllLib.unload();	//Error occurs in final DLL unload
	}
	ReEntrantDLL=false;
}

bool	RWAlgorithmDLLList::LoadDLL(const QString &filename)
{
	DllLib.setFileName(filename);
	if(DllLib.load()==false)
		return(false);
	DLL_GetDLLType				=(WORD (*)(void))DllLib.resolve("DLL_GetDLLType");
	DLL_GetOrganization			=(bool (*)(QString &))DllLib.resolve("DLL_GetOrganization");
	DLL_GetName					=(bool (*)(QString &Root ,QString &Name))DllLib.resolve("DLL_GetName");
	DLL_GetVersion				=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLLManager::LoadDLL(DllLib)==false){
		return false;
	}
	DLL_GetExplain				=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	DLL_SetLanguage				=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguage");
	DLL_SetLanguageCommon		=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguageCommon");
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");

	DLL_InitialAlloc			=(RW3DBaseRoot *(*)(RegulusWorld *Base))DllLib.resolve("DLL_InitialAlloc");
	DLL_Close					=(void (*)(void))DllLib.resolve(/**/"DLL_Close");
	DLL_ReleaseAlgorithmBase	=(void (*)(RW3DBaseRoot *))DllLib.resolve(/**/"DLL_ReleaseAlgorithmBase");
	DLL_AssociateComponent		=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");

	DLL_RegistMacroFunction		=(int32	(*)(ExportFuncForMacro Functions[],int MaxBuffer))DllLib.resolve("DLL_RegistMacroFunction");

	return(true);
}

void	RWAlgorithmDLLList::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetOrganization!=NULL){
		Str.append("DLL_GetOrganization");
	}
	if(DLL_GetDLLType!=NULL){
		Str.append("DLL_GetDLLType");
	}
	if(DLL_GetName!=NULL){
		Str.append("DLL_GetName");
	}
	if(DLL_GetVersion!=NULL){
		Str.append("DLL_GetVersion");
	}
	if(DLL_GetExplain!=NULL){
		Str.append("DLL_GetExplain");
	}
	if(DLL_SetLanguage!=NULL){
		Str.append("DLL_SetLanguage");
	}
	if(DLL_SetLanguageCommon!=NULL){
		Str.append("DLL_SetLanguageCommon");
	}
	if(DLL_CheckCopyright!=NULL){
		Str.append("DLL_CheckCopyright");
	}
	if(DLL_InitialAlloc!=NULL){
		Str.append("DLL_InitialAlloc");
	}
	if(DLL_Close!=NULL){
		Str.append("DLL_Close");
	}
	if(DLL_ReleaseAlgorithmBase!=NULL){
		Str.append("DLL_ReleaseAlgorithmBase");
	}
	if(DLL_AssociateComponent!=NULL){
		Str.append("DLL_AssociateComponent");
	}
	if(DLL_RegistMacroFunction!=NULL){
		Str.append("DLL_RegistMacroFunction");
	}
	DLLManager::GetExportFunctions(Str);
}

bool		RWAlgorithmDLLList::GetOrganization(QString &str)
{
	if(DLL_GetOrganization!=NULL){
		InFunc=true;
		bool	ret=DLL_GetOrganization(str);
		InFunc=false;
		return ret;
	}
	return false;
}

bool	RWAlgorithmDLLList::IsRWAlgorithm(void)
{
	int	d=GetDLLType();
	if((d&DLLModeMask)==DLLRWAlgorithmMode){
		return(true);
	}
	return(false);
}

WORD	RWAlgorithmDLLList::GetDLLType(void)
{
	if(DLL_GetDLLType!=NULL){
		InFunc=true;
		WORD	ret=DLL_GetDLLType();
		InFunc=false;
		return ret;
	}
	return 0;
}
bool	RWAlgorithmDLLList::GetName(QString &Root ,QString &Name)
{
	if(DLL_GetName!=NULL){
		InFunc=true;
		bool	ret=DLL_GetName(Root ,Name);
		InFunc=false;
		return ret;
	}
	return false;
}
bool	RWAlgorithmDLLList::GetName(void)
{
	return GetName(DLLRoot,DLLName);
}

WORD	RWAlgorithmDLLList::GetVersion(void)
{
	if(DLL_GetVersion!=NULL){
		InFunc=true;
		WORD	ret=DLL_GetVersion();
		InFunc=false;
		return ret;
	}
	return 0;
}

LayersBase		*RWAlgorithmDLLList::GetLayersBase(void)
{
	if(Base!=NULL){
		return Base->GetLayersBase();
	}
	return NULL;
}

const QString	RWAlgorithmDLLList::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		InFunc=true;
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			const QString	ret=QString(c);	
			InFunc=false;
			return ret;
		}
		InFunc=false;
	}
	return /**/"";
}
bool	RWAlgorithmDLLList::SetLanguage(int LanguageCode)
{
	if(DLL_SetLanguage!=NULL){
		InFunc=true;
		DLL_SetLanguageCommon(Base->GetLayersBase()->GetLanguagePackageData(),LanguageCode);
		DLL_SetLanguage(Base->GetLayersBase()->GetLanguagePackageData(),LanguageCode);
		InFunc=false;
		return true;
	}
	return false;
}
bool	RWAlgorithmDLLList::CheckCopyright(QString &CopyrightString)
{
	if(DLL_CheckCopyright!=NULL){
		InFunc=true;
		bool	ret=DLL_CheckCopyright(CopyrightString);
		InFunc=false;
		return ret;
	}
	return false;
}

RW3DBaseRoot	*RWAlgorithmDLLList::InitialAlloc(RegulusWorld *Base)
{
	if(DLL_InitialAlloc!=NULL){
		InFunc=true;
		RW3DBaseRoot	*ret=DLL_InitialAlloc(Base);
		InFunc=false;
		return ret;
	}
	return NULL;
}
bool	RWAlgorithmDLLList::Close(RW3DBaseRoot *handle)
{
	if(DLL_ReleaseAlgorithmBase!=NULL){
		InFunc=true;
		DLL_ReleaseAlgorithmBase(handle);
		InFunc=false;
		return true;
	}
	return false;
}

bool	RWAlgorithmDLLList::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"RWAlgorithmDLL",DLLRoot ,DLLName);
}

int		RWAlgorithmDLLList::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	if(DLL_RegistMacroFunction!=NULL){
		return DLL_RegistMacroFunction(Functions,MaxBuffer);
	}
	return 0;
}
void	RWAlgorithmDLLList::AssociateComponent(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}
int	RWAlgorithmDLLContainer::SearchAddDLL(RegulusWorld *Base 
										,const QStringList &AlgorithmPathList)
{
	int	N=0;
	RWAlgorithmDLLList	*DLL;
	QString	AlgoFileName;

	char	buff[200];

	for(int k=0;k<AlgorithmPathList.count();k++){
		QString	path=AlgorithmPathList[k];

		QString2Char(path,buff,sizeof(buff));
		printf("%s\n",buff);
		QDir::setCurrent(Base->GetLayersBase()->GetSystemPath());
		QString	kstr=QDir::currentPath();
		QDir	Dir;
		if(Dir.cd(path)==true){
			QString	SearchFile=QString("*.")+GetDynamicFileExt();
			QStringList nameFilters(SearchFile);
			QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );

			for(int i=0;i<List.size();i++){
				QString	FileName=path+GetSeparator()+List[i];
				Base->GetLayersBase()->TestLoadDLL(FileName);
				if(QLibrary::isLibrary(FileName)==true){
					DLL=new RWAlgorithmDLLList(Base);
					DLL->SetFileName(FileName);
					printf("LoadDLL\n");
					if(DLL->LoadDLL(FileName)==true){
						printf("LoadDLL OK\n");
						if(DLL->IsRWAlgorithm()==true && DLL->GetName()==true){
							AlgoFileName=List.at(i);

							printf("AppendList\n");
							AppendList(DLL);
							if(Base->GetLayersBase()!=NULL){
								Base->GetLayersBase()->InformToLoadDLL(FileName);
							}
							N++;
						}
						else{
							delete	DLL;
						}
					}
					else{
						delete	DLL;
					}
				}
			}
		}
	}

	return(N);
}


bool	RWAlgorithmDLLContainer::LoadOneDLL(RegulusWorld *Base ,const QString &DLLFileNameWithPath)
{
	Base->GetLayersBase()->TestLoadDLL(DLLFileNameWithPath);
	if(QLibrary::isLibrary(DLLFileNameWithPath)==true){
		RWAlgorithmDLLList	*DLL=new RWAlgorithmDLLList(Base);
		DLL->SetFileName(DLLFileNameWithPath);
		if(DLL->LoadDLL(DLLFileNameWithPath)==true){
			if(DLL->IsRWAlgorithm()==true){
				bool	FoundA=false;
				for(RWAlgorithmDLLList *a=GetFirst();a!=NULL;a=a->GetNext()){
					if(a->CheckDLL(DLL->GetDLLRoot(),DLL->GetDLLName())==true){
						FoundA=true;
					}
				}
				if(FoundA==false){
					AppendList(DLL);
					if(Base->GetLayersBase()!=NULL){
						Base->GetLayersBase()->InformToLoadDLL(DLLFileNameWithPath);
					}
					return true;
				}
			}
		}
		delete	DLL;
	}
	return false;
}


bool	RWAlgorithmDLLContainer::CheckSystemVersion(QStringList &Str)
{
	bool	Ret=true;
	for(RWAlgorithmDLLList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	return Ret;
}
