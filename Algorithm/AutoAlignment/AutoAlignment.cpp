/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoAlignment\AutoAlignment.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "AutoAlignmentResource.h"
#include "AutoAlignment.h"
#include "XAlgorithmDLL.h"
#include "XAutoAlignment.h"

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
	Name=/**/"AutoAlignment";
	return true;
}
DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return AutoAlignmentVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "自動アラインメント";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"AutoAlignment";
}
DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeAlignment;
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	AlgorithmBase	*base=new AutoAlignmentBase(Base);
	base->Initial(Base);
	return base;
}

DEFFUNCEX	AlignmentPacketBase	*DLL_GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY ,AlgorithmItemRoot *Item,bool FromGlobal)
{
	AlgorithmBase	*abase=dynamic_cast<AlgorithmBase *>(base);
	if(abase!=NULL){
		return ((AutoAlignmentInPage *)(abase->GetPageData(localPage)))->AppendAlignmentPacket2D(Item,localX,localY,FromGlobal);
	}
	return NULL;
}

DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new AutoAlignmentLibraryContainer(Base);
}

DEFFUNCEX	void	DLL_GetAlignmentForProcessing(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet)
{
	AutoAlignmentBase	*abase=dynamic_cast<AutoAlignmentBase *>(base);
	if(abase!=NULL){
		AlignmentPacketWithColor	*p2d=static_cast<AlignmentPacketWithColor *>(&Packet);
		if(p2d!=NULL)
			((AutoAlignmentInPage *)(abase->GetPageData(localPage)))->GetAlignment(p2d);
	}
}
DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((AutoAlignmentSheet *)item)->Save(f);
	//return true;
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	//return true;
	return ((AutoAlignmentSheet *)item)->Load(f,LBase);
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}


DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);


