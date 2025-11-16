/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDotColorMatchingLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XDotColorMatchingLibrary.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XDotColorMatching.h"
#include "XTypeDef.h"

DotColorMatchingLibrary::MLibThreshold::MLibThreshold(void)
{
	BrightWidthRL	=0;		//暗側輝度幅
	BrightWidthRH	=0;		//明側輝度幅
	BrightWidthGL	=0;		//暗側輝度幅
	BrightWidthGH	=0;		//明側輝度幅
	BrightWidthBL	=0;		//暗側輝度幅
	BrightWidthBH	=0;		//明側輝度幅
	
	OKDot			=0;		//ＯＫドット数
	OKLength		=99999999;

	RThrOffsetL		=0;
	RThrOffsetH		=0;
	GThrOffsetL		=0;
	GThrOffsetH		=0;
	BThrOffsetL		=0;
	BThrOffsetH		=0;
}

bool	DotColorMatchingLibrary::MLibThreshold::SaveBlob(QIODevice *f)
{
	int32	Ver=DotColorMatchingInspectionVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,BrightWidthRL)==false)
		return false;
	if(::Save(f,BrightWidthRH)==false)
		return false;
	if(::Save(f,BrightWidthGL)==false)
		return false;
	if(::Save(f,BrightWidthGH)==false)
		return false;
	if(::Save(f,BrightWidthBL)==false)
		return false;
	if(::Save(f,BrightWidthBH)==false)
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
bool	DotColorMatchingLibrary::MLibThreshold::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

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

	if(::Load(f,OKDot)==false)
		return false;
	if(::Load(f,OKLength)==false)
		return false;

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

	return true;
}


DotColorMatchingLibrary::DotColorMatchingLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{

	EvenWidth0				=255;
	EvenWidth255			=255;
    MinDotColorMatchingSize	=0;
    MaxDotColorMatchingSize	=1000000;
    MinDotColorMatchingDots	=0;
    MaxDotColorMatchingDots	=2000000000;
    LimitDotColorMatchingSize=400;
	OverlappedLength		=0;
	GenerateOnEdgeWidth		=0;
	OutlineAroundPriorItems	=0;
	SearchDotForBrightnessRange	=1;
	BindGroupArea			=0;
	PriorityToShow			=100;

	NoiseSize				=0;
	NoiseSizePinHole		=0;
    SpaceToOutline			=0;
    Priority				=0;
	AreaType				=1;
	EnableOverlap			=false;
	GenerateOutlineMode		=true;
	ThresholdPickupEdge		=10.0;
	ThresholdFlatPattern	=5;
	UseBackGround			=false;
	GenerateOnlyLimitedMask	=false;

	VarietySigma	=0;
	MultiSpotDot	=0;
	MultiSpotCount	=0;
	MultiSpotDotGathered	=0;	//密集多点
	MultiSpotCountGathered	=0;
	MultiSpotLengthGathered	=99999999;
	BackGroundOKDot		=100;	
	BackGroundOKLength	=100;		

	AdjustBlack		=0;		//輝度補正の下限幅
    AdjustWhite		=0;		//輝度補正の上限幅
	AdjustContribute=10;
	AreaSearchX		=20;
	AreaSearchY		=20;
    SelfSearch		=0;		//自己探索ドット数
	PreciseSearch	=false;
	Clusterize		=false;
	EnableT2M		=true;
	EnableM2T		=true;
	UseMaster2		=false;
	ExpandToSubBlock=20;
	MaxAreaSearch	=99;		//最大領域探索ドット数
    MaxSelfSearch	=99;		//最大自己探索ドット数

	ScratchStartDirection	=0.0;
	ScratchRotationAngle	=0.0;
	ScratchVariety			=1.0;
	ScratchDetectLevelL		=5;
	ScratchDetectLevelH		=5;
	ScratchMaxWidth			=15;
	ScratchEnable			=false;
	ScratchUseMaster		=true;
	ScratchVOffset			=0;
	ScratchDiff				=5;

	RedCheckMode		=false;
	RedHighRate			=150;
	RedMinBrightness	=70;
	RedGBMerginRate		=20;
	RedGBMerginOffset	=15;
	RedShrink			=0;
	RedOKDot			=100;

	HsvCheckMode		=false;
	HsvFixedColorMode	=false;
	HsvH				=180;
	HsvS				=128;
	HsvV				=128;
	HsvPHL				=10;
	HsvPHH				=10;
	HsvPSL				=10;
	HsvPSH				=10;
	HsvPVL				=10;
	HsvPVH				=10;
	HsvDHL				=10;
	HsvDHH				=10;
	HsvDSL				=10;
	HsvDSH				=10;
	HsvDVL				=10;
	HsvDVH				=10;
	HsvOKDot			=100;
	HsvOKLength			=99999999;

	UseOneLayer			=0xFF;
	MatchBrightnessByLayerH	=0xFF;
	MatchBrightnessByLayerL	=0xFF;
	MasterNoOriginCode	=0;

	VariationMode		=false;
	VariationRL=0;	VariationRH=255;	//R-OKバラツキ偏差値
	VariationGL=0;	VariationGH=255;	//G-OKバラツキ偏差値
	VariationBL=0;	VariationBH=255;	//B-OKバラツキ偏差値
	VariationAdaptMinSize	=1000;
	VariationMultiplyMaster	=0.0;
	VariationDifMaster		=false;
	VariationAndLogic		=false;
	VariationSubMasterVari	=0;

	PitMode				=false;
	PitBrightWidthRL	=50;
	PitBrightWidthRH	=50;
	PitBrightWidthGL	=50;
	PitBrightWidthGH	=50;
	PitBrightWidthBL	=50;
	PitBrightWidthBH	=50;

	LineMode				=false;
	LineOKMinLength			=30;
	LineMaxWidth			=5;
	LineMinDensityPercent	=20;
	LineMinCluster			=3;
}
DotColorMatchingLibrary::~DotColorMatchingLibrary(void)
{
}

bool	DotColorMatchingLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=DotColorMatchingInspectionVersion;

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
	if(::Save(f,EvenWidth0) == false)
		return false;
	if(::Save(f,EvenWidth255) == false)
		return false;
	if(::Save(f,MinDotColorMatchingSize)==false)
		return false;
    if(::Save(f,MaxDotColorMatchingSize)==false)
		return false;
    if(::Save(f,MinDotColorMatchingDots)==false)
		return false;
    if(::Save(f,MaxDotColorMatchingDots)==false)
		return false;
    if(::Save(f,LimitDotColorMatchingSize)==false)
		return false;
   if(::Save(f,GenerateOnEdgeWidth)==false)
		return false;
    if(::Save(f,OutlineAroundPriorItems)==false)
		return false;
    if(::Save(f,SearchDotForBrightnessRange)==false)
		return false;
	if(::Save(f,BindGroupArea)==false)
		return false;
	if(::Save(f,PriorityToShow)==false)
		return false;

	if(::Save(f,NoiseSize)==false)
		return false;
	if(::Save(f,NoiseSizePinHole)==false)
		return false;
    if(::Save(f,SpaceToOutline)==false)
		return false;
    if(::Save(f,Priority)==false)
		return false;
    if(::Save(f,AreaType)==false)
		return false;
    if(::Save(f,EnableOverlap)==false)
		return false;
    if(::Save(f,GenerateOutlineMode)==false)
		return false;
	if(::Save(f,ThresholdPickupEdge)==false)
		return false;
	if(::Save(f,ThresholdFlatPattern)==false)
		return false;
	if(::Save(f,UseBackGround)==false)
		return false;
	if(::Save(f,GenerateOnlyLimitedMask)==false)
		return false;

	if(Broad.SaveBlob(f)==false)
		return false;
	if(Narrow.SaveBlob(f)==false)
		return false;

	if(::Save(f,VarietySigma)==false)
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
    if(::Save(f,PreciseSearch)==false)
		return false;
	if(::Save(f,Clusterize)==false)
		return false;
    if(::Save(f,EnableT2M)==false)
		return false;
    if(::Save(f,EnableM2T)==false)
		return false;
    if(::Save(f,UseMaster2)==false)
		return false;
    if(::Save(f,ExpandToSubBlock)==false)
		return false;
    if(::Save(f,MaxAreaSearch)==false)
		return false;
    if(::Save(f,MaxSelfSearch)==false)
		return false;

    if(::Save(f,ScratchStartDirection)==false)
		return false;
    if(::Save(f,ScratchRotationAngle)==false)
		return false;
    if(::Save(f,ScratchVariety)==false)
		return false;
    if(::Save(f,ScratchDetectLevelL)==false)
		return false;
    if(::Save(f,ScratchDetectLevelH)==false)
		return false;
    if(::Save(f,ScratchMaxWidth)==false)
		return false;
    if(::Save(f,ScratchEnable)==false)
		return false;
    if(::Save(f,ScratchUseMaster)==false)
		return false;
    if(::Save(f,ScratchVOffset)==false)
		return false;
    if(::Save(f,ScratchDiff)==false)
		return false;

    if(::Save(f,UseOneLayer)==false)
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

    if(::Save(f,MatchBrightnessByLayerH)==false)
		return false;
    if(::Save(f,MatchBrightnessByLayerL)==false)
		return false;
    if(::Save(f,MasterNoOriginCode)==false)
		return false;

	if(::Save(f,HsvCheckMode	)==false)
		return false;	
	if(::Save(f,HsvFixedColorMode	)==false)
		return false;
	if(::Save(f,HsvH	)==false)
		return false;			
	if(::Save(f,HsvS	)==false)
		return false;			
	if(::Save(f,HsvV	)==false)
		return false;			
	if(::Save(f,HsvPHL	)==false)
		return false;			
	if(::Save(f,HsvPHH	)==false)
		return false;			
	if(::Save(f,HsvPSL	)==false)
		return false;			
	if(::Save(f,HsvPSH	)==false)
		return false;			
	if(::Save(f,HsvPVL	)==false)
		return false;			
	if(::Save(f,HsvPVH	)==false)
		return false;
	if(::Save(f,HsvDHL	)==false)
		return false;			
	if(::Save(f,HsvDHH	)==false)
		return false;			
	if(::Save(f,HsvDSL	)==false)
		return false;			
	if(::Save(f,HsvDSH	)==false)
		return false;			
	if(::Save(f,HsvDVL	)==false)
		return false;			
	if(::Save(f,HsvDVH	)==false)
		return false;	
	if(::Save(f,HsvOKDot)==false)
		return false;			
	if(::Save(f,HsvOKLength)==false)
		return false;
	if(SubtractLibID.Save(f)==false)
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

	if(::Save(f,PitMode)==false)
		return false;
	if(::Save(f,PitBrightWidthRL)==false)
		return false;
	if(::Save(f,PitBrightWidthRH)==false)
		return false;
	if(::Save(f,PitBrightWidthGL)==false)
		return false;
	if(::Save(f,PitBrightWidthGH)==false)
		return false;
	if(::Save(f,PitBrightWidthBL)==false)
		return false;
	if(::Save(f,PitBrightWidthBH)==false)
		return false;

	if(::Save(f,AdjustContribute)==false)
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
bool	DotColorMatchingLibrary::LoadBlob(QIODevice *f)
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
	if(Ver>=10023){
		if (::Load(f,EvenWidth0) == false)
			return false;
		if (::Load(f,EvenWidth255) == false)
			return false;
	}
	else if(Ver==10022){
		if (::Load(f,EvenWidth0) == false)
			return false;
		EvenWidth255=EvenWidth0;
	}
	else{
		EvenWidth255=255;
		EvenWidth0	=255;
	}
	if(::Load(f,MinDotColorMatchingSize)==false)
		return false;
	if(::Load(f,MaxDotColorMatchingSize)==false)
		return false;
	if(::Load(f,MinDotColorMatchingDots)==false)
		return false;
	if(::Load(f,MaxDotColorMatchingDots)==false)
		return false;
	if(::Load(f,LimitDotColorMatchingSize)==false)
		return false;

	if(Ver>=10028){
		if(::Load(f,GenerateOnEdgeWidth)==false)
			return false;
	}
	else{
		GenerateOnEdgeWidth=0;
	}
	if(Ver>=10029){
		if(::Load(f,OutlineAroundPriorItems)==false)
			return false;
	}
	else{
		OutlineAroundPriorItems=0;
	}
	if(Ver>=10031){
		if(::Load(f,SearchDotForBrightnessRange)==false)
			return false;
	}
	else{
		SearchDotForBrightnessRange=1;
	}
	if(Ver>=10032){
		if(::Load(f,BindGroupArea)==false)
			return false;
	}
	else{
		BindGroupArea=0;
	}
	if(Ver>=10039){
		if(::Load(f,PriorityToShow)==false)
			return false;
	}
	else{
		PriorityToShow=0;
	}

	if(::Load(f,NoiseSize)==false)
		return false;
	if(::Load(f,NoiseSizePinHole)==false)
		return false;
	if(::Load(f,SpaceToOutline)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
 	if(Ver>=10007){
		if(::Load(f,AreaType)==false)
			return false;
	}
	else{
		AreaType=0;
	}
 	if(Ver>=10019){
		if(::Load(f,EnableOverlap)==false)
			return false;
	}
	else{
		EnableOverlap=false;
	}
 	if(Ver>=10026){
		if(::Load(f,GenerateOutlineMode)==false)
			return false;
	}
	else{
		GenerateOutlineMode=false;
	}
 	if(Ver>=10036){
		if(::Load(f,ThresholdPickupEdge)==false)
			return false;
	}
	else{
		ThresholdPickupEdge=10.0;
	}
 	if(Ver>=10037){
		if(::Load(f,ThresholdFlatPattern)==false)
			return false;
	}
	else{
		ThresholdFlatPattern=5.0;
	}
 	if(Ver>=10041){
		if(::Load(f,UseBackGround)==false)
			return false;
	}
	else{
		UseBackGround=false;
	}
	if(Ver>=10058){
		if(::Load(f,GenerateOnlyLimitedMask)==false)
			return false;
	}
	else{
		GenerateOnlyLimitedMask=false;
	}

	if(Ver<10063){
		if(::Load(f,Broad.BrightWidthRL)==false)
			return false;
		if(::Load(f,Broad.BrightWidthRH)==false)
			return false;
		if(::Load(f,Broad.BrightWidthGL)==false)
			return false;
		if(::Load(f,Broad.BrightWidthGH)==false)
			return false;
		if(::Load(f,Broad.BrightWidthBL)==false)
			return false;
		if(::Load(f,Broad.BrightWidthBH)==false)
			return false;
		if(Ver>=10014){
			if(::Load(f,VarietySigma)==false)
				return false;
		}
		else{
			VarietySigma=0;
		}
		if(::Load(f,Broad.OKDot)==false)
			return false;
		if(Ver>=10012){
			if(::Load(f,Broad.OKLength)==false)
				return false;
		}
		else{
			Broad.OKLength=99999999;
		}
		if(Ver>=10008){
			if(::Load(f,MultiSpotDot)==false)
				return false;
			if(::Load(f,MultiSpotCount)==false)
				return false;
		}
		if(Ver>=10043){
			if(::Load(f,MultiSpotDotGathered)==false)
				return false;
			if(::Load(f,MultiSpotCountGathered)==false)
				return false;
			if(::Load(f,MultiSpotLengthGathered)==false)
				return false;
		}
		else{
			MultiSpotDotGathered	=0;
			MultiSpotCountGathered	=0;
			MultiSpotLengthGathered	=99999999;
		}
		if(Ver>=10040){
			if(::Load(f,BackGroundOKDot)==false)
				return false;
			if(::Load(f,BackGroundOKLength)==false)
				return false;
		}
		else{
			BackGroundOKDot		=Broad.OKDot;
			BackGroundOKLength	=Broad.OKLength;
		}

		if(::Load(f,AdjustBlack)==false)
			return false;
		if(::Load(f,AdjustWhite)==false)
			return false;
		if(Ver>=10003){
			if(Ver>=10059){
				if(::Load(f,AreaSearchX)==false)
					return false;
				if(::Load(f,AreaSearchY)==false)
					return false;
			}
			else{
				WORD	AreaSearch;
				if(::Load(f,AreaSearch)==false)
					return false;
				AreaSearchX=AreaSearch;
				AreaSearchY=AreaSearch;
			}
		}
		if(::Load(f,SelfSearch)==false)
			return false;
		if(Ver>=10060){
		    if(::Load(f,PreciseSearch)==false)
				return false;
		}
		else{
			PreciseSearch=false;
		}
		if(Ver>=10002){
		    if(::Load(f,Clusterize)==false)
				return false;
		}
		else{
			Clusterize=false;
		}
 		if(Ver>=10009){
			if(::Load(f,EnableT2M)==false)
				return false;
		    if(::Load(f,EnableM2T)==false)
				return false;
		}
 		if(Ver>=10021){
			if(::Load(f,UseMaster2)==false)
				return false;
		}
		else{
			UseMaster2=false;
		}
 		if(Ver>=10047){
			if(::Load(f,ExpandToSubBlock)==false)
				return false;
		}
		else{
			ExpandToSubBlock=20;
		}
		if(Ver>=10010){
		    if(::Load(f,Broad.RThrOffsetL)==false)
				return false;
		    if(::Load(f,Broad.RThrOffsetH)==false)
				return false;
		    if(::Load(f,Broad.GThrOffsetL)==false)
				return false;
		    if(::Load(f,Broad.GThrOffsetH)==false)
				return false;
		    if(::Load(f,Broad.BThrOffsetL)==false)
				return false;
		    if(::Load(f,Broad.BThrOffsetH)==false)
				return false;
		}
		if(Ver>=10051){
		    if(::Load(f,MaxAreaSearch)==false)
				return false;
		    if(::Load(f,MaxSelfSearch)==false)
				return false;
		}
		if(Ver==10011){
			double	dScratchStartDirection;
			if(::Load(f,dScratchStartDirection)==false)
				return false;
			ScratchStartDirection=dScratchStartDirection;
		}
		else
		if(Ver>=10012){
			if(::Load(f,ScratchStartDirection)==false)
				return false;
		}
		if(Ver>=10016){
			if(::Load(f,ScratchRotationAngle)==false)
				return false;
		}
		if(Ver>=10017){
			if(::Load(f,ScratchVariety)==false)
				return false;
		}
		if(Ver>=10011){
			if(::Load(f,ScratchDetectLevelL)==false)
				return false;
			if(::Load(f,ScratchDetectLevelH)==false)
				return false;
			if(::Load(f,ScratchMaxWidth)==false)
				return false;
		}
		if(Ver>=10012){
			if(::Load(f,ScratchEnable)==false)
				return false;
		}
		else{
			ScratchEnable=false;
		}
		if(Ver>=10024){
			if(::Load(f,ScratchUseMaster)==false)
				return false;
		}
		else{
			ScratchUseMaster=true;
		}
		if(Ver>=10025){
			if(::Load(f,ScratchVOffset)==false)
				return false;
		}
		else{
			ScratchVOffset=0;
		}
		if(Ver>=10033){
			if(::Load(f,ScratchDiff)==false)
				return false;
		}
		else{
			ScratchDiff=5;
		}

		if(Ver>=10015){
			if(::Load(f,UseOneLayer)==false)
				return false;
		}
		else{
			UseOneLayer=0xFF;
		}

		if(Ver>=10026){
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
		}
		else{
			RedCheckMode		=false;
			RedHighRate			=150;
			RedGBMerginRate		=20;
			RedGBMerginOffset	=15;
			RedOKDot			=100;
		}
		if(Ver>=10038){
			if(::Load(f,RedShrink)==false)
				return false;
		}
		else{
			RedShrink=0;
		}
		if(Ver>=10027){
			if(::Load(f,RedMinBrightness)==false)
				return false;
		}
		else{
			RedMinBrightness		=70;
		}

		if(Ver>=10030){
			if(::Load(f,MatchBrightnessByLayerH)==false)
				return false;
			if(::Load(f,MatchBrightnessByLayerL)==false)
				return false;
		}
		else{
			MatchBrightnessByLayerH	=0xFF;
			MatchBrightnessByLayerL	=0xFF;
		}
		if(Ver>=10035){
			if(::Load(f,MasterNoOriginCode)==false)
				return false;
		}
		else{
			MasterNoOriginCode	=0;
		}
		if(Ver>=10042){
			if(::Load(f,HsvCheckMode	)==false)
				return false;	
			if(::Load(f,HsvFixedColorMode	)==false)
				return false;
			if(::Load(f,HsvH	)==false)
				return false;			
			if(::Load(f,HsvS	)==false)
				return false;			
			if(::Load(f,HsvV	)==false)
				return false;			
			if(::Load(f,HsvPHL	)==false)
				return false;			
			if(::Load(f,HsvPHH	)==false)
				return false;			
			if(::Load(f,HsvPSL	)==false)
				return false;			
			if(::Load(f,HsvPSH	)==false)
				return false;			
			if(::Load(f,HsvPVL	)==false)
				return false;			
			if(::Load(f,HsvPVH	)==false)
				return false;
			if(::Load(f,HsvDHL	)==false)
				return false;			
			if(::Load(f,HsvDHH	)==false)
				return false;			
			if(::Load(f,HsvDSL	)==false)
				return false;			
			if(::Load(f,HsvDSH	)==false)
				return false;			
			if(::Load(f,HsvDVL	)==false)
				return false;			
			if(::Load(f,HsvDVH	)==false)
				return false;	
			if(::Load(f,HsvOKDot)==false)
				return false;
			if(::Load(f,HsvOKLength)==false)
				return false;
		}
		if(Ver>=10045){
			if(SubtractLibID.Load(f)==false)
				return false;
		}
		if(Ver>=10048){
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
		}
		if(Ver>=10049){
			if(::Load(f,VariationAdaptMinSize	)==false)
				return false;
		}
		if(Ver>=10052){
			if(::Load(f,VariationMultiplyMaster	)==false)
				return false;
		}
		if(Ver>=10054){
			if(::Load(f,VariationDifMaster	)==false)
				return false;
		}
		if(Ver>=10056){
			if(::Load(f,VariationAndLogic	)==false)
				return false;
		}
		if(Ver>=10057){
			if(::Load(f,VariationSubMasterVari	)==false)
				return false;
		}
		if(Ver>=10050){
			if(::Load(f,PitMode)==false)
				return false;
			if(::Load(f,PitBrightWidthRL)==false)
				return false;
			if(::Load(f,PitBrightWidthRH)==false)
				return false;
			if(::Load(f,PitBrightWidthGL)==false)
				return false;
			if(::Load(f,PitBrightWidthGH)==false)
				return false;
			if(::Load(f,PitBrightWidthBL)==false)
				return false;
			if(::Load(f,PitBrightWidthBH)==false)
				return false;
		}
		if(Ver>=10053){
			if(::Load(f,AdjustContribute)==false)
				return false;
		}
		if(Ver>=10055){
			if(::Load(f,OverlappedLength)==false)
				return false;
		}
		else{
			OverlappedLength=max(AreaSearchX,AreaSearchY);
		}
		if(Ver>=10061){
			if(::Load(f,LineMode				)==false)
				return false;	
			if(::Load(f,LineOKMinLength			)==false)
				return false;
			if(::Load(f,LineMaxWidth			)==false)
				return false;
			if(::Load(f,LineMinDensityPercent	)==false)
				return false;
		}
		if(Ver>=10062){
			if(::Load(f,LineMinCluster			)==false)
				return false;
		}
	}
	else{
		if(Broad.LoadBlob(f)==false)
			return false;
		if(Narrow.LoadBlob(f)==false)
			return false;

		if(::Load(f,VarietySigma)==false)
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
		if(::Load(f,PreciseSearch)==false)
			return false;
		if(::Load(f,Clusterize)==false)
			return false;
		if(::Load(f,EnableT2M)==false)
			return false;
		if(::Load(f,EnableM2T)==false)
			return false;
		if(::Load(f,UseMaster2)==false)
			return false;
		if(::Load(f,ExpandToSubBlock)==false)
			return false;
		if(::Load(f,MaxAreaSearch)==false)
			return false;
		if(::Load(f,MaxSelfSearch)==false)
			return false;

		if(::Load(f,ScratchStartDirection)==false)
			return false;
		if(::Load(f,ScratchRotationAngle)==false)
			return false;
		if(::Load(f,ScratchVariety)==false)
			return false;
		if(::Load(f,ScratchDetectLevelL)==false)
			return false;
		if(::Load(f,ScratchDetectLevelH)==false)
			return false;
		if(::Load(f,ScratchMaxWidth)==false)
			return false;
		if(::Load(f,ScratchEnable)==false)
			return false;
		if(::Load(f,ScratchUseMaster)==false)
			return false;
		if(::Load(f,ScratchVOffset)==false)
			return false;
		if(::Load(f,ScratchDiff)==false)
			return false;

		if(::Load(f,UseOneLayer)==false)
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

		if(::Load(f,MatchBrightnessByLayerH)==false)
			return false;
		if(::Load(f,MatchBrightnessByLayerL)==false)
			return false;
		if(::Load(f,MasterNoOriginCode)==false)
			return false;

		if(::Load(f,HsvCheckMode	)==false)
			return false;	
		if(::Load(f,HsvFixedColorMode	)==false)
			return false;
		if(::Load(f,HsvH	)==false)
			return false;			
		if(::Load(f,HsvS	)==false)
			return false;			
		if(::Load(f,HsvV	)==false)
			return false;			
		if(::Load(f,HsvPHL	)==false)
			return false;			
		if(::Load(f,HsvPHH	)==false)
			return false;			
		if(::Load(f,HsvPSL	)==false)
			return false;			
		if(::Load(f,HsvPSH	)==false)
			return false;			
		if(::Load(f,HsvPVL	)==false)
			return false;			
		if(::Load(f,HsvPVH	)==false)
			return false;
		if(::Load(f,HsvDHL	)==false)
			return false;			
		if(::Load(f,HsvDHH	)==false)
			return false;			
		if(::Load(f,HsvDSL	)==false)
			return false;			
		if(::Load(f,HsvDSH	)==false)
			return false;			
		if(::Load(f,HsvDVL	)==false)
			return false;			
		if(::Load(f,HsvDVH	)==false)
			return false;	
		if(::Load(f,HsvOKDot)==false)
			return false;			
		if(::Load(f,HsvOKLength)==false)
			return false;
		if(SubtractLibID.Load(f)==false)
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

		if(::Load(f,PitMode)==false)
			return false;
		if(::Load(f,PitBrightWidthRL)==false)
			return false;
		if(::Load(f,PitBrightWidthRH)==false)
			return false;
		if(::Load(f,PitBrightWidthGL)==false)
			return false;
		if(::Load(f,PitBrightWidthGH)==false)
			return false;
		if(::Load(f,PitBrightWidthBL)==false)
			return false;
		if(::Load(f,PitBrightWidthBH)==false)
			return false;

		if(::Load(f,AdjustContribute)==false)
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
	}
	return true;
}


DotColorMatchingLibrary	&DotColorMatchingLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((DotColorMatchingLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

void	DotColorMatchingLibrary::MakePickupTest(ImageBuffer *IBuff[]
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

	int	YNumb=min(YLen,IBuff[0]->GetHeight());
	int	XNumb=min(XLen,IBuff[0]->GetWidth());
	if(GetLayerNumb(Page)>=3){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*srcR=IBuff[0]->GetY(y);
				BYTE	*srcG=IBuff[1]->GetY(y);
				BYTE	*srcB=IBuff[2]->GetY(y);
				BYTE	*dest=BmpPoint[y];
				int		cR,cG,cB;
				for(int x=0;x<XNumb;x++,srcR++,srcG++,srcB++){
					cR=*srcR;
					cG=*srcG;
					cB=*srcB;
					if(PickupRL<=cR && cR<=PickupRH && PickupGL<=cG && cG<=PickupGH && PickupBL<=cB && cB<=PickupBH){
						dest[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	else if(GetLayerNumb(Page)==2){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*srcR=IBuff[0]->GetY(y);
				BYTE	*srcG=IBuff[1]->GetY(y);
				BYTE	*dest=BmpPoint[y];
				int		cR,cG;
				for(int x=0;x<XNumb;x++,srcR++,srcG++){
					cR=*srcR;
					cG=*srcG;
					if(PickupRL<=cR && cR<=PickupRH && PickupGL<=cG && cG<=PickupGH){
						dest[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	else if(GetLayerNumb(Page)==1){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*srcR=IBuff[0]->GetY(y);
				BYTE	*dest=BmpPoint[y];
				int		cR;
				for(int x=0;x<XNumb;x++,srcR++){
					cR=*srcR;
					if(PickupRL<=cR && cR<=PickupRH){
						dest[x>>3] |= 0x80>>(x&7);
					}
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
	if(SpaceToOutline>0){
		if(SpaceToOutline>1){
			GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen ,SpaceToOutline-1);
		}
		GetLayersBase()->ThinArea1(BmpPoint,TmpData ,XByte, YLen);
	}
	else if(SpaceToOutline<0){
		GetLayersBase()->FatAreaN(BmpPoint,TmpData ,XByte, YLen ,-SpaceToOutline);
	}

	if(0<MinDotColorMatchingDots || 0<MinDotColorMatchingSize || MaxDotColorMatchingSize<GetDotPerLine(Page) || MaxDotColorMatchingSize<GetMaxLines(Page)
	|| MaxDotColorMatchingDots<2000000000 || MaxDotColorMatchingDots<GetDotPerLine(Page)*GetMaxLines(Page)){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BmpPoint,XByte,XLen,YLen ,FPack);
		MatrixBuffClear(BmpPoint ,0 ,XByte ,YLen);
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			int	DotN=a->GetPatternByte();
			if(MinDotColorMatchingDots<=DotN && DotN<=MaxDotColorMatchingDots && MinDotColorMatchingSize<=a->GetWidth() && a->GetWidth()<=MaxDotColorMatchingSize && MinDotColorMatchingSize<=a->GetHeight() && a->GetHeight()<=MaxDotColorMatchingSize){
				a->MakeBitData(BmpPoint,XLen ,YLen);
			}
		}
	}
	if(0<GenerateOnEdgeWidth && GenerateOnEdgeWidth<10000){
		MatrixBuffCopy(TmpData2					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);
		GetLayersBase()->ThinAreaN(TmpData2,TmpData ,XByte, YLen,GenerateOnEdgeWidth);
		MatrixBuffCopy(TmpData					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);
		MatrixBuffNotAnd(BmpPoint,(const BYTE **)TmpData2,XByte,YLen);
		if(EnableOverlap==false){
			int	MSearch=OverlappedLength;
			GetLayersBase()->FatAreaN(BmpPoint,TmpData2 ,XByte, YLen,MSearch);
			MatrixBuffNotAnd(BmpPoint,(const BYTE **)TmpData,XByte,YLen);
		}
	}

	GetLayersBase()->StepProcessing(-1);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);

		if(SpaceToOutline>0){
			if(SpaceToOutline>1){
				GetLayersBase()->FatAreaN(OcupyMap,TmpData ,XByte, YLen,SpaceToOutline-1);
			}
			GetLayersBase()->ThinArea1(BmpPoint,TmpData ,XByte, YLen);
		}
		else if(SpaceToOutline<0){
			GetLayersBase()->ThinAreaN(OcupyMap,TmpData ,XByte, YLen,-SpaceToOutline);
		}
	}
	DeleteMatrixBuff(TmpData2,YLen);


	GetLayersBase()->StepProcessing(-1);
	DeleteMatrixBuff(TmpData,YLen);
}


class	PureFlexAreaListPoint : public NPList<PureFlexAreaListPoint>
{
public:
	PureFlexAreaList	*Point;
	PureFlexAreaListPoint(PureFlexAreaList *p){	Point=p;	}
};

static	int	DbgLoopXY;

void	DotColorMatchingLibrary::MakeDotColorMatching(
			ImageBuffer *IBuff[]
			,BYTE **CurrentMap,BYTE **OcupyMap,BYTE **SubBlockMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &DotColorMatchingList)
{
	BYTE	**TmpData =MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);
	if(OutlineAroundPriorItems>0){
		MatrixBuffCopy(TmpData				 ,XByte,YLen
					, (const BYTE **)OcupyMap,XByte,YLen);
		MatrixBuffNotAnd(TmpData,(const BYTE **)SubBlockMap,XByte,YLen);
		GetLayersBase()->FatAreaN(TmpData,TmpData2 ,XByte, YLen,OutlineAroundPriorItems);
		MatrixBuffAnd	(TmpData,(const BYTE **)CurrentMap,XByte,YLen);
		MatrixBuffNotAnd(CurrentMap,(const BYTE **)TmpData,XByte,YLen);

		if(EnableOverlap==false){
			int	MSearch=OverlappedLength;
			GetLayersBase()->FatAreaN(TmpData,TmpData2 ,XByte, YLen,MSearch);
			MatrixBuffCopy(TmpData2				 ,XByte,YLen
						, (const BYTE **)OcupyMap,XByte,YLen);
			MatrixBuffOr(TmpData2,(const BYTE **)SubBlockMap,XByte,YLen);
			MatrixBuffNotAnd(TmpData,(const BYTE **)TmpData2,XByte,YLen);
		}
			
		MatrixBuffCopy(TmpData2				 ,XByte,YLen
					, (const BYTE **)OcupyMap,XByte,YLen);
		MatrixBuffNotAnd(TmpData2,(const BYTE **)SubBlockMap,XByte,YLen);
		NPListPack<AlgorithmItemPI> TmpDotColorMatchingList;
		MakeDotColorMatchingInner(
			IBuff
			,TmpData,TmpData2
			,Page
			,XByte ,XLen,YLen
			,TmpDotColorMatchingList);
		for(AlgorithmItemPI *a=TmpDotColorMatchingList.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
			if(Item!=NULL){
				Item->OutlineBlock=true;
			}
		}
		DotColorMatchingList.AddMove(TmpDotColorMatchingList);
	}

	MatrixBuffCopy(TmpData2				 ,XByte,YLen
				, (const BYTE **)OcupyMap,XByte,YLen);
	MatrixBuffNotAnd(TmpData2,(const BYTE **)SubBlockMap,XByte,YLen);
	MakeDotColorMatchingInner(
			IBuff
			,CurrentMap,TmpData2
			,Page
			,XByte ,XLen,YLen
			,DotColorMatchingList);
		
	DeleteMatrixBuff(TmpData2,YLen);
	DeleteMatrixBuff(TmpData,YLen);
}

void	DotColorMatchingLibrary::MakeDotColorMatchingInner(
			ImageBuffer *IBuff[]
			,BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &DotColorMatchingList)
{
	GetLayersBase()->SetMaxProcessing(6);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(TmpData					,XByte,YLen
		         , (const BYTE **)CurrentMap,XByte,YLen);

	PureFlexAreaListContainer	L3List;

	int	XNumbInt =XByte/sizeof(unsigned int);
	int	XNumbLeft=XByte%sizeof(unsigned int);
	if(EnableOverlap==false){
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
	}

	GetLayersBase()->StepProcessing(-1);

	try{
		PureFlexAreaListContainer FPack;
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
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

		//#pragma omp parallel
		//{
		//	#pragma omp for
			for(int k=0;k<N;k++){
				PureFlexAreaList *h=PureFlexAreaPointerDim[k];
				PureFlexAreaListContainer Piece;
				if(LimitDotColorMatchingSize==0 || (h->GetWidth()<LimitDotColorMatchingSize && h->GetHeight()<LimitDotColorMatchingSize)){
					Piece.AppendList(h);
					h=NULL;
				}
				else{
					h->ChopRect(Piece ,LimitDotColorMatchingSize);
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
		//}
		delete	[]PureFlexAreaPointerDim;
	}	
	catch(...){}

	GetLayersBase()->StepProcessing(-1);

	int	MSearch=OverlappedLength;
	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		int	aXLen=a->GetWidth()+MSearch*2+2+16;
		int	aXByte=(aXLen+7)/8;
		int	aYLen=a->GetHeight()+MSearch*2+2;
		BYTE	**TmpBuff =MakeMatrixBuff(aXByte ,aYLen);
		BYTE	**TmpBuff2=MakeMatrixBuff(aXByte ,aYLen);
		MatrixBuffClear(TmpBuff,0,aXByte,aYLen);
		int	dx=-a->GetMinX()+MSearch+8;
		int	dy=-a->GetMinY()+MSearch;
		int	dx2=a->GetMinX();
		int	dy2=a->GetMinY();
		a->MakeBitData(TmpBuff,dx,dy,aXLen,aYLen);
		FatAreaN(TmpBuff,TmpBuff2,aXByte, aYLen ,MSearch );
		
		for(int y=0;y<aYLen;y++){
			if(y-dy<0)
				continue;
			if(y-dy>=GetMaxLines(Page))
				break;
			BYTE	*YPoint	=TmpBuff[y];
			BYTE	*YSrc	=TmpData[y-dy];
			int	sx=-dx;
			if(sx+aXLen>GetDotPerLine(Page))
				aXLen=GetDotPerLine(Page)-sx;
			for(int x=0;x<aXLen;x++,sx++){
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

		if(EnableOverlap==false){
			int	iGetDotPerLine=GetDotPerLine(Page);
			for(int y=0;y<aYLen;y++){
				if(y-dy<0)
					continue;
				if(y-dy>=GetMaxLines(Page))
					break;
				BYTE	*Src=(BYTE *)OcupyMap[y-dy];
				BYTE	*Dst=(BYTE *)TmpBuff[y];
				for(int x=0;x<aXLen;x++){
					int	X=x-dx;
					if(0<=X && X<iGetDotPerLine){
						if(GetBmpBitOnY(Src,X)!=0){
							SetBmpBitOnY0(Dst,x);
						}
					}
				}
			}
		}

		PureFlexAreaListContainer aFPack;
		PickupFlexArea(TmpBuff ,aXByte ,aXByte*8,aYLen ,aFPack);
		int	aMaxD=0;
		PureFlexAreaList *MaxTa;
		for(PureFlexAreaList *ta=aFPack.GetFirst();ta!=NULL;ta=ta->GetNext()){
			if(aMaxD<ta->GetPatternByte()){
				aMaxD=ta->GetPatternByte();
				MaxTa=ta;
			}
		}
		*a=*MaxTa;
		a->MoveToNoClip(-dx,-dy);

		//a->BuildFromRaster(TmpBuff,aXByte,aYLen ,-dx ,-dy);
	
		DeleteMatrixBuff(TmpBuff,aYLen);
		DeleteMatrixBuff(TmpBuff2,aYLen);
	}		
	DeleteMatrixBuff(TmpData,YLen);
	GetLayersBase()->StepProcessing(-1);

	int	LayerNumb=GetLayerNumb(Page);
	if(EvenWidth255<255 || EvenWidth0<255){
		PureFlexAreaListContainer	E3List;

		for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
			if(LayerNumb>=3){
				double	AvrR=a->GetAverage(0 ,0,*IBuff[0],1.0,1.0);
				double	AvrG=a->GetAverage(0 ,0,*IBuff[1],1.0,1.0);
				double	AvrB=a->GetAverage(0 ,0,*IBuff[2],1.0,1.0);
				PureFlexAreaList *t=MakeEvenArea(*a,IBuff,LayerNumb,AvrR,AvrG,AvrB);
				PureFlexAreaListContainer Piece;
				t->Clusterize(Piece);
				E3List.AddMove(Piece);
				delete	t;
			}
			else if(LayerNumb==2){
				double	AvrR=a->GetAverage(0 ,0,*IBuff[0],1.0,1.0);
				double	AvrG=a->GetAverage(0 ,0,*IBuff[1],1.0,1.0);
				PureFlexAreaList *t=MakeEvenArea(*a,IBuff,LayerNumb,AvrR,AvrG,AvrG);
				PureFlexAreaListContainer Piece;
				t->Clusterize(Piece);
				E3List.AddMove(Piece);
				delete	t;
			}
			else if(LayerNumb==1){
				double	AvrR=a->GetAverage(0 ,0,*IBuff[0],1.0,1.0);
				PureFlexAreaList *t=MakeEvenArea(*a,IBuff,LayerNumb,AvrR,AvrR,AvrR);
				PureFlexAreaListContainer Piece;
				t->Clusterize(Piece);
				E3List.AddMove(Piece);
				delete	t;
			}
		}
		BindBlockInner(E3List);
		for(PureFlexAreaList *a=E3List.GetFirst();a!=NULL;a=a->GetNext()){
			a->Regulate();
			a->ClipArea(0,0,GetDotPerLine(Page),GetMaxLines(Page));
			if(a->GetPatternByte()<5)
				continue;
			DotColorMatchingItem	*v=new DotColorMatchingItem(*a);

			v->CopyThresholdFromLibrary(GetParentLevelContainer());
			v->SetLibID(GetLibID());
			int	MasterNo=GetLayersBase()->FindBufferInfo(MasterNoOriginCode);
			if(MasterNo<0)
				MasterNo=0;
			v->SetMasterNo(MasterNo);
			DotColorMatchingList.AppendList(v);
		}
	}
	else{
		BindBlockInner(L3List);
		for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
			a->Regulate();
			a->ClipArea(0,0,GetDotPerLine(Page),GetMaxLines(Page));
			if(a->GetPatternByte()<5)
				continue;
			DotColorMatchingItem	*v=new DotColorMatchingItem(*a);

			v->CopyThresholdFromLibrary(GetParentLevelContainer());
			v->SetLibID(GetLibID());
			int	MasterNo=GetLayersBase()->FindBufferInfo(MasterNoOriginCode);
			if(MasterNo<0)
				MasterNo=0;
			v->SetMasterNo(MasterNo);
			DotColorMatchingList.AppendList(v);
		}
	}
}

void	DotColorMatchingLibrary::MakeDotColorMatchingItems(BYTE **CurrentMap
															,int Page
															,int XByte ,int XLen,int YLen
															,PureFlexAreaListContainer &AreaList)
{
	GetLayersBase()->SetMaxProcessing(6);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(TmpData					,XByte,YLen
		         , (const BYTE **)CurrentMap,XByte,YLen);
	AreaList.RemoveAll();

	try{
		PureFlexAreaListContainer FPack;
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
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

		//#pragma omp parallel
		//{
		//	#pragma omp for
			for(int k=0;k<N;k++){
				PureFlexAreaList *h=PureFlexAreaPointerDim[k];
				PureFlexAreaListContainer Piece;
				if(LimitDotColorMatchingSize==0 || (h->GetWidth()<LimitDotColorMatchingSize && h->GetHeight()<LimitDotColorMatchingSize)){
					Piece.AppendList(h);
					h=NULL;
				}
				else{
					h->ChopRect(Piece ,LimitDotColorMatchingSize);
				}
				PureFlexAreaList *b;
				while((b=Piece.GetFirst())!=NULL){
					Piece.RemoveList(b);
					#pragma omp critical
					{
						AreaList.AppendList(b);
					}
				}
				if(h!=NULL){
					delete	h;
				}
			}
		//}
		delete	[]PureFlexAreaPointerDim;
	}	
	catch(...){}

	GetLayersBase()->StepProcessing(-1);

	int	MSearch=OverlappedLength;
	for(PureFlexAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext()){
				//if(a->IsInclude(424,672)==true){
				//	DbgLoopXY++;
				//}
		int	aXLen=a->GetWidth()+MSearch*2+2+16;
		int	aXByte=(aXLen+7)/8;
		int	aYLen=a->GetHeight()+MSearch*2+2;
		BYTE	**TmpBuff =MakeMatrixBuff(aXByte ,aYLen);
		BYTE	**TmpBuff2=MakeMatrixBuff(aXByte ,aYLen);
		MatrixBuffClear(TmpBuff,0,aXByte,aYLen);
		int	dx=-a->GetMinX()+MSearch+8;
		int	dy=-a->GetMinY()+MSearch;
		int	dx2=a->GetMinX();
		int	dy2=a->GetMinY();
		a->MakeBitData(TmpBuff,dx,dy,aXLen,aYLen);
		FatAreaN(TmpBuff,TmpBuff2,aXByte, aYLen ,MSearch );
		
		for(int y=0;y<aYLen;y++){
			if(y-dy<0)
				continue;
			if(y-dy>=GetMaxLines(Page))
				break;
			BYTE	*YPoint	=TmpBuff[y];
			BYTE	*YSrc	=TmpData[y-dy];
			int	sx=-dx;
			if(sx+aXLen>GetDotPerLine(Page))
				aXLen=GetDotPerLine(Page)-sx;
			for(int x=0;x<aXLen;x++,sx++){
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

		a->BuildFromRaster(TmpBuff,aXByte,aYLen ,-dx ,-dy);

		DeleteMatrixBuff(TmpBuff,aYLen);
		DeleteMatrixBuff(TmpBuff2,aYLen);
	}		

	GetLayersBase()->StepProcessing(-1);

	int	LayerNumb=GetLayerNumb(Page);

	BindBlockInner(AreaList);
	for(PureFlexAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(Page),GetMaxLines(Page));
	}
	DeleteMatrixBuff(TmpData,YLen);
}


PureFlexAreaList *DotColorMatchingLibrary::MakeEvenArea(
								 FlexArea &a,ImageBuffer *IBuff[],int LayerNumb
								,double AvrR,double AvrG,double AvrB)
{
	int	RL=floor(AvrR-(EvenWidth255*AvrR/255.0+EvenWidth0*(255-AvrR)/255.0));
	int	GL=floor(AvrG-(EvenWidth255*AvrG/255.0+EvenWidth0*(255-AvrG)/255.0));
	int	BL=floor(AvrB-(EvenWidth255*AvrB/255.0+EvenWidth0*(255-AvrB)/255.0));
	int	RH=ceil (AvrR+(EvenWidth255*AvrR/255.0+EvenWidth0*(255-AvrR)/255.0));
	int	GH=ceil (AvrG+(EvenWidth255*AvrG/255.0+EvenWidth0*(255-AvrG)/255.0));
	int	BH=ceil (AvrB+(EvenWidth255*AvrB/255.0+EvenWidth0*(255-AvrB)/255.0));

	int	N=a.GetFLineLen();
	NPListPack<FlexLineList>	LineContainer;

	for(int i=0;i<N;i++){
		int	Y	=a.GetFLineAbsY(i);
		int	X1	=a.GetFLineLeftX(i);
		int	Numb=a.GetFLineNumb(i);
		if(LayerNumb>=3){
			BYTE	*sR=IBuff[0]->GetY(Y);
			BYTE	*sG=IBuff[1]->GetY(Y);
			BYTE	*sB=IBuff[2]->GetY(Y);
			int		DestX=-1;
			int		DestN=0;
			for(int n=0;n<Numb;n++){
				BYTE	dR=sR[X1+n];
				BYTE	dG=sG[X1+n];
				BYTE	dB=sB[X1+n];
				if(RL<=dR && dR<=RH
				&& GL<=dG && dG<=GH
				&& BL<=dB && dB<=BH){
					if(DestN==0){
						DestX=X1+n;
						DestN=1;
					}
					else{
						DestN++;
					}
				}
				else{
					if(DestN>0){
						FlexLineList	*L=new FlexLineList();
						L->x1=DestX;
						L->x2=DestX+DestN;
						L->y =Y;
						LineContainer.AppendList(L);
					}
					DestN=0;
				}
			}
			if(DestN>0){
				FlexLineList	*L=new FlexLineList();
				L->x1=DestX;
				L->x2=DestX+DestN;
				L->y =Y;
				LineContainer.AppendList(L);
			}
		}
		else if(LayerNumb==2){
			BYTE	*sR=IBuff[0]->GetY(Y);
			BYTE	*sG=IBuff[1]->GetY(Y);
			int		DestX=-1;
			int		DestN=0;
			for(int n=0;n<Numb;n++){
				BYTE	dR=sR[X1+n];
				BYTE	dG=sG[X1+n];
				if(RL<=dR && dR<=RH
				&& GL<=dG && dG<=GH){
					if(DestN==0){
						DestX=X1+n;
						DestN=1;
					}
					else{
						DestN++;
					}
				}
				else{
					if(DestN>0){
						FlexLineList	*L=new FlexLineList();
						L->x1=DestX;
						L->x2=DestX+DestN;
						L->y =Y;
						LineContainer.AppendList(L);
					}
					DestN=0;
				}
			}
			if(DestN>0){
				FlexLineList	*L=new FlexLineList();
				L->x1=DestX;
				L->x2=DestX+DestN;
				L->y =Y;
				LineContainer.AppendList(L);
			}
		}
		else if(LayerNumb==1){
			BYTE	*sR=IBuff[0]->GetY(Y);
			int		DestX=-1;
			int		DestN=0;
			for(int n=0;n<Numb;n++){
				BYTE	dR=sR[X1+n];
				if(RL<=dR && dR<=RH){
					if(DestN==0){
						DestX=X1+n;
						DestN=1;
					}
					else{
						DestN++;
					}
				}
				else{
					if(DestN>0){
						FlexLineList	*L=new FlexLineList();
						L->x1=DestX;
						L->x2=DestX+DestN;
						L->y =Y;
						LineContainer.AppendList(L);
					}
					DestN=0;
				}
			}
			if(DestN>0){
				FlexLineList	*L=new FlexLineList();
				L->x1=DestX;
				L->x2=DestX+DestN;
				L->y =Y;
				LineContainer.AppendList(L);
			}
		}
	}
	struct  FlexLine    *FL=new struct FlexLine[LineContainer.GetCount()];
	int	Row=0;
	for(FlexLineList *L=LineContainer.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		FL[Row]._SetAbsY(L->y);
		FL[Row]._SetLeftX(L->x1);
		FL[Row].SetNumb(L->x2-L->x1);
	}
	PureFlexAreaList	*Ret=new PureFlexAreaList();
	Ret->SetFLine(FL,Row);
	Ret->ThinAreaN(2);
	Ret->FatAreaN(4);
	if(SpaceToOutline>0){
		Ret->ThinAreaN(2+SpaceToOutline);
	}
	else{
		Ret->ThinAreaN(2);
	}
	return Ret;
}

void	DotColorMatchingLibrary::BindBlockInner(
				 PureFlexAreaListContainer &TmpDotColorMatchingData)
{
	for(PureFlexAreaList *f=TmpDotColorMatchingData.GetFirst();f!=NULL;f=f->GetNext()){
		int	sx1,sy1,sx2,sy2;
		f->GetXY(sx1,sy1,sx2,sy2);
		for(PureFlexAreaList *g=f->GetNext();g!=NULL;){
			int	dx1,dy1,dx2,dy2;
			g->GetXY(dx1,dy1,dx2,dy2);
			int	Lx1=min(sx1,dx1);
			int	Ly1=min(sy1,dy1);
			int	Lx2=max(sx2,dx2);
			int	Ly2=max(sy2,dy2);
			if((Lx2-Lx1)<=BindGroupArea
			&& (Ly2-Ly1)<=BindGroupArea){
				PureFlexAreaList *NextG=g->GetNext();
				TmpDotColorMatchingData.RemoveList(g);
				*f+=*g;
				f->GetXY(sx1,sy1,sx2,sy2);
				g=NextG;
			}
			else{
				g=g->GetNext();
			}
		}
	}
	for(PureFlexAreaList *f=TmpDotColorMatchingData.GetFirst();f!=NULL;){
		PureFlexAreaList *NextF=f->GetNext();
		int	sx1,sy1,sx2,sy2;
		f->GetXY(sx1,sy1,sx2,sy2);
		for(PureFlexAreaList *g=TmpDotColorMatchingData.GetFirst();g!=NULL;g=g->GetNext()){
			if(f!=g){
				int	dx1,dy1,dx2,dy2;
				g->GetXY(dx1,dy1,dx2,dy2);
				if(dx1<=sx1 && sx2<=dx2
				&& dy1<=sy1 && sy2<=dy2){
					if(g->IsInclude(f)==true){
						TmpDotColorMatchingData.RemoveList(f);
						delete	f;
						break;
					}
				}
			}
		}
		f=NextF;
	}
}

//==============================================================================

DotColorMatchingLibraryContainer::DotColorMatchingLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
DotColorMatchingLibraryContainer::~DotColorMatchingLibraryContainer(void)
{
}


