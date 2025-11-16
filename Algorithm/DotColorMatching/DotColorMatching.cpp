/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DotColorMatchingInspection\DotColorMatchingInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DotColorMatchingResource.h"
#include "XAlgorithmDLL.h"
#include "XDotColorMatching.h"
#include "XDotColorMatchingLibrary.h"
#include "XTypeDef.h"
#include "HistgramDotColorMatchingForm.h"
#include "XDirectCommPacket.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"DotColorMatching";

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
	return DotColorMatchingInspectionVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "カラーマッチング検査";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"DotColorMatchingIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	DotColorMatchingBase	*base=new DotColorMatchingBase(Base);
	base->Initial(Base);

	//(*Base)=new SlaveCommReqLibraryInMaskOfDotColorMatching(Base,sRoot,sName);
	//(*Base)=new SlaveCommAckLibraryInMaskOfDotColorMatching(Base,sRoot,sName);
	(*Base)=new GUICmdReqHSVPanelImage	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckHSVPanelImage	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqHSVValue		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckHSVValue		(Base, QString(sRoot), QString(sName));

	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new DotColorMatchingLibraryContainer(Base);
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
	HistgramDotColorMatchingForm	*DForm=new HistgramDotColorMatchingForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}
DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}


DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((DotColorMatchingItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((DotColorMatchingItem *)item)->Load(f,LBase);
}

