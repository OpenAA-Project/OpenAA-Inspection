/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\PieceForReview\PieceForReview.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PieceForReviewResource.h"
#include "PieceForReview.h"
#include "XAlgorithmDLL.h"
#include "XPieceForReview.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"PieceForReview";

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
	return PieceForReviewVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return /**/"PieceForReview algorithm";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"PieceForReview";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	PieceForReviewBase	*base=new PieceForReviewBase(Base);
	base->Initial(Base);
	return base;
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return NULL;
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypePostProcessing | AlgorithmBit_TypeManageResult;
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((PieceForReviewItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((PieceForReviewItem *)item)->Load(f,LBase);
}
DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}

DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

//===========================================================
//===========================================================

DEFFUNCEX	bool	DLL_Name2GloalPos(AlgorithmBase *Base ,QString Name ,int &XGlobalPos, int &YGlobalPos)
{
	PieceForReviewBase	*NBase=(PieceForReviewBase	*)Base;
	return NBase->Name2GloalPos(Name ,XGlobalPos, YGlobalPos);
}
DEFFUNCEX	bool	DLL_Name2LocalPos(AlgorithmBase *Base ,QString Name ,int &Page ,int &XLocalPos, int &YLocalPos)
{
	PieceForReviewBase	*NBase=(PieceForReviewBase	*)Base;
	return NBase->Name2LocalPos(Name ,Page ,XLocalPos, YLocalPos);
}
DEFFUNCEX	bool	DLL_LocalPos2Name(AlgorithmBase *Base ,int Page ,int XLocalPos, int YLocalPos ,QString &Name)
{
	PieceForReviewBase	*NBase=(PieceForReviewBase	*)Base;
	return NBase->LocalPos2Name(Page ,XLocalPos, YLocalPos ,Name);
}
DEFFUNCEX	bool	DLL_GlobalPos2Name(AlgorithmBase *Base ,int XGlobalPos, int YGlobalPos ,QString &Name)
{
	PieceForReviewBase	*NBase=(PieceForReviewBase	*)Base;
	return NBase->GlobalPos2Name(XGlobalPos, YGlobalPos ,Name);
}
