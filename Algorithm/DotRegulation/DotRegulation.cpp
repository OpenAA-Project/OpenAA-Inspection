/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DotRegulation\DotRegulation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DotRegulation.h"
#include "XAlgorithmDLL.h"
#include "XDotRegulation.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"DotRegulation";

DEFFUNCEX	bool		DLL_GetOrganization(QString &str)
{
	str=/**/"MEGATRADE";
	return true;
}
DEFFUNCEX	WORD		DLL_GetDLLType(void)
{
	return DLLAlgorithmMode;
}
DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return true;
}
DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return DotRegulationVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "正規化ドット計測";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"DotRegulation";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	DotRegulationBase	*base=new DotRegulationBase(Base);
	base->Initial(Base);
	return base;
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return NULL;
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return 0;
}
DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType)
{
	return NULL;
}
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType)
{
	return true;
}
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d)
{
	delete	d;
}


DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPLI(parent);
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((AlgorithmItemPLI *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((AlgorithmItemPLI *)item)->Load(f,LBase);
}

