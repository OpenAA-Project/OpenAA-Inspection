/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFlatInspectionLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XFlatInspectionLibrary.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XFlatInspection.h"
#include "XTypeDef.h"

FlatInspectionLibrary::MLibThreshold::MLibThreshold(void)
{
	OKDot			=0;		//ＯＫドット数
	OKLength		=99999999;

	RThrOffsetL		=0;
	RThrOffsetH		=0;
	GThrOffsetL		=0;
	GThrOffsetH		=0;
	BThrOffsetL		=0;
	BThrOffsetH		=0;
}

bool	FlatInspectionLibrary::MLibThreshold::SaveBlob(QIODevice *f)
{
	int32	Ver=FlatInspectionVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,OKDot)==false)
		return false;
	if(::Save(f,OKLength)==false)
		return false;

	if(::Save(f,RThrOffsetL)==false)
		return false;
    if(::Save(f,RThrOffsetH)==false)
		return false;
    if(::Save(f,GThrOffsetL)==false)
		return false;
    if(::Save(f,GThrOffsetH)==false)
		return false;
    if(::Save(f,BThrOffsetL)==false)
		return false;
    if(::Save(f,BThrOffsetH)==false)
		return false;

	return true;
}
bool	FlatInspectionLibrary::MLibThreshold::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(Ver<=1){
		WORD	BrightWidthRL;	//暗側輝度幅
		WORD	BrightWidthRH;	//明側輝度幅
		WORD	BrightWidthGL;	//暗側輝度幅
		WORD	BrightWidthGH;	//明側輝度幅
		WORD	BrightWidthBL;	//暗側輝度幅
		WORD	BrightWidthBH;	//明側輝度幅
		if(::Load(f,BrightWidthRL)==false)
			return false;
		if(::Load(f,BrightWidthRH)==false)
			return false;
		if(::Load(f,BrightWidthGL)==false)
			return false;
		if(::Load(f,BrightWidthGH)==false)
			return false;
		if(::Load(f,BrightWidthBL)==false)
			return false;
		if(::Load(f,BrightWidthBH)==false)
			return false;
	}

	if(::Load(f,OKDot)==false)
		return false;
	if(::Load(f,OKLength)==false)
		return false;

	if(Ver<=1){
		char	tRThrOffsetL;
		char	tRThrOffsetH;
		char	tGThrOffsetL;
		char	tGThrOffsetH;
		char	tBThrOffsetL;
		char	tBThrOffsetH;
		if(::Load(f,tRThrOffsetL)==false)
			return false;
		if(::Load(f,tRThrOffsetH)==false)
			return false;
		if(::Load(f,tGThrOffsetL)==false)
			return false;
		if(::Load(f,tGThrOffsetH)==false)
			return false;
		if(::Load(f,tBThrOffsetL)==false)
			return false;
		if(::Load(f,tBThrOffsetH)==false)
			return false;

		RThrOffsetL=tRThrOffsetL;
		RThrOffsetH=tRThrOffsetH;
		GThrOffsetL=tGThrOffsetL;
		GThrOffsetH=tGThrOffsetH;
		BThrOffsetL=tBThrOffsetL;
		BThrOffsetH=tBThrOffsetH;
	}
	else{
		if(::Load(f,RThrOffsetL)==false)
			return false;
		if(::Load(f,RThrOffsetH)==false)
			return false;
		if(::Load(f,GThrOffsetL)==false)
			return false;
		if(::Load(f,GThrOffsetH)==false)
			return false;
		if(::Load(f,BThrOffsetL)==false)
			return false;
		if(::Load(f,BThrOffsetH)==false)
			return false;
	}
	return true;
}


FlatInspectionLibrary::FlatInspectionLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
    MinFlatInspectionSize	=0;
    MaxFlatInspectionSize	=1000000;
    MinFlatInspectionDots	=0;
    MaxFlatInspectionDots	=2000000000;
    LimitFlatInspectionSize=400;
	OverlappedLength		=0;

	NoiseSize				=0;
	NoiseSizePinHole		=0;
    SpaceToOutline			=0;
	UseBackGround			=false;

	MultiSpotDot	=0;
	MultiSpotCount	=0;
	MultiSpotDotGathered	=0;	//密集多点
	MultiSpotCountGathered	=0;
	MultiSpotLengthGathered	=99999999;
	BackGroundOKDot		=100;	
	BackGroundOKLength	=100;		

	AdjustBlack		=0;		//輝度補正の下限幅
    AdjustWhite		=0;		//輝度補正の上限幅
	AreaSearchX		=20;
	AreaSearchY		=20;
    SelfSearch		=0;		//自己探索ドット数
	MaxAreaSearch	=99;		//最大領域探索ドット数
    MaxSelfSearch	=99;		//最大自己探索ドット数

	RedCheckMode		=false;
	RedHighRate			=150;
	RedMinBrightness	=70;
	RedGBMerginRate		=20;
	RedGBMerginOffset	=15;
	RedShrink			=0;
	RedOKDot			=100;

	VariationMode		=false;
	VariationRL=0;	VariationRH=255;	//R-OKバラツキ偏差値
	VariationGL=0;	VariationGH=255;	//G-OKバラツキ偏差値
	VariationBL=0;	VariationBH=255;	//B-OKバラツキ偏差値
	VariationAdaptMinSize	=1000;
	VariationMultiplyMaster	=0.0;
	VariationDifMaster		=false;
	VariationAndLogic		=false;
	VariationSubMasterVari	=0;

	LineMode				=false;
	LineOKMinLength			=30;
	LineMaxWidth			=5;
	LineMinDensityPercent	=20;
	LineMinCluster			=3;
}
FlatInspectionLibrary::~FlatInspectionLibrary(void)
{
}

bool	FlatInspectionLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=FlatInspectionVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,PickupRL)==false)
		return false;
	if(::Save(f,PickupRH)==false)
		return false;
	if(::Save(f,PickupGL)==false)
		return false;
	if(::Save(f,PickupGH)==false)
		return false;
	if(::Save(f,PickupBL)==false)
		return false;
	if(::Save(f,PickupBH)==false)
		return false;
	if(::Save(f,MinFlatInspectionSize)==false)
		return false;
    if(::Save(f,MaxFlatInspectionSize)==false)
		return false;
    if(::Save(f,MinFlatInspectionDots)==false)
		return false;
    if(::Save(f,MaxFlatInspectionDots)==false)
		return false;
    if(::Save(f,LimitFlatInspectionSize)==false)
		return false;

	if(::Save(f,NoiseSize)==false)
		return false;
	if(::Save(f,NoiseSizePinHole)==false)
		return false;
    if(::Save(f,SpaceToOutline)==false)
		return false;
	if(::Save(f,UseBackGround)==false)
		return false;

	if(Broad.SaveBlob(f)==false)
		return false;
	if(Narrow.SaveBlob(f)==false)
		return false;

	if(::Save(f,MultiSpotDot)==false)
		return false;
	if(::Save(f,MultiSpotCount)==false)
		return false;
	if(::Save(f,MultiSpotDotGathered)==false)
		return false;
	if(::Save(f,MultiSpotCountGathered)==false)
		return false;
	if(::Save(f,MultiSpotLengthGathered)==false)
		return false;
	if(::Save(f,BackGroundOKDot)==false)
		return false;
	if(::Save(f,BackGroundOKLength)==false)
		return false;

    if(::Save(f,AdjustBlack)==false)
		return false;
    if(::Save(f,AdjustWhite)==false)
		return false;
    if(::Save(f,AreaSearchX)==false)
		return false;
    if(::Save(f,AreaSearchY)==false)
		return false;
    if(::Save(f,SelfSearch)==false)
		return false;
    if(::Save(f,MaxAreaSearch)==false)
		return false;
    if(::Save(f,MaxSelfSearch)==false)
		return false;

    if(::Save(f,RedCheckMode)==false)
		return false;
    if(::Save(f,RedHighRate)==false)
		return false;
    if(::Save(f,RedGBMerginRate)==false)
		return false;
    if(::Save(f,RedGBMerginOffset)==false)
		return false;
	if(::Save(f,RedOKDot)==false)
		return false;
    if(::Save(f,RedShrink)==false)
		return false;
    if(::Save(f,RedMinBrightness)==false)
		return false;

	if(::Save(f,VariationMode	)==false)
		return false;	
	if(::Save(f,VariationRL	)==false)
		return false;
	if(::Save(f,VariationRH	)==false)
		return false;			
	if(::Save(f,VariationGL	)==false)
		return false;
	if(::Save(f,VariationGH	)==false)
		return false;
	if(::Save(f,VariationBL	)==false)
		return false;
	if(::Save(f,VariationBH	)==false)
		return false;
	if(::Save(f,VariationAdaptMinSize	)==false)
		return false;
	if(::Save(f,VariationMultiplyMaster	)==false)
		return false;
	if(::Save(f,VariationDifMaster	)==false)
		return false;
	if(::Save(f,VariationAndLogic	)==false)
		return false;
	if(::Save(f,VariationSubMasterVari	)==false)
		return false;

	if(::Save(f,OverlappedLength)==false)
		return false;
 
	if(::Save(f,LineMode				)==false)
		return false;	
	if(::Save(f,LineOKMinLength			)==false)
		return false;
	if(::Save(f,LineMaxWidth			)==false)
		return false;
	if(::Save(f,LineMinDensityPercent	)==false)
		return false;
	if(::Save(f,LineMinCluster			)==false)
		return false;
	return true;
}
bool	FlatInspectionLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,PickupRL)==false)
		return false;
	if(::Load(f,PickupRH)==false)
		return false;
	if(::Load(f,PickupGL)==false)
		return false;
	if(::Load(f,PickupGH)==false)
		return false;
	if(::Load(f,PickupBL)==false)
		return false;
	if(::Load(f,PickupBH)==false)
		return false;

	if(::Load(f,MinFlatInspectionSize)==false)
		return false;
	if(::Load(f,MaxFlatInspectionSize)==false)
		return false;
	if(::Load(f,MinFlatInspectionDots)==false)
		return false;
	if(::Load(f,MaxFlatInspectionDots)==false)
		return false;
	if(::Load(f,LimitFlatInspectionSize)==false)
		return false;

	if(::Load(f,NoiseSize)==false)
		return false;
	if(::Load(f,NoiseSizePinHole)==false)
		return false;
	if(::Load(f,SpaceToOutline)==false)
		return false;

	if(::Load(f,UseBackGround)==false)
		return false;


	if(Broad.LoadBlob(f)==false)
		return false;
	if(Narrow.LoadBlob(f)==false)
		return false;

	if(::Load(f,MultiSpotDot)==false)
		return false;
	if(::Load(f,MultiSpotCount)==false)
		return false;
	if(::Load(f,MultiSpotDotGathered)==false)
		return false;
	if(::Load(f,MultiSpotCountGathered)==false)
		return false;
	if(::Load(f,MultiSpotLengthGathered)==false)
		return false;
	if(::Load(f,BackGroundOKDot)==false)
		return false;
	if(::Load(f,BackGroundOKLength)==false)
		return false;

	if(::Load(f,AdjustBlack)==false)
		return false;
	if(::Load(f,AdjustWhite)==false)
		return false;
	if(::Load(f,AreaSearchX)==false)
		return false;
	if(::Load(f,AreaSearchY)==false)
		return false;
	if(::Load(f,SelfSearch)==false)
		return false;
	if(::Load(f,MaxAreaSearch)==false)
		return false;
	if(::Load(f,MaxSelfSearch)==false)
		return false;

	if(::Load(f,RedCheckMode)==false)
		return false;
	if(::Load(f,RedHighRate)==false)
		return false;
	if(::Load(f,RedGBMerginRate)==false)
		return false;
	if(::Load(f,RedGBMerginOffset)==false)
		return false;
	if(::Load(f,RedOKDot)==false)
		return false;
	if(::Load(f,RedShrink)==false)
		return false;
	if(::Load(f,RedMinBrightness)==false)
		return false;

	if(::Load(f,VariationMode	)==false)
		return false;	
	if(::Load(f,VariationRL	)==false)
		return false;
	if(::Load(f,VariationRH	)==false)
		return false;			
	if(::Load(f,VariationGL	)==false)
		return false;
	if(::Load(f,VariationGH	)==false)
		return false;
	if(::Load(f,VariationBL	)==false)
		return false;
	if(::Load(f,VariationBH	)==false)
		return false;
	if(::Load(f,VariationAdaptMinSize	)==false)
		return false;
	if(::Load(f,VariationMultiplyMaster	)==false)
		return false;
	if(::Load(f,VariationDifMaster	)==false)
		return false;
	if(::Load(f,VariationAndLogic	)==false)
		return false;
	if(::Load(f,VariationSubMasterVari	)==false)
		return false;

	if(::Load(f,OverlappedLength)==false)
		return false;
 
	if(::Load(f,LineMode				)==false)
		return false;	
	if(::Load(f,LineOKMinLength			)==false)
		return false;
	if(::Load(f,LineMaxWidth			)==false)
		return false;
	if(::Load(f,LineMinDensityPercent	)==false)
		return false;
	if(::Load(f,LineMinCluster			)==false)
		return false;

	return true;
}


FlatInspectionLibrary	&FlatInspectionLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((FlatInspectionLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

//==============================================================================

FlatInspectionLibraryContainer::FlatInspectionLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
FlatInspectionLibraryContainer::~FlatInspectionLibraryContainer(void)
{
}


