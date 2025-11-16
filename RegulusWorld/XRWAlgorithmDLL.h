#pragma once
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\RegulusWorld\XRWAlgorithmDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QtGui>
#include <QColor>
#include <QString>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XCSV.h"
#include "XDataComponent.h"
#include "XRegulusWorld.h"
#include "XMacroFunction.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	LanguagePackage;

extern	"C"{

struct	DllToAppFuncs
{
	void		(*APP_MouseMove)(int gx ,int gy);
};


#ifdef _MSC_VER
DEFFUNCEX	bool		DLL_GetOrganization(QString &str);
DEFFUNCEX	WORD		DLL_GetDLLType(void);
DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	WORD		DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	bool		DLL_CheckCopyright(QString &CopyrightString);
DEFFUNCEX	const char	*DLL_GetExplain(void);
DEFFUNCEX	void		DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	void		DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);

DEFFUNCEX	RW3DBaseRoot	*DLL_InitialAlloc(RegulusWorld *Base);
DEFFUNCEX	void		DLL_Close(void);
DEFFUNCEX	void		ReleaseAlgorithmBase(RW3DBaseRoot *handle);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);

DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);
#endif

};
