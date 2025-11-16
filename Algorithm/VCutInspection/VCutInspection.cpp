
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\VCutInspection\VCutInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "VCutInspectionResource.h"
#include "VCutInspection.h"
#include "XAlgorithmDLL.h"
#include "XVCutInspection.h"
#include "ShowSettingVCutForm.h"

const	char	*sRoot=/**/"PCB";
const	char	*sName=/**/"VCutInspection";

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
	return VCutInspectionVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Vカット検査";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"VCutInspection";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	VCutInspectionBase	*base=new VCutInspectionBase(Base);
	base->Initial(Base);
	Base->SetUseDynamicMasking(true);
	return base;
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new VCutInspectionLibraryContainer(Base);
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeProcessing;
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
DEFFUNCEX	int			DLL_GetPriority(int AlgorithmBit_Type)
{
	if(AlgorithmBit_Type==PriorityType_ExecuteProcessing)
		return 10;
	return 100;
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	ShowSettingVCutForm	*DForm=new ShowSettingVCutForm(InstBase->GetLayersBase());
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
	return ((AlgorithmItemPI *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((AlgorithmItemPI *)item)->Load(f,LBase);
}

//------------------------------------------------------------------------------------------------------

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff=/**/"Need Fin";
		return false;
	}
	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());

	if(c!=NULL){
		RetStrBuff=c->GetLibName();
	}

	RetStrBuff+=" V-Cut";

	return true;
}


DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos 
										 ,DetailResultInfoListContainer &RetList)
{
	DetailResultInfoList	*L=new DetailResultInfoList("V-Cut");
	L->SetColor(qRgba(160,255,0,100));
	RetList.AppendList(L);
	return true;
}

