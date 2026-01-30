/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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