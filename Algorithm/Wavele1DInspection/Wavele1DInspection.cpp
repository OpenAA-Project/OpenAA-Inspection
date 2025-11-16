/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Wavelet1DInspection\Wavelet1DInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "XWavelet1DInspectionResource.h"
#include "Wavelet1DInspection.h"
#include "XAlgorithmDLL.h"
#include "XWavelet1DInspection.h"
#include "XWavelet1DInspectionLibrary.h"
#include "Wavelet1DHistgramForm.h"
#include "XWavelet1DInspectionAlgoPacket.h"

char	*sRoot=/**/"Basic";
char	*sName=/**/"Wavelet1DInspection";

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
	return Wavelet1DInspectionVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Wavelet 1D Inspection algorithm";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"Wavelet1DInspectionIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(EntryPointBase *EPoint)
{
	Wavelet1DInspectionBase	*base=new Wavelet1DInspectionBase();
	base->Initial(EPoint);

	new SlaveCommReqLibraryInMaskOfWavelet1DInspection(EPoint->GetLayersBase(),sRoot,sName);
	new SlaveCommAckLibraryInMaskOfWavelet1DInspection(EPoint->GetLayersBase(),sRoot,sName);

	return base;
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new Wavelet1DInspectionLibraryContainer(Base);
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
	TrueColorHistgramForm	*DForm=new TrueColorHistgramForm(Something ,InstBase->GetLayersBase());
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
	return ((Wavelet1DInspectionItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((Wavelet1DInspectionItem *)item)->Load(f,LBase);
}
