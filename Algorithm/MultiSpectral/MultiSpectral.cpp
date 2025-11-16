/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MultiSpectral\MultiSpectral.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "MultiSpectral.h"
#include "XAlgorithmDLL.h"
#include "XMultiSpectral.h"
#include "XMultiSpectralLibrary.h"
#include "AdjustMultipectalForm.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"MultiSpectral";

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
	return MultiSpectralVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Multi spectral process";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"MultiSpectral";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	MultiSpectralBase	*base=new MultiSpectralBase(Base);
	base->Initial(Base);

	(*Base)=new GUICmdReqPanelImage	(Base,sRoot,sName);
	(*Base)=new GUICmdAckPanelImage	(Base,sRoot,sName);
	(*Base)=new GUICmdReqComparedPanelImage	(Base,sRoot,sName);
	(*Base)=new GUICmdAckComparedPanelImage	(Base,sRoot,sName);
	return base;
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeProcessing;
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((MultiSpectralItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((MultiSpectralItem *)item)->Load(f,LBase);
}
DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new MultiSpectralLibraryContainer(Base);
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	AdjustMultipectalForm	*DForm=new AdjustMultipectalForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}
DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

