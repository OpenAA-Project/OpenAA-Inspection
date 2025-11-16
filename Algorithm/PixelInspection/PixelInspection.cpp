/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\PixelInspection\PixelInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "PixelInspectionResource.h"
#define _USE_MATH_DEFINES
#include "XAlgorithmDLL.h"
#include "XPixelInspection.h"
#include <stdio.h> 
#include <math.h> 
#include <QTemporaryFile>
#include "mtFrameDraw.h"
#include "XGUI.h"
#include "swap.h"
#include "XPointer.h"
#include "XCrossObj.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XResultDLLManager.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "PixelHistogramForm.h"

const	char	*sPixelInspectionRoot=/**/"Basic";
const	char	*sPixelInspectionName=/**/"PixelInspection";

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
	Root=sPixelInspectionRoot;
	Name=sPixelInspectionName;
	return true;
}
DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return PixelInspectionVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return /**/"PixelInspection algorithm";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"PixelInsp";
}
DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeProcessing | AlgorithmBit_TypePreProcessing | AlgorithmBit_TypeScanning;
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	AlgorithmBase	*base=new PixelInspectionBase(Base);
	base->Initial(Base);
	return base;
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new PixelInspectionLibraryContainer(Base);
}


DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((PixelInspectionItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((PixelInspectionItem *)item)->Load(f,LBase);	//D-20100204
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPixel(parent);
}


DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

DEFFUNCEX	bool	DLL_BindSpecialResult(ResultInItemRoot *ItemRes ,ErrorGroupPack &Dest)
{
	AlgorithmItemRoot	*Item=ItemRes->GetAlgorithmItemRoot();
	if(Item==NULL)
		return false;

	int	NGImageWidth	=300;
	int	NGImageHeight	=600;
	int	NGImageBevel	=50;
	LayersBase	*LBase=Item->GetLayersBase();
	if(LBase->GetResultDLLBase()->GetFirst()!=NULL){
		ResultDLL	*R=LBase->GetResultDLLBase()->GetFirst();
		if(R!=NULL){
			NGImageWidth =R->GetDLLPoint()->NGImageWidth;
			NGImageHeight=R->GetDLLPoint()->NGImageHeight;
			NGImageBevel =R->GetDLLPoint()->NGImageBevel;	
		}
	}
	if(ItemRes->GetAddedDataType()==ResultPixelOnItemType){
		ResultClusterOnItem	*L=(ResultClusterOnItem	*)(ItemRes->GetAddedData());
		PureFlexAreaListContainer	List;
		for(;;){
			PureFlexAreaList *f=L->List.GetFirst();
			if(f==NULL)
				break;
			L->List.RemoveList(f);
			int	MinX=f->GetMinX();
			int	MinY=f->GetMinY();
			int	MaxX=f->GetMaxX();
			int	MaxY=f->GetMaxY();
			ErrorGroup *h;
			for(h=Dest.GetFirst();h!=NULL;h=h->GetNext()){
				int	hx1,hy1,hx2,hy2;
				h->GetXY(hx1,hy1,hx2,hy2);
				int	LMinX=min(MinX,hx1);
				int	LMinY=min(MinY,hy1);
				int	LMaxX=max(MaxX,hx2);
				int	LMaxY=max(MaxY,hy2);
				if((LMaxX-LMinX)<(NGImageWidth-2*NGImageBevel) && (LMaxY-LMinY)<(NGImageHeight-2*NGImageBevel)){
					hx1=LMinX;
					hy1=LMinY;
					hx2=LMaxX;
					hy2=LMaxY;
					h->SetRectangle(hx1,hy1,hx2,hy2);
					if(h->GetNGSize()<f->GetPatternByte()){
						h->SetNGSize(f->GetPatternByte());
					}
					break;
				}
			}
			if(h==NULL){
				h=new ErrorGroup(LBase);
				h->SetRectangle(MinX,MinY,MaxX,MaxY);
				h->SetPage(ItemRes->GetPage());
				h->SetNGSize(f->GetPatternByte());
				Dest.AppendList(h);
			}
			List.AppendList(f);
		}
		for(;;){
			PureFlexAreaList	*c=List.GetFirst();
			if(c==NULL)
				break;
			List.RemoveList(c);
			L->List.AppendList(c);
		}
	}
	return true;
}
/*
DEFFUNCEX	void	DLL_MakeIndependentItems(int32 localPage ,bool SubResultMoving, int localX ,int localY,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(DForm!=NULL){
		delete	DForm;
	}
	DForm=new PixelHistogramForm(InstBase->GetLayersBase());
	DForm->SetLocalPage	(localPage);
	DForm->SetLocalX	(localX);
	DForm->SetLocalY	(localY);
}
*/
DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	PixelHistogramForm	*DForm=new PixelHistogramForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}
