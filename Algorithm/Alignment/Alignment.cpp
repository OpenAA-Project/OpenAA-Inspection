/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Alignment\Alignment.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAlignmentResource.h"
#include "XAlgorithmDLL.h"
#include "Alignment.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"Alignment";

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
	return AlignmentVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "アラインメント";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"Alignment";
}
DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypePreAlignment | AlgorithmBit_TypeAlignment;
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	AlgorithmBase	*base=new AlignmentBase(Base);
	base->Initial(Base);

	(*Base)=new SlaveCommReqAlignmentPoint(Base,sRoot,sName);
	(*Base)=new SlaveCommAckAlignmentPoint(Base,sRoot,sName);
	(*Base)=new SlaveCommReqAlignmentShift(Base,sRoot,sName);
	(*Base)=new SlaveCommAckAlignmentShift(Base,sRoot,sName);
	return base;
}

DEFFUNCEX	AlignmentPacketBase	*DLL_GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY ,AlgorithmItemRoot *Item,bool FromGlobal)
{
	AlignmentBase	*abase=dynamic_cast<AlignmentBase *>(base);
	if(abase!=NULL){
		return ((AlignmentInPage *)(abase->GetPageDataPhase(Item->GetPhaseCode())->GetPageData(localPage)))->AppendAlignmentPacket2D(Item,localX,localY,FromGlobal);
	}
	return NULL;
}
DEFFUNCEX	void	DLL_GetAlignmentForProcessing(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet)
{
	AlignmentBase	*abase=dynamic_cast<AlignmentBase *>(base);
	if(abase!=NULL){
		AlignmentPacket2D	*p2d=static_cast<AlignmentPacket2D *>(&Packet);
		if(p2d!=NULL)
			((AlignmentInPage *)(abase->GetPageData(localPage)))->GetAlignment(*p2d);
	}
}
DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((XAlignment *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((XAlignment *)item)->Load(f,LBase);
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPLI(parent);
}


DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

