/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\ColorBlockInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ColorBlockInspection.h"
#include "XAlgorithmDLL.h"
#include "XColorBlockInspection.h"
#include "XColorBlockLibrary.h"
#include "ColorHistogramForm.h"
#include "ColorBlockFormResource.h"
#include "ColorChangeShiftForm.h"
#include "XColorBlockAlgoPacket.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"ColorBlockInspection";

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
	return ColorBlockInspectionVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "カラーブロック検査";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"ColorBlockIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	ColorBlockBase	*base=new ColorBlockBase(Base);
	base->Initial(Base);

	(*Base)=new SlaveCommReqLibraryInMaskOfColorBlock(Base,sRoot,sName);
	(*Base)=new SlaveCommAckLibraryInMaskOfColorBlock(Base,sRoot,sName);

	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new ColorBlockLibraryContainer(Base);
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
	ColorHistogramForm	*DForm=new ColorHistogramForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}
DEFFUNCEX	QWidget	*DLL_ChangeItemsAttr(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	ColorChangeShiftForm	*CForm=new ColorChangeShiftForm(InstBase->GetLayersBase());
	CForm->Initial(parent ,InstBase ,Data);
	CForm->show();
	return CForm;
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((ColorBlockItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((ColorBlockItem *)item)->Load(f,LBase);
}

