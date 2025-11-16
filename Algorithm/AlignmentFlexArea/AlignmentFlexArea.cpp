/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentFlexArea\AlignmentFlexArea.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AlignmentFlexAreaResource.h"
#include "XAlgorithmDLL.h"
#include "AlignmentFlexArea.h"
#include "XAlignmentFlexArea.h"
#include "AdjustAlignmentFlexAreaForm.h"
#include "XPacketAlignmentFlexArea.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"AlignmentFlexArea";

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
	return AlignmentFlexAreaVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "形状でのアラインメント";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"AlignmentFlexArea";
}
DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypePreAlignment | AlgorithmBit_TypeAlignment;
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	AlgorithmBase	*base=new AlignmentFlexAreaBase(Base);
	base->Initial(Base);

	(*Base)=new SlaveCommReqAlignmentFlexAreaPoint	(Base,sRoot,sName);
	(*Base)=new SlaveCommAckAlignmentFlexAreaPoint	(Base,sRoot,sName);
	(*Base)=new SlaveCommReqAlignmentFlexAreaShift	(Base,sRoot,sName);
	(*Base)=new SlaveCommAckAlignmentFlexAreaShift	(Base,sRoot,sName);
	(*Base)=new SlaveCommReqSAreaInWholeMatch		(Base,sRoot,sName);
	(*Base)=new SlaveCommAckSAreaInWholeMatch		(Base,sRoot,sName);
	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new AlignmentFlexAreaLibraryContainer(Base);
}

DEFFUNCEX	AlignmentPacketBase	*DLL_GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY ,AlgorithmItemRoot *Item,bool FromGlobal)
{
	AlignmentFlexAreaBase	*abase=dynamic_cast<AlignmentFlexAreaBase *>(base);
	if(abase!=NULL){
		return ((AlignmentFlexAreaInPage *)(abase->GetPageDataPhase(Item->GetPhaseCode())
											->GetPageData(localPage)))
											->AppendAlignmentFlexAreaPacket2D(Item,localX,localY,FromGlobal);
	}
	return NULL;
}
DEFFUNCEX	int			DLL_GetPriority(int AlgorithmBit_Type)
{
	if(AlgorithmBit_Type==PriorityType_ExecuteInitialAfterEdit)
		return 10;
	return 100;
}
DEFFUNCEX	void	DLL_GetAlignmentForProcessing(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet)
{
	AlignmentFlexAreaBase	*abase=dynamic_cast<AlignmentFlexAreaBase *>(base);
	if(abase!=NULL){
		AlignmentPacket2D	*p2d=static_cast<AlignmentPacket2D *>(&Packet);
		if(p2d!=NULL)
			((AlignmentFlexAreaInPage *)(abase->GetPageData(localPage)))->GetAlignmentFlexArea(*p2d);
	}
}
DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((AlignmentFlexAreaItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((AlignmentFlexAreaItem *)item)->Load(f,LBase);
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	AdjustAlignmentFlexAreaForm	*DForm=new AdjustAlignmentFlexAreaForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}

DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

