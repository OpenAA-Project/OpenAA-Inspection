/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DynamicClassify\XDynamicClassifyLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XDynamicClassify.h"
#include "XBitImageProcessor.h"
#include "omp.h"
#include "XDisplayBitImage.h"

DynamicClassifyLibrary::DynamicClassifyLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
    MinAreaSize		=0;
    MaxAreaSize		=10000;
    MinAreaDots		=0;
    MaxAreaDots		=100000000;

	NoiseDot		=1;
	ShrinkDot		=0;
	Priority		=100;
	VariableWidth	=5;

	OutlineOWidth	=3;
	OutlineTWidth	=3;
	OutlineIWidth	=3;
	OverlapInEachArea=1;

	MakeEachArea	=false;

	AdjustBrightH	=20;
	AdjustBrightL	=20;
	StartupExecute	=false;
}
DynamicClassifyLibrary::~DynamicClassifyLibrary(void)
{
}

bool	DynamicClassifyLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false)
		return false;
	if(PickupColor.Save(f)==false)
		return false;
	if(::Save(f,MinAreaSize)==false)
		return false;
	if(::Save(f,MaxAreaSize)==false)
		return false;
	if(::Save(f,MinAreaDots)==false)
		return false;
	if(::Save(f,MaxAreaDots)==false)
		return false;
	if(::Save(f,NoiseDot)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,VariableWidth)==false)
		return false;
	if(::Save(f,OutlineOWidth)==false)
		return false;
	if(::Save(f,OutlineTWidth)==false)
		return false;
	if(::Save(f,OutlineIWidth)==false)
		return false;
	if(::Save(f,OverlapInEachArea)==false)
		return false;
	if(::Save(f,MakeEachArea)==false)
		return false;
	if(::Save(f,AdjustBrightH)==false)
		return false;
	if(::Save(f,AdjustBrightL)==false)
		return false;
	if(::Save(f,StartupExecute)==false)
		return false;
	return true;
}
bool	DynamicClassifyLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(PickupColor.Load(f)==false)
		return false;
	if(::Load(f,MinAreaSize)==false)
		return false;
	if(::Load(f,MaxAreaSize)==false)
		return false;
	if(::Load(f,MinAreaDots)==false)
		return false;
	if(::Load(f,MaxAreaDots)==false)
		return false;
	if(::Load(f,NoiseDot)==false)
		return false;
	if(::Load(f,ShrinkDot)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,VariableWidth)==false)
		return false;
	if(::Load(f,OutlineOWidth)==false)
		return false;
	if(::Load(f,OutlineTWidth)==false)
		return false;
	if(::Load(f,OutlineIWidth)==false)
		return false;
	if(::Load(f,OverlapInEachArea)==false)
		return false;
	if(::Load(f,MakeEachArea)==false)
		return false;
	if(::Load(f,AdjustBrightH)==false)
		return false;
	if(::Load(f,AdjustBrightL)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,StartupExecute)==false){
			return false;
		}
	}

	return true;
}

DynamicClassifyLibrary	&DynamicClassifyLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((DynamicClassifyLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

void	DynamicClassifyLibrary::MakePickupTest(ImagePointerContainer &ImageBuff
									 ,const BYTE **MaskBitmap
									 ,BYTE **BmpPoint 
									 ,BYTE **OcupyMap
									 ,int Page
									 ,int XByte ,int XLen ,int YLen
									 ,int OmitZoneDot)
{
	if(GetLayersBase()->GetBootingLevel()!=0)
		OmitZoneDot=10;
	GetLayersBase()->SetMaxProcessing(7);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	MatrixBuffClear(BmpPoint ,0,XByte ,YLen);
	int	YNumb;
	int	XNumb;
	if(GetLayerNumb(Page)>=3){
		ImageBuffer	*RBuff=ImageBuff.GetItem(0)->GetImage();
		ImageBuffer	*GBuff=ImageBuff.GetItem(1)->GetImage();
		ImageBuffer	*BBuff=ImageBuff.GetItem(2)->GetImage();
		YNumb=min(min(min(YLen,RBuff->GetHeight()),GBuff->GetHeight()),BBuff->GetHeight());
		XNumb=min(min(min(XLen,RBuff->GetWidth()) ,GBuff->GetWidth()) ,BBuff->GetWidth());
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*srcR=RBuff->GetY(y);
				BYTE	*srcG=GBuff->GetY(y);
				BYTE	*srcB=BBuff->GetY(y);
				BYTE	*dest=BmpPoint[y];
				BYTE	cR,cG,cB;
				for(int x=0;x<XNumb;x++,srcR++,srcG++,srcB++){
					cR=*srcR;
					cG=*srcG;
					cB=*srcB;
					if(PickupColor.Calc(cR,cG,cB,1)==true){
						dest[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	else if(GetLayerNumb(Page)==2){
		ImageBuffer	*RBuff=ImageBuff.GetItem(0)->GetImage();
		ImageBuffer	*GBuff=ImageBuff.GetItem(1)->GetImage();
		YNumb=min(min(YLen,RBuff->GetHeight()),GBuff->GetHeight());
		XNumb=min(min(XLen,RBuff->GetWidth()) ,GBuff->GetWidth());
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*srcR=RBuff->GetY(y);
				BYTE	*srcG=GBuff->GetY(y);
				BYTE	*dest=BmpPoint[y];
				BYTE	cR,cG;
				for(int x=0;x<XNumb;x++,srcR++,srcG++){
					cR=*srcR;
					cG=*srcG;
					if(PickupColor.Calc(cR,cG,cG,1)==true){
						dest[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	else if(GetLayerNumb(Page)==1){
		ImageBuffer	*RBuff=ImageBuff.GetItem(0)->GetImage();
		YNumb=min(YLen,RBuff->GetHeight());
		XNumb=min(XLen,RBuff->GetWidth());
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*srcR=RBuff->GetY(y);
				BYTE	*dest=BmpPoint[y];
				BYTE	cR;
				for(int x=0;x<XNumb;x++,srcR++){
					cR=*srcR;
					if(PickupColor.Calc(cR,cR,cR,1)==true){
						dest[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	else
		return;
	GetLayersBase()->StepProcessing(-1);

	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	GetLayersBase()->StepProcessing(-1);
	BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(	 TmpData2				,XByte ,YLen
					,(const BYTE **)BmpPoint,XByte ,YLen);

	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseDot);
	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,NoiseDot);

	MatrixBuffAnd	(BmpPoint,(const BYTE **)TmpData2,XByte,YLen);
	DeleteMatrixBuff(TmpData2,YLen);

	for(int y=0;y<OmitZoneDot;y++){
		memset(BmpPoint[y],0,XByte);
	}
	for(int y=0;y<OmitZoneDot;y++){
		memset(BmpPoint[YLen-y-1],0,XByte);
	}
	for(int y=OmitZoneDot;y<YLen-OmitZoneDot;y++){
		for(int x=0;x<OmitZoneDot;x++){
			BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
		}
		for(int x=XLen-OmitZoneDot;x<XLen;x++){
			BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
		}
	}

	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,NoiseDot);
	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseDot);
	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	GetLayersBase()->StepProcessing(-1);
	if(ShrinkDot<0){
		GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,-ShrinkDot);
	}
	else{
		GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,ShrinkDot);
	}

	GetLayersBase()->StepProcessing(-1);
	if(0<MinAreaDots || 0<MinAreaSize || MaxAreaSize<GetDotPerLine(Page) || MaxAreaSize<GetMaxLines(Page)
	|| MaxAreaDots<2000000000 || MaxAreaDots<GetDotPerLine(Page)*GetMaxLines(Page)){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BmpPoint,XByte,XLen,YLen ,FPack);
		MatrixBuffClear(BmpPoint ,0 ,XByte ,YLen);
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			int64	DotN=a->GetPatternByte();
			if(MinAreaDots<=DotN && DotN<=MaxAreaDots
			&& MinAreaSize<=a->GetWidth() && a->GetWidth()<=MaxAreaSize
			&& MinAreaSize<=a->GetHeight() && a->GetHeight()<=MaxAreaSize){
				a->MakeBitData(BmpPoint,XLen ,YLen);
			}
		}
	}

	GetLayersBase()->StepProcessing(-1);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);
	}
	GetLayersBase()->StepProcessing(-1);
	DeleteMatrixBuff(TmpData,YLen);
}

void	DynamicClassifyLibrary::MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &TmpData)
{
	GetLayersBase()->SetMaxProcessing(2);
	GetLayersBase()->StepProcessing(-1);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
		
	GetLayersBase()->StepProcessing(-1);
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(Page),GetMaxLines(Page));
		DynamicClassifyItem	*v=new DynamicClassifyItem();
		v->SetArea(*a);

		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		TmpData.AppendList(v);
		a->MakeBitData(OcupyMap,XLen,YLen);
	}
}

//==============================================================================

DynamicClassifyLibraryContainer::DynamicClassifyLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
DynamicClassifyLibraryContainer::~DynamicClassifyLibraryContainer(void)
{
}

