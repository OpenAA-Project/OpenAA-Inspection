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
#include <cmath>
#include "XDLLManager.h"
#include "XErrorCode.h"


DLLManager::DLLManager(void)
{
	DLL_GetSystemVersion			=NULL;
	DLL_GetRelatedDLL				=NULL;
	DLL_GetRelatedDLLSystemVersion	=NULL;
	ReEntrantDLL					=false;
}
DLLManager::~DLLManager(void)
{
	DLL_GetSystemVersion			=NULL;
	DLL_GetRelatedDLL				=NULL;
	DLL_GetRelatedDLLSystemVersion	=NULL;
	ReEntrantDLL					=false;
}

bool	DLLManager::LoadDLL(QLibrary &DllLib)
{
	DLL_GetSystemVersion		=(const char *(*)(VersionType vtype))DllLib.resolve("DLL_GetSystemVersion");
	if(DLL_GetSystemVersion==NULL){
		return false;
	}
	DLL_GetRelatedDLL			=(bool (*)(QStringList &DLLFileNames))DllLib.resolve("DLL_GetRelatedDLL");
	DLL_GetRelatedDLLSystemVersion	=(char *(*)(const QString &DLLFileName ,VersionType vtype))DllLib.resolve("DLL_GetRelatedDLLSystemVersion");

	return true;
}

bool	DLLManager::GetRelatedDLL(QStringList &DLLFileNames)
{
	if(DLL_GetRelatedDLL!=NULL){
		return DLL_GetRelatedDLL(DLLFileNames);
	}
	return false;
}
	
char	*DLLManager::GetRelatedDLLSystemVersion(const QString &DLLFileName ,VersionType vtype)
{
	if(DLL_GetRelatedDLLSystemVersion!=NULL){
		return DLL_GetRelatedDLLSystemVersion(DLLFileName ,vtype);
	}
	return NULL;
}

const char	*DLLManager::GetSystemVersion(VersionType vtype)
{
	if(DLL_GetSystemVersion!=NULL){
		const char	*ret=DLL_GetSystemVersion(vtype);
		return ret;
	}
	return NULL;
}

bool	DLLManager::CheckSystemVersionFunc(QStringList &Str 
										   ,const QString &DLLType 
										   ,const QString &DLLRoot 
										   ,const QString &DLLName)
{
	return ::CheckSystemVersionFunc(Str 
							   ,DLLType 
							   ,DLLRoot 
							   ,DLLName 
							   ,DLL_GetSystemVersion);
}
void	DLLManager::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetSystemVersion!=NULL){
		Str.append("DLL_GetSystemVersion");
	}
	if(DLL_GetRelatedDLL!=NULL){
		Str.append("DLL_GetRelatedDLL");
	}
	if(DLL_GetRelatedDLLSystemVersion!=NULL){
		Str.append("DLL_GetRelatedDLLSystemVersion");
	}
}