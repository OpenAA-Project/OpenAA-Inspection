/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\HoleWall\XHoleWallLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XHoleWallLibrary.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XHoleWallInspection.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


HoleWallLibrary::HoleWallLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	PickupL					=0;
	PickupH					=255;
    MinBlockSize			=0;
    MaxBlockSize			=100;
    MinBlockDots			=0;
    MaxBlockDots			=10000;

	NoiseSize				=1;			//孤立点削除
	NoiseSizePinHole		=1;	//ピンホール削除
	SpaceToOutline			=0;		//Plus:Shrink Plus:Expand


	NGSize					=0;		
	SearchDot				=0;
}

bool	HoleWallLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=5;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,PickupL)==false)
		return false;
	if(::Save(f,PickupH)==false)
		return false;
    if(::Save(f,MinBlockSize)==false)
		return false;
    if(::Save(f,MaxBlockSize)==false)
		return false;
    if(::Save(f,MinBlockDots)==false)
		return false;
    if(::Save(f,MaxBlockDots)==false)
		return false;

	if(::Save(f,NoiseSize)==false)
		return false;
	if(::Save(f,NoiseSizePinHole)==false)
		return false;
	if(::Save(f,SpaceToOutline)==false)
		return false;

    if(::Save(f,NGSize)==false)
		return false;
    if(::Save(f,SearchDot)==false)
		return false;

	return true;
}
bool	HoleWallLibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,PickupL)==false)
		return false;
	if(::Load(f,PickupH)==false)
		return false;
    if(::Load(f,MinBlockSize)==false)
		return false;
    if(::Load(f,MaxBlockSize)==false)
		return false;
    if(::Load(f,MinBlockDots)==false)
		return false;
    if(::Load(f,MaxBlockDots)==false)
		return false;

	if(::Load(f,NoiseSize)==false)
		return false;
	if(::Load(f,NoiseSizePinHole)==false)
		return false;
	if(::Load(f,SpaceToOutline)==false)
		return false;

    if(::Load(f,NGSize)==false)
		return false;
    if(::Load(f,SearchDot)==false)
		return false;

	return true;
}
	
void	HoleWallLibrary::MakePickupTest(int localpage
									,ImageBuffer &IBuff 
									,const BYTE **MaskBitmap
									,BYTE **BmpPoint 
									,BYTE **OcupyMap
									,int XByte ,int XLen ,int YLen
									,int OmitZoneDot)
{
	if(GetLayersBase()->GetBootingLevel()!=0)
		OmitZoneDot=10;
	GetLayersBase()->SetMaxProcessing(7);
	GetLayersBase()->StepProcessing(localpage);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	MatrixBuffClear(BmpPoint ,0,XByte ,YLen);
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
	GetLayersBase()->StepProcessing(localpage);

	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	GetLayersBase()->StepProcessing(localpage);
	BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(	 TmpData2				,XByte ,YLen
					,(const BYTE **)BmpPoint,XByte ,YLen);

	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseSize);
	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,NoiseSize);

	MatrixBuffAnd	(BmpPoint,(const BYTE **)TmpData2,XByte,YLen);

	GetLayersBase()->StepProcessing(localpage);

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

	GetLayersBase()->StepProcessing(localpage);

	if(SpaceToOutline<0){
		GetLayersBase()->FatAreaN(BmpPoint,TmpData ,XByte, YLen,-SpaceToOutline);
	}
	else{
		GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,SpaceToOutline);
	}

	DeleteMatrixBuff(TmpData2,YLen);

	if(0<MinBlockDots || 0<MinBlockSize || MaxBlockSize<GetDotPerLine(localpage) || MaxBlockSize<GetMaxLines(localpage)
	|| MaxBlockDots<2000000000 || MaxBlockDots<GetDotPerLine(localpage)*GetMaxLines(localpage)){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BmpPoint,XByte,XLen,YLen ,FPack);
		MatrixBuffClear(BmpPoint ,0 ,XByte ,YLen);
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			int64	DotN=a->GetPatternByte();
			if(MinBlockDots<=DotN && DotN<=MaxBlockDots && MinBlockSize<=a->GetWidth() && a->GetWidth()<=MaxBlockSize && MinBlockSize<=a->GetHeight() && a->GetHeight()<=MaxBlockSize){
				a->MakeBitData(BmpPoint,XLen ,YLen);
			}
		}
	}

	GetLayersBase()->StepProcessing(localpage);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);
	}
	GetLayersBase()->StepProcessing(localpage);
	DeleteMatrixBuff(TmpData,YLen);
}


void	HoleWallLibrary::MakeBlock(int localpage
			,BYTE **CurrentMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData
			,double ShiftXParamLeft[4],double ShiftXParamRight[4]
			,int ShiftY)
{
	GetLayersBase()->SetMaxProcessing(4);
	GetLayersBase()->StepProcessing(localpage);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(TmpData					,XByte,YLen
		         , (const BYTE **)CurrentMap,XByte,YLen);

	GetLayersBase()->StepProcessing(-1);


	PureFlexAreaListContainer FPack;
	try{
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);

		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
			int64	DotN=a->GetPatternByte();
			if((MinBlockDots<=0 && MinBlockSize<=0 && GetDotPerLine(localpage)<MaxBlockSize && GetMaxLines(localpage)<MaxBlockSize
			&& (20000000000<=MaxBlockDots || GetDotPerLine(localpage)*GetMaxLines(localpage)<=MaxBlockDots))
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

	GetLayersBase()->StepProcessing(localpage);
    DeleteMatrixBuff(TmpData,YLen);

	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(localpage),GetMaxLines(localpage));
		if(a->GetPatternByte()<5)
			continue;

		HoleWallItem	*v=new HoleWallItem(*a);

		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		TmpBlockData.AppendList(v);
	}
	GetLayersBase()->StepProcessing(localpage);
}

HoleWallLibrary	&HoleWallLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((HoleWallLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

HoleWallLibraryContainer::HoleWallLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}


