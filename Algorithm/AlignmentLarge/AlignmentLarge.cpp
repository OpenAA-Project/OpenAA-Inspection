/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentLarge\AlignmentLarge.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XAlignmentLargeResource.h"
#include "XAlgorithmDLL.h"
#include "AlignmentLarge.h"
#include "XAlignmentLarge.h"
#include "AdjustAlignmentLargeForm.h"
#include "XPacketAlignmentLarge.h"


const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"AlignmentLarge";

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
	return AlignmentLargeVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "広域でのアラインメント";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"AlignmentLarge";
}
DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypePreAlignment | AlgorithmBit_TypeAlignment;
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	AlgorithmBase	*base=new AlignmentLargeBase(Base);
	base->Initial(Base);

	(*Base)=new SlaveCommReqAlignmentLargePoint(Base,sRoot,sName);
	(*Base)=new SlaveCommAckAlignmentLargePoint(Base,sRoot,sName);
	(*Base)=new SlaveCommReqAlignmentLargeShift(Base,sRoot,sName);
	(*Base)=new SlaveCommAckAlignmentLargeShift(Base,sRoot,sName);
	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new AlignmentLargeLibraryContainer(Base);
}
DEFFUNCEX	AlignmentPacketBase	*DLL_GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY ,AlgorithmItemRoot *Item,bool FromGlobal)
{
	AlignmentLargeBase	*abase=dynamic_cast<AlignmentLargeBase *>(base);
	if(abase!=NULL){
		int	PhaseCode=Item->GetPhaseCode();
		AlgorithmInPageInOnePhase	*Ph=abase->GetPageDataPhase(PhaseCode);
		AlgorithmInPageRoot	*Ap=Ph->GetPageData(localPage);
		return ((AlignmentLargeInPage *)Ap)->AppendAlignmentLargePacket2D(Item,localX,localY,FromGlobal);
	}
	return NULL;
}
DEFFUNCEX	void	DLL_GetAlignmentForProcessing(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet)
{
	AlignmentLargeBase	*abase=dynamic_cast<AlignmentLargeBase *>(base);
	if(abase!=NULL){
		AlignmentPacket2D	*p2d=static_cast<AlignmentPacket2D *>(&Packet);
		if(p2d!=NULL)
			((AlignmentLargeInPage *)(abase->GetPageData(localPage)))->GetAlignmentLarge(*p2d);
	}
}
DEFFUNCEX	void	DLL_GetAlignmentForProcessingByHandle(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet,void *Handle)
{
	AlignmentLargeBase	*abase=dynamic_cast<AlignmentLargeBase *>(base);
	if(abase!=NULL){
		AlignmentPacket2D	*p2d=static_cast<AlignmentPacket2D *>(&Packet);
		if(p2d!=NULL)
			((AlignmentLargeInPage *)(abase->GetPageData(localPage)))->GetAlignmentLargeByHandle(*p2d,Handle);
	}
}
DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((XAlignmentLarge *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((XAlignmentLarge *)item)->Load(f,LBase);
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPLI(parent);
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	AdjustAlignmentLargeForm	*DForm=new AdjustAlignmentLargeForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}

DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

