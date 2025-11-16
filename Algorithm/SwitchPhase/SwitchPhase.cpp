/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\SwitchPhase\SwitchPhase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "SwitchPhaseResource.h"
#include "SwitchPhase.h"
#include "XAlgorithmDLL.h"
#include "XSwitchPhase.h"
#include "ShowMarkForm.h"

const	char	*sSwitchPhaseRoot=/**/"Basic";
const	char	*sSwitchPhaseName=/**/"SwitchPhase";

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
	Root=sSwitchPhaseRoot;
	Name=sSwitchPhaseName;
	return true;
}
DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return SwitchPhaseVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Phase切替";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"SwitchPhase";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	SwitchPhaseBase	*base=new SwitchPhaseBase(Base);
	base->Initial(Base);
	return base;
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypePreProcessing;
}
//DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
//{
//	return new SwitchPhaseLibraryContainer(Base);
//}
DEFFUNCEX	int			DLL_GetPriority(int AlgorithmBit_Type)	//0:Strongest 100:Default
{
	if(AlgorithmBit_Type==PriorityType_ExecuteInitialAfterEdit)
		return 20;
	return 100;
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((SwitchPhaseItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((SwitchPhaseItem *)item)->Load(f,LBase);
}
DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}
DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	ShowMarkForm	*DForm=new ShowMarkForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}

DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

