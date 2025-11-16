/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Aklgorithm\ThinMetal\XThinMetalLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XThinMetalLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XThinMetal.h"


//============================================================

ThinMetalLibrary::ThinMetalLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	PickupL		=0;
	PickupH		=0;
    MinSize=0;
    MaxSize=1000000;
    MinDots=0;
    MaxDots=2000000000;
    LimitSize=400;

	NoiseSize		=0;
	NoiseSizePinHole=0;
    SpaceToOutline	=0;
    Priority		=0;

	BrightWidthL	=0;
	BrightWidthH	=0;
	OKDotL			=0;
	OKDotH			=0;
	MaxNGDotL		=99999999;
	MaxNGDotH		=99999999;
	OKLengthL		=0;
	OKLengthH		=0;
	ShrinkDot		=1;
	EnlargeDot		=1;
}
ThinMetalLibrary::~ThinMetalLibrary(void)
{
}

bool	ThinMetalLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=ThinMetalVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,PickupL)==false)
		return false;
	if(::Save(f,PickupH)==false)
		return false;
    if(::Save(f,MinSize)==false)
		return false;
    if(::Save(f,MaxSize)==false)
		return false;
    if(::Save(f,MinDots)==false)
		return false;
    if(::Save(f,MaxDots)==false)
		return false;
    if(::Save(f,LimitSize)==false)
		return false;

	if(::Save(f,NoiseSize)==false)
		return false;
	if(::Save(f,NoiseSizePinHole)==false)
		return false;
    if(::Save(f,SpaceToOutline)==false)
		return false;
    if(::Save(f,Priority)==false)
		return false;

	if(::Save(f,BrightWidthL)==false)
		return false;
	if(::Save(f,BrightWidthH)==false)
		return false;
	if(::Save(f,OKDotL)==false)
		return false;
	if(::Save(f,OKDotH)==false)
		return false;
	if(::Save(f,OKLengthL)==false)
		return false;
	if(::Save(f,OKLengthH)==false)
		return false;

	if(::Save(f,MaxNGDotL)==false)
		return false;
	if(::Save(f,MaxNGDotH)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,EnlargeDot)==false)
		return false;

	return true;
}
bool	ThinMetalLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,PickupL)==false)
		return false;
	if(::Load(f,PickupH)==false)
		return false;
    if(::Load(f,MinSize)==false)
		return false;
    if(::Load(f,MaxSize)==false)
		return false;
    if(::Load(f,MinDots)==false)
		return false;
    if(::Load(f,MaxDots)==false)
		return false;
    if(::Load(f,LimitSize)==false)
		return false;

	if(::Load(f,NoiseSize)==false)
		return false;
	if(::Load(f,NoiseSizePinHole)==false)
		return false;
    if(::Load(f,SpaceToOutline)==false)
		return false;
    if(::Load(f,Priority)==false)
		return false;

//????C?f?[?^

	if(::Load(f,BrightWidthL)==false)
		return false;
	if(::Load(f,BrightWidthH)==false)
		return false;
	if(::Load(f,OKDotL)==false)
		return false;
	if(::Load(f,OKDotH)==false)
		return false;
	if(::Load(f,OKLengthL)==false)
		return false;
	if(::Load(f,OKLengthH)==false)
		return false;

	if(::Load(f,MaxNGDotL)==false)
		return false;
	if(::Load(f,MaxNGDotH)==false)
		return false;
	if(::Load(f,ShrinkDot)==false)
		return false;
	if(::Load(f,EnlargeDot)==false)
		return false;

	return true;
}


ThinMetalLibrary	&ThinMetalLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((ThinMetalLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}


void	ThinMetalLibrary::MakePickupTest(ImageBuffer &IBuff 
									 ,const BYTE **MaskBitmap
									 ,BYTE **BmpPoint 
									 ,BYTE **OcupyMap
									 ,int page
									 ,int XByte ,int XLen ,int YLen
									 ,int OmitZoneDot)
{
	if(GetLayersBase()->GetBootingLevel()!=0)
		OmitZoneDot=10;

	GetLayersBase()->SetMaxProcessing(7);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	int	YNumb=min(YLen,IBuff.GetHeight());
	int	XNumb=min(XLen,IBuff.GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*src=IBuff.GetY(y);
			BYTE	*dest=BmpPoint[y];
			int		c;
			for(int x=0;x<XNumb;x++,src++){
				c=*src;
				if(PickupL<=c && c<=PickupH){
					dest[x>>3] |= 0x80>>(x&7);
				}
			}
		}
	}
	GetLayersBase()->StepProcessing(-1);

	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(	 TmpData2				,XByte ,YLen
					,(const BYTE **)BmpPoint,XByte ,YLen);

	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseSize);
	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,NoiseSize);

	MatrixBuffAnd	(BmpPoint,(const BYTE **)TmpData2,XByte,YLen);

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

	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,NoiseSizePinHole);
	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseSizePinHole);

	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	
	GetLayersBase()->StepProcessing(-1);
	//BitmapClusterSized(BmpPoint,XByte ,YLen 
	//					,TmpData,TmpData2
	//					   ,MaxVIASize ,MinVIASize ,MaxVIADots ,MinVIADots
	//					   ,XLen, YLen);

	GetLayersBase()->StepProcessing(-1);

	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,-SpaceToOutline);
	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,SpaceToOutline);

	DeleteMatrixBuff(TmpData2,YLen);

	if(0<MinDots || 0<MinSize || MaxSize<GetDotPerLine(page) || MaxSize<GetMaxLines(page)
	|| MaxDots<2000000000 || MaxDots<GetDotPerLine(page)*GetMaxLines(page)){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BmpPoint,XByte,XLen,YLen ,FPack);
		MatrixBuffClear(BmpPoint ,0 ,XByte ,YLen);
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			int64	DotN=a->GetPatternByte();
			if(MinDots<=DotN && DotN<=MaxDots && MinSize<=a->GetWidth() && a->GetWidth()<=MaxSize && MinSize<=a->GetHeight() && a->GetHeight()<=MaxSize){
				a->MakeBitData(BmpPoint,XLen ,YLen);
			}
		}
	}

	GetLayersBase()->StepProcessing(-1);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);

		GetLayersBase()->FatAreaN(OcupyMap,TmpData ,XByte, YLen,SpaceToOutline);
	}

	GetLayersBase()->StepProcessing(-1);
	DeleteMatrixBuff(TmpData,YLen);
}



class	PureFlexAreaListPoint : public NPList<PureFlexAreaListPoint>
{
public:
	PureFlexAreaList	*Point;
	PureFlexAreaListPoint(PureFlexAreaList *p){	Point=p;	}
};


void	ThinMetalLibrary::Make(
			 BYTE **CurrentMap,BYTE **OcupyMap
			 ,int page
			 ,int XByte ,int XLen,int YLen
			 ,NPListPack<AlgorithmItemPLI> &VIAList)
{
	GetLayersBase()->SetMaxProcessing(6);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(TmpData					,XByte,YLen
		         , (const BYTE **)CurrentMap,XByte,YLen);

	PureFlexAreaListContainer	L3List;

	int	XNumbInt =XByte/sizeof(unsigned int);
	int	XNumbLeft=XByte%sizeof(unsigned int);
	for(int y=0;y<YLen;y++){
		unsigned int	*Src=(unsigned int *)OcupyMap[y];
		unsigned int	*Dst=(unsigned int *)CurrentMap[y];
		for(int x=0;x<XNumbInt;x++,Src++,Dst++){
			*Dst &= ~*Src;
		}
		BYTE	*S=(BYTE *)Src;
		BYTE	*D=(BYTE *)Dst;
		for(int x=0;x<XNumbLeft;x++,S++,D++){
			*D &= ~*S;
		}
	}
	GetLayersBase()->StepProcessing(-1);

	try{
		PureFlexAreaListContainer FPack;
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
		GetLayersBase()->StepProcessing(-1);

		GetLayersBase()->StepProcessing(-1);
		PureFlexAreaList *a;

		int	N=FPack.GetCount();
		PureFlexAreaList **PureFlexAreaPointerDim=new PureFlexAreaList *[N];
		int	i=0;
		while((a=FPack.GetFirst())!=NULL){
			FPack.RemoveList(a);
			PureFlexAreaPointerDim[i]=a;
			i++;
		}

		#pragma omp parallel
		{
			#pragma omp for
			for(int k=0;k<N;k++){
				PureFlexAreaList *h=PureFlexAreaPointerDim[k];

				PureFlexAreaListContainer Piece;
				if(LimitSize==0 || (h->GetWidth()<LimitSize && h->GetHeight()<LimitSize)){
					Piece.AppendList(h);
					h=NULL;
				}
				else{
					h->ChopRect(Piece ,LimitSize);
				}
				PureFlexAreaList *b;
				while((b=Piece.GetFirst())!=NULL){
					Piece.RemoveList(b);
					#pragma omp critical
					{
						L3List.AppendList(b);
					}
				}
				if(h!=NULL){
					delete	h;
				}
			}
		}

		delete	[]PureFlexAreaPointerDim;
	}	
	catch(...){}

	GetLayersBase()->StepProcessing(-1);
	try{
		int	OverlapArea=10;
		for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
			int	XLen=a->GetWidth()+OverlapArea*2+2+16;
			int	XByte=(XLen+7)/8;
			int	YLen=a->GetHeight()+OverlapArea*2+2;
			BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
			BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
			MatrixBuffClear(TmpBuff,0,XByte,YLen);
			int	dx=-a->GetMinX()+OverlapArea+8;
			int	dy=-a->GetMinY()+OverlapArea;
			int	dx2=a->GetMinX();
			int	dy2=a->GetMinY();
			a->MakeBitData(TmpBuff,dx,dy,XLen,YLen);
			GetLayersBase()->FatAreaN(TmpBuff,TmpBuff2,XByte, YLen ,OverlapArea);

			for(int y=0;y<YLen;y++){
				if(y-dy<0)
					continue;
				if(y-dy>=GetMaxLines(page))
					break;
				BYTE	*YPoint	=TmpBuff[y];
				BYTE	*YSrc	=TmpData[y-dy];
				int	sx=-dx;
				if(sx+XLen>GetDotPerLine(page))
					XLen=GetDotPerLine(page)-sx;
				for(int x=0;x<XLen;x++,sx++){
					if(sx<0){
						YPoint[x>>3] &= ~(0x80>>(x&7));
						continue;
					}
					if((YPoint[x>>3]&(0x80>>(x&7)))!=0){
						if((YSrc[sx>>3]&(0x80>>(sx&7)))==0)
							YPoint[x>>3] &= ~(0x80>>(x&7));
					}
				}
			}
			a->BuildFromRaster(TmpBuff,XByte,YLen ,-dx ,-dy);
			DeleteMatrixBuff(TmpBuff,YLen);
			DeleteMatrixBuff(TmpBuff2,YLen);
		}
	}
	catch(...){}

	GetLayersBase()->StepProcessing(-1);
	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(page),GetMaxLines(page));
		if(a->GetPatternByte()<5)
			continue;
		ThinMetalItem	*v=new ThinMetalItem();
		v->SetArea(*a);

		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		VIAList.AppendList(v);
	}
}

//==============================================================================

ThinMetalLibraryContainer::ThinMetalLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
ThinMetalLibraryContainer::~ThinMetalLibraryContainer(void)
{
}


