/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\OutlineInspection\OutlineInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "OutlineInspectionResource.h"
#include "XOutlineInspect.h"
#include "XAlgorithmDLL.h"
#include "OutlineHistgram.h"
#include "MonoOutlineForm.h"
#include "XOutlineAlgoPacket.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"OutlineInspection";

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
	return OutlineInspectionVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "輪郭検査";
}
DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"OutlineIns";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	OutlineBase	*base=new OutlineBase(Base);
	base->Initial(Base);

	(*Base)=new SlaveCommReqLibraryInMaskOfOutline(Base,sRoot,sName);
	(*Base)=new SlaveCommAckLibraryInMaskOfOutline(Base,sRoot,sName);

	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}

DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new OutlineInspectLibraryContainer(Base);
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
	MonoOutlineForm	*DFormMono=new MonoOutlineForm(InstBase->GetLayersBase());
	DFormMono->Initial(InstBase ,Data);
	DFormMono->show();
	return DFormMono;
}
DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPLI(parent);
}


DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((OutlineItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((OutlineItem *)item)->Load(f,LBase);
}
