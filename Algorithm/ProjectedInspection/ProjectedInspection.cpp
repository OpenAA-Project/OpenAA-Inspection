/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ProjectedInspection\ProjectedInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XAlgorithmDLL.h"
#include "ProjectedInspection.h"
#include "XProjectedInspection.h"
#include "XProjectedInspectionLibrary.h"
#include "ProjectionMapForm.h"
#include "XProjectedInspectionAlgoPacket.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"ProjectedInspection";

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
	return ProjectedInspectionVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "射影検査";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"ProjectedInspectionIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	ProjectedInspectionBase	*base=new ProjectedInspectionBase(Base);
	base->Initial(Base);

	//(*Base)=new SlaveCommReqLibraryInMaskOfProjectedInspection(Base,sRoot,sName);
	//(*Base)=new SlaveCommAckLibraryInMaskOfProjectedInspection(Base,sRoot,sName);

	return base;
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new ProjectedInspectionLibraryContainer(Base);
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeProcessing | AlgorithmBit_TypeProcessingRevived;
}
DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	ProjectionMapForm	*DForm=new ProjectionMapForm(InstBase->GetLayersBase());
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
	return ((ProjectedInspectionItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((ProjectedInspectionItem *)item)->Load(f,LBase);
}

