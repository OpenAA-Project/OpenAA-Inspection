/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoPCBHoleAligner\AutoPCBHoleAligner.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "AutoPCBHoleAlignerResource.h"
#include "AutoPCBHoleAligner.h"
#include "XAlgorithmDLL.h"
#include "XAutoPCBHoleAligner.h"

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
	Root=/**/"Basic";
	Name=/**/"AutoPCBHoleAligner";
	return true;
}
DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return AutoPCBHoleAlignerVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return /**/"Auto PCBHole Aligner algorithm";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"AutoPCBHoleAligner";
}
DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeAlignment;
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	AlgorithmBase	*base=new AutoPCBHoleAlignerBase(Base);
	base->Initial(Base);
	return base;
}

	/*
DEFFUNCEX	AlignmentPacketBase	*DLL_GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY ,AlgorithmItemRoot *Item,bool FromGlobal)
{
	AlgorithmBase	*abase=dynamic_cast<AlgorithmBase *>(base);
	if(abase!=NULL){
		return ((AutoPCBHoleAlignerInPage *)(abase->GetPageData(localPage)))->AppendAlignmentPacket2D(Item,localX,localY,FromGlobal);
	}
	return NULL;
}
*/
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new AutoPCBHoleAlignerLibraryContainer(Base);
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((AutoPCBHoleAlignerHole *)item)->Save(f);
	//return true;
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	//return true;
	return ((AutoPCBHoleAlignerHole *)item)->Load(f,LBase);
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}


DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

