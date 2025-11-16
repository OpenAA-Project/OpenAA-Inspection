/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\FilterCommon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XDataInLayer.h"
#include "Regulus64Version.h"
#include <QtGlobal>
#include "XPQSystemPlugin.h"
#include "XPQSystemRunner.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}
WORD	DLL_GetDLLType(void)
//	return	DLL type for FilterDLL
{
	return(DLLPQSystemRunner);
}

bool		_cdecl	DLL_Release(PQSystemRunner *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	delete	handle;
	return true;
}
DEFFUNCEX	void	DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangLibSolver.SetLanguage(Pkg,LanguageCode);
}
