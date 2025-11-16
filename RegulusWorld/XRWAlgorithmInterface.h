#pragma once

/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XAlgorithmInterfaceDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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

