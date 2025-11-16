/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRing\XEulerRingLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XEulerRingLibrary.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XEulerRing.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>

EulerRingLibrary::EulerRingLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
    MinBlockSize=0;
    MaxBlockSize=1000000;
    MinBlockDots=0;
    MaxBlockDots=2000000000;

	NoiseSize		=3;
	ExpandedDotToPad=10;

	ExpandedDot		=2;
	Mergin			=10;

    AdjustBlack		=20;    //‹P“x•â³‚Ì‰ºŒÀ•
    AdjustWhite		=20;    //‹P“x•â³‚ÌãŒÀ•
}

bool	EulerRingLibrary::SaveBlob(QIODevice *f)
{
	if(HoleColor.Save(f)==false)
		return false;
	if(CupperColor.Save(f)==false)
		return false;
    if(::Save(f,MinBlockSize)==false)
		return false;
    if(::Save(f,MaxBlockSize)==false)
		return false;
    if(::Save(f,MinBlockDots)==false)
		return false;
    if(::Save(f,MaxBlockDots)==false)
		return false;

	if(InspectionColor.Save(f)==false)
		return false;
	if(::Save(f,NoiseSize)==false)
		return false;
	if(::Save(f,ExpandedDotToPad)==false)
		return false;
	if(::Save(f,ExpandedDot)==false)
		return false;
	if(::Save(f,Mergin)==false)
		return false;

    if(::Save(f,AdjustBlack)==false)
		return false;
    if(::Save(f,AdjustWhite)==false)
		return false;

	return true;
}
bool	EulerRingLibrary::LoadBlob(QIODevice *f)
{
	if(HoleColor.Load(f)==false)
		return false;
	if(CupperColor.Load(f)==false)
		return false;
	if(::Load(f,MinBlockSize)==false)
		return false;
    if(::Load(f,MaxBlockSize)==false)
		return false;
    if(::Load(f,MinBlockDots)==false)
		return false;
    if(::Load(f,MaxBlockDots)==false)
		return false;

	if(InspectionColor.Load(f)==false)
		return false;
	if(::Load(f,NoiseSize)==false)
		return false;
	if(::Load(f,ExpandedDotToPad)==false)
		return false;
	if(::Load(f,ExpandedDot)==false)
		return false;
	if(::Load(f,Mergin)==false)
		return false;

    if(::Load(f,AdjustBlack)==false)
		return false;
    if(::Load(f,AdjustWhite)==false)
		return false;

	return true;
}
	
void	EulerRingLibrary::MakePickupTest(ImagePointerContainer &ImageBuff
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
					if(HoleColor.Calc(cR,cG,cB,1)==true){
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
					if(HoleColor.Calc(cR,cG,cG,1)==true){
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
					if(HoleColor.Calc(cR,cR,cR,1)==true){
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

	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseSize);
	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,NoiseSize*2);
	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseSize);

	MatrixBuffAnd	(BmpPoint,(const BYTE **)TmpData2,XByte,YLen);
	DeleteMatrixBuff(TmpData2,YLen);

	GetLayersBase()->StepProcessing(-1);

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

	GetLayersBase()->StepProcessing(-1);

	if(0<MinBlockDots || 0<MinBlockSize || MaxBlockSize<GetDotPerLine(Page) || MaxBlockSize<GetMaxLines(Page)
	|| MaxBlockDots<2000000000 || MaxBlockDots<GetDotPerLine(Page)*GetMaxLines(Page)){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BmpPoint,XByte,XLen,YLen ,FPack);
		MatrixBuffClear(BmpPoint ,0 ,XByte ,YLen);
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			int64	DotN=a->GetPatternByte();
			if(MinBlockDots<=DotN && DotN<=MaxBlockDots && MinBlockSize<=a->GetWidth() && a->GetWidth()<=MaxBlockSize && MinBlockSize<=a->GetHeight() && a->GetHeight()<=MaxBlockSize){
				int	Cupper=0;
				for(int i=0;i<64;i++){
					double	s=2.0*M_PI*i/64.0;
					if(ExistCupper(ImageBuff,*a,s,(max(a->GetWidth(),a->GetHeight())+1)/2+5)==true)
						Cupper++;
				}
				if(Cupper>=50){
					a->MakeBitData(BmpPoint,XLen ,YLen);
				}
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
bool	EulerRingLibrary::ExistCupper(ImagePointerContainer &ImageBuff
									  ,FlexArea &A,double s, int Len)
{
	double	Cx,Cy;
	A.GetCenter(Cx,Cy);
	int	LMin=min(A.GetWidth(),A.GetHeight())/2;

	double	coss=cos(s);
	double	sins=sin(s);
	for(int L=LMin;L<=Len;L+=2){
		int	x=(int)(L*coss+Cx);
		int	y=(int)(L*sins+Cy);

		if(GetLayerNumb(0)>=3){
			ImageBuffer	*RBuff=ImageBuff.GetItem(0)->GetImage();
			ImageBuffer	*GBuff=ImageBuff.GetItem(1)->GetImage();
			ImageBuffer	*BBuff=ImageBuff.GetItem(2)->GetImage();
			double	R=0;
			double	G=0;
			double	B=0;
			for(int iy=-1;iy<=1;iy++){
				for(int ix=-1;ix<=1;ix++){
					R+=RBuff->GetY(y+iy)[x+ix];
					G+=GBuff->GetY(y+iy)[x+ix];
					B+=BBuff->GetY(y+iy)[x+ix];
				}
			}
			R/=9.0;
			G/=9.0;
			B/=9.0;
			if(CupperColor.Calc(R,G,B,0)==true)
				return true;
		}
		else if(GetLayerNumb(0)==2){
			ImageBuffer	*RBuff=ImageBuff.GetItem(0)->GetImage();
			ImageBuffer	*GBuff=ImageBuff.GetItem(1)->GetImage();
			double	R=0;
			double	G=0;
			for(int iy=-1;iy<=1;iy++){
				for(int ix=-1;ix<=1;ix++){
					R+=RBuff->GetY(y+iy)[x+ix];
					G+=GBuff->GetY(y+iy)[x+ix];
				}
			}
			R/=9.0;
			G/=9.0;
			if(CupperColor.Calc(R,G,G,0)==true)
				return true;
		}
		else if(GetLayerNumb(0)==1){
			ImageBuffer	*RBuff=ImageBuff.GetItem(0)->GetImage();
			double	R=0;
			for(int iy=-1;iy<=1;iy++){
				for(int ix=-1;ix<=1;ix++){
					R+=RBuff->GetY(y+iy)[x+ix];
				}
			}
			R/=9.0;
			if(CupperColor.Calc(R,R,R,0)==true)
				return true;
		}
	}
	return false;
}

void	EulerRingLibrary::MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &TmpBlockData)
{
	GetLayersBase()->SetMaxProcessing(4);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(TmpData					,XByte,YLen
		         , (const BYTE **)CurrentMap,XByte,YLen);

	GetLayersBase()->StepProcessing(-1);


	PureFlexAreaListContainer FPack;
	try{
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);

		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
			int64	DotN=a->GetPatternByte();
			if((MinBlockDots<=0 && MinBlockSize<=0 && GetDotPerLine(Page)<MaxBlockSize && GetMaxLines(Page)<MaxBlockSize
			&& (2000000000<=MaxBlockDots || GetDotPerLine(Page)*GetMaxLines(Page)<=MaxBlockDots))
			|| (MinBlockDots<=DotN && DotN<=MaxBlockDots && MinBlockSize<=a->GetWidth() && a->GetWidth()<=MaxBlockSize && MinBlockSize<=a->GetHeight() && a->GetHeight()<=MaxBlockSize)){
				a=a->GetNext();
			}
			else{
				PureFlexAreaList *NextA=a->GetNext();
				FPack.RemoveList(a);
				delete	a;
				a=NextA;
			}
		}
	}	
	catch(...){}

	GetLayersBase()->StepProcessing(-1);
    DeleteMatrixBuff(TmpData,YLen);

	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(Page),GetMaxLines(Page));
		if(a->GetPatternByte()<5)
			continue;

		int	XLen=a->GetWidth()+ExpandedDotToPad*2+2+16;
		int	XByte=(XLen+7)/8;
		int	YLen=a->GetHeight()+ExpandedDotToPad*2+2;
		BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
		BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
		MatrixBuffClear(TmpBuff,0,XByte,YLen);
		int	dx=-a->GetMinX()+ExpandedDotToPad+8;
		int	dy=-a->GetMinY()+ExpandedDotToPad;

		a->MakeBitData(TmpBuff,dx,dy,XLen,YLen);
		GetLayersBase()->FatAreaN(TmpBuff,TmpBuff2,XByte, YLen ,ExpandedDotToPad);
		a->BuildFromRaster(TmpBuff,XByte,YLen ,-dx ,-dy);
		DeleteMatrixBuff(TmpBuff,YLen);
		DeleteMatrixBuff(TmpBuff2,YLen);


		EulerRingItem	*v=new EulerRingItem(*a);

		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		TmpBlockData.AppendList(v);
	}
	GetLayersBase()->StepProcessing(-1);
}


EulerRingLibrary	&EulerRingLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((EulerRingLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

EulerRingLibraryContainer::EulerRingLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}