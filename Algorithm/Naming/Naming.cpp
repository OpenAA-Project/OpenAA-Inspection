/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Naming\Naming.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "NamingResource.h"
#include "Naming.h"
#include "XAlgorithmDLL.h"
#include "XNaming.h"
#include "SetNamingForm.h"
#include "XNamingPacket.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"Naming";

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
	return NamingVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "命名処理";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"Naming";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	NamingBase	*base=new NamingBase(Base);
	base->Initial(Base);

	(*Base)=new SlaveCommReqOverlappedIndex		(Base,sRoot,sName);
	(*Base)=new SlaveCommAckOverlappedIndex		(Base,sRoot,sName);

	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return NULL;
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeNoProcessing | AlgorithmBit_TypeManageResult | AlgorithmBit_TypePostProcessing;
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((NamingItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((NamingItem *)item)->Load(f,LBase);
}
DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	SetNamingForm	*DForm=new SetNamingForm(Something ,InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}

DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

//===========================================================
//===========================================================

DEFFUNCEX	bool	DLL_Name2GloalPos(AlgorithmBase *Base ,QString Name ,int &XGlobalPos, int &YGlobalPos)
{
	NamingBase	*NBase=(NamingBase	*)Base;
	return NBase->Name2GloalPos(Name ,XGlobalPos, YGlobalPos);
}
DEFFUNCEX	bool	DLL_Name2LocalPos(AlgorithmBase *Base ,QString Name ,int &Page ,int &XLocalPos, int &YLocalPos)
{
	NamingBase	*NBase=(NamingBase	*)Base;
	return NBase->Name2LocalPos(Name ,Page ,XLocalPos, YLocalPos);
}
DEFFUNCEX	bool	DLL_LocalPos2Name(AlgorithmBase *Base ,int Page ,int XLocalPos, int YLocalPos ,QString &Name)
{
	NamingBase	*NBase=(NamingBase	*)Base;
	return NBase->LocalPos2Name(Page ,XLocalPos, YLocalPos ,Name);
}
DEFFUNCEX	bool	DLL_GlobalPos2Name(AlgorithmBase *Base ,int XGlobalPos, int YGlobalPos ,QString &Name)
{
	NamingBase	*NBase=(NamingBase	*)Base;
	return NBase->GlobalPos2Name(XGlobalPos, YGlobalPos ,Name);
}
