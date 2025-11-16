/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ReplaceImage\ReplaceImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ReplaceImage.h"
#include "XAlgorithmDLL.h"
#include "XReplaceImage.h"
#include "XDirectCommPacket.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"ReplaceImage";

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
	return ReplaceImageVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "画像置換";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"ReplaceImageIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	ReplaceImageBase	*base=new ReplaceImageBase(Base);
	base->Initial(Base);

	//(*Base)=new GUICmdReqPanelImage	(Base,sRoot,sName);
	//(*Base)=new GUICmdAckPanelImage	(Base,sRoot,sName);

	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}

DEFFUNCEX	DWORD	DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeDynamicMasking | AlgorithmBit_TypeProcessing;
}

DEFFUNCEX	void	DLL_RemoveAddedResultData(AddedDataClass *d)
{
	delete	d;
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((ReplaceImageItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((ReplaceImageItem *)item)->Load(f,LBase);
}
