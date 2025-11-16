/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\RepeatControl\RepeatControl.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "RepeatControl.h"
#include "XAlgorithmDLL.h"
#include "XRepeatControl.h"
#include "XDirectCommPacket.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"RepeatControl";

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
	return RepeatControlVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "連続ＮＧ制御";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"RepeatControlIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	RepeatControlBase	*base=new RepeatControlBase(Base);
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
	return AlgorithmBit_TypePostProcessing | AlgorithmBit_TypeDynamicMasking;
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
	return ((RepeatControlItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((RepeatControlItem *)item)->Load(f,LBase);
}
