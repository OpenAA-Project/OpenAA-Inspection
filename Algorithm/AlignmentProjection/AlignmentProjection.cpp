/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentProjection\AlignmentProjection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "XAlignmentProjectionResource.h"
#include "XAlgorithmDLL.h"
#include "AlignmentProjection.h"
#include "XAlignmentProjection.h"
#include "SettingAlignmentProjectionForm.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"AlignmentProjection";

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
	return AlignmentProjectionVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "射影アラインメント";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"AlignmentProjection";
}
DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeAlignment;
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	AlgorithmBase	*base=new AlignmentProjectionBase(Base);
	base->Initial(Base);

	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}
DEFFUNCEX	AlignmentPacketBase	*DLL_GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY ,AlgorithmItemRoot *Item,bool FromGlobal)
{
	AlignmentProjectionBase	*abase=dynamic_cast<AlignmentProjectionBase *>(base);
	if(abase!=NULL){
		int	PhaseCode=Item->GetPhaseCode();
		AlgorithmInPageInOnePhase	*Ph=abase->GetPageDataPhase(PhaseCode);
		AlgorithmInPageRoot	*Ap=Ph->GetPageData(localPage);
		return ((AlignmentProjectionInPage *)Ap)->AppendAlignmentProjectionPacket2D(Item,localX,localY,FromGlobal);
	}
	return NULL;
}
DEFFUNCEX	void	DLL_GetAlignmentForProcessing(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet)
{
	AlignmentProjectionBase	*abase=dynamic_cast<AlignmentProjectionBase *>(base);
	if(abase!=NULL){
		AlignmentPacket2D	*p2d=static_cast<AlignmentPacket2D *>(&Packet);
		if(p2d!=NULL)
			((AlignmentProjectionInPage *)(abase->GetPageData(localPage)))->GetAlignmentProjection(*p2d);
	}
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((AlignmentProjectionItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((AlignmentProjectionItem *)item)->Load(f,LBase);
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	SettingAlignmentProjectionForm	*DForm=new SettingAlignmentProjectionForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}

DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

