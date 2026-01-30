/*
 * Copyright (C) 2025
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

#pragma once


#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XIntClass.h"
#include "XMapBuffer.h"
#include "XDLLManager.h"
#include "XMacroFunction.h"
#include "XRegulusWorld.h"

class	EntryPointBase;
class	ExcludedListPack;
class	ClipboardAlgorithm;
class	ShowAndSetItemsBaseClass;
class	RootNameListContainer;
class	AlgorithmDefList;
class	QSqlDatabase;
class	ErrorCodeList;
class	LotInformation;
class	LotBase;
class	LanguagePackage;
class	ExecuteInitialAfterEditInfo;

class	RWAlgorithmDLLList : public NPList<RWAlgorithmDLLList>,public DLLManager
{	
	RegulusWorld	*Base;
	QString			FileName;
	QLibrary 		DllLib;

	bool			(*DLL_GetOrganization)(QString &str);
	WORD			(*DLL_GetDLLType)(void);
	bool			(*DLL_GetName)(QString &Root ,QString &Name);
	WORD			(*DLL_GetVersion)(void);
	const char		*(*DLL_GetExplain)(void);
	void			(*DLL_SetLanguage)		(LanguagePackage &Pkg ,int LanguageCode);
	void			(*DLL_SetLanguageCommon)(LanguagePackage &Pkg ,int LanguageCode);
	bool			(*DLL_CheckCopyright)(QString &CopyrightString);
	RW3DBaseRoot	*(*DLL_InitialAlloc)(RegulusWorld *Base);
	void			(*DLL_Close)(void);
	void			(*DLL_ReleaseAlgorithmBase)(RW3DBaseRoot *handle);
	void			(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);	
	int32			(*DLL_RegistMacroFunction)(ExportFuncForMacro Functions[],int MaxBuffer);

	bool			InFunc;

	QString			DLLRoot;
	QString			DLLName;

public:
	RWAlgorithmDLLList(RegulusWorld *Base);
	~RWAlgorithmDLLList(void);

	bool	LoadDLL(const QString &filename);
	virtual	void	GetExportFunctions(QStringList &Str)	override;

	bool			IsRWAlgorithm(void);
	QString			GetFileName(void)		const	{	return FileName;	}
	void			SetFileName(const QString &_FileName){	FileName=_FileName;		}
	bool			GetOrganization(QString &str);
	WORD			GetDLLType(void);
	bool			GetName(QString &Root ,QString &Name);
	bool			GetName(void);
	WORD			GetVersion(void);
	const QString	GetExplain(void);
	bool			SetLanguage(int LanguageCode);
	bool			CheckCopyright(QString &CopyrightString);

	RW3DBaseRoot	*InitialAlloc(RegulusWorld *Base);
	LayersBase		*GetLayersBase(void);
	bool			Close(RW3DBaseRoot *handle);

	bool			CheckDLL(const QString &root, const QString &name)	{	return (DLLRoot==root && DLLName==name)?true:false;	}
	QString			GetDLLRoot(void)	const	{	return DLLRoot;		}
	QString			GetDLLName(void)	const	{	return DLLName;		}
	bool			CheckSystemVersion(QStringList &Str);
	void			AssociateComponent	(ComponentListContainer &List);

	int		RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);
};


class	RWAlgorithmDLLContainer : public NPListPack<RWAlgorithmDLLList>
{
public:
	RWAlgorithmDLLContainer(RegulusWorld *Base){}

	int		SearchAddDLL(RegulusWorld *Base 
						,const QStringList &AlgorithmPath);
	bool	LoadOneDLL(RegulusWorld *Base ,const QString &DLLFileNameWithPath);
	bool	CheckSystemVersion(QStringList &Str);

};
