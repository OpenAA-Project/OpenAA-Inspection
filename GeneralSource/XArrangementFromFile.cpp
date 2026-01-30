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
#include "XArrangementFromFile.h"
#include "XArrangementDLL.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XErrorCode.h"
#include "XDataInLayer.h"

ArrangementDLLClass::ArrangementDLLClass(LayersBase *base)
	:ServiceForLayers(base)
{
	DLL_GetOrganization	=NULL;
	DLL_GetDLLType		=NULL;
	DLL_GetName			=NULL;
	DLL_GetVersion		=NULL;
	DLL_GetSystemVersion=NULL;
	DLL_GetExplain		=NULL;

	DLL_Initial			=NULL;
	
	DLL_GetFileExtType	=NULL;
	DLL_LoadFromFile	=NULL;
	DLL_LoadFromStream	=NULL;
}
ArrangementDLLClass::~ArrangementDLLClass(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;

	if(DllLib.isLoaded()==true){
		DllLib.unload();
	}
	ReEntrantDLL=false;
}

bool		ArrangementDLLClass::LoadDLL(QString &filename)
{
	DllLib.setFileName(filename);
	if(DllLib.load()==false){
		return(false);
	}
	FileName=filename;

	DLL_GetDLLType		=(WORD (*)(void))DllLib.resolve("DLL_GetDLLType");
	DLL_GetOrganization	=(bool (*)(QString &))DllLib.resolve("DLL_GetOrganization");
	DLL_GetName			=(bool (*)(QString &Root ,QString &Name))DllLib.resolve("DLL_GetName");
	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	DLL_GetSystemVersion=(const char *(*)(VersionType vtype))DllLib.resolve("DLL_GetSystemVersion");

	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	
	DLL_Initial			=(bool (*)(LayersBase *))DllLib.resolve("DLL_Initial");

	DLL_GetFileExtType	=(bool (*)(QString &ExtTypeStr))DllLib.resolve("DLL_GetFileExtType");
	DLL_LoadFromFile	=(bool (*)(QString &FileName ,NPListPack<ArrangementItem> &RetList))DllLib.resolve("DLL_LoadFromFile");
	DLL_LoadFromStream	=(bool (*)(QIODevice *DevStr ,NPListPack<ArrangementItem> &RetList))DllLib.resolve("DLL_LoadFromStream");

	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(filename);
	}
	return(true);
}
bool		ArrangementDLLClass::IsArrangementDLL(void)
{
	if(DLL_GetDLLType!=NULL){
		int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLArrangement){
			return(true);
		}
	}
	return(false);
}
bool		ArrangementDLLClass::Initial(LayersBase *Base)
{
	if(DLL_GetVersion!=NULL){
		Ver=DLL_GetVersion();
	}
	if(DLL_GetName!=NULL){
		DLL_GetName(DLLRoot,DLLName);
	}
	if(DLL_GetOrganization!=NULL){
		DLL_GetOrganization(Organization);
	}

	if(DLL_Initial!=NULL){
		if(DLL_Initial(Base)==false){
			return false;
		}
	}
	return(true);
}

bool		ArrangementDLLClass::GetFileExtType(QString &ExtTypeStr)
{
	if(DLL_GetFileExtType!=NULL){
		return DLL_GetFileExtType(ExtTypeStr);
	}
	return false;
}
bool		ArrangementDLLClass::LoadFile(QString &FileName ,NPListPack<ArrangementItem> &RetList)
{
	if(QFile::exists (FileName)==false){
		return false;
	}

	if(DLL_LoadFromFile!=NULL){
		return DLL_LoadFromFile(FileName ,RetList);
	}

	QFile	F(FileName);
	if(F.open(QIODevice::ReadOnly)==false){
		return false;
	}
	if(DLL_LoadFromStream!=NULL){
		return DLL_LoadFromStream(&F ,RetList);
	}
	return false;
}


bool	ArrangementDLLClass::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"ArrangementDLL",DLLRoot ,DLLName);
}

void	ArrangementDLLClass::CopyPointerFrom(ArrangementDLLClass &src)
{
	DLL_GetOrganization	=src.DLL_GetOrganization;
	DLL_GetDLLType		=src.DLL_GetDLLType;
	DLL_GetName			=src.DLL_GetName;
	DLL_GetVersion		=src.DLL_GetVersion;
	DLL_GetSystemVersion=src.DLL_GetSystemVersion;
	DLL_GetExplain		=src.DLL_GetExplain;

	DLL_Initial			=src.DLL_Initial;

	DLL_GetFileExtType	=src.DLL_GetFileExtType;
	DLL_LoadFromFile	=src.DLL_LoadFromFile;
	DLL_LoadFromStream	=src.DLL_LoadFromStream;

	FileName			=src.FileName;
	Organization		=src.Organization;
	DLLRoot				=src.DLLRoot;
	DLLName				=src.DLLName;
	Ver					=src.Ver;
}

//===============================================================================================

ArrangementDLLBase::ArrangementDLLBase(LayersBase *Base)
:ServiceForLayers(Base)
{
}

int	ArrangementDLLBase::SearchAddDLL(QString path)
{
	QDir	Dir(path);

	char	buff[200];
	QString2Char(path,buff,sizeof(buff));
	printf("%s\n",buff);

	QString	SearchFile=QString("*.")+GetDynamicFileExt();
	QStringList nameFilters(SearchFile);
	QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );
	int	N=0;
	for(int i=0;i<List.size();i++){
		QString	FileName=path+QString(GetSeparator())+List.at(i);
		GetLayersBase()->TestLoadDLL(FileName);
		if(QLibrary::isLibrary(FileName)==true){
			ArrangementDLLClass	*DLL=new ArrangementDLLClass(GetLayersBase());
			DLL->FileName=FileName;
			printf("ArrangementDLL\n");
			if(DLL->LoadDLL(FileName)==true){
				printf("LoadDLL OK\n");
				if(DLL->IsArrangementDLL()==true){
					printf("Initialc\n");
					DLL->Initial(GetLayersBase());

					printf("AppendList\n");
					AppendList(DLL);
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
	return(N);
}

bool	ArrangementDLLBase::CheckSystemVersion(QStringList &Str)
{
	bool	Ret=true;
	for(ArrangementDLLClass *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	return Ret;
}

void	ArrangementDLLBase::CopyPointerFrom(ArrangementDLLBase &src)
{
	RemoveAll();
	for(ArrangementDLLClass *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ArrangementDLLClass *b=new ArrangementDLLClass(GetLayersBase());
		b->CopyPointerFrom(*a);
		AppendList(b);
	}
}
