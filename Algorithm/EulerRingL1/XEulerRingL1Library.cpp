/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRingL1\XEulerRingL1Library.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XEulerRingL1Library.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XEulerRingL1.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


EulerRingL1Library::EulerRingL1Library(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	LockFirst				=false;
	PickupL					=0;
	PickupH					=255;
    MinBlockSize			=0;
    MaxBlockSize			=100;
    MinBlockDots			=0;
    MaxBlockDots			=10000;

	NoiseSize				=1;			//孤立点削除
	NoiseSizePinHole		=1;	//ピンホール削除
	SpaceToOutline			=0;		//Plus:Shrink Plus:Expand
    Priority				=0;
	OutlineGeneration		=1000;	//輪郭に生成するドット数	1000以上で通常生成
	ExpandedDotToPad		=5;

	StandardHoleDiameter	=10;
	MerginForRing			=10;

	PointMove.ModeEnabled				=true;
	PointMove.ModeAbsoluteBright		=false;
	PointMove.ModeMakeDynamicMask		=true;
	PointMove.ModeEnableHoleCheck		=true;
	PointMove.ModeCenterBrightFromParts	=false;
	PointMove.ModeEnableOpenRingCheck	=true;
	PointMove.ModeEnableInRound			=true;

	DarkWidth				=0;		//For ring brightness
	LightWidth				=0;
	MinHoleDiameter			=10;
	MaxHoleDiameter			=20;
	MaxShiftHole			=10;
	ConnectLen				=0;
	ExpandForDynamicMask	=0;

    AdjustBlack				=0;	//For ring brightness
    AdjustWhite				=0;
	SearchDot				=0;
	HoleBrightnessAsReference	=-1;
}

bool	EulerRingL1Library::SaveBlob(QIODevice *f)
{
	WORD	Ver=5;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,LockFirst)==false)
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
    if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,OutlineGeneration)==false)
		return false;
	if(::Save(f,ExpandedDotToPad)==false)
		return false;

    if(::Save(f,StandardHoleDiameter)==false)
		return false;
    if(::Save(f,MerginForRing)==false)
		return false;

	if(::Save(f,DarkWidth)==false)
		return false;
	if(::Save(f,LightWidth)==false)
		return false;
	if(::Save(f,MinHoleDiameter)==false)
		return false;
	if(::Save(f,MaxHoleDiameter)==false)
		return false;
	if(::Save(f,MaxShiftHole)==false)
		return false;
	if(::Save(f,ConnectLen)==false)
		return false;
	if(::Save(f,ExpandForDynamicMask)==false)
		return false;

    if(::Save(f,AdjustBlack)==false)
		return false;
    if(::Save(f,AdjustWhite)==false)
		return false;
    if(::Save(f,SearchDot)==false)
		return false;
    if(::Save(f,HoleBrightnessAsReference)==false)
		return false;

	if(f->write((const char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;

	return true;
}
bool	EulerRingL1Library::LoadBlob(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,LockFirst)==false)
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
    if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,OutlineGeneration)==false)
		return false;
	if(::Load(f,ExpandedDotToPad)==false)
		return false;
	
	if(::Load(f,StandardHoleDiameter)==false)
		return false;
    if(::Load(f,MerginForRing)==false)
		return false;

	if(::Load(f,DarkWidth)==false)
		return false;
	if(::Load(f,LightWidth)==false)
		return false;
	if(::Load(f,MinHoleDiameter)==false)
		return false;
	if(::Load(f,MaxHoleDiameter)==false)
		return false;
	if(::Load(f,MaxShiftHole)==false)
		return false;
	if(::Load(f,ConnectLen)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,ExpandForDynamicMask)==false)
			return false;
	}

    if(::Load(f,AdjustBlack)==false)
		return false;
    if(::Load(f,AdjustWhite)==false)
		return false;
	if(Ver>=4){
	  if(::Load(f,SearchDot)==false)
			return false;
	}
	if(Ver>=5){
	  if(::Load(f,HoleBrightnessAsReference)==false)
			return false;
	}
	if(f->read((char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;
	if(Ver<3){
		PointMove.ModeEnableOpenRingCheck	=true;
		PointMove.ModeEnableInRound			=true;
	}
	return true;
}
	
void	EulerRingL1Library::MakePickupTest(int localpage
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
	if(OutlineGeneration<1000){
		MatrixBuffCopy(TmpData					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);
		for(int i=0;i<OutlineGeneration;i++){
		GetLayersBase()->ThinAreaN(TmpData,TmpData2 ,XByte, YLen,OutlineGeneration);
		}
		MatrixBuffXor(BmpPoint,(const BYTE **)TmpData,XByte,YNumb);

		if(MaskBitmap!=NULL){
			MatrixBuffCopy(TmpData					,XByte,YLen
			             , (const BYTE **)MaskBitmap,XByte,YLen);
			GetLayersBase()->ThinAreaN(TmpData,TmpData2 ,XByte, YLen,(OutlineGeneration+SpaceToOutline+1));
			MatrixBuffAnd(BmpPoint,(const BYTE **)TmpData,XByte,YNumb);
		}
		int	tmpOmitZoneDot=OmitZoneDot+OutlineGeneration+SpaceToOutline+1;
		for(int y=0;y<tmpOmitZoneDot;y++){
			memset(BmpPoint[y],0,XByte);
		}
		for(int y=0;y<tmpOmitZoneDot;y++){
			memset(BmpPoint[YLen-y-1],0,XByte);
		}
		for(int y=tmpOmitZoneDot;y<YLen-tmpOmitZoneDot;y++){
			for(int x=0;x<tmpOmitZoneDot;x++){
				BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
			}
			for(int x=XLen-tmpOmitZoneDot;x<XLen;x++){
				BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
			}	
		}
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

	GetLayersBase()->FatAreaN(BmpPoint,TmpData,XByte, YLen ,ExpandedDotToPad);

	GetLayersBase()->StepProcessing(localpage);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);
	}
	GetLayersBase()->StepProcessing(localpage);
	DeleteMatrixBuff(TmpData,YLen);
}


void	EulerRingL1Library::MakeBlock(int localpage
			,BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData
			,int tExpandedDotToPad)
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
			&& (2000000000<=MaxBlockDots || GetDotPerLine(localpage)*GetMaxLines(localpage)<=MaxBlockDots))
			|| (MinBlockDots<=DotN && DotN<=MaxBlockDots && MinBlockSize<=a->GetWidth() && a->GetWidth()<=MaxBlockSize && MinBlockSize<=a->GetHeight() && a->GetHeight()<=MaxBlockSize)){
				a->FatAreaN(tExpandedDotToPad);
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

		EulerRingL1Item	*v=new EulerRingL1Item(*a);

		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->MasterHoleDiameter	=a->GetWidth()-tExpandedDotToPad*2;
		v->GetThresholdW()->MinHoleDiameter=MinHoleDiameter;
		v->GetThresholdW()->MaxHoleDiameter=MaxHoleDiameter;
		v->SetLibID(GetLibID());
		if(LockFirst==true){
			v->SetEditLocked(true);
		}
		TmpBlockData.AppendList(v);
	}
	GetLayersBase()->StepProcessing(localpage);
}


void	EulerRingL1Library::MakeBlockOnly(int localpage
			,BYTE **CurrentMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &BlockList
			,double RoundRateInHole)
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
			&& (2000000000<=MaxBlockDots || GetDotPerLine(localpage)*GetMaxLines(localpage)<=MaxBlockDots))
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
		double	HoleWidth=(a->GetWidth()+a->GetHeight()+1)/2;
		double	HoleArea=HoleWidth*HoleWidth*M_PI;
		bool	ModeEnableInRound=true;
		if(HoleArea>0){
			if(fabs(a->GetPatternByte()-HoleArea)/HoleArea>fabs(1.0-RoundRateInHole)*HoleArea){
				ModeEnableInRound=false;
			}
		}
		else{
			continue;
		}

		int	XLen=a->GetWidth()+ExpandedDotToPad*4+2+16;
		int	XByte=(XLen+7)/8;
		int	YLen=a->GetHeight()+ExpandedDotToPad*4+2;
		BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
		BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
		MatrixBuffClear(TmpBuff,0,XByte,YLen);
		int	dx=-a->GetMinX()+2*ExpandedDotToPad+8;
		int	dy=-a->GetMinY()+2*ExpandedDotToPad;

		a->MakeBitData(TmpBuff,dx,dy,XLen,YLen);
		GetLayersBase()->FatAreaN(TmpBuff,TmpBuff2,XByte, YLen ,ExpandedDotToPad);
		a->BuildFromRaster(TmpBuff,XByte,YLen ,-dx ,-dy);
		DeleteMatrixBuff(TmpBuff,YLen);
		DeleteMatrixBuff(TmpBuff2,YLen);

		EulerRingL1Item	*v=new EulerRingL1Item(*a);

		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		//v->GetThresholdW()->MinHoleDiameter=Clipping((int)HoleWidth-MinHoleDiameter,0,99999999);
		//v->GetThresholdW()->MaxHoleDiameter=Clipping((int)HoleWidth+MaxHoleDiameter,0,99999999);
		v->MasterHoleDiameter	=HoleWidth;
		v->GetThresholdW()->MinHoleDiameter=MinHoleDiameter;
		v->GetThresholdW()->MaxHoleDiameter=MaxHoleDiameter;
		v->SetLibID(GetLibID());
		if(LockFirst==true){
			v->SetEditLocked(true);
		}
		v->GetThresholdW()->PointMove.ModeEnableInRound	=ModeEnableInRound;
		BlockList.AppendList(v);
	}
	GetLayersBase()->StepProcessing(localpage);
}


EulerRingL1Library	&EulerRingL1Library::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((EulerRingL1Library *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

EulerRingL1LibraryContainer::EulerRingL1LibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}


