/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticBlock\StatisticBlock.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StatisticBlockResource.h"
#include "XAlgorithmDLL.h"
#include "XStatisticBlock.h"
#include "XStatisticBlockLibrary.h"
#include "StatisticHistogramForm.h"
//#include "ChangeShiftForm.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"StatisticBlock";

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
	return StatisticBlockVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "統計的ブロック検査";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"StatisticBlockIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	StatisticBlockBase	*base=new StatisticBlockBase(Base);
	base->Initial(Base);
	Base->SetUseDynamicMasking(true);
	return base;
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new StatisticBlockLibraryContainer(Base);
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeProcessing;
}
DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	StatisticHistogramForm	*DForm=new StatisticHistogramForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPLI(parent);
}


DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((StatisticBlockItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((StatisticBlockItem *)item)->Load(f,LBase);
}
