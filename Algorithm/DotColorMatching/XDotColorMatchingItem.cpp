#include "DotColorMatchingResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DotColorMatchingInspection\XDotColorMatching.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XDotColorMatchingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "XPropertyDotColorMatchingPacket.h"
#include "XDotColorMatchingAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "swap.h"
#include "XLearningRegist.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

static	int	DbgID=3770;
static	int	DbgNumer=0;


DotColorMatchingThreshold::MThreshold::MThreshold(void)
{
	OrgBrightWidthRL	=0;
	OrgBrightWidthRH	=0;
	OrgBrightWidthGL	=0;
	OrgBrightWidthGH	=0;
	OrgBrightWidthBL	=0;
	OrgBrightWidthBH	=0;
	OrgOKDot			=0;
	OrgOKLength			=99999999;

	BrightWidthRL		=0;
	BrightWidthRH		=0;
	BrightWidthGL		=0;
	BrightWidthGH		=0;
	BrightWidthBL		=0;
	BrightWidthBH		=0;

	OKDot					=0;
	OKLength				=99999999;

	RThrOffsetL		=0;
	RThrOffsetH		=0;
	GThrOffsetL		=0;
	GThrOffsetH		=0;
	BThrOffsetL		=0;
	BThrOffsetH		=0;
}

void	DotColorMatchingThreshold::MThreshold::CopyFrom(const DotColorMatchingThreshold::MThreshold &src)
{
	OrgBrightWidthRL	=src.OrgBrightWidthRL;
	OrgBrightWidthRH	=src.OrgBrightWidthRH;
	OrgBrightWidthGL	=src.OrgBrightWidthGL;
	OrgBrightWidthGH	=src.OrgBrightWidthGH;
	OrgBrightWidthBL	=src.OrgBrightWidthBL;
	OrgBrightWidthBH	=src.OrgBrightWidthBH;
	OrgOKDot			=src.OrgOKDot;
	OrgOKLength			=src.OrgOKLength;

	BrightWidthRL		=src.BrightWidthRL;
	BrightWidthRH		=src.BrightWidthRH;
	BrightWidthGL		=src.BrightWidthGL;
	BrightWidthGH		=src.BrightWidthGH;
	BrightWidthBL		=src.BrightWidthBL;
	BrightWidthBH		=src.BrightWidthBH;

	OKDot				=src.OKDot;
	OKLength			=src.OKLength;

	RThrOffsetL			=src.RThrOffsetL;
	RThrOffsetH			=src.RThrOffsetH;
	GThrOffsetL			=src.GThrOffsetL;
	GThrOffsetH			=src.GThrOffsetH;
	BThrOffsetL			=src.BThrOffsetL;
	BThrOffsetH			=src.BThrOffsetH;
}

bool	DotColorMatchingThreshold::MThreshold::Save(QIODevice *file)
{
	WORD	Ver=DotColorMatchingInspectionVersion;

	if(::Save(file,Ver)==false)
		return false;

	if(::Save(file,OrgBrightWidthRL)==false)
		return false;
	if(::Save(file,OrgBrightWidthRH)==false)
		return false;
	if(::Save(file,OrgBrightWidthGL)==false)
		return false;
	if(::Save(file,OrgBrightWidthGH)==false)
		return false;
	if(::Save(file,OrgBrightWidthBL)==false)
		return false;
	if(::Save(file,OrgBrightWidthBH)==false)
		return false;
	if(::Save(file,OrgOKDot)==false)
		return false;
	if(::Save(file,OrgOKLength)==false)
		return false;

	if(::Save(file,BrightWidthRL)==false)
		return false;
	if(::Save(file,BrightWidthRH)==false)
		return false;
	if(::Save(file,BrightWidthGL)==false)
		return false;
	if(::Save(file,BrightWidthGH)==false)
		return false;
	if(::Save(file,BrightWidthBL)==false)
		return false;
	if(::Save(file,BrightWidthBH)==false)
		return false;

	if(::Save(file,OKDot)==false)
		return false;
	if(::Save(file,OKLength)==false)
		return false;

	if(::Save(file,RThrOffsetL)==false)
		return false;
    if(::Save(file,RThrOffsetH)==false)
		return false;
    if(::Save(file,GThrOffsetL)==false)
		return false;
    if(::Save(file,GThrOffsetH)==false)
		return false;
    if(::Save(file,BThrOffsetL)==false)
		return false;
    if(::Save(file,BThrOffsetH)==false)
		return false;

	return true;
}
bool	DotColorMatchingThreshold::MThreshold::Load(QIODevice *file)
{
	WORD	Ver;

	if(::Load(file,Ver)==false)
		return false;

	if(::Load(file,OrgBrightWidthRL)==false)
		return false;
	if(::Load(file,OrgBrightWidthRH)==false)
		return false;
	if(::Load(file,OrgBrightWidthGL)==false)
		return false;
	if(::Load(file,OrgBrightWidthGH)==false)
		return false;
	if(::Load(file,OrgBrightWidthBL)==false)
		return false;
	if(::Load(file,OrgBrightWidthBH)==false)
		return false;
	if(::Load(file,OrgOKDot)==false)
		return false;
	if(::Load(file,OrgOKLength)==false)
		return false;

	if(::Load(file,BrightWidthRL)==false)
		return false;
	if(::Load(file,BrightWidthRH)==false)
		return false;
	if(::Load(file,BrightWidthGL)==false)
		return false;
	if(::Load(file,BrightWidthGH)==false)
		return false;
	if(::Load(file,BrightWidthBL)==false)
		return false;
	if(::Load(file,BrightWidthBH)==false)
		return false;

	if(::Load(file,OKDot)==false)
		return false;
	if(::Load(file,OKLength)==false)
		return false;

	if(::Load(file,RThrOffsetL)==false)
		return false;
    if(::Load(file,RThrOffsetH)==false)
		return false;
    if(::Load(file,GThrOffsetL)==false)
		return false;
    if(::Load(file,GThrOffsetH)==false)
		return false;
    if(::Load(file,BThrOffsetL)==false)
		return false;
    if(::Load(file,BThrOffsetH)==false)
		return false;

	return true;
}

void	DotColorMatchingThreshold::MThreshold::FromLibrary(DotColorMatchingLibrary::MLibThreshold *LSrc)
{
	OrgBrightWidthRL	=LSrc->BrightWidthRL;
	OrgBrightWidthRH	=LSrc->BrightWidthRH;
	OrgBrightWidthGL	=LSrc->BrightWidthGL;
	OrgBrightWidthGH	=LSrc->BrightWidthGH;
	OrgBrightWidthBL	=LSrc->BrightWidthBL;
	OrgBrightWidthBH	=LSrc->BrightWidthBH;
	OrgOKDot			=LSrc->OKDot;
	OrgOKLength			=LSrc->OKLength;

	BrightWidthRL	=LSrc->BrightWidthRL;
	BrightWidthRH	=LSrc->BrightWidthRH;
	BrightWidthGL	=LSrc->BrightWidthGL;
	BrightWidthGH	=LSrc->BrightWidthGH;
	BrightWidthBL	=LSrc->BrightWidthBL;
	BrightWidthBH	=LSrc->BrightWidthBH;

	OKDot			=LSrc->OKDot;
	OKLength		=LSrc->OKLength;

	RThrOffsetL			=LSrc->RThrOffsetL;
	RThrOffsetH			=LSrc->RThrOffsetH;
	GThrOffsetL			=LSrc->GThrOffsetL;
	GThrOffsetH			=LSrc->GThrOffsetH;
	BThrOffsetL			=LSrc->BThrOffsetL;
	BThrOffsetH			=LSrc->BThrOffsetH;
}
void	DotColorMatchingThreshold::MThreshold::ToLibrary  (DotColorMatchingLibrary::MLibThreshold *LDst)
{
	LDst->BrightWidthRL	=BrightWidthRL;
	LDst->BrightWidthRH	=BrightWidthRH;
	LDst->BrightWidthGL	=BrightWidthGL;
	LDst->BrightWidthGH	=BrightWidthGH;
	LDst->BrightWidthBL	=BrightWidthBL;
	LDst->BrightWidthBH	=BrightWidthBH;

	LDst->OKDot			=OKDot			;
	LDst->OKLength		=OKLength		;

	LDst->RThrOffsetL		=RThrOffsetL	;
	LDst->RThrOffsetH		=RThrOffsetH	;
	LDst->GThrOffsetL		=GThrOffsetL	;
	LDst->GThrOffsetH		=GThrOffsetH	;
	LDst->BThrOffsetL		=BThrOffsetL	;
	LDst->BThrOffsetH		=BThrOffsetH	;
}

void	DotColorMatchingThreshold::MThreshold::SetToOrigin(void)
{
	OrgBrightWidthRL		=BrightWidthRL;
	OrgBrightWidthRH		=BrightWidthRH;
	OrgBrightWidthGL		=BrightWidthGL;
	OrgBrightWidthGH		=BrightWidthGH;
	OrgBrightWidthBL		=BrightWidthBL;
	OrgBrightWidthBH		=BrightWidthBH;
	OrgOKDot				=OKDot;
	OrgOKLength				=OKLength;
}

//=====================================================================================
DotColorMatchingThreshold::DotColorMatchingThreshold(DotColorMatchingItem *parent)
:AlgorithmThreshold(parent)
{
	OrgMultiSpotDot		=0;
	OrgMultiSpotCount	=0;

	VarietySigma			=3.0;

	MultiSpotDot			=0;
	MultiSpotCount			=0;
	MultiSpotDotGathered	=0;	//密集多点
	MultiSpotCountGathered	=0;
	MultiSpotLengthGathered	=99999999;
	BackGroundOKDot			=0;
	BackGroundOKLength		=99999999;
	UseBackGround			=false;

    AdjustBlack		=20;    //輝度補正の下限幅
    AdjustWhite		=20;    //輝度補正の上限幅
	AdjustContribute=10;	//補正の寄与度
	AreaSearchX		=20;
	AreaSearchY		=20;
    SelfSearch		=4;     //自己探索ドット数
	PreciseSearch	=false;
	Clusterize		=false;
	SmoothCluster	=false;
	EnableT2M		=true;
	EnableM2T		=true;
	UseMaster2		=false;
	ExpandToSubBlock=20;
	MaxAreaSearch	=99;		//最大領域探索ドット数
    MaxSelfSearch	=99;		//最大自己探索ドット数

	MasterNo		=0;

	ScratchStartDirection	=0.0;
	ScratchRotationAngle	=0.0;
	ScratchDiff				=5;
	ScratchVariety			=1.0;
	ScratchDetectLevelL		=5;
	ScratchDetectLevelH		=5;
	ScratchMaxWidth			=15;
	ScratchEnable			=false;
	ScratchUseMaster		=true;
	ScratchVOffset			=0;

	AddedBrightness		=0;
	AddedOffset			=0;
	AddedShift			=0;

	UseOneLayer			=0xFF;

	RedCheckMode		=false;
	RedHighRate			=150;
	RedMinBrightness	=70;
	RedGBMerginRate		=20;
	RedGBMerginOffset	=15;
	RedOKDot			=100;
	RedShrink			=0;

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

	MatchBrightnessByLayerH	=0xFF;
	MatchBrightnessByLayerL	=0xFF;
	//Set("NBrightWidthL"	,&NBrightWidthL,1,255,4);
	//Set("NBrightWidthH"	,&NBrightWidthH,1,255,4);
	//Set("BBrightWidthL"	,&BBrightWidthL,1,255,4);
	//Set("BBrightWidthH"	,&BBrightWidthH,1,255,4);
	//Set("NOKDotL"		,&NOKDotL	,1,1000,10);
	//Set("NOKDotH"		,&NOKDotH	,1,1000,10);
	//Set("BOKDotL"		,&BOKDotL	,1,1000,10);
	//Set("BOKDotH"		,&BOKDotH	,1,1000,10);
	//Set("NOKLengthL"	,&NOKLengthL,1,1000,5);
	//Set("NOKLengthH"	,&NOKLengthH,1,1000,5);
	//Set("BOKLengthL"	,&BOKLengthL,1,1000,5);
	//Set("BOKLengthH"	,&BOKLengthH,1,1000,5);

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

	SetModifierMember(ID_BroadOKDot		,&Broad.OKDot);
	SetModifierMember(ID_BroadOKLength	,&Broad.OKLength);
	SetModifierMember(ID_NarrowOKDot	,&Narrow.OKDot);
	SetModifierMember(ID_NarrowOKLength	,&Narrow.OKLength);

	SetModifierMember(ID_BroadBrightWidthRL	,&Broad.BrightWidthRL);
	SetModifierMember(ID_BroadBrightWidthRH	,&Broad.BrightWidthRH);
	SetModifierMember(ID_BroadBrightWidthGL	,&Broad.BrightWidthGL);
	SetModifierMember(ID_BroadBrightWidthGH	,&Broad.BrightWidthGH);
	SetModifierMember(ID_BroadBrightWidthBL	,&Broad.BrightWidthBL);
	SetModifierMember(ID_BroadBrightWidthBH	,&Broad.BrightWidthBH);

	SetModifierMember(ID_BroadRThrOffsetL	,&Broad.RThrOffsetL);
	SetModifierMember(ID_BroadRThrOffsetH	,&Broad.RThrOffsetH);
	SetModifierMember(ID_BroadGThrOffsetL	,&Broad.GThrOffsetL);
	SetModifierMember(ID_BroadGThrOffsetH	,&Broad.GThrOffsetH);
	SetModifierMember(ID_BroadBThrOffsetL	,&Broad.BThrOffsetL);
	SetModifierMember(ID_BroadBThrOffsetH	,&Broad.BThrOffsetH);

	SetModifierMember(ID_NarrowBrightWidthRL,&Narrow.BrightWidthRL);
	SetModifierMember(ID_NarrowBrightWidthRH,&Narrow.BrightWidthRH);
	SetModifierMember(ID_NarrowBrightWidthGL,&Narrow.BrightWidthGL);
	SetModifierMember(ID_NarrowBrightWidthGH,&Narrow.BrightWidthGH);
	SetModifierMember(ID_NarrowBrightWidthBL,&Narrow.BrightWidthBL);
	SetModifierMember(ID_NarrowBrightWidthBH,&Narrow.BrightWidthBH);

	SetModifierMember(ID_NarrowRThrOffsetL	,&Narrow.RThrOffsetL);
	SetModifierMember(ID_NarrowRThrOffsetH	,&Narrow.RThrOffsetH);
	SetModifierMember(ID_NarrowGThrOffsetL	,&Narrow.GThrOffsetL);
	SetModifierMember(ID_NarrowGThrOffsetH	,&Narrow.GThrOffsetH);
	SetModifierMember(ID_NarrowBThrOffsetL	,&Narrow.BThrOffsetL);
	SetModifierMember(ID_NarrowBThrOffsetH	,&Narrow.BThrOffsetH);
}

void	DotColorMatchingThreshold::RegistHist(void)
{
	static	bool	InitialStr	=false;

	static	QString	StrCenterBrightR	;
	static	QString	StrCenterBrightG	;
	static	QString	StrCenterBrightB	;
	static	QString	StrNGSize			;
	static	QString	StrNGLength			;
	static	QString	StrSearchArea		;


	if(InitialStr==false){
		StrCenterBrightR	="Center Bright R";
		StrCenterBrightG	="Center Bright G";
		StrCenterBrightB	="Center Bright B";
		StrNGSize				="NG size";
		StrNGLength				="NG length";
		StrSearchArea			="Search area";

		InitialStr=true;
	}

	RegistShort	(StrCenterBrightR	,Hist_DotColorMatching_CenterBrightR);
	RegistShort	(StrCenterBrightG	,Hist_DotColorMatching_CenterBrightG);
	RegistShort	(StrCenterBrightB	,Hist_DotColorMatching_CenterBrightB);
	RegistInt	(StrNGSize			,Hist_DotColorMatching_NGSize		);
	RegistInt	(StrNGLength		,Hist_DotColorMatching_NGLength		);
	RegistInt	(StrSearchArea		,Hist_DotColorMatching_SearchArea	);
}

void	DotColorMatchingThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const DotColorMatchingThreshold *s=(const DotColorMatchingThreshold *)&src;

	Broad.CopyFrom(s->Broad);
	Narrow.CopyFrom(s->Narrow);

	OrgMultiSpotDot			=s->OrgMultiSpotDot	;
	OrgMultiSpotCount		=s->OrgMultiSpotCount;
	OrgBackGroundOKDot		=s->OrgBackGroundOKDot;
	OrgBackGroundOKLength	=s->OrgBackGroundOKLength;
	OrgUseBackGround		=s->OrgUseBackGround;

	VarietySigma		=s->VarietySigma;
	MultiSpotDot		=s->MultiSpotDot	;
	MultiSpotCount		=s->MultiSpotCount;
	MultiSpotDotGathered	=s->MultiSpotDotGathered	;	//密集多点
	MultiSpotCountGathered	=s->MultiSpotCountGathered	;
	MultiSpotLengthGathered	=s->MultiSpotLengthGathered	;

	BackGroundOKDot		=s->BackGroundOKDot;
	BackGroundOKLength	=s->BackGroundOKLength;
	UseBackGround		=s->UseBackGround;

	SmoothCluster		=s->SmoothCluster;
	EnableT2M			=s->EnableT2M;
	EnableM2T			=s->EnableM2T;
	UseMaster2			=s->UseMaster2;
	ExpandToSubBlock	=s->ExpandToSubBlock;
	MasterNo			=s->MasterNo;

	AdjustBlack			=s->AdjustBlack;
    AdjustWhite			=s->AdjustWhite;
	AdjustContribute	=s->AdjustContribute;
	AreaSearchX			=s->AreaSearchX;
	AreaSearchY			=s->AreaSearchY;
    SelfSearch			=s->SelfSearch;
	PreciseSearch		=s->PreciseSearch;
	Clusterize			=s->Clusterize;
	MaxAreaSearch		=s->MaxAreaSearch;
    MaxSelfSearch		=s->MaxSelfSearch;

	ScratchStartDirection	=s->ScratchStartDirection	;
	ScratchRotationAngle	=s->ScratchRotationAngle	;
	ScratchDiff				=s->ScratchDiff			;
	ScratchVariety			=s->ScratchVariety		;
	ScratchDetectLevelL		=s->ScratchDetectLevelL	;
	ScratchDetectLevelH		=s->ScratchDetectLevelH	;
	ScratchMaxWidth			=s->ScratchMaxWidth		;
	ScratchEnable			=s->ScratchEnable		;
	ScratchUseMaster		=s->ScratchUseMaster	;
	ScratchVOffset			=s->ScratchVOffset	;

	AddedBrightness			=s->AddedBrightness	;
	AddedOffset				=s->AddedOffset		;
	AddedShift				=s->AddedShift		;

	UseOneLayer				=s->UseOneLayer		;

	RedCheckMode			=s->RedCheckMode		;
	RedHighRate				=s->RedHighRate		;
	RedMinBrightness		=s->RedMinBrightness	;
	RedGBMerginRate			=s->RedGBMerginRate	;
	RedGBMerginOffset		=s->RedGBMerginOffset	;
	RedOKDot				=s->RedOKDot			;
	RedShrink				=s->RedShrink			;

	HsvCheckMode		=s->HsvCheckMode		;
	HsvFixedColorMode	=s->HsvFixedColorMode	;
	HsvH				=s->HsvH				;
	HsvS				=s->HsvS				;
	HsvV				=s->HsvV				;
	HsvPHL				=s->HsvPHL				;
	HsvPHH				=s->HsvPHH				;
	HsvPSL				=s->HsvPSL				;
	HsvPSH				=s->HsvPSH				;
	HsvPVL				=s->HsvPVL				;
	HsvPVH				=s->HsvPVH				;
	HsvDHL				=s->HsvDHL				;
	HsvDHH				=s->HsvDHH				;
	HsvDSL				=s->HsvDSL				;
	HsvDSH				=s->HsvDSH				;
	HsvDVL				=s->HsvDVL				;
	HsvDVH				=s->HsvDVH				;
	HsvOKDot			=s->HsvOKDot			;
	HsvOKLength			=s->HsvOKLength			;

	MatchBrightnessByLayerH	=s->MatchBrightnessByLayerH;
	MatchBrightnessByLayerL	=s->MatchBrightnessByLayerL;
	SubtractLibID		=s->SubtractLibID		;

	VariationMode	=s->VariationMode	;
	VariationRL		=s->VariationRL		;
	VariationRH		=s->VariationRH		;
	VariationGL		=s->VariationGL		;
	VariationGH		=s->VariationGH		;
	VariationBL		=s->VariationBL		;
	VariationBH		=s->VariationBH		;
	VariationAdaptMinSize	=s->VariationAdaptMinSize;
	VariationMultiplyMaster	=s->VariationMultiplyMaster;
	VariationDifMaster		=s->VariationDifMaster;
	VariationAndLogic		=s->VariationAndLogic;
	VariationSubMasterVari	=s->VariationSubMasterVari;

	PitMode				=s->PitMode			;
	PitBrightWidthRL	=s->PitBrightWidthRL;
	PitBrightWidthRH	=s->PitBrightWidthRH;
	PitBrightWidthGL	=s->PitBrightWidthGL;
	PitBrightWidthGH	=s->PitBrightWidthGH;
	PitBrightWidthBL	=s->PitBrightWidthBL;
	PitBrightWidthBH	=s->PitBrightWidthBH;

	LineMode				=s->LineMode				;
	LineOKMinLength			=s->LineOKMinLength			;
	LineMaxWidth			=s->LineMaxWidth			;
	LineMinDensityPercent	=s->LineMinDensityPercent	;
	LineMinCluster			=s->LineMinCluster			;
}

void	DotColorMatchingThreshold::CopyFrom(const AlgorithmThreshold &src,IntList &EdittedMemberID)
{
	const DotColorMatchingThreshold *s=(const DotColorMatchingThreshold *)&src;

	if(EdittedMemberID.IsInclude(ID_BroadBrightWidthRL)==true)
		Broad.BrightWidthRL	=s->Broad.BrightWidthRL;
	if(EdittedMemberID.IsInclude(ID_BroadBrightWidthRH)==true)
		Broad.BrightWidthRH	=s->Broad.BrightWidthRH;
	if(EdittedMemberID.IsInclude(ID_BroadBrightWidthGL)==true)
		Broad.BrightWidthGL	=s->Broad.BrightWidthGL;
	if(EdittedMemberID.IsInclude(ID_BroadBrightWidthGH)==true)
		Broad.BrightWidthGH	=s->Broad.BrightWidthGH;
	if(EdittedMemberID.IsInclude(ID_BroadBrightWidthBL)==true)
		Broad.BrightWidthBL	=s->Broad.BrightWidthBL;
	if(EdittedMemberID.IsInclude(ID_BroadBrightWidthBH)==true)
		Broad.BrightWidthBH	=s->Broad.BrightWidthBH;

	if(EdittedMemberID.IsInclude(ID_BroadOKDot			)==true)
		Broad.OKDot			=s->Broad.OKDot;
	if(EdittedMemberID.IsInclude(ID_BroadOKLength		)==true)
		Broad.OKLength		=s->Broad.OKLength;

	if(EdittedMemberID.IsInclude(ID_BroadRThrOffsetL		)==true)
		Broad.RThrOffsetL		=s->Broad.RThrOffsetL;
	if(EdittedMemberID.IsInclude(ID_BroadRThrOffsetH)==true)
		Broad.RThrOffsetH		=s->Broad.RThrOffsetH;
	if(EdittedMemberID.IsInclude(ID_BroadGThrOffsetL)==true)
		Broad.GThrOffsetL		=s->Broad.GThrOffsetL;
	if(EdittedMemberID.IsInclude(ID_BroadGThrOffsetH)==true)
		Broad.GThrOffsetH		=s->Broad.GThrOffsetH;
	if(EdittedMemberID.IsInclude(ID_BroadBThrOffsetL)==true)
		Broad.BThrOffsetL		=s->Broad.BThrOffsetL;
	if(EdittedMemberID.IsInclude(ID_BroadBThrOffsetH)==true)
		Broad.BThrOffsetH		=s->Broad.BThrOffsetH;

	if(EdittedMemberID.IsInclude(ID_NarrowBrightWidthRL)==true)
		Narrow.BrightWidthRL	=s->Narrow.BrightWidthRL;
	if(EdittedMemberID.IsInclude(ID_NarrowBrightWidthRH)==true)
		Narrow.BrightWidthRH	=s->Narrow.BrightWidthRH;
	if(EdittedMemberID.IsInclude(ID_NarrowBrightWidthGL)==true)
		Narrow.BrightWidthGL	=s->Narrow.BrightWidthGL;
	if(EdittedMemberID.IsInclude(ID_NarrowBrightWidthGH)==true)
		Narrow.BrightWidthGH	=s->Narrow.BrightWidthGH;
	if(EdittedMemberID.IsInclude(ID_NarrowBrightWidthBL)==true)
		Narrow.BrightWidthBL	=s->Narrow.BrightWidthBL;
	if(EdittedMemberID.IsInclude(ID_NarrowBrightWidthBH)==true)
		Narrow.BrightWidthBH	=s->Narrow.BrightWidthBH;

	if(EdittedMemberID.IsInclude(ID_NarrowOKDot			)==true)
		Narrow.OKDot			=s->Narrow.OKDot;
	if(EdittedMemberID.IsInclude(ID_NarrowOKLength		)==true)
		Narrow.OKLength			=s->Narrow.OKLength;

	if(EdittedMemberID.IsInclude(ID_NarrowRThrOffsetL		)==true)
		Narrow.RThrOffsetL		=s->Narrow.RThrOffsetL;
	if(EdittedMemberID.IsInclude(ID_NarrowRThrOffsetH)==true)
		Narrow.RThrOffsetH		=s->Narrow.RThrOffsetH;
	if(EdittedMemberID.IsInclude(ID_NarrowGThrOffsetL)==true)
		Narrow.GThrOffsetL		=s->Narrow.GThrOffsetL;
	if(EdittedMemberID.IsInclude(ID_NarrowGThrOffsetH)==true)
		Narrow.GThrOffsetH		=s->Narrow.GThrOffsetH;
	if(EdittedMemberID.IsInclude(ID_NarrowBThrOffsetL)==true)
		Narrow.BThrOffsetL		=s->Narrow.BThrOffsetL;
	if(EdittedMemberID.IsInclude(ID_NarrowBThrOffsetH)==true)
		Narrow.BThrOffsetH		=s->Narrow.BThrOffsetH;

	if(EdittedMemberID.IsInclude(ID_VarietySigma)==true)
		VarietySigma	=s->VarietySigma;
	if(EdittedMemberID.IsInclude(ID_MultiSpotDot	)==true)
		MultiSpotDot	=s->MultiSpotDot	;
	if(EdittedMemberID.IsInclude(ID_MultiSpotCount	)==true)
		MultiSpotCount	=s->MultiSpotCount;
	if(EdittedMemberID.IsInclude(ID_MultiSpotDotGathered		)==true)
		MultiSpotDotGathered	=s->MultiSpotDotGathered	;	//密集多点
	if(EdittedMemberID.IsInclude(ID_MultiSpotCountGathered		)==true)
		MultiSpotCountGathered	=s->MultiSpotCountGathered	;
	if(EdittedMemberID.IsInclude(ID_MultiSpotLengthGathered		)==true)
		MultiSpotLengthGathered	=s->MultiSpotLengthGathered	;

	if(EdittedMemberID.IsInclude(ID_BackGroundOKDot		)==true)
		BackGroundOKDot		=s->BackGroundOKDot;
	if(EdittedMemberID.IsInclude(ID_BackGroundOKLength	)==true)
		BackGroundOKLength	=s->BackGroundOKLength;
	if(EdittedMemberID.IsInclude(ID_UseBackGround	)==true)
		UseBackGround	=s->UseBackGround;

	if(EdittedMemberID.IsInclude(ID_SmoothCluster)==true)
		SmoothCluster	=s->SmoothCluster;
	if(EdittedMemberID.IsInclude(ID_EnableT2M)==true)
		EnableT2M		=s->EnableT2M;
	if(EdittedMemberID.IsInclude(ID_EnableM2T)==true)
		EnableM2T		=s->EnableM2T;
	if(EdittedMemberID.IsInclude(ID_UseMaster2)==true)
		UseMaster2		=s->UseMaster2;
	if(EdittedMemberID.IsInclude(ID_ExpandToSubBlock)==true)
		ExpandToSubBlock=s->ExpandToSubBlock;
	if(EdittedMemberID.IsInclude(ID_MasterNo)==true)
		MasterNo		=s->MasterNo;

	if(EdittedMemberID.IsInclude(ID_AdjustBlack		)==true)
		AdjustBlack		=s->AdjustBlack;
 	if(EdittedMemberID.IsInclude(ID_AdjustWhite		)==true)
		AdjustWhite		=s->AdjustWhite;
	if(EdittedMemberID.IsInclude(ID_AdjustContribute)==true)
		AdjustContribute=s->AdjustContribute;
	if(EdittedMemberID.IsInclude(ID_AreaSearchX)==true)
		AreaSearchX		=s->AreaSearchX;
	if(EdittedMemberID.IsInclude(ID_AreaSearchY)==true)
		AreaSearchY		=s->AreaSearchY;
 	if(EdittedMemberID.IsInclude(ID_SelfSearch		)==true)
		SelfSearch		=s->SelfSearch;
	if(EdittedMemberID.IsInclude(ID_PreciseSearch		)==true)
		PreciseSearch		=s->PreciseSearch;
	if(EdittedMemberID.IsInclude(ID_Clusterize		)==true)
		Clusterize		=s->Clusterize;
	if(EdittedMemberID.IsInclude(ID_MaxAreaSearch)==true)
		MaxAreaSearch	=s->MaxAreaSearch;
 	if(EdittedMemberID.IsInclude(ID_MaxSelfSearch		)==true)
		MaxSelfSearch	=s->MaxSelfSearch;

	if(EdittedMemberID.IsInclude(ID_ScratchStartDirection	)==true)
		ScratchStartDirection	=s->ScratchStartDirection	;
	if(EdittedMemberID.IsInclude(ID_ScratchRotationAngle 	)==true)
		ScratchRotationAngle	=s->ScratchRotationAngle	;
	if(EdittedMemberID.IsInclude(ID_ScratchDiff 			)==true)
		ScratchDiff				=s->ScratchDiff	;
	if(EdittedMemberID.IsInclude(ID_ScratchVariety			)==true)
		ScratchVariety			=s->ScratchVariety		;
	if(EdittedMemberID.IsInclude(ID_ScratchDetectLevelL		)==true)
		ScratchDetectLevelL		=s->ScratchDetectLevelL	;
	if(EdittedMemberID.IsInclude(ID_ScratchDetectLevelH		)==true)
		ScratchDetectLevelH		=s->ScratchDetectLevelH	;
	if(EdittedMemberID.IsInclude(ID_ScratchMaxWidth			)==true)
		ScratchMaxWidth			=s->ScratchMaxWidth		;
	if(EdittedMemberID.IsInclude(ID_ScratchEnable			)==true)
		ScratchEnable			=s->ScratchEnable		;
	if(EdittedMemberID.IsInclude(ID_ScratchUseMaster		)==true)
		ScratchUseMaster		=s->ScratchUseMaster	;
	if(EdittedMemberID.IsInclude(ID_ScratchVOffset			)==true)
		ScratchVOffset			=s->ScratchVOffset	;

	if(EdittedMemberID.IsInclude(ID_AddedBrightness	)==true)
		AddedBrightness			=s->AddedBrightness	;
	if(EdittedMemberID.IsInclude(ID_AddedOffset		)==true)
		AddedOffset				=s->AddedOffset		;
	if(EdittedMemberID.IsInclude(ID_AddedShift		)==true)
		AddedShift				=s->AddedShift		;

	if(EdittedMemberID.IsInclude(ID_UseOneLayer)==true)
		UseOneLayer			=s->UseOneLayer		;

	if(EdittedMemberID.IsInclude(ID_RedCheckMode)==true)
		RedCheckMode		=s->RedCheckMode		;
	if(EdittedMemberID.IsInclude(ID_RedHighRate			)==true)
		RedHighRate			=s->RedHighRate		;
	if(EdittedMemberID.IsInclude(ID_RedMinBrightness)==true)
		RedMinBrightness	=s->RedMinBrightness	;
	if(EdittedMemberID.IsInclude(ID_RedGBMerginRate)==true)
		RedGBMerginRate		=s->RedGBMerginRate	;
	if(EdittedMemberID.IsInclude(ID_RedGBMerginOffset)==true)
		RedGBMerginOffset	=s->RedGBMerginOffset	;
	if(EdittedMemberID.IsInclude(ID_RedOKDot)==true)
		RedOKDot			=s->RedOKDot			;
	if(EdittedMemberID.IsInclude(ID_RedShrink)==true)
		RedShrink			=s->RedShrink			;

	if(EdittedMemberID.IsInclude(ID_MatchBrightnessByLayerH)==true)
		MatchBrightnessByLayerH	=s->MatchBrightnessByLayerH;
	if(EdittedMemberID.IsInclude(ID_MatchBrightnessByLayerL)==true)
		MatchBrightnessByLayerL	=s->MatchBrightnessByLayerL;

	if(EdittedMemberID.IsInclude(ID_HsvCheckMode)==true)
		HsvCheckMode		=s->HsvCheckMode		;
	if(EdittedMemberID.IsInclude(ID_HsvFixedColorMode)==true)
		HsvFixedColorMode	=s->HsvFixedColorMode	;
	if(EdittedMemberID.IsInclude(ID_HsvH)==true)
		HsvH				=s->HsvH				;
	if(EdittedMemberID.IsInclude(ID_HsvS)==true)
		HsvS				=s->HsvS			;
	if(EdittedMemberID.IsInclude(ID_HsvV)==true)
		HsvV				=s->HsvV			;
	if(EdittedMemberID.IsInclude(ID_HsvPHL)==true)
		HsvPHL				=s->HsvPHL			;
	if(EdittedMemberID.IsInclude(ID_HsvPHH)==true)
		HsvPHH				=s->HsvPHH			;
	if(EdittedMemberID.IsInclude(ID_HsvPSL)==true)
		HsvPSL				=s->HsvPSL			;
	if(EdittedMemberID.IsInclude(ID_HsvPSH)==true)
		HsvPSH				=s->HsvPSH			;
	if(EdittedMemberID.IsInclude(ID_HsvPVL)==true)
		HsvPVL				=s->HsvPVL			;
	if(EdittedMemberID.IsInclude(ID_HsvPVH)==true)
		HsvPVH				=s->HsvPVH			;
	if(EdittedMemberID.IsInclude(ID_HsvDHL)==true)
		HsvDHL				=s->HsvDHL			;
	if(EdittedMemberID.IsInclude(ID_HsvDHH)==true)
		HsvDHH				=s->HsvDHH			;
	if(EdittedMemberID.IsInclude(ID_HsvDSL)==true)
		HsvDSL				=s->HsvDSL			;
	if(EdittedMemberID.IsInclude(ID_HsvDSH)==true)
		HsvDSH				=s->HsvDSH			;
	if(EdittedMemberID.IsInclude(ID_HsvDVL)==true)
		HsvDVL				=s->HsvDVL			;
	if(EdittedMemberID.IsInclude(ID_HsvDVH)==true)
		HsvDVH				=s->HsvDVH			;
	if(EdittedMemberID.IsInclude(ID_HsvOKDot)==true)
		HsvOKDot			=s->HsvOKDot		;
	if(EdittedMemberID.IsInclude(ID_HsvOKLength)==true)
		HsvOKLength			=s->HsvOKLength		;
	if(EdittedMemberID.IsInclude(ID_SubtractLibID)==true)
		SubtractLibID		=s->SubtractLibID		;


	if(EdittedMemberID.IsInclude(ID_VariationMode	)==true)
		VariationMode	=s->VariationMode;
	if(EdittedMemberID.IsInclude(ID_VariationRL	)==true)	
		VariationRL	=s->VariationRL;
	if(EdittedMemberID.IsInclude(ID_VariationRH	)==true)	
		VariationRH	=s->VariationRH;
	if(EdittedMemberID.IsInclude(ID_VariationGL	)==true)	
		VariationGL	=s->VariationGL;
	if(EdittedMemberID.IsInclude(ID_VariationGH	)==true)	
		VariationGH	=s->VariationGH;
	if(EdittedMemberID.IsInclude(ID_VariationBL	)==true)	
		VariationBL	=s->VariationBL;
	if(EdittedMemberID.IsInclude(ID_VariationBH	)==true)	
		VariationBH	=s->VariationBH;
	if(EdittedMemberID.IsInclude(ID_VariationAdaptMinSize	)==true)	
		VariationAdaptMinSize	=s->VariationAdaptMinSize;
	if(EdittedMemberID.IsInclude(ID_VariationMultiplyMaster	)==true)	
		VariationMultiplyMaster	=s->VariationMultiplyMaster;
	if(EdittedMemberID.IsInclude(ID_VariationDifMaster	)==true)	
		VariationDifMaster	=s->VariationDifMaster;
	if(EdittedMemberID.IsInclude(ID_VariationAndLogic	)==true)	
		VariationAndLogic	=s->VariationAndLogic;
	if(EdittedMemberID.IsInclude(ID_VariationSubMasterVari	)==true)	
		VariationSubMasterVari	=s->VariationSubMasterVari;

	if(EdittedMemberID.IsInclude(ID_PitMode	)==true)	
		PitMode	=s->PitMode;
	if(EdittedMemberID.IsInclude(ID_PitBrightWidthRL	)==true)	
		PitBrightWidthRL	=s->PitBrightWidthRL;
	if(EdittedMemberID.IsInclude(ID_PitBrightWidthRH	)==true)	
		PitBrightWidthRH	=s->PitBrightWidthRH;
	if(EdittedMemberID.IsInclude(ID_PitBrightWidthGL	)==true)	
		PitBrightWidthGL	=s->PitBrightWidthGL;
	if(EdittedMemberID.IsInclude(ID_PitBrightWidthGH	)==true)	
		PitBrightWidthGH	=s->PitBrightWidthGH;
	if(EdittedMemberID.IsInclude(ID_PitBrightWidthBL	)==true)	
		PitBrightWidthBL	=s->PitBrightWidthBL;
	if(EdittedMemberID.IsInclude(ID_PitBrightWidthBH	)==true)	
		PitBrightWidthBH	=s->PitBrightWidthBH;

	if(EdittedMemberID.IsInclude(ID_LineMode			)==true)	
		LineMode	=s->LineMode;
	if(EdittedMemberID.IsInclude(ID_LineOKMinLength		)==true)	
		LineOKMinLength	=s->LineOKMinLength;
	if(EdittedMemberID.IsInclude(ID_LineMaxWidth		)==true)	
		LineMaxWidth	=s->LineMaxWidth;
	if(EdittedMemberID.IsInclude(ID_LineMinDensityPercent	)==true)	
		LineMinDensityPercent	=s->LineMinDensityPercent;
	if(EdittedMemberID.IsInclude(ID_LineMinCluster		)==true)	
		LineMinCluster	=s->LineMinCluster;

}
bool	DotColorMatchingThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const DotColorMatchingThreshold *s=(const DotColorMatchingThreshold *)&src;

	if(Broad.OrgBrightWidthRL	!=s->Broad.OrgBrightWidthRL)	return false;
	if(Broad.OrgBrightWidthRH	!=s->Broad.OrgBrightWidthRH)	return false;
	if(Broad.OrgBrightWidthGL	!=s->Broad.OrgBrightWidthGL)	return false;
	if(Broad.OrgBrightWidthGH	!=s->Broad.OrgBrightWidthGH)	return false;
	if(Broad.OrgBrightWidthBL	!=s->Broad.OrgBrightWidthBL)	return false;
	if(Broad.OrgBrightWidthBH	!=s->Broad.OrgBrightWidthBH)	return false;
	if(Broad.OrgOKDot			!=s->Broad.OrgOKDot)			return false;
	if(Broad.OrgOKLength		!=s->Broad.OrgOKLength)			return false;
	if(Broad.BrightWidthRL		!=s->Broad.BrightWidthRL)		return false;
	if(Broad.BrightWidthRH		!=s->Broad.BrightWidthRH)		return false;
	if(Broad.BrightWidthGL		!=s->Broad.BrightWidthGL)		return false;
	if(Broad.BrightWidthGH		!=s->Broad.BrightWidthGH)		return false;
	if(Broad.BrightWidthBL		!=s->Broad.BrightWidthBL)		return false;
	if(Broad.BrightWidthBH		!=s->Broad.BrightWidthBH)		return false;
	if(Broad.OKDot				!=s->Broad.OKDot	)			return false;
	if(Broad.OKLength			!=s->Broad.OKLength	)			return false;
	if(Broad.RThrOffsetL		!=s->Broad.RThrOffsetL)			return false;
	if(Broad.RThrOffsetH		!=s->Broad.RThrOffsetH)			return false;
	if(Broad.GThrOffsetL		!=s->Broad.GThrOffsetL)			return false;
	if(Broad.GThrOffsetH		!=s->Broad.GThrOffsetH)			return false;
	if(Broad.BThrOffsetL		!=s->Broad.BThrOffsetL)			return false;
	if(Broad.BThrOffsetH		!=s->Broad.BThrOffsetH)			return false;

	if(Narrow.OrgBrightWidthRL	!=s->Narrow.OrgBrightWidthRL)	return false;
	if(Narrow.OrgBrightWidthRH	!=s->Narrow.OrgBrightWidthRH)	return false;
	if(Narrow.OrgBrightWidthGL	!=s->Narrow.OrgBrightWidthGL)	return false;
	if(Narrow.OrgBrightWidthGH	!=s->Narrow.OrgBrightWidthGH)	return false;
	if(Narrow.OrgBrightWidthBL	!=s->Narrow.OrgBrightWidthBL)	return false;
	if(Narrow.OrgBrightWidthBH	!=s->Narrow.OrgBrightWidthBH)	return false;
	if(Narrow.OrgOKDot			!=s->Narrow.OrgOKDot)			return false;
	if(Narrow.OrgOKLength		!=s->Narrow.OrgOKLength)		return false;
	if(Narrow.BrightWidthRL		!=s->Narrow.BrightWidthRL)		return false;
	if(Narrow.BrightWidthRH		!=s->Narrow.BrightWidthRH)		return false;
	if(Narrow.BrightWidthGL		!=s->Narrow.BrightWidthGL)		return false;
	if(Narrow.BrightWidthGH		!=s->Narrow.BrightWidthGH)		return false;
	if(Narrow.BrightWidthBL		!=s->Narrow.BrightWidthBL)		return false;
	if(Narrow.BrightWidthBH		!=s->Narrow.BrightWidthBH)		return false;
	if(Narrow.OKDot				!=s->Narrow.OKDot		)		return false;
	if(Narrow.OKLength			!=s->Narrow.OKLength	)		return false;
	if(Narrow.RThrOffsetL		!=s->Narrow.RThrOffsetL)		return false;
	if(Narrow.RThrOffsetH		!=s->Narrow.RThrOffsetH)		return false;
	if(Narrow.GThrOffsetL		!=s->Narrow.GThrOffsetL)		return false;
	if(Narrow.GThrOffsetH		!=s->Narrow.GThrOffsetH)		return false;
	if(Narrow.BThrOffsetL		!=s->Narrow.BThrOffsetL)		return false;
	if(Narrow.BThrOffsetH		!=s->Narrow.BThrOffsetH)		return false;

	if(OrgMultiSpotDot		!=s->OrgMultiSpotDot)	return false;
	if(OrgMultiSpotCount	!=s->OrgMultiSpotCount)	return false;
	if(OrgBackGroundOKDot	!=s->OrgBackGroundOKDot)	return false;
	if(OrgBackGroundOKLength!=s->OrgBackGroundOKLength)	return false;
	if(OrgUseBackGround		!=s->UseBackGround)		return false;


	if(VarietySigma		!=s->VarietySigma)	return false;

	if(MultiSpotDot				!=s->MultiSpotDot			)	return false;
	if(MultiSpotCount			!=s->MultiSpotCount			)	return false;
	if(MultiSpotDotGathered		!=s->MultiSpotDotGathered	)	return false;
	if(MultiSpotCountGathered	!=s->MultiSpotCountGathered	)	return false;
	if(MultiSpotLengthGathered	!=s->MultiSpotLengthGathered)	return false;
	if(BackGroundOKDot			!=s->BackGroundOKDot		)	return false;
	if(BackGroundOKLength		!=s->BackGroundOKLength		)	return false;
	if(UseBackGround			!=s->UseBackGround			)	return false;

	if(SmoothCluster	!=s->SmoothCluster)		return false;
	if(EnableT2M		!=s->EnableT2M)			return false;
	if(EnableM2T		!=s->EnableM2T)			return false;
	if(UseMaster2		!=s->UseMaster2)		return false;
	if(ExpandToSubBlock	!=s->ExpandToSubBlock)	return false;
	if(MasterNo			!=s->MasterNo)			return false;

	if(AdjustBlack		!=s->AdjustBlack)		return false;
    if(AdjustWhite		!=s->AdjustWhite)		return false;
	if(AdjustContribute	!=s->AdjustContribute)	return false;
	if(AreaSearchX		!=s->AreaSearchX)		return false;
	if(AreaSearchY		!=s->AreaSearchY)		return false;
    if(SelfSearch		!=s->SelfSearch	)		return false;
	if(PreciseSearch	!=s->PreciseSearch	)	return false;
	if(Clusterize		!=s->Clusterize	)		return false;
	if(MaxAreaSearch	!=s->MaxAreaSearch	)	return false;
    if(MaxSelfSearch	!=s->MaxSelfSearch	)	return false;

	if(ScratchStartDirection!=s->ScratchStartDirection	)	return false;
	if(ScratchRotationAngle	!=s->ScratchRotationAngle	)	return false;
	if(ScratchDiff			!=s->ScratchDiff			)	return false;
	if(ScratchVariety		!=s->ScratchVariety			)	return false;
	if(ScratchDetectLevelL	!=s->ScratchDetectLevelL	)	return false;
	if(ScratchDetectLevelH	!=s->ScratchDetectLevelH	)	return false;
	if(ScratchMaxWidth		!=s->ScratchMaxWidth		)	return false;
	if(ScratchEnable		!=s->ScratchEnable			)	return false;
	if(ScratchUseMaster		!=s->ScratchUseMaster		)	return false;
	if(ScratchVOffset		!=s->ScratchVOffset			)	return false;

	if(AddedBrightness		!=s->AddedBrightness	)	return false;
	if(AddedOffset			!=s->AddedOffset		)	return false;
	if(AddedShift			!=s->AddedShift			)	return false;

	if(UseOneLayer			!=s->UseOneLayer		)	return false;

	if(RedCheckMode			!=s->RedCheckMode		)	return false;
	if(RedHighRate			!=s->RedHighRate		)	return false;
	if(RedMinBrightness		!=s->RedMinBrightness	)	return false;
	if(RedGBMerginRate		!=s->RedGBMerginRate	)	return false;
	if(RedGBMerginOffset	!=s->RedGBMerginOffset	)	return false;
	if(RedOKDot				!=s->RedOKDot			)	return false;
	if(RedShrink			!=s->RedShrink			)	return false;

	if(MatchBrightnessByLayerH!=s->MatchBrightnessByLayerH)	return false;
	if(MatchBrightnessByLayerL!=s->MatchBrightnessByLayerL)	return false;


	if(HsvCheckMode			!=s->HsvCheckMode		)	return false;	
	if(HsvFixedColorMode	!=s->HsvFixedColorMode	)	return false;
	if(HsvH					!=s->HsvH				)	return false;	
	if(HsvS					!=s->HsvS				)	return false;	
	if(HsvV					!=s->HsvV				)	return false;	
	if(HsvPHL				!=s->HsvPHL				)	return false;
	if(HsvPHH				!=s->HsvPHH				)	return false;
	if(HsvPSL				!=s->HsvPSL				)	return false;
	if(HsvPSH				!=s->HsvPSH				)	return false;
	if(HsvPVL				!=s->HsvPVL				)	return false;
	if(HsvPVH				!=s->HsvPVH				)	return false;
	if(HsvDHL				!=s->HsvDHL				)	return false;
	if(HsvDHH				!=s->HsvDHH				)	return false;
	if(HsvDSL				!=s->HsvDSL				)	return false;
	if(HsvDSH				!=s->HsvDSH				)	return false;
	if(HsvDVL				!=s->HsvDVL				)	return false;
	if(HsvDVH				!=s->HsvDVH				)	return false;
	if(HsvOKDot				!=s->HsvOKDot			)	return false;
	if(HsvOKLength			!=s->HsvOKLength		)	return false;
	if(SubtractLibID		!=s->SubtractLibID		)	return false;

	if(VariationMode	!=s->VariationMode	)	return false;
	if(VariationRL		!=s->VariationRL	)	return false;	
	if(VariationRH		!=s->VariationRH	)	return false;	
	if(VariationGL		!=s->VariationGL	)	return false;	
	if(VariationGH		!=s->VariationGH	)	return false;	
	if(VariationBL		!=s->VariationBL	)	return false;	
	if(VariationBH		!=s->VariationBH	)	return false;	
	if(VariationAdaptMinSize	!=s->VariationAdaptMinSize)		return false;
	if(VariationMultiplyMaster	!=s->VariationMultiplyMaster)	return false;
	if(VariationDifMaster		!=s->VariationDifMaster		)	return false;
	if(VariationAndLogic		!=s->VariationAndLogic		)	return false;
	if(VariationSubMasterVari	!=s->VariationSubMasterVari	)	return false;

	if(PitMode			!=s->PitMode			)	return false;
	if(PitBrightWidthRL	!=s->PitBrightWidthRL	)	return false;	
	if(PitBrightWidthRH	!=s->PitBrightWidthRH	)	return false;	
	if(PitBrightWidthGL	!=s->PitBrightWidthGL	)	return false;	
	if(PitBrightWidthGH	!=s->PitBrightWidthGH	)	return false;	
	if(PitBrightWidthBL	!=s->PitBrightWidthBL	)	return false;	
	if(PitBrightWidthBH	!=s->PitBrightWidthBH	)	return false;	

	if(LineMode				!=s->LineMode				)	return false;
	if(LineOKMinLength		!=s->LineOKMinLength		)	return false;
	if(LineMaxWidth			!=s->LineMaxWidth			)	return false;
	if(LineMinDensityPercent!=s->LineMinDensityPercent	)	return false;
	if(LineMinCluster		!=s->LineMinCluster			)	return false;

	return true;
}
bool	DotColorMatchingThreshold::Save(QIODevice *file)
{
	WORD	Ver=DotColorMatchingInspectionVersion;

	if(::Save(file,Ver)==false)
		return false;

	if(Broad.Save(file)==false)
		return false;
	if(Narrow.Save(file)==false)
		return false;

	if(::Save(file,OrgMultiSpotDot)==false)
		return false;
	if(::Save(file,OrgMultiSpotCount)==false)
		return false;
	if(::Save(file,OrgBackGroundOKDot)==false)
		return false;
	if(::Save(file,OrgBackGroundOKLength)==false)
		return false;
	if(::Save(file,OrgUseBackGround)==false)
		return false;

	if(::Save(file,VarietySigma)==false)
		return false;

	if(::Save(file,MultiSpotDot)==false)
		return false;
	if(::Save(file,MultiSpotCount)==false)
		return false;
	if(::Save(file,MultiSpotDotGathered)==false)
		return false;
	if(::Save(file,MultiSpotCountGathered)==false)
		return false;
	if(::Save(file,MultiSpotLengthGathered)==false)
		return false;
	if(::Save(file,BackGroundOKDot)==false)
		return false;
	if(::Save(file,BackGroundOKLength)==false)
		return false;
	if(::Save(file,UseBackGround)==false)
		return false;

	if(::Save(file,AdjustBlack)==false)
		return false;
	if(::Save(file,AdjustWhite)==false)
		return false;
	if(::Save(file,AdjustContribute	)==false)
		return false;
	if(::Save(file,AreaSearchX)==false)
		return false;
	if(::Save(file,AreaSearchY)==false)
		return false;
	if(::Save(file,SelfSearch)==false)
		return false;
	if(::Save(file,PreciseSearch)==false)
		return false;
	if(::Save(file,Clusterize)==false)
		return false;
	if(::Save(file,MaxAreaSearch)==false)
		return false;
	if(::Save(file,MaxSelfSearch)==false)
		return false;
	if(::Save(file,EnableT2M)==false)
		return false;
	if(::Save(file,EnableM2T)==false)
		return false;
 	if(::Save(file,UseMaster2)==false)
		return false;
 	if(::Save(file,ExpandToSubBlock)==false)
		return false;
	if(::Save(file,MasterNo)==false)
		return false;

    if(::Save(file,ScratchStartDirection)==false)
		return false;
    if(::Save(file,ScratchRotationAngle)==false)
		return false;
    if(::Save(file,ScratchVariety)==false)
		return false;
    if(::Save(file,ScratchDetectLevelL)==false)
		return false;
    if(::Save(file,ScratchDetectLevelH)==false)
		return false;
    if(::Save(file,ScratchMaxWidth)==false)
		return false;
    if(::Save(file,ScratchEnable)==false)
		return false;
    if(::Save(file,ScratchUseMaster)==false)
		return false;
    if(::Save(file,ScratchVOffset)==false)
		return false;
    if(::Save(file,ScratchDiff)==false)
		return false;

    if(::Save(file,AddedBrightness)==false)
		return false;
    if(::Save(file,AddedOffset)==false)
		return false;
    if(::Save(file,AddedShift)==false)
		return false;

    if(::Save(file,UseOneLayer)==false)
		return false;

    if(::Save(file,RedCheckMode)==false)
		return false;
    if(::Save(file,RedHighRate)==false)
		return false;
    if(::Save(file,RedGBMerginRate)==false)
		return false;
    if(::Save(file,RedGBMerginOffset)==false)
		return false;
    if(::Save(file,RedOKDot)==false)
		return false;
    if(::Save(file,RedShrink)==false)
		return false;
    if(::Save(file,RedMinBrightness)==false)
		return false;

    if(::Save(file,MatchBrightnessByLayerH)==false)
		return false;
    if(::Save(file,MatchBrightnessByLayerL)==false)
		return false;

	if(::Save(file,HsvCheckMode	)==false)
		return false;	
	if(::Save(file,HsvFixedColorMode	)==false)
		return false;
	if(::Save(file,HsvH	)==false)
		return false;			
	if(::Save(file,HsvS	)==false)
		return false;			
	if(::Save(file,HsvV	)==false)
		return false;			
	if(::Save(file,HsvPHL	)==false)
		return false;			
	if(::Save(file,HsvPHH	)==false)
		return false;			
	if(::Save(file,HsvPSL	)==false)
		return false;			
	if(::Save(file,HsvPSH	)==false)
		return false;			
	if(::Save(file,HsvPVL	)==false)
		return false;			
	if(::Save(file,HsvPVH	)==false)
		return false;
	if(::Save(file,HsvDHL	)==false)
		return false;			
	if(::Save(file,HsvDHH	)==false)
		return false;			
	if(::Save(file,HsvDSL	)==false)
		return false;			
	if(::Save(file,HsvDSH	)==false)
		return false;			
	if(::Save(file,HsvDVL	)==false)
		return false;			
	if(::Save(file,HsvDVH	)==false)
		return false;	
	if(::Save(file,HsvOKDot)==false)
		return false;	
	if(::Save(file,HsvOKLength)==false)
		return false;
	if(SubtractLibID.Save(file)==false)
		return false;

	if(::Save(file,VariationMode)==false)
		return false;	
	if(::Save(file,VariationRL	)==false)
		return false;
	if(::Save(file,VariationRH	)==false)
		return false;			
	if(::Save(file,VariationGL	)==false)
		return false;
	if(::Save(file,VariationGH	)==false)
		return false;
	if(::Save(file,VariationBL	)==false)
		return false;
	if(::Save(file,VariationBH	)==false)
		return false;
	if(::Save(file,VariationAdaptMinSize	)==false)
		return false;
	if(::Save(file,VariationMultiplyMaster	)==false)
		return false;
	if(::Save(file,VariationDifMaster	)==false)
		return false;
	if(::Save(file,VariationAndLogic	)==false)
		return false;
	if(::Save(file,VariationSubMasterVari)==false)
		return false;

	if(::Save(file,PitMode)==false)
		return false;	
	if(::Save(file,PitBrightWidthRL	)==false)
		return false;
	if(::Save(file,PitBrightWidthRH	)==false)
		return false;			
	if(::Save(file,PitBrightWidthGL	)==false)
		return false;
	if(::Save(file,PitBrightWidthGH	)==false)
		return false;
	if(::Save(file,PitBrightWidthBL	)==false)
		return false;
	if(::Save(file,PitBrightWidthBH	)==false)
		return false;

	if(::Save(file,LineMode				)==false)
		return false;
	if(::Save(file,LineOKMinLength		)==false)
		return false;
	if(::Save(file,LineMaxWidth			)==false)
		return false;
	if(::Save(file,LineMinDensityPercent)==false)
		return false;
	if(::Save(file,LineMinCluster		)==false)
		return false;
	return true;
}
bool	DotColorMatchingThreshold::Load(QIODevice *file)
{
	WORD	Ver;

	if(::Load(file,Ver)==false)
		return false;

	if(Ver<10063){
		if(Ver>=10004){
			if(::Load(file,Broad.OrgBrightWidthRL)==false)
				return false;
			if(::Load(file,Broad.OrgBrightWidthRH)==false)
				return false;
			if(::Load(file,Broad.OrgBrightWidthGL)==false)
				return false;
			if(::Load(file,Broad.OrgBrightWidthGH)==false)
				return false;
			if(::Load(file,Broad.OrgBrightWidthBL)==false)
				return false;
			if(::Load(file,Broad.OrgBrightWidthBH)==false)
				return false;
			if(::Load(file,Broad.OrgOKDot)==false)
				return false;
		}
		if(Ver>=10012){
			if(::Load(file,Broad.OrgOKLength)==false)
				return false;
		}
		if(Ver>=10040){
			if(::Load(file,OrgBackGroundOKDot)==false)
				return false;
			if(::Load(file,OrgBackGroundOKLength)==false)
				return false;
		}
		else{
			OrgBackGroundOKDot		=Broad.OrgOKDot;
			OrgBackGroundOKLength	=Broad.OrgOKLength;
		}
		if(Ver>=10041){
			if(::Load(file,UseBackGround)==false)
				return false;
		}
		else{
			UseBackGround		=false;
		}

		if(Ver>=10008){
			if(::Load(file,OrgMultiSpotDot)==false)
				return false;
			if(::Load(file,OrgMultiSpotCount)==false)
				return false;
		}
		if(::Load(file,Broad.BrightWidthRL)==false)
			return false;
		if(::Load(file,Broad.BrightWidthRH)==false)
			return false;
		if(::Load(file,Broad.BrightWidthGL)==false)
			return false;
		if(::Load(file,Broad.BrightWidthGH)==false)
			return false;
		if(::Load(file,Broad.BrightWidthBL)==false)
			return false;
		if(::Load(file,Broad.BrightWidthBH)==false)
			return false;

		if(Ver==10013){
			WORD	BrightWidthRAdded;
			WORD	BrightWidthGAdded;
			WORD	BrightWidthBAdded;
			if(::Load(file,BrightWidthRAdded)==false)
				return false;
			if(::Load(file,BrightWidthGAdded)==false)
				return false;
			if(::Load(file,BrightWidthBAdded)==false)
				return false;
		}
		if(Ver>=10014){
			if(::Load(file,VarietySigma)==false)
				return false;
		}
		if(::Load(file,Broad.OKDot)==false)
			return false;

		if(Ver>=10012){
			if(::Load(file,Broad.OKLength)==false)
				return false;
		}
		if(Ver>=10008){
			if(::Load(file,MultiSpotDot)==false)
				return false;
			if(::Load(file,MultiSpotCount)==false)
				return false;
		}
		if(Ver>=10043){
			if(::Load(file,MultiSpotDotGathered)==false)
				return false;
			if(::Load(file,MultiSpotCountGathered)==false)
				return false;
			if(::Load(file,MultiSpotLengthGathered)==false)
				return false;
		}
		else{
			MultiSpotDotGathered	=0;
			MultiSpotCountGathered	=0;
			MultiSpotLengthGathered	=99999999;
		}
		if(Ver>=10040){
			if(::Load(file,BackGroundOKDot)==false)
				return false;
			if(::Load(file,BackGroundOKLength)==false)
				return false;
		}
		else{
			BackGroundOKDot		=Broad.OKDot;
			BackGroundOKLength	=Broad.OKLength;
		}
		if(Ver>=10041){
			if(::Load(file,UseBackGround)==false)
				return false;
		}
		else{
			UseBackGround		=false;
		}

		if(::Load(file,AdjustBlack)==false)
			return false;
		if(::Load(file,AdjustWhite)==false)
			return false;

		if(Ver>=10053){
			if(::Load(file,AdjustContribute	)==false)
				return false;
		}
		else{
			AdjustContribute=100;
		}

		if(Ver>=10003){
			if(Ver>=10059){
				if(::Load(file,AreaSearchX)==false)
					return false;
				if(::Load(file,AreaSearchY)==false)
					return false;
			}
			else{
				WORD	AreaSearch;
				if(::Load(file,AreaSearch)==false)
					return false;
				AreaSearchX=AreaSearch;
				AreaSearchY=AreaSearch;
			}
		}
		if(::Load(file,SelfSearch)==false)
			return false;
		if(Ver>=10060){
			if(::Load(file,PreciseSearch)==false)
				return false;
		}
		else{
			PreciseSearch=false;
		}
		if(Ver>=10002){
			if(::Load(file,Clusterize)==false)
				return false;
		}
		if(Ver>=10051){
			if(::Load(file,MaxAreaSearch)==false)
				return false;
			if(::Load(file,MaxSelfSearch)==false)
				return false;
		}
		if(Ver>=10009){
			if(::Load(file,EnableT2M)==false)
				return false;
			if(::Load(file,EnableM2T)==false)
				return false;
		}
 		if(Ver>=10021){
			if(::Load(file,UseMaster2)==false)
				return false;
		}
		else{
			UseMaster2=false;
		}
 		if(Ver>=10047){
			if(::Load(file,ExpandToSubBlock)==false)
				return false;
		}
		else{
			ExpandToSubBlock=20;
		}
		if(Ver>=10044){
			if(::Load(file,MasterNo)==false)
				return false;
		}
		else{
			MasterNo=0;
		}
		if(Ver>=10010){
			if(::Load(file,Broad.RThrOffsetL)==false)
				return false;
		    if(::Load(file,Broad.RThrOffsetH)==false)
				return false;
		    if(::Load(file,Broad.GThrOffsetL)==false)
				return false;
		    if(::Load(file,Broad.GThrOffsetH)==false)
				return false;
		    if(::Load(file,Broad.BThrOffsetL)==false)
				return false;
		    if(::Load(file,Broad.BThrOffsetH)==false)
				return false;
		}
		if(Ver<10004){
			SetToOrigin();
		}
		if(Ver==10011){
			double	dScratchStartDirection;
			if(::Load(file,dScratchStartDirection)==false)
				return false;
			ScratchStartDirection=dScratchStartDirection;
		}
		else
		if(Ver>=10012){
			if(::Load(file,ScratchStartDirection)==false)
				return false;
		}
		if(Ver>=10016){
			if(::Load(file,ScratchRotationAngle)==false)
				return false;
		}
		if(Ver>=10017){
			if(::Load(file,ScratchVariety)==false)
				return false;
		}
		if(Ver>=10011){
			if(::Load(file,ScratchDetectLevelL)==false)
				return false;
			if(::Load(file,ScratchDetectLevelH)==false)
				return false;
			if(::Load(file,ScratchMaxWidth)==false)
				return false;
		}
		if(Ver>=10012){
			if(::Load(file,ScratchEnable)==false)
				return false;
		}
		else{
			ScratchEnable=false;
		}
		if(Ver>=10024){
			if(::Load(file,ScratchUseMaster)==false)
				return false;
		}
		else{
			ScratchUseMaster=true;
		}
		if(Ver>=10025){
			if(::Load(file,ScratchVOffset)==false)
				return false;
		}
		else{
			ScratchVOffset=0;
		}
		if(Ver>=10034){
			if(::Load(file,ScratchDiff)==false)
				return false;
		}
		else{
			ScratchDiff=5;
		}
		if(Ver>=10018){
			if(::Load(file,AddedBrightness)==false)
				return false;
			if(::Load(file,AddedOffset)==false)
				return false;
			if(::Load(file,AddedShift)==false)
				return false;
		}
		if(Ver>=10015){
			if(::Load(file,UseOneLayer)==false)
				return false;
		}
		else{
			UseOneLayer=0xFF;
		}

		if(Ver>=10026){
			if(::Load(file,RedCheckMode)==false)
				return false;
			if(::Load(file,RedHighRate)==false)
				return false;
			if(::Load(file,RedGBMerginRate)==false)
				return false;
			if(::Load(file,RedGBMerginOffset)==false)
				return false;
			if(::Load(file,RedOKDot)==false)
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
			if(::Load(file,RedShrink)==false)
				return false;
		}
		else{
			RedShrink=0;
		}
		if(Ver>=10027){
			if(::Load(file,RedMinBrightness)==false)
				return false;
		}
		else{
			RedMinBrightness	=70;
		}
		if(Ver>=10030){
			if(::Load(file,MatchBrightnessByLayerH)==false)
				return false;
			if(::Load(file,MatchBrightnessByLayerL)==false)
				return false;
		}
		else{
			MatchBrightnessByLayerH	=0xFF;
			MatchBrightnessByLayerL	=0xFF;
		}
		if(Ver>=10042){
			if(::Load(file,HsvCheckMode	)==false)
				return false;	
			if(::Load(file,HsvFixedColorMode	)==false)
				return false;
			if(::Load(file,HsvH	)==false)
				return false;			
			if(::Load(file,HsvS	)==false)
				return false;			
			if(::Load(file,HsvV	)==false)
				return false;			
			if(::Load(file,HsvPHL	)==false)
				return false;			
			if(::Load(file,HsvPHH	)==false)
				return false;			
			if(::Load(file,HsvPSL	)==false)
				return false;			
			if(::Load(file,HsvPSH	)==false)
				return false;			
			if(::Load(file,HsvPVL	)==false)
				return false;			
			if(::Load(file,HsvPVH	)==false)
				return false;
			if(::Load(file,HsvDHL	)==false)
				return false;			
			if(::Load(file,HsvDHH	)==false)
				return false;			
			if(::Load(file,HsvDSL	)==false)
				return false;			
			if(::Load(file,HsvDSH	)==false)
				return false;			
			if(::Load(file,HsvDVL	)==false)
				return false;			
			if(::Load(file,HsvDVH	)==false)
				return false;	
			if(::Load(file,HsvOKDot)==false)
				return false;
			if(::Load(file,HsvOKLength)==false)
				return false;
		}
		if(Ver>=10046){
			if(SubtractLibID.Load(file)==false)
				return false;
		}
		if(Ver>=10048){
			if(::Load(file,VariationMode	)==false)
				return false;	
			if(::Load(file,VariationRL	)==false)
				return false;
			if(::Load(file,VariationRH	)==false)
				return false;			
			if(::Load(file,VariationGL	)==false)
				return false;
			if(::Load(file,VariationGH	)==false)
				return false;
			if(::Load(file,VariationBL	)==false)
				return false;
			if(::Load(file,VariationBH	)==false)
				return false;
		}
		if(Ver>=10049){
			if(::Load(file,VariationAdaptMinSize	)==false)
				return false;
		}
		if(Ver>=10052){
			if(::Load(file,VariationMultiplyMaster	)==false)
				return false;
		}
		if(Ver>=10054){
			if(::Load(file,VariationDifMaster	)==false)
				return false;
		}
		if(Ver>=10056){
			if(::Load(file,VariationAndLogic	)==false)
				return false;
		}
		if(Ver>=10057){
			if(::Load(file,VariationSubMasterVari)==false)
				return false;
		}

		if(Ver>=10050){
			if(::Load(file,PitMode)==false)
				return false;	
			if(::Load(file,PitBrightWidthRL	)==false)
				return false;
			if(::Load(file,PitBrightWidthRH	)==false)
				return false;			
			if(::Load(file,PitBrightWidthGL	)==false)
				return false;
			if(::Load(file,PitBrightWidthGH	)==false)
				return false;
			if(::Load(file,PitBrightWidthBL	)==false)
				return false;
			if(::Load(file,PitBrightWidthBH	)==false)
				return false;
		}
		else{
			PitMode=false;
		}
		if(Ver>=10061){
			if(::Load(file,LineMode				)==false)
				return false;
			if(::Load(file,LineOKMinLength		)==false)
				return false;
			if(::Load(file,LineMaxWidth			)==false)
				return false;
			if(::Load(file,LineMinDensityPercent)==false)
				return false;
		}
		if(Ver>=10062){
			if(::Load(file,LineMinCluster		)==false)
				return false;
		}
	}
	else{
		if(Broad.Load(file)==false)
			return false;
		if(Narrow.Load(file)==false)
			return false;

		if(::Load(file,OrgMultiSpotDot)==false)
			return false;
		if(::Load(file,OrgMultiSpotCount)==false)
			return false;
		if(::Load(file,OrgBackGroundOKDot)==false)
			return false;
		if(::Load(file,OrgBackGroundOKLength)==false)
			return false;
		if(::Load(file,OrgUseBackGround)==false)
			return false;

		if(::Load(file,VarietySigma)==false)
			return false;

		if(::Load(file,MultiSpotDot)==false)
			return false;
		if(::Load(file,MultiSpotCount)==false)
			return false;
		if(::Load(file,MultiSpotDotGathered)==false)
			return false;
		if(::Load(file,MultiSpotCountGathered)==false)
			return false;
		if(::Load(file,MultiSpotLengthGathered)==false)
			return false;
		if(::Load(file,BackGroundOKDot)==false)
			return false;
		if(::Load(file,BackGroundOKLength)==false)
			return false;
		if(::Load(file,UseBackGround)==false)
			return false;

		if(::Load(file,AdjustBlack)==false)
			return false;
		if(::Load(file,AdjustWhite)==false)
			return false;
		if(::Load(file,AdjustContribute	)==false)
			return false;
		if(::Load(file,AreaSearchX)==false)
			return false;
		if(::Load(file,AreaSearchY)==false)
			return false;
		if(::Load(file,SelfSearch)==false)
			return false;
		if(::Load(file,PreciseSearch)==false)
			return false;
		if(::Load(file,Clusterize)==false)
			return false;
		if(::Load(file,MaxAreaSearch)==false)
			return false;
		if(::Load(file,MaxSelfSearch)==false)
			return false;
		if(::Load(file,EnableT2M)==false)
			return false;
		if(::Load(file,EnableM2T)==false)
			return false;
 		if(::Load(file,UseMaster2)==false)
			return false;
 		if(::Load(file,ExpandToSubBlock)==false)
			return false;
		if(::Load(file,MasterNo)==false)
			return false;

		if(::Load(file,ScratchStartDirection)==false)
			return false;
		if(::Load(file,ScratchRotationAngle)==false)
			return false;
		if(::Load(file,ScratchVariety)==false)
			return false;
		if(::Load(file,ScratchDetectLevelL)==false)
			return false;
		if(::Load(file,ScratchDetectLevelH)==false)
			return false;
		if(::Load(file,ScratchMaxWidth)==false)
			return false;
		if(::Load(file,ScratchEnable)==false)
			return false;
		if(::Load(file,ScratchUseMaster)==false)
			return false;
		if(::Load(file,ScratchVOffset)==false)
			return false;
		if(::Load(file,ScratchDiff)==false)
			return false;

		if(::Load(file,AddedBrightness)==false)
			return false;
		if(::Load(file,AddedOffset)==false)
			return false;
		if(::Load(file,AddedShift)==false)
			return false;

		if(::Load(file,UseOneLayer)==false)
			return false;

		if(::Load(file,RedCheckMode)==false)
			return false;
		if(::Load(file,RedHighRate)==false)
			return false;
		if(::Load(file,RedGBMerginRate)==false)
			return false;
		if(::Load(file,RedGBMerginOffset)==false)
			return false;
		if(::Load(file,RedOKDot)==false)
			return false;
		if(::Load(file,RedShrink)==false)
			return false;
		if(::Load(file,RedMinBrightness)==false)
			return false;

		if(::Load(file,MatchBrightnessByLayerH)==false)
			return false;
		if(::Load(file,MatchBrightnessByLayerL)==false)
			return false;

		if(::Load(file,HsvCheckMode	)==false)
			return false;	
		if(::Load(file,HsvFixedColorMode	)==false)
			return false;
		if(::Load(file,HsvH	)==false)
			return false;			
		if(::Load(file,HsvS	)==false)
			return false;			
		if(::Load(file,HsvV	)==false)
			return false;			
		if(::Load(file,HsvPHL	)==false)
			return false;			
		if(::Load(file,HsvPHH	)==false)
			return false;			
		if(::Load(file,HsvPSL	)==false)
			return false;			
		if(::Load(file,HsvPSH	)==false)
			return false;			
		if(::Load(file,HsvPVL	)==false)
			return false;			
		if(::Load(file,HsvPVH	)==false)
			return false;
		if(::Load(file,HsvDHL	)==false)
			return false;			
		if(::Load(file,HsvDHH	)==false)
			return false;			
		if(::Load(file,HsvDSL	)==false)
			return false;			
		if(::Load(file,HsvDSH	)==false)
			return false;			
		if(::Load(file,HsvDVL	)==false)
			return false;			
		if(::Load(file,HsvDVH	)==false)
			return false;	
		if(::Load(file,HsvOKDot)==false)
			return false;	
		if(::Load(file,HsvOKLength)==false)
			return false;
		if(SubtractLibID.Load(file)==false)
			return false;

		if(::Load(file,VariationMode)==false)
			return false;	
		if(::Load(file,VariationRL	)==false)
			return false;
		if(::Load(file,VariationRH	)==false)
			return false;			
		if(::Load(file,VariationGL	)==false)
			return false;
		if(::Load(file,VariationGH	)==false)
			return false;
		if(::Load(file,VariationBL	)==false)
			return false;
		if(::Load(file,VariationBH	)==false)
			return false;
		if(::Load(file,VariationAdaptMinSize	)==false)
			return false;
		if(::Load(file,VariationMultiplyMaster	)==false)
			return false;
		if(::Load(file,VariationDifMaster	)==false)
			return false;
		if(::Load(file,VariationAndLogic	)==false)
			return false;
		if(::Load(file,VariationSubMasterVari)==false)
			return false;

		if(::Load(file,PitMode)==false)
			return false;	
		if(::Load(file,PitBrightWidthRL	)==false)
			return false;
		if(::Load(file,PitBrightWidthRH	)==false)
			return false;			
		if(::Load(file,PitBrightWidthGL	)==false)
			return false;
		if(::Load(file,PitBrightWidthGH	)==false)
			return false;
		if(::Load(file,PitBrightWidthBL	)==false)
			return false;
		if(::Load(file,PitBrightWidthBH	)==false)
			return false;

		if(::Load(file,LineMode				)==false)
			return false;
		if(::Load(file,LineOKMinLength		)==false)
			return false;
		if(::Load(file,LineMaxWidth			)==false)
			return false;
		if(::Load(file,LineMinDensityPercent)==false)
			return false;
		if(::Load(file,LineMinCluster		)==false)
			return false;
	}
	return true;
}

void	DotColorMatchingThreshold::FromLibrary(AlgorithmLibrary *src)
{
	DotColorMatchingLibrary	*LSrc=dynamic_cast<DotColorMatchingLibrary *>(src);
	if(LSrc==NULL)
		return;

	Broad.FromLibrary(&LSrc->Broad);
	Narrow.FromLibrary(&LSrc->Narrow);

	OrgMultiSpotDot		=LSrc->MultiSpotDot	;
	OrgMultiSpotCount	=LSrc->MultiSpotCount;
	OrgBackGroundOKDot		=LSrc->BackGroundOKDot;
	OrgBackGroundOKLength	=LSrc->BackGroundOKLength;
	OrgUseBackGround	=LSrc->UseBackGround;

	VarietySigma	=LSrc->VarietySigma;

	MultiSpotDot			=LSrc->MultiSpotDot	;
	MultiSpotCount			=LSrc->MultiSpotCount;
	MultiSpotDotGathered	=LSrc->MultiSpotDotGathered		;
	MultiSpotCountGathered	=LSrc->MultiSpotCountGathered	;
	MultiSpotLengthGathered	=LSrc->MultiSpotLengthGathered	;
	BackGroundOKDot		=LSrc->BackGroundOKDot;
	BackGroundOKLength	=LSrc->BackGroundOKLength;
	UseBackGround		=LSrc->UseBackGround;

	AdjustBlack			=LSrc->AdjustBlack;
	AdjustWhite			=LSrc->AdjustWhite;
	AdjustContribute	=LSrc->AdjustContribute;
	AreaSearchX			=LSrc->AreaSearchX;
	AreaSearchY			=LSrc->AreaSearchY;
	SelfSearch			=LSrc->SelfSearch;
	PreciseSearch		=LSrc->PreciseSearch;
	Clusterize			=LSrc->Clusterize;
	MaxAreaSearch		=LSrc->MaxAreaSearch;
	MaxSelfSearch		=LSrc->MaxSelfSearch;
	EnableT2M			=LSrc->EnableT2M;
	EnableM2T			=LSrc->EnableM2T;
	UseMaster2			=LSrc->UseMaster2;
	LayersBase	*LBase=GetLayersBase();
	if(LBase==NULL){
		LBase=LSrc->GetLayersBase();
	}
	if(LBase!=NULL){
		MasterNo		=LBase->FindBufferInfo(LSrc->MasterNoOriginCode);
	}
	else{
		MasterNo=-1;
	}

	ScratchStartDirection	=LSrc->ScratchStartDirection;
	ScratchRotationAngle	=LSrc->ScratchRotationAngle ;
	ScratchDiff				=LSrc->ScratchDiff			;
	ScratchVariety			=LSrc->ScratchVariety		;
	ScratchDetectLevelL		=LSrc->ScratchDetectLevelL	;
	ScratchDetectLevelH		=LSrc->ScratchDetectLevelH	;
	ScratchMaxWidth			=LSrc->ScratchMaxWidth		;
	ScratchEnable			=LSrc->ScratchEnable		;
	ScratchUseMaster		=LSrc->ScratchUseMaster		;
	ScratchVOffset			=LSrc->ScratchVOffset		;

	UseOneLayer			=LSrc->UseOneLayer			;

	RedCheckMode		=LSrc->RedCheckMode			;
	RedHighRate			=LSrc->RedHighRate			;
	RedMinBrightness	=LSrc->RedMinBrightness		;
	RedGBMerginRate		=LSrc->RedGBMerginRate		;
	RedGBMerginOffset	=LSrc->RedGBMerginOffset	;
	RedOKDot			=LSrc->RedOKDot				;
	RedShrink			=LSrc->RedShrink			;

	MatchBrightnessByLayerH	=LSrc->MatchBrightnessByLayerH;
	MatchBrightnessByLayerL	=LSrc->MatchBrightnessByLayerL;

	HsvCheckMode		=LSrc->HsvCheckMode		;
	HsvFixedColorMode	=LSrc->HsvFixedColorMode;
	HsvH				=LSrc->HsvH				;
	HsvS				=LSrc->HsvS				;
	HsvV				=LSrc->HsvV				;
	HsvPHL				=LSrc->HsvPHL			;
	HsvPHH				=LSrc->HsvPHH			;
	HsvPSL				=LSrc->HsvPSL			;
	HsvPSH				=LSrc->HsvPSH			;
	HsvPVL				=LSrc->HsvPVL			;
	HsvPVH				=LSrc->HsvPVH			;
	HsvDHL				=LSrc->HsvDHL			;
	HsvDHH				=LSrc->HsvDHH			;
	HsvDSL				=LSrc->HsvDSL			;
	HsvDSH				=LSrc->HsvDSH			;
	HsvDVL				=LSrc->HsvDVL			;
	HsvDVH				=LSrc->HsvDVH			;
	HsvOKDot			=LSrc->HsvOKDot			;
	HsvOKLength			=LSrc->HsvOKLength		;
	SubtractLibID		=LSrc->SubtractLibID	;

	VariationMode		=LSrc->VariationMode	;
	VariationRL			=LSrc->VariationRL		;
	VariationRH			=LSrc->VariationRH		;
	VariationGL			=LSrc->VariationGL		;
	VariationGH			=LSrc->VariationGH		;
	VariationBL			=LSrc->VariationBL		;
	VariationBH			=LSrc->VariationBH		;
	VariationAdaptMinSize	=LSrc->VariationAdaptMinSize;
	VariationMultiplyMaster	=LSrc->VariationMultiplyMaster;
	VariationDifMaster		=LSrc->VariationDifMaster;
	VariationAndLogic		=LSrc->VariationAndLogic;
	VariationSubMasterVari	=LSrc->VariationSubMasterVari;

	PitMode				=LSrc->PitMode			;
	PitBrightWidthRL	=LSrc->PitBrightWidthRL	;
	PitBrightWidthRH	=LSrc->PitBrightWidthRH	;
	PitBrightWidthGL	=LSrc->PitBrightWidthGL	;
	PitBrightWidthGH	=LSrc->PitBrightWidthGH	;
	PitBrightWidthBL	=LSrc->PitBrightWidthBL	;
	PitBrightWidthBH	=LSrc->PitBrightWidthBH	;

	LineMode				=LSrc->LineMode				;
	LineOKMinLength			=LSrc->LineOKMinLength		;
	LineMaxWidth			=LSrc->LineMaxWidth			;
	LineMinDensityPercent	=LSrc->LineMinDensityPercent;
	LineMinCluster			=LSrc->LineMinCluster		;
}
void	DotColorMatchingThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	DotColorMatchingLibrary	*LDst=dynamic_cast<DotColorMatchingLibrary *>(Dest);
	if(LDst==NULL)
		return;

	Broad.ToLibrary(&LDst->Broad);
	Narrow.ToLibrary(&LDst->Narrow);

	LDst->VarietySigma	=VarietySigma	;

	LDst->MultiSpotDot	=MultiSpotDot	;
	LDst->MultiSpotCount=MultiSpotCount	;
	LDst->MultiSpotDotGathered		=MultiSpotDotGathered	;
	LDst->MultiSpotCountGathered	=MultiSpotCountGathered	;
	LDst->MultiSpotLengthGathered	=MultiSpotLengthGathered;
	LDst->BackGroundOKDot	=BackGroundOKDot	;
	LDst->BackGroundOKLength=BackGroundOKLength	;
	LDst->UseBackGround	=UseBackGround;

	LDst->AdjustBlack		=AdjustBlack	;
	LDst->AdjustWhite		=AdjustWhite	;
	LDst->AdjustContribute	=AdjustContribute;
	LDst->AreaSearchX		=AreaSearchX	;
	LDst->AreaSearchY		=AreaSearchY	;
	LDst->SelfSearch		=SelfSearch		;
	LDst->PreciseSearch		=PreciseSearch	;
	LDst->Clusterize		=Clusterize		;
	LDst->MaxAreaSearch		=MaxAreaSearch	;
	LDst->MaxSelfSearch		=MaxSelfSearch	;
	LDst->EnableT2M			=EnableT2M		;
	LDst->EnableM2T			=EnableM2T		;
	LDst->UseMaster2		=UseMaster2		;

	LayersBase	*LBase=GetLayersBase();
	if(LBase==NULL){
		LBase=LDst->GetLayersBase();
	}
	if(LBase!=NULL){
		BufferInfoList	*L=LBase->GetBufferInfo(MasterNo);
		if(L!=NULL){
			LDst->MasterNoOriginCode=L->OriginCode;
		}
	}
	else{
		LDst->MasterNoOriginCode=-1;
	}

	LDst->ScratchStartDirection	=ScratchStartDirection	;
	LDst->ScratchRotationAngle	=ScratchRotationAngle	;
	LDst->ScratchDiff			=ScratchDiff			;
	LDst->ScratchVariety		=ScratchVariety			;
	LDst->ScratchDetectLevelL	=ScratchDetectLevelL	;
	LDst->ScratchDetectLevelH	=ScratchDetectLevelH	;
	LDst->ScratchMaxWidth		=ScratchMaxWidth		;
	LDst->ScratchEnable			=ScratchEnable			;
	LDst->ScratchUseMaster		=ScratchUseMaster		;
	LDst->ScratchVOffset		=ScratchVOffset			;

	LDst->UseOneLayer			=UseOneLayer			;

	LDst->RedCheckMode			=RedCheckMode			;
	LDst->RedHighRate			=RedHighRate			;
	LDst->RedMinBrightness		=RedMinBrightness		;
	LDst->RedGBMerginRate		=RedGBMerginRate		;
	LDst->RedGBMerginOffset		=RedGBMerginOffset		;
	LDst->RedOKDot				=RedOKDot				;
	LDst->RedShrink				=RedShrink				;

	LDst->MatchBrightnessByLayerH	=MatchBrightnessByLayerH;
	LDst->MatchBrightnessByLayerL	=MatchBrightnessByLayerL;

	LDst->HsvCheckMode		=HsvCheckMode		;
	LDst->HsvFixedColorMode	=HsvFixedColorMode	;
	LDst->HsvH				=HsvH				;
	LDst->HsvS				=HsvS				;
	LDst->HsvV				=HsvV				;
	LDst->HsvPHL			=HsvPHL				;
	LDst->HsvPHH			=HsvPHH				;
	LDst->HsvPSL			=HsvPSL				;
	LDst->HsvPSH			=HsvPSH				;
	LDst->HsvPVL			=HsvPVL				;
	LDst->HsvPVH			=HsvPVH				;
	LDst->HsvDHL			=HsvDHL				;
	LDst->HsvDHH			=HsvDHH				;
	LDst->HsvDSL			=HsvDSL				;
	LDst->HsvDSH			=HsvDSH				;
	LDst->HsvDVL			=HsvDVL				;
	LDst->HsvDVH			=HsvDVH				;
	LDst->HsvOKDot			=HsvOKDot			;
	LDst->HsvOKLength		=HsvOKLength		;
	LDst->SubtractLibID		=SubtractLibID		;

	LDst->VariationMode	=VariationMode	;
	LDst->VariationRL	=VariationRL	;		
	LDst->VariationRH	=VariationRH	;		
	LDst->VariationGL	=VariationGL	;		
	LDst->VariationGH	=VariationGH	;		
	LDst->VariationBL	=VariationBL	;		
	LDst->VariationBH	=VariationBH	;
	LDst->VariationAdaptMinSize		=VariationAdaptMinSize	;
	LDst->VariationMultiplyMaster	=VariationMultiplyMaster;
	LDst->VariationDifMaster		=VariationDifMaster;
	LDst->VariationAndLogic			=VariationAndLogic;
	LDst->VariationSubMasterVari	=VariationSubMasterVari;

	LDst->PitMode			=PitMode			;
	LDst->PitBrightWidthRL	=PitBrightWidthRL	;
	LDst->PitBrightWidthRH	=PitBrightWidthRH	;
	LDst->PitBrightWidthGL	=PitBrightWidthGL	;
	LDst->PitBrightWidthGH	=PitBrightWidthGH	;
	LDst->PitBrightWidthBL	=PitBrightWidthBL	;
	LDst->PitBrightWidthBH	=PitBrightWidthBH	;

	LDst->LineMode				=LineMode				;
	LDst->LineOKMinLength		=LineOKMinLength		;
	LDst->LineMaxWidth			=LineMaxWidth			;
	LDst->LineMinDensityPercent	=LineMinDensityPercent	;
	LDst->LineMinCluster		=LineMinCluster			;
}

void	DotColorMatchingThreshold::SetToOrigin(void)
{
	Broad.SetToOrigin();
	Narrow.SetToOrigin();

	OrgMultiSpotDot			=MultiSpotDot	;
	OrgMultiSpotCount		=MultiSpotCount;
	OrgBackGroundOKDot		=BackGroundOKDot;
	OrgBackGroundOKLength	=BackGroundOKLength;
	OrgUseBackGround		=UseBackGround;
}


//====================================================================================================
DotColorMatchingItem::DotColorMatchingItem(void)
{
	ExtraCreation	=false;
	MasterPattern	=NULL;
	CurrentMasterPattern	=NULL;
	PatternCount	=0;
	RotationDiv		=0;
	CenterBrightR	=0;
	CenterBrightG	=0;
	CenterBrightB	=0;
	AVector=NULL;
	Map		=NULL;
	DummyMap=NULL;
	MapXByte=0;
	MapYLen	=0;
	AreaAR=AreaAAR=0.0;
	AreaAG=AreaAAG=0.0;
	AreaAB=AreaAAB=0.0;
	MatchingType			=0;
	CurrentRotationPatternNo=0;
	OutlineArea				=false;
	FoldingArea				=false;
	OutlineBlock			=false;

	MaxCoefItem				=NULL;
	ReferedDx=ReferedDy		=0;
	ScratchTableDim			=NULL;
	ScratchTableMasterDim	=NULL;
	ScratchLayer			=0;
	ScratchResultAngle		=0;
	ScratchResultWidth		=0;
	ScratchResultPeakH		=0;
	ScratchResultPeakL		=0;
	ScratchResultStartDim	=0;
	ScratchResultEndDim		=0;
	//for(int i=0;i<sizeof(ScratchXYTable)/sizeof(ScratchXYTable[0]);i++){
	//	ScratchXYTable[i]=NULL;
	//}
	//Locked=0;
	DeviationResultR	=0;
	DeviationResultG	=0;
	DeviationResultB	=0;
}
DotColorMatchingItem::DotColorMatchingItem(FlexArea &area)
:AlgorithmItemPI(area)
{
	ExtraCreation	=false;
	MasterPattern	=NULL;
	CurrentMasterPattern	=NULL;
	PatternCount	=0;
	RotationDiv		=0;
	CenterBrightR	=0;
	CenterBrightG	=0;
	CenterBrightB	=0;
	AVector=NULL;
	Map		=NULL;
	DummyMap=NULL;
	MapXByte=0;
	MapYLen	=0;
	AreaAR=AreaAAR=0.0;
	AreaAG=AreaAAG=0.0;
	AreaAB=AreaAAB=0.0;
	MatchingType	=0;
	CurrentRotationPatternNo=0;
	OutlineArea		=false;
	FoldingArea		=false;
	OutlineBlock	=false;

	MaxCoefItem	=NULL;
	ReferedDx=ReferedDy		=0;
	ScratchTableDim			=NULL;
	ScratchTableMasterDim	=NULL;
	ScratchLayer			=0;
	ScratchResultAngle		=0;
	ScratchResultWidth		=0;
	ScratchResultPeakH		=0;
	ScratchResultPeakL		=0;
	ScratchResultStartDim	=0;
	ScratchResultEndDim		=0;
	//for(int i=0;i<sizeof(ScratchXYTable)/sizeof(ScratchXYTable[0]);i++){
	//	ScratchXYTable[i]=NULL;
	//}
	//Locked=0;
	DeviationResultR	=0;
	DeviationResultG	=0;
	DeviationResultB	=0;
}


DotColorMatchingItem::~DotColorMatchingItem(void)
{
	if(DummyMap!=NULL){
		DeleteMatrixBuff(DummyMap,MapYLen);
		DummyMap=NULL;
	}
	if(Map!=NULL){
		DeleteMatrixBuff(Map,MapYLen);
		Map=NULL;
	}
	if(MasterPattern!=NULL){
		delete	[]MasterPattern;
		MasterPattern=NULL;
	}
	MapXByte=0;
	MapYLen	=0;
	if(ScratchTableDim!=NULL){
		delete	[]ScratchTableDim;
		ScratchTableDim		=NULL;
	}
	if(ScratchTableMasterDim!=NULL){
		delete	[]ScratchTableMasterDim;
		ScratchTableMasterDim	=NULL;
	}
	ScratchLayer		=0;

	//for(int i=0;i<sizeof(ScratchXYTable)/sizeof(ScratchXYTable[0]);i++){
	//	if(ScratchXYTable[i]!=NULL){
	//		delete	[]ScratchXYTable[i];
	//		ScratchXYTable[i]=NULL;
	//	}
	//}
	if(GetParentInPage()!=NULL){
		DotColorMatchingInPage	*Ap=(DotColorMatchingInPage *)GetParentInPage();
		Ap->RemoveItemInList(this);
	}
}
void    DotColorMatchingItem::MoveTo(int dx ,int dy)
{
	AlgorithmItemPI::MoveTo(dx,dy);
}

AlgorithmItemPI	&DotColorMatchingItem::operator=(const AlgorithmItemRoot &src)
{
	const DotColorMatchingItem	*s=dynamic_cast<const DotColorMatchingItem *>(&src);
	if(s!=NULL){
		ExtraCreation	=s->ExtraCreation;
		AreaAR			=s->AreaAR		;
		AreaAAR			=s->AreaAAR		;
		AreaAG			=s->AreaAG		;
		AreaAAG			=s->AreaAAG		;
		AreaAB			=s->AreaAB		;
		AreaAAB			=s->AreaAAB		;
		MatchingType	=s->MatchingType;		//0:Coefficient	1:Difference
		SearchType		=s->SearchType	;		//0:No search	1:Co-efficience search	2:Flat search
		OutlineArea		=s->OutlineArea	;
		FoldingArea		=s->FoldingArea	;
		OutlineBlock	=s->OutlineBlock;
		return AlgorithmItemPI::operator=(*s);
	}
	return *this;
}
DotColorMatchingItem &DotColorMatchingItem::operator=(const DotColorMatchingItem &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(*((DotColorMatchingItem *)&src));
	ExtraCreation	=src.ExtraCreation;
	AreaAR			=src.AreaAR			;
	AreaAAR			=src.AreaAAR		;
	AreaAG			=src.AreaAG			;
	AreaAAG			=src.AreaAAG		;
	AreaAB			=src.AreaAB			;
	AreaAAB			=src.AreaAAB		;
	MatchingType	=src.MatchingType	;		//0:Coefficient	1:Difference
	SearchType		=src.SearchType		;		//0:No search	1:Co-efficience search	2:Flat search
	OutlineArea		=src.OutlineArea	;
	FoldingArea		=src.FoldingArea	;
	OutlineBlock	=src.OutlineBlock	;

	return *this;
}

void	DotColorMatchingItem::CopyThreshold(DotColorMatchingItem &src)
{
	CenterBrightR	=src.CenterBrightR;
	CenterBrightG	=src.CenterBrightG;
	CenterBrightB	=src.CenterBrightB;
	GetThresholdW()->CopyFrom(*((DotColorMatchingThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

void	DotColorMatchingItem::CopyThresholdOnly(DotColorMatchingItem &src,IntList &EdittedMemberID)
{
	GetThresholdW()->CopyFrom(*((DotColorMatchingThreshold *)src.GetThresholdR()),EdittedMemberID);
	SetInvertLogic(src.GetInvertLogic());
}

bool    DotColorMatchingItem::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;

	int32	Ver=10007;
	if(::Save(file,Ver)==false)
		return false;

	if(::Save(file,ExtraCreation)==false)
		return false;

	if(::Save(file,CenterBrightR)==false)
		return false;
	if(::Save(file,CenterBrightG)==false)
		return false;
	if(::Save(file,CenterBrightB)==false)
		return false;
	if(::Save(file,OutlineArea)==false)
		return false;
	if(::Save(file,FoldingArea)==false)
		return false;
	if(::Save(file,OutlineBlock)==false)
		return false;
	return true;
}
bool    DotColorMatchingItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(file,Ver)==false)
		return false;

	if(Ver>=10007){
		if(::Load(file,ExtraCreation)==false){
			return false;
		}
	}

	if(::Load(file,CenterBrightR)==false)
		return false;
	if(::Load(file,CenterBrightG)==false)
		return false;
	if(::Load(file,CenterBrightB)==false)
		return false;
	if(::Load(file,OutlineArea)==false)
		return false;
	if(::Load(file,FoldingArea)==false)
		return false;
	if(Ver>=10006){
		if(::Load(file,OutlineBlock)==false)
			return false;
	}
	else{
		OutlineBlock=false;
	}

	return true;
}

void	DotColorMatchingItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID() && ((DotColorMatchingItem *)Data)->GetPhaseCode()==GetPhaseCode()){
			DotColorMatchingInPage	*Ly=dynamic_cast<DotColorMatchingInPage *>(GetParentInPage());
			UndoElement<DotColorMatchingInPage>	*UPointer=new UndoElement<DotColorMatchingInPage>(Ly,&DotColorMatchingInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());

			DotColorMatchingThreshold	*WThr=GetThresholdW();
			WThr->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CopyThresholdOnly(*((DotColorMatchingItem *)Data),EdittedMemberID);
			//if(ScratchResultPeakH>0)
			//	WThr->ScratchDetectLevelH=ScratchResultPeakH;
			//if(ScratchResultPeakL>0)
			//	WThr->ScratchDetectLevelL=ScratchResultPeakL;
			SetItemName(((DotColorMatchingItem *)Data)->GetItemName());

			int	LayerNumb=GetLayerNumb();
			ImagePointerContainer ImageList;
			GetMasterBuffList(ImageList);
			CenterBrightR=CalcCenterBright(*ImageList[0],0,0,MasterSDRL,MasterSDRH);
			if(LayerNumb>=2){
				CenterBrightG=CalcCenterBright(*ImageList[1],0,0,MasterSDGL,MasterSDGH);
			}
			if(LayerNumb>=3){
				CenterBrightB=CalcCenterBright(*ImageList[2],0,0,MasterSDBL,MasterSDBH);
			}
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((DotColorMatchingItem *)Data)->GetLibID()){
			DotColorMatchingInPage	*Ly=dynamic_cast<DotColorMatchingInPage *>(GetParentInPage());
			UndoElement<DotColorMatchingInPage>	*UPointer=new UndoElement<DotColorMatchingInPage>(Ly,&DotColorMatchingInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			
			DotColorMatchingThreshold	*WThr=GetThresholdW();
			WThr->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CopyThresholdOnly(*((DotColorMatchingItem *)Data),EdittedMemberID);
			//if(ScratchResultPeakH>0)
			//	WThr->ScratchDetectLevelH=ScratchResultPeakH;
			//if(ScratchResultPeakL>0)
			//	WThr->ScratchDetectLevelL=ScratchResultPeakL;


			int	LayerNumb=GetLayerNumb();
			ImagePointerContainer ImageList;
			GetMasterBuffList(ImageList);
			CenterBrightR=CalcCenterBright(*ImageList[0],0,0,MasterSDRL,MasterSDRH);
			if(LayerNumb>=2){
				CenterBrightG=CalcCenterBright(*ImageList[1],0,0,MasterSDGL,MasterSDGH);
			}
			if(LayerNumb>=3){
				CenterBrightB=CalcCenterBright(*ImageList[2],0,0,MasterSDBL,MasterSDBH);
			}
		}
	}
	else if(Command==SetIndependentItemDataCommand_SetToOrigin){
		if(GetLibID()==((DotColorMatchingItem *)Data)->GetLibID()){
			//DotColorMatchingInPage	*Ly=dynamic_cast<DotColorMatchingInPage *>(GetParentInPage());
			GetThresholdW()->SetToOrigin();
		}
	}
}
void	DotColorMatchingItem::SetArea(const FlexArea &area)
{
	AlgorithmItemPI::SetArea(area);
	SavedArea	=area;
}
void	DotColorMatchingItem::CopyArea(DotColorMatchingItem &src)
{
	SetArea(src.GetArea());
}

QString	DotColorMatchingItem::GetComment(Type_ItemComment t)
{
	AlgorithmLibraryLevelContainer	*Lib=GetLibrary();
	if(Lib!=NULL){
		QString	Ret=Lib->GetLibName();
		delete	Lib;
		return Ret;
	}
	return /**/"";
}
int		DotColorMatchingItem::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 100;
}

void	DotColorMatchingItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	DotColorMatchingItem	*ASrc=dynamic_cast<DotColorMatchingItem *>(src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((DotColorMatchingBase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		CenterBrightR	=ASrc->CenterBrightR;
		CenterBrightG	=ASrc->CenterBrightG;
		CenterBrightB	=ASrc->CenterBrightB;
	}
}

ExeResult	DotColorMatchingItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	return ExecuteInitialAfterEditByThread(true,ExeID ,ThreadNo,Res,EInfo);
}

ExeResult	DotColorMatchingItem::ExecuteInitialAfterEditByThread(bool ThreadMode,int ExeID ,int ThreadNo
																,ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);
	
	//_CrtCheckMemory();
	if(GetID()==DbgID){
		DbgNumer++;
	}

	int	gap=((DotColorMatchingBase *)GetParentBase())->OmitZoneDot;
	if(GetLayersBase()->GetBootingLevel()>=1){
		gap=5;
	}
	GetArea().ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);
	if(GetArea().GetPatternByte()==10){
		return Ret;
	}
	if(EInfo.ApplicableArea==NULL || GetArea().CheckOverlap(EInfo.ApplicableArea)==true){
		//if((ExecuteInitialAfterEdit_Changed & ExecuteInitialAfterEdit_ChangedAlignment)!=0
		//|| (ExecuteInitialAfterEdit_Changed & ExecuteInitialAfterEdit_ChangedAlgorithm)!=0){
			GetArea().GetCenter(MasterCx,MasterCy);
			AVector=(AlignmentPacket2D *)GetAlignmentPointer(MasterCx,MasterCy);
			if(AVector!=NULL)
				AVector->Set(this);
		//}

		//if((ExecuteInitialAfterEdit_Changed & ExecuteInitialAfterEdit_ChangedMask)!=0
		//|| (ExecuteInitialAfterEdit_Changed & ExecuteInitialAfterEdit_ChangedAlgorithm)!=0){
			ImageBuffer *ImageMasterList[100];
			GetMasterBuffList(ImageMasterList);
			ImageBuffer *ImageMaster2List[100];
			memset(ImageMaster2List,0,sizeof(ImageMaster2List));
			DotColorMatchingBase	*ABase=(DotColorMatchingBase *)GetParentBase();
			if(0<=ABase->MasterNoFor2nd && ABase->MasterNoFor2nd<GetCountOnlyMasterBuff()){
				GetMasterBuffList(ABase->MasterNoFor2nd,ImageMaster2List);
			}

			FlexArea	Surround;
			Surround=GetArea();
			int	SurroundWidth=max(GetThresholdR()->AreaSearchX,GetThresholdR()->AreaSearchY)*2;
			Surround.FatAreaN(SurroundWidth);
			Surround-=GetArea();

			SurroundTop		=Surround;
			SurroundLeft	=Surround;
			SurroundRight	=Surround;
			SurroundBottom	=Surround;

			SurroundTop		.ClipArea(SurroundTop	.GetMinX(),SurroundTop	.GetMinY()	,SurroundTop.GetMaxX(),SurroundTop.GetMinY()+SurroundWidth);
			SurroundLeft	.ClipArea(SurroundLeft	.GetMinX(),SurroundLeft	.GetMinY()	,SurroundLeft.GetMinX()+SurroundWidth,SurroundLeft.GetMaxY());
			SurroundRight	.ClipArea(SurroundRight	.GetMaxX()-SurroundWidth,SurroundRight.GetMinY()	,SurroundRight.GetMaxX(),SurroundRight.GetMaxY());
			SurroundBottom	.ClipArea(SurroundBottom.GetMinX(),SurroundBottom.GetMaxY()-SurroundWidth	,SurroundBottom.GetMaxX(),SurroundBottom.GetMaxY());

			//double	SurroundCoef[3];
			//double	SurroundEdge[3][4];
			for(int Layer=0;Layer<GetLayerNumb();Layer++){
				double	SAvr;
				double	D1=SurroundTop	.GetVar(0,0,*ImageMasterList[Layer],SAvr);
				double	D2=SurroundLeft	.GetVar(0,0,*ImageMasterList[Layer],SAvr);
				double	D3=SurroundRight.GetVar(0,0,*ImageMasterList[Layer],SAvr);
				double	D4=SurroundBottom.GetVar(0,0,*ImageMasterList[Layer],SAvr);
				SurroundEdge[Layer][0]=D1;
				SurroundEdge[Layer][1]=D2;
				SurroundEdge[Layer][2]=D3;
				SurroundEdge[Layer][3]=D4;
				SurroundCoef[Layer]=Surround.GetVar(0,0,*ImageMasterList[Layer],SAvr)*max(max(D1,D2),max(D3,D4));
			}

			if(MasterPattern!=NULL){
				delete	[]MasterPattern;
			}
			int	MaxLen=max(GetArea().GetWidth(),GetArea().GetHeight());
			RotationDiv	=atan(4.5/((double)MaxLen));
			int	NCount=ceil(((DotColorMatchingBase *)GetParentBase())->MaxRotation*2.0*M_PI/360.0/RotationDiv);
			PatternCount=2*NCount+1;
			MasterPattern=new RotationPattern[PatternCount];
			CurrentMasterPattern=MasterPattern;

			MaxXLen=GetArea().GetWidth();
			MaxYLen=GetArea().GetHeight();

			SearchDotForBrightnessRange	=1;
			ThresholdPickupEdge			=10.0;
			ThresholdFlatPattern		=5.0;
			AlgorithmLibraryLevelContainer	*LibC=GetLibFromManagedCacheLib();	//GetLibrary();	//GetLibFromManagedCacheLib();
			if(LibC!=NULL){
				AlgorithmLibrary	*Lib=LibC->GetLibrary();
				if(Lib!=NULL){
					DotColorMatchingLibrary	*DLib=(DotColorMatchingLibrary *)Lib;
					SearchDotForBrightnessRange=DLib->SearchDotForBrightnessRange;
					ThresholdPickupEdge			=DLib->ThresholdPickupEdge;
					ThresholdFlatPattern		=DLib->ThresholdFlatPattern;
				}
				delete	LibC;
			}
			if(ThreadMode==true && PatternCount>=8){
				#pragma omp parallel
				{
					#pragma omp for
					for(int i=0;i<PatternCount;i++){
						double	Angle=(-NCount+i)*RotationDiv;
						MasterPattern[i].MakePatternOnAngle(this,Angle
															,((DotColorMatchingInPage *)Parent)->EdgeArea
															,ImageMasterList
															,ImageMaster2List
															,SurroundCoef
															,SearchDotForBrightnessRange
															,ThresholdPickupEdge
															,ThresholdFlatPattern);

						#pragma omp critical
						{
							MaxXLen=max(MaxXLen,MasterPattern[i].GetWidth ());
							MaxYLen=max(MaxYLen,MasterPattern[i].GetHeight());
						}
					}
				}
			}
			else{
				for(int i=0;i<PatternCount;i++){
					double	Angle=(-NCount+i)*RotationDiv;
					MasterPattern[i].MakePatternOnAngle(this,Angle
														,((DotColorMatchingInPage *)Parent)->EdgeArea
														,ImageMasterList
														,ImageMaster2List
														,SurroundCoef
														,SearchDotForBrightnessRange
														,ThresholdPickupEdge
														,ThresholdFlatPattern);
					MaxXLen=max(MaxXLen,MasterPattern[i].GetWidth ());
					MaxYLen=max(MaxYLen,MasterPattern[i].GetHeight());
				}
			}
			CurrentRotationPatternNo=(PatternCount-1)/2;
			CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
			
			//_CrtCheckMemory();
			int	iMapXByte	=(MaxXLen+24)/8;
			int	iMapYLen	=MaxYLen+16;

			if(iMapXByte!=MapXByte || iMapYLen!=MapYLen || Map==NULL || DummyMap==NULL){
				if(Map!=NULL){
					DeleteMatrixBuff(Map,MapYLen);
				}
				if(DummyMap!=NULL){
					DeleteMatrixBuff(DummyMap,MapYLen);
				}
				MapXByte=iMapXByte;
				MapYLen	=iMapYLen;
				Map		=MakeMatrixBuff(MapXByte,MapYLen);
				DummyMap=MakeMatrixBuff(MapXByte,MapYLen);
			}
			NeighborList.RemoveAll();
			for(AlgorithmItemPI	*L=Parent->GetFirstData();L!=NULL;L=L->GetNext()){
				if(L->GetID()==GetID())
					continue;
				DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(L);
				if(GetArea().CheckOverlap(&d->GetArea())==true){
					NeighborList.Add(d);
				}
			}

		//}
	}
	return Ret;
}


ExeResult	DotColorMatchingItem::ExecuteInitialAfterEditPost(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEditPost(ExeID ,ThreadNo,Res,EInfo);
	
	//_CrtCheckMemory();
	if(GetID()==DbgID){
		DbgNumer++;
	}

	if(GetArea().GetPatternByte()==10){
		return Ret;
	}
	if(EInfo.ApplicableArea==NULL || GetArea().CheckOverlap(EInfo.ApplicableArea)==true){
			
		ImageBuffer *ImageMasterList[100];
		GetMasterBuffList(ImageMasterList);

		CenterBrightR=CalcCenterBright(*ImageMasterList[0],0,0,MasterSDRL,MasterSDRH);
		if(GetLayerNumb()>=2){
			CenterBrightG=CalcCenterBright(*ImageMasterList[1],0,0,MasterSDGL,MasterSDGH);
		}
		if(GetLayerNumb()>=3){
			CenterBrightB=CalcCenterBright(*ImageMasterList[2],0,0,MasterSDBL,MasterSDBH);
		}
		CenterTargetBrightR=CenterBrightR;
		CenterTargetBrightG=CenterBrightG;
		CenterTargetBrightB=CenterBrightB;

		CalcAAA();

		double DAvr;
		MasterVariationR	=GetArea().GetVar(0,0,*ImageMasterList[0],DAvr);

		InitialScratch(ImageMasterList);
	}
}


void	DotColorMatchingItem::InitializeOnlyByImage(void)
{
	bool	ThreadMode=true;

	ImageBuffer *ImageMasterList[100];
	GetMasterBuffList(ImageMasterList);
	ImageBuffer *ImageMaster2List[100];
	DotColorMatchingBase	*ABase=(DotColorMatchingBase *)GetParentBase();
	if(0<=ABase->MasterNoFor2nd && ABase->MasterNoFor2nd<GetCountOnlyMasterBuff()){
		GetMasterBuffList(ABase->MasterNoFor2nd,ImageMaster2List);
	}
	int	NCount=ceil(((DotColorMatchingBase *)GetParentBase())->MaxRotation*2.0*M_PI/360.0/RotationDiv);
	MaxXLen=GetArea().GetWidth();
	MaxYLen=GetArea().GetHeight();

	if(ThreadMode==true){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<PatternCount;i++){
				double	Angle=(-NCount+i)*RotationDiv;
				MasterPattern[i].InitializeOnlyByImage ( ImageMasterList
														,ImageMaster2List
														,((DotColorMatchingInPage *)Parent)->EdgeArea
														,SearchDotForBrightnessRange
														,ThresholdPickupEdge
														,ThresholdFlatPattern);
				#pragma omp critical
				{
					MaxXLen=max(MaxXLen,MasterPattern[i].GetWidth ());
					MaxYLen=max(MaxYLen,MasterPattern[i].GetHeight());
				}
			}
		}
	}
	else{
		for(int i=0;i<PatternCount;i++){
			double	Angle=(-NCount+i)*RotationDiv;
			MasterPattern[i].InitializeOnlyByImage ( ImageMasterList
													,ImageMaster2List
													,((DotColorMatchingInPage *)Parent)->EdgeArea
													,SearchDotForBrightnessRange
													,ThresholdPickupEdge
													,ThresholdFlatPattern);
			MaxXLen=max(MaxXLen,MasterPattern[i].GetWidth ());
			MaxYLen=max(MaxYLen,MasterPattern[i].GetHeight());
		}
	}
	CurrentRotationPatternNo=(PatternCount-1)/2;
	CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];

	CenterBrightR=CalcCenterBright(*ImageMasterList[0],0,0,MasterSDRL,MasterSDRH);
	if(GetLayerNumb()>=2){
		CenterBrightG=CalcCenterBright(*ImageMasterList[1],0,0,MasterSDGL,MasterSDGH);
	}
	if(GetLayerNumb()>=3){
		CenterBrightB=CalcCenterBright(*ImageMasterList[2],0,0,MasterSDBL,MasterSDBH);
	}
	CenterTargetBrightR=CenterBrightR;
	CenterTargetBrightG=CenterBrightG;
	CenterTargetBrightB=CenterBrightB;

	CalcAAA();
}

void	DotColorMatchingItem::RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map)
{
	//if(Mode==_Reflection_Variety){
	//	FlexArea	&A=GetArea();
	//	int	N=A.GetFLineLen();
	//	int	MaxVariety[100];
	//	int	AvrNumb[100];
	//	for(int layer=0;layer<GetLayerNumb();layer++){
	//		MaxVariety[layer]=0;
	//		AvrNumb[layer]=0;
	//	}
	//	
	//	for(int i=0;i<N;i++){
	//		int	y	=A.GetFLineAbsY(i);
	//		int	x1	=A.GetFLineLeftX(i);
	//		int	Numb=A.GetFLineNumb(i);
	//		for(int layer=0;layer<GetLayerNumb();layer++){
	//			ConstMapBufferList	*CMap=Map[layer];
	//
	//			const BYTE	*m=(*CMap->GetMapBuffer())[y];
	//			int	iAdded=0;
	//			for(int n=0;n<Numb;n++){
	//				MaxVariety[layer]=max(MaxVariety[layer],m[x1+n]);
	//			}
	//			AvrNumb[layer]	+=Numb;
	//		}
	//	}
	//}
}
RotationPattern	*DotColorMatchingItem::GetRotationPattern(int PatternNo)
{
	if(MasterPattern!=NULL && PatternNo<PatternCount){
		return &MasterPattern[PatternNo];
	}
	return NULL;
}

bool	DotColorMatchingItem::HasHOrVLine(void)
{
	if(MasterPattern!=NULL){
		RotationPattern	*R=&MasterPattern[PatternCount/2];
		if(R!=NULL && (R->CountVLine>0 || R->CountHLine>0))
			return true;
	}
	return false;
}
bool	DotColorMatchingItem::HasHAndVLine(void)
{
	if(MasterPattern!=NULL){
		RotationPattern	*R=&MasterPattern[PatternCount/2];
		if(R!=NULL && R->CountVLine>0 && R->CountHLine>0)
			return true;
	}
	return false;
}


int	DotColorMatchingItem::GetDivPointY(FlexArea &MaskArea,int X,int StartY,int EndY ,bool InsideDown)
{
	if(InsideDown==true){
		for(int y=StartY;y<EndY;y++){
			if(MaskArea.IsInclude(X,y)==false && MaskArea.IsInclude(X,y+1)==true){
				return y;
			}
		}
	}
	else{
		for(int y=StartY;y>=EndY;y--){
			if(MaskArea.IsInclude(X,y)==true && MaskArea.IsInclude(X,y+1)==false){
				return y;
			}
		}
	}
	return -1;
}

int	DotColorMatchingItem::GetDivPointX(FlexArea &MaskArea,int Y,int StartX,int EndX ,bool InsideRight)
{
	if(InsideRight==true){
		for(int x=StartX;x<EndX;x++){
			if(MaskArea.IsInclude(x,Y)==false && MaskArea.IsInclude(x+1,Y)==true){
				return x;
			}
		}
	}
	else{
		for(int x=StartX;x>=EndX;x--){
			if(MaskArea.IsInclude(x,Y)==true && MaskArea.IsInclude(x+1,Y)==false){
				return x;
			}
		}
	}
	return -1;
}

void	DotColorMatchingItem::MakeHVLine(FlexArea &MaskArea)
{
	int	LineLength		=((DotColorMatchingBase *)GetParentBase())->HookingLineLength;
	int	EdgeMergin		=((DotColorMatchingBase *)GetParentBase())->EdgeMerginForLine;
	int	MaxCountOutline	=((DotColorMatchingBase *)GetParentBase())->MaxCountOutline;
	int	Skip=2;
	if(GetID()==DbgID)
		DbgNumer++;

	ImageBuffer *ImageMasterList[100];
	GetMasterBuffList(ImageMasterList);

	int	LineLength2=LineLength/2;
	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);

	double	EndRate=0.15;
	int	StartX,StartY,EndX,EndY;

	bool	FoundTop1=false;
	bool	FoundTop2=false;
	bool	VFlag=false;
	bool	HFlag=false;
	int	X1=x1+(x2-x1)*EndRate;
	StartY	=y1-LineLength2;
	EndY	=y2+LineLength2;
	{
		int	y=GetDivPointY(MaskArea,X1,StartY,EndY,true);
		if(y>0){
			int	ty11=GetDivPointY(MaskArea,X1-5,StartY,EndY,true);
			int	ty12=GetDivPointY(MaskArea,X1-4,StartY,EndY,true);
			int	ty13=GetDivPointY(MaskArea,X1-3,StartY,EndY,true);
			int	ty21=GetDivPointY(MaskArea,X1+3,StartY,EndY,true);
			int	ty22=GetDivPointY(MaskArea,X1+4,StartY,EndY,true);
			int	ty23=GetDivPointY(MaskArea,X1+5,StartY,EndY,true);
			int	ty1=(ty11+ty12+ty13)/3;
			int	ty2=(ty21+ty22+ty23)/3;
			if(ty1>0 && ty2>0 && abs(ty1-ty2)<=8){
				FoundTop1=true;
				VFlag=true;
			}
		}
	}
	int	X2=x1+(x2-x1)*(1.0-EndRate);
	{
		int	y=GetDivPointY(MaskArea,X2,StartY,EndY,true);
		if(y>0){
			int	ty11=GetDivPointY(MaskArea,X2-5,StartY,EndY,true);
			int	ty12=GetDivPointY(MaskArea,X2-4,StartY,EndY,true);
			int	ty13=GetDivPointY(MaskArea,X2-3,StartY,EndY,true);
			int	ty21=GetDivPointY(MaskArea,X2+3,StartY,EndY,true);
			int	ty22=GetDivPointY(MaskArea,X2+4,StartY,EndY,true);
			int	ty23=GetDivPointY(MaskArea,X2+5,StartY,EndY,true);
			int	ty1=(ty11+ty12+ty13)/3;
			int	ty2=(ty21+ty22+ty23)/3;
			if(ty1>0 && ty2>0 && abs(ty1-ty2)<=8){
				FoundTop2=true;
				VFlag=true;
			}
		}
	}
	if(FoundTop1==false && FoundTop2==true){
		int	X11=x1+(x2-x1)*0.5;
		{
			int	y=GetDivPointY(MaskArea,X11,StartY,EndY,true);
			if(y>0){
				int	ty11=GetDivPointY(MaskArea,X11-5,StartY,EndY,true);
				int	ty12=GetDivPointY(MaskArea,X11-4,StartY,EndY,true);
				int	ty13=GetDivPointY(MaskArea,X11-3,StartY,EndY,true);
				int	ty21=GetDivPointY(MaskArea,X11+3,StartY,EndY,true);
				int	ty22=GetDivPointY(MaskArea,X11+4,StartY,EndY,true);
				int	ty23=GetDivPointY(MaskArea,X11+5,StartY,EndY,true);
				int	ty1=(ty11+ty12+ty13)/3;
				int	ty2=(ty21+ty22+ty23)/3;
				if(ty1>0 && ty2>0 && abs(ty1-ty2)<=8){
					FoundTop1=true;
					VFlag=true;
				}
			}
		}
	}
	else
	if(FoundTop1==true && FoundTop2==false){
		int	X21=x1+(x2-x1)*0.5;
		{
			int	y=GetDivPointY(MaskArea,X21,StartY,EndY,true);
			if(y>0){
				int	ty11=GetDivPointY(MaskArea,X21-5,StartY,EndY,true);
				int	ty12=GetDivPointY(MaskArea,X21-4,StartY,EndY,true);
				int	ty13=GetDivPointY(MaskArea,X21-3,StartY,EndY,true);
				int	ty21=GetDivPointY(MaskArea,X21+3,StartY,EndY,true);
				int	ty22=GetDivPointY(MaskArea,X21+4,StartY,EndY,true);
				int	ty23=GetDivPointY(MaskArea,X21+5,StartY,EndY,true);
				int	ty1=(ty11+ty12+ty13)/3;
				int	ty2=(ty21+ty22+ty23)/3;
				if(ty1>0 && ty2>0 && abs(ty1-ty2)<=8){
					FoundTop2=true;
					VFlag=true;
				}
			}
		}
	}
	else
	if(FoundTop1==false && FoundTop2==false){
		bool	FoundBottom1=false;
		bool	FoundBottom2=false;
		StartY	=y2+LineLength2;
		EndY	=y1-LineLength2;
		{
			int	y=GetDivPointY(MaskArea,X1,StartY,EndY,false);
			if(y>0){
				int	ty11=GetDivPointY(MaskArea,X1-5,StartY,EndY,false);
				int	ty12=GetDivPointY(MaskArea,X1-4,StartY,EndY,false);
				int	ty13=GetDivPointY(MaskArea,X1-3,StartY,EndY,false);
				int	ty21=GetDivPointY(MaskArea,X1+3,StartY,EndY,false);
				int	ty22=GetDivPointY(MaskArea,X1+4,StartY,EndY,false);
				int	ty23=GetDivPointY(MaskArea,X1+5,StartY,EndY,false);
				int	ty1=(ty11+ty12+ty13)/3;
				int	ty2=(ty21+ty22+ty23)/3;
				if(ty1>0 && ty2>0 && abs(ty1-ty2)<=8){
					FoundBottom1=true;
				}
			}
		}
		{
			int	y=GetDivPointY(MaskArea,X2,StartY,EndY,false);
			if(y>0){
				int	ty11=GetDivPointY(MaskArea,X2-5,StartY,EndY,false);
				int	ty12=GetDivPointY(MaskArea,X2-4,StartY,EndY,false);
				int	ty13=GetDivPointY(MaskArea,X2-3,StartY,EndY,false);
				int	ty21=GetDivPointY(MaskArea,X2+3,StartY,EndY,false);
				int	ty22=GetDivPointY(MaskArea,X2+4,StartY,EndY,false);
				int	ty23=GetDivPointY(MaskArea,X2+5,StartY,EndY,false);
				int	ty1=(ty11+ty12+ty13)/3;
				int	ty2=(ty21+ty22+ty23)/3;
				if(ty1>0 && ty2>0 && abs(ty1-ty2)<=8){
					FoundBottom2=true;
				}
			}
		}
		if(FoundBottom1==false && FoundBottom2==true){
			int	X11=x1+(x2-x1)*0.5;
			int	y=GetDivPointY(MaskArea,X11,StartY,EndY,false);
			if(y>0){
				int	ty11=GetDivPointY(MaskArea,X11-5,StartY,EndY,false);
				int	ty12=GetDivPointY(MaskArea,X11-4,StartY,EndY,false);
				int	ty13=GetDivPointY(MaskArea,X11-3,StartY,EndY,false);
				int	ty21=GetDivPointY(MaskArea,X11+3,StartY,EndY,false);
				int	ty22=GetDivPointY(MaskArea,X11+4,StartY,EndY,false);
				int	ty23=GetDivPointY(MaskArea,X11+5,StartY,EndY,false);
				int	ty1=(ty11+ty12+ty13)/3;
				int	ty2=(ty21+ty22+ty23)/3;
				if(ty1>0 && ty2>0 && abs(ty1-ty2)<=8){
					FoundBottom1=true;
				}
			}
		}
		else
		if(FoundBottom1==true && FoundBottom2==false){
			int	X21=x1+(x2-x1)*0.5;
			int	y=GetDivPointY(MaskArea,X21,StartY,EndY,false);
			if(y>0){
				int	ty11=GetDivPointY(MaskArea,X21-5,StartY,EndY,false);
				int	ty12=GetDivPointY(MaskArea,X21-4,StartY,EndY,false);
				int	ty13=GetDivPointY(MaskArea,X21-3,StartY,EndY,false);
				int	ty21=GetDivPointY(MaskArea,X21+3,StartY,EndY,false);
				int	ty22=GetDivPointY(MaskArea,X21+4,StartY,EndY,false);
				int	ty23=GetDivPointY(MaskArea,X21+5,StartY,EndY,false);
				int	ty1=(ty11+ty12+ty13)/3;
				int	ty2=(ty21+ty22+ty23)/3;
				if(ty1>0 && ty2>0 && abs(ty1-ty2)<=8){
					FoundBottom2=true;
				}
			}
		}
	}
	bool	FoundLeft1=false;
	bool	FoundLeft2=false;
	int	Y1=y1+(y2-y1)*EndRate;
	StartX	=x1-LineLength2;
	EndX	=x2+LineLength2;
	{
		int	x=GetDivPointX(MaskArea,Y1,StartX,EndX,true);
		if(x>0){
			int	tx11=GetDivPointX(MaskArea,Y1-5,StartX,EndX,true);
			int	tx12=GetDivPointX(MaskArea,Y1-4,StartX,EndX,true);
			int	tx13=GetDivPointX(MaskArea,Y1-3,StartX,EndX,true);
			int	tx21=GetDivPointX(MaskArea,Y1+3,StartX,EndX,true);
			int	tx22=GetDivPointX(MaskArea,Y1+4,StartX,EndX,true);
			int	tx23=GetDivPointX(MaskArea,Y1+5,StartX,EndX,true);
			int	tx1=(tx11+tx12+tx13)/3;
			int	tx2=(tx21+tx22+tx23)/3;
			if(tx1>0 && tx2>0 && abs(tx1-tx2)<=8){
				FoundLeft1=true;
				HFlag=true;
			}
		}
	}
	int	Y2=y1+(y2-y1)*(1.0-EndRate);
	{
		int	x=GetDivPointX(MaskArea,Y2,StartX,EndX,true);
		if(x>0){
			int	tx11=GetDivPointX(MaskArea,Y2-5,StartX,EndX,true);
			int	tx12=GetDivPointX(MaskArea,Y2-4,StartX,EndX,true);
			int	tx13=GetDivPointX(MaskArea,Y2-3,StartX,EndX,true);
			int	tx21=GetDivPointX(MaskArea,Y2+3,StartX,EndX,true);
			int	tx22=GetDivPointX(MaskArea,Y2+4,StartX,EndX,true);
			int	tx23=GetDivPointX(MaskArea,Y2+5,StartX,EndX,true);
			int	tx1=(tx11+tx12+tx13)/3;
			int	tx2=(tx21+tx22+tx23)/3;
			if(tx1>0 && tx2>0 && abs(tx1-tx2)<=8){
				FoundLeft2=true;
				HFlag=true;
			}
		}
	}
	if(FoundLeft1==false && FoundLeft2==true){
		int	Y11=y1+(y2-y1)*0.5;
		int	x=GetDivPointX(MaskArea,Y11,StartX,EndX,true);
		if(x>0){
			int	tx11=GetDivPointX(MaskArea,Y11-5,StartX,EndX,true);
			int	tx12=GetDivPointX(MaskArea,Y11-4,StartX,EndX,true);
			int	tx13=GetDivPointX(MaskArea,Y11-3,StartX,EndX,true);
			int	tx21=GetDivPointX(MaskArea,Y11+3,StartX,EndX,true);
			int	tx22=GetDivPointX(MaskArea,Y11+4,StartX,EndX,true);
			int	tx23=GetDivPointX(MaskArea,Y11+5,StartX,EndX,true);
			int	tx1=(tx11+tx12+tx13)/3;
			int	tx2=(tx21+tx22+tx23)/3;
			if(tx1>0 && tx2>0 && abs(tx1-tx2)<=8){
				FoundLeft1=true;
				HFlag=true;
			}
		}
	}
	else
	if(FoundLeft1==true && FoundLeft2==false){
		int	Y21=y1+(y2-y1)*0.5;
		int	x=GetDivPointX(MaskArea,Y21,StartX,EndX,true);
		if(x>0){
			int	tx11=GetDivPointX(MaskArea,Y21-5,StartX,EndX,true);
			int	tx12=GetDivPointX(MaskArea,Y21-4,StartX,EndX,true);
			int	tx13=GetDivPointX(MaskArea,Y21-3,StartX,EndX,true);
			int	tx21=GetDivPointX(MaskArea,Y21+3,StartX,EndX,true);
			int	tx22=GetDivPointX(MaskArea,Y21+4,StartX,EndX,true);
			int	tx23=GetDivPointX(MaskArea,Y21+5,StartX,EndX,true);
			int	tx1=(tx11+tx12+tx13)/3;
			int	tx2=(tx21+tx22+tx23)/3;
			if(tx1>0 && tx2>0 && abs(tx1-tx2)<=8){
				FoundLeft2=true;
				HFlag=true;
			}
		}
	}
	if(FoundLeft1==false && FoundLeft2==false){
		bool	FoundRight1	=false;
		bool	FoundRight2	=false;
		StartX	=x2+LineLength2;
		EndX	=x1-LineLength2;
		{
			int	x=GetDivPointX(MaskArea,Y1,StartX,EndX,false);
			if(x>0){
				int	tx11=GetDivPointX(MaskArea,Y1-5,StartX,EndX,false);
				int	tx12=GetDivPointX(MaskArea,Y1-4,StartX,EndX,false);
				int	tx13=GetDivPointX(MaskArea,Y1-3,StartX,EndX,false);
				int	tx21=GetDivPointX(MaskArea,Y1+3,StartX,EndX,false);
				int	tx22=GetDivPointX(MaskArea,Y1+4,StartX,EndX,false);
				int	tx23=GetDivPointX(MaskArea,Y1+5,StartX,EndX,false);
				int	tx1=(tx11+tx12+tx13)/3;
				int	tx2=(tx21+tx22+tx23)/3;
				if(tx1>0 && tx2>0 && abs(tx1-tx2)<=8){
					FoundRight1=true;
				}
			}
		}
		{
			int	x=GetDivPointX(MaskArea,Y2,StartX,EndX,false);
			if(x>0){
				int	tx11=GetDivPointX(MaskArea,Y2-5,StartX,EndX,false);
				int	tx12=GetDivPointX(MaskArea,Y2-4,StartX,EndX,false);
				int	tx13=GetDivPointX(MaskArea,Y2-3,StartX,EndX,false);
				int	tx21=GetDivPointX(MaskArea,Y2+3,StartX,EndX,false);
				int	tx22=GetDivPointX(MaskArea,Y2+4,StartX,EndX,false);
				int	tx23=GetDivPointX(MaskArea,Y2+5,StartX,EndX,false);
				int	tx1=(tx11+tx12+tx13)/3;
				int	tx2=(tx21+tx22+tx23)/3;
				if(tx1>0 && tx2>0 && abs(tx1-tx2)<=8){
					FoundRight2=true;
				}
			}
		}
		if(FoundRight1==false && FoundRight2==true){
			int	Y11=y1+(y2-y1)*0.5;
			int	x=GetDivPointX(MaskArea,Y11,StartX,EndX,false);
			if(x>0){
				int	tx11=GetDivPointX(MaskArea,Y11-5,StartX,EndX,false);
				int	tx12=GetDivPointX(MaskArea,Y11-4,StartX,EndX,false);
				int	tx13=GetDivPointX(MaskArea,Y11-3,StartX,EndX,false);
				int	tx21=GetDivPointX(MaskArea,Y11+3,StartX,EndX,false);
				int	tx22=GetDivPointX(MaskArea,Y11+4,StartX,EndX,false);
				int	tx23=GetDivPointX(MaskArea,Y11+5,StartX,EndX,false);
				int	tx1=(tx11+tx12+tx13)/3;
				int	tx2=(tx21+tx22+tx23)/3;
				if(tx1>0 && tx2>0 && abs(tx1-tx2)<=8){
					FoundRight1=true;
				}
			}
		}
		else
		if(FoundRight1==true && FoundRight2==false){
			int	Y21=y1+(y2-y1)*0.5;
			int	x=GetDivPointX(MaskArea,Y21,StartX,EndX,false);
			if(x>0){
				int	tx11=GetDivPointX(MaskArea,Y21-5,StartX,EndX,false);
				int	tx12=GetDivPointX(MaskArea,Y21-4,StartX,EndX,false);
				int	tx13=GetDivPointX(MaskArea,Y21-3,StartX,EndX,false);
				int	tx21=GetDivPointX(MaskArea,Y21+3,StartX,EndX,false);
				int	tx22=GetDivPointX(MaskArea,Y21+4,StartX,EndX,false);
				int	tx23=GetDivPointX(MaskArea,Y21+5,StartX,EndX,false);
				int	tx1=(tx11+tx12+tx13)/3;
				int	tx2=(tx21+tx22+tx23)/3;
				if(tx1>0 && tx2>0 && abs(tx1-tx2)<=8){
					FoundRight2=true;
				}
			}
		}
	}


	for(int i=0;i<PatternCount;i++){
		if(MasterPattern[i].VLine!=NULL){
			delete	[]MasterPattern[i].VLine;
			
		}
		MasterPattern[i].VLine=new DotColorMatchingVLine[MaxCountOutline];
	}

	double	IsoX=(x2-x1)/((double)(MaxCountOutline+1));
	for(int xn=0;xn<MaxCountOutline;xn++){
		int	X=x1+IsoX*(xn+1);

		int	y=GetDivPointY(MaskArea,X,StartY,EndY,VFlag);
		if(y>0){
			int	ty11=GetDivPointY(MaskArea,X-5,StartY,EndY,VFlag);
			int	ty12=GetDivPointY(MaskArea,X-4,StartY,EndY,VFlag);
			int	ty13=GetDivPointY(MaskArea,X-3,StartY,EndY,VFlag);
			int	ty21=GetDivPointY(MaskArea,X+3,StartY,EndY,VFlag);
			int	ty22=GetDivPointY(MaskArea,X+4,StartY,EndY,VFlag);
			int	ty23=GetDivPointY(MaskArea,X+5,StartY,EndY,VFlag);
			int	ty1=(ty11+ty12+ty13)/3;
			int	ty2=(ty21+ty22+ty23)/3;
			if(ty1>0 && ty2>0 && abs(ty1-ty2)<=IsoX){
				for(int i=0;i<PatternCount;i++){
					MasterPattern[i].VLine[xn].VLineX=X;
					MasterPattern[i].VLine[xn].VLineY1=y-LineLength2+((VFlag==true)?-EdgeMergin:EdgeMergin);
					MasterPattern[i].VLine[xn].VLineY2=y+LineLength2+((VFlag==true)?-EdgeMergin:EdgeMergin);
					if(VFlag==true){
						MasterPattern[i].VLine[xn].VLineBackY1=MasterPattern[i].VLine[xn].VLineY2;
						MasterPattern[i].VLine[xn].VLineBackY2=MasterPattern[i].VLine[xn].VLineBackY1+LineLength;
					}
					else{
						MasterPattern[i].VLine[xn].VLineBackY2=MasterPattern[i].VLine[xn].VLineY1;
						MasterPattern[i].VLine[xn].VLineBackY1=MasterPattern[i].VLine[xn].VLineBackY2-LineLength;
					}
					ImageBuffer	*Master=ImageMasterList[MasterPattern[i].AdoptLayer];
					MasterPattern[i].VLine[xn].MakeDot(*Master,MasterPattern[i].Angle,MasterCx,MasterCy
													,this,Skip);
					if(MasterPattern[i].VLine[xn].IsEffevtive()==true){
						for(int tn=0;tn<xn;tn++){
							if(MasterPattern[i].VLine[tn].VLineX==MasterPattern[i].VLine[xn].VLineX){
								delete	[]MasterPattern[i].VLine[xn].VDot;
								MasterPattern[i].VLine[xn].VDot=NULL;
							}
						}
					}
				}
			}
		}
	}
	for(int i=0;i<PatternCount;i++){
		MasterPattern[i].CountVLine=0;
		for(int xn=0;xn<MaxCountOutline;xn++){
			if(MasterPattern[i].VLine[xn].IsEffevtive()==true){
				MasterPattern[i].CountVLine++;
			}
		}
		if(MasterPattern[i].CountVLine==0){
			delete	[]MasterPattern[i].VLine;
			MasterPattern[i].VLine=NULL;
		}
		else{
			DotColorMatchingVLine	*VDim=new DotColorMatchingVLine[MasterPattern[i].CountVLine];
			int	n=0;
			for(int xn=0;xn<MaxCountOutline;xn++){
				if(MasterPattern[i].VLine[xn].IsEffevtive()==true){
					VDim[n]=MasterPattern[i].VLine[xn];
					n++;
				}
			}
			delete	[]MasterPattern[i].VLine;
			MasterPattern[i].VLine=VDim;
		}
	}

	
	for(int i=0;i<PatternCount;i++){
		if(MasterPattern[i].HLine!=NULL){
			delete	[]MasterPattern[i].HLine;
			
		}
		MasterPattern[i].HLine=new DotColorMatchingHLine[MaxCountOutline];
	}

	double	IsoY=(y2-y1)/((double)(MaxCountOutline+1));
	for(int yn=0;yn<MaxCountOutline;yn++){
		int	Y=y1+IsoY*(yn+1);

		int	x=GetDivPointX(MaskArea,Y,StartX,EndX,HFlag);
		if(x>0){
			int	tx11=GetDivPointX(MaskArea,Y-5,StartX,EndX,HFlag);
			int	tx12=GetDivPointX(MaskArea,Y-4,StartX,EndX,HFlag);
			int	tx13=GetDivPointX(MaskArea,Y-3,StartX,EndX,HFlag);
			int	tx21=GetDivPointX(MaskArea,Y+3,StartX,EndX,HFlag);
			int	tx22=GetDivPointX(MaskArea,Y+4,StartX,EndX,HFlag);
			int	tx23=GetDivPointX(MaskArea,Y+5,StartX,EndX,HFlag);
			int	tx1=(tx11+tx12+tx13)/3;
			int	tx2=(tx21+tx22+tx23)/3;
			if(tx1>0 && tx2>0 && abs(tx1-tx2)<=IsoY){
				for(int i=0;i<PatternCount;i++){
					MasterPattern[i].HLine[yn].HLineX1=x-LineLength2+((HFlag==true)?-EdgeMergin:EdgeMergin);
					MasterPattern[i].HLine[yn].HLineX2=x+LineLength2+((HFlag==true)?-EdgeMergin:EdgeMergin);
					MasterPattern[i].HLine[yn].HLineY =Y;
					if(HFlag==true){
						MasterPattern[i].HLine[yn].HLineBackX1=MasterPattern[i].HLine[yn].HLineX2;
						MasterPattern[i].HLine[yn].HLineBackX2=MasterPattern[i].HLine[yn].HLineBackX1+LineLength;
					}
					else{
						MasterPattern[i].HLine[yn].HLineBackX2=MasterPattern[i].HLine[yn].HLineX1;
						MasterPattern[i].HLine[yn].HLineBackX1=MasterPattern[i].HLine[yn].HLineBackX2-LineLength;
					}
					ImageBuffer	*Master=ImageMasterList[MasterPattern[i].AdoptLayer];
					MasterPattern[i].HLine[yn].MakeDot(*Master,MasterPattern[i].Angle,MasterCx,MasterCy
													,this,Skip);
					if(MasterPattern[i].HLine[yn].IsEffevtive()==true){
						for(int tn=0;tn<yn;tn++){
							if(MasterPattern[i].HLine[tn].HLineY==MasterPattern[i].HLine[yn].HLineY){
								delete	[]MasterPattern[i].HLine[yn].HDot;
								MasterPattern[i].HLine[yn].HDot=NULL;
							}
						}
					}
				}
			}
		}
	}
	for(int i=0;i<PatternCount;i++){
		MasterPattern[i].CountHLine=0;
		for(int yn=0;yn<MaxCountOutline;yn++){
			if(MasterPattern[i].HLine[yn].IsEffevtive()==true){
				MasterPattern[i].CountHLine++;
			}
		}
		if(MasterPattern[i].CountHLine==0){
			delete	[]MasterPattern[i].HLine;
			MasterPattern[i].HLine=NULL;
		}
		else{
			DotColorMatchingHLine	*HDim=new DotColorMatchingHLine[MasterPattern[i].CountHLine];
			int	n=0;
			for(int yn=0;yn<MaxCountOutline;yn++){
				if(MasterPattern[i].HLine[yn].IsEffevtive()==true){
					HDim[n]=MasterPattern[i].HLine[yn];
					n++;
				}
			}
			delete	[]MasterPattern[i].HLine;
			MasterPattern[i].HLine=HDim;
		}
	}
}

void	DotColorMatchingItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	DotColorMatchingDrawAttr	*BAttr=dynamic_cast<DotColorMatchingDrawAttr *>(Attr);
	if(BAttr!=NULL){
		DotColorMatchingDrawAttr	TmpAttr;
		TmpAttr=*BAttr;
		//QColor	BuffColor=BAttr->NormalColor;
		switch(GetLibID()&7){
			case 0:	TmpAttr.NormalColor=BAttr->DotColorMatchingColor0;	break;
			case 1:	TmpAttr.NormalColor=BAttr->DotColorMatchingColor1;	break;
			case 2:	TmpAttr.NormalColor=BAttr->DotColorMatchingColor2;	break;
			case 3:	TmpAttr.NormalColor=BAttr->DotColorMatchingColor3;	break;
			case 4:	TmpAttr.NormalColor=BAttr->DotColorMatchingColor4;	break;
			case 5:	TmpAttr.NormalColor=BAttr->DotColorMatchingColor5;	break;
			case 6:	TmpAttr.NormalColor=BAttr->DotColorMatchingColor6;	break;
			case 7:	TmpAttr.NormalColor=BAttr->DotColorMatchingColor7;	break;
		}
		if(MatchingType==1){
			TmpAttr.NormalColor=qRgba(TmpAttr.NormalColor.red()*0.7
									, TmpAttr.NormalColor.green()*0.7
									, TmpAttr.NormalColor.blue()*1.5
									, TmpAttr.NormalColor.alpha());
		}
		RotationPattern	*R=NULL;
		if(MasterPattern!=NULL){
			R=&MasterPattern[CurrentRotationPatternNo];
		}
		if(BAttr->ModeShowArea==true){
			AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		}
		if(BAttr->ModeShowRotation==true){
			if(R!=NULL){
				AlgorithmItemPI::DrawArea(*R,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
			}
			else{
				AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
			}
		}
		if(BAttr->ModeShowDiv==true){
			if(R!=NULL){
				for(FlexAreaCoef *a=R->DivArea.GetFirst();a!=NULL;a=a->GetNext()){
					AlgorithmItemPI::DrawArea(*a,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
				}
			}
			else{
				AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
			}
		}
		if(BAttr->ModeShowFlat==true){
			if(R!=NULL){
				AlgorithmItemPI::DrawArea(R->DetailSearchArea,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
			}
			else{
				AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
			}
		}
		if(BAttr->ModeShowBackGround==true){
			if(R!=NULL){
				AlgorithmItemPI::DrawArea(R->BackGround,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
			}
			else{
				AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
			}
		}
		if(R!=NULL){
			for(int i=0;i<R->CountVLine;i++){
				if(R->VLine[i].IsEffevtive()==true){
					R->VLine[i].Draw(pnt,movx,movy,ZoomRate);
				}
			}
			for(int i=0;i<R->CountHLine;i++){
				if(R->HLine[i].IsEffevtive()==true){
					R->HLine[i].Draw(pnt,movx,movy,ZoomRate);
				}
			}
		}
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	DotColorMatchingItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			if(MasterPattern!=NULL){
				MasterPattern[CurrentRotationPatternNo].Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
			}
			else{
				GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
			}
			if(Res->IsOk()==false && ZoomRate>1.0){
				int	kx=(MasterCx+MovX)*ZoomRate;
				int	ky=(MasterCy+MovY)*ZoomRate;
				if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
					QRect	rect(0,0,IData.width(),IData.height());
					PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/" Sft(")+QString::number((int)Res->GetTotalShiftedX())+QString(/**/",")+QString::number((int)Res->GetTotalShiftedY())+QString(/**/")")
						+QString(/**/" ID:")+QString::number((int)GetID())
						,&rect);
					if(Res->GetError()==2){
						PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"N: L=")+QString::number(Res->GetResult1()) +QString(/**/" H=")+QString::number(Res->GetResult2())
							,&rect);
					}
					else if(Res->GetError()==3){
						PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"B: L=")+QString::number(Res->GetResult1()) +QString(/**/" H=")+QString::number(Res->GetResult2())
							,&rect);
					}
				}
			}
		}
	}
}

bool	DotColorMatchingItem::IsCoeffType(void)
{
	for(int i=0;i<PatternCount;i++){
		if(MasterPattern[i].DivArea.IsNull()==false){
			return true;
		}
	}
	return false;
}

double	DotColorMatchingItem::GetMaxSelfMatch(int &_dx ,int &_dy)
{
	ImageBuffer *ImageMasterList[100];
	GetMasterBuffList(ImageMasterList);

	int	SearchAreaX=GetThresholdR()->AreaSearchX;
	int	SearchAreaY=GetThresholdR()->AreaSearchY;
	int	Neighbor=5;
	RotationPattern	*R=&MasterPattern[PatternCount/2];

	struct	XYRateStruct	*SList=new struct	XYRateStruct[(2*SearchAreaX+1)*(2*SearchAreaY+1)];

	int	SListNumb=0;
	for(int dy=-SearchAreaY;dy<=SearchAreaY;dy+=2){
		for(int dx=-SearchAreaX;dx<=SearchAreaX;dx+=2){
			if(-Neighbor<=dy && dy<=Neighbor && -Neighbor<=dx && dx<=Neighbor)
				continue;

			SList[SListNumb].Dx=dx;
			SList[SListNumb].Dy=dy;
			SListNumb++;
		}
	}

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<SListNumb;i++){
			double	D=R->GetMaxSelfMatch(ImageMasterList[R->AdoptLayer],SList[i].Dx ,SList[i].Dy);
			SList[i].Rate=D;
		}
	}
	double	MaxD	=0;
	int		MaxDx	=0;
	int		MaxDy	=0;
	for(int i=0;i<SListNumb;i++){
		if(MaxD<SList[i].Rate){
			MaxD=SList[i].Rate;
			MaxDx=SList[i].Dx;
			MaxDy=SList[i].Dy;
		}
	}
	int		tMaxDx	=0;
	int		tMaxDy	=0;
	for(int dy=-1;dy<=1;dy++){
		for(int dx=-1;dx<=1;dx++){
			if(dx==0 && dy==0)
				continue;
			double	D=R->GetMaxSelfMatch(ImageMasterList[R->AdoptLayer],MaxDx+dx ,MaxDy+dy);
			if(MaxD<D){
				MaxD=D;
				tMaxDx=dx;
				tMaxDy=dy;
			}
		}
	}
	MaxDx+=tMaxDx;
	MaxDy+=tMaxDy;
	delete	[]SList;

	_dx=MaxDx;
	_dy=MaxDy;
	return MaxD;
}
void	DotColorMatchingItem::UpdateThreshold(int LearningMenuID ,LearningResource &LRes)
{
	DotColorMatchingThreshold	*WThr=GetThresholdW();

	if(LearningMenuID==LearningMenu_DotColorMatching_OK_BroadByBrightness){
		WThr->Broad.BrightWidthRL	=Clipping((int)(WThr->Broad.BrightWidthRL*1.3+5),0,255);
		WThr->Broad.BrightWidthRH	=Clipping((int)(WThr->Broad.BrightWidthRH*1.3+5),0,255);
		WThr->Broad.BrightWidthGL	=Clipping((int)(WThr->Broad.BrightWidthGL*1.3+5),0,255);
		WThr->Broad.BrightWidthGH	=Clipping((int)(WThr->Broad.BrightWidthGH*1.3+5),0,255);
		WThr->Broad.BrightWidthBL	=Clipping((int)(WThr->Broad.BrightWidthBL*1.3+5),0,255);
		WThr->Broad.BrightWidthBH	=Clipping((int)(WThr->Broad.BrightWidthBH*1.3+5),0,255);
		WThr->Broad.RThrOffsetL		=Clipping((int)(WThr->Broad.RThrOffsetL*1.3+5	),-100,100);
		WThr->Broad.RThrOffsetH		=Clipping((int)(WThr->Broad.RThrOffsetH*1.3+5	),-100,100);
		WThr->Broad.GThrOffsetL		=Clipping((int)(WThr->Broad.GThrOffsetL*1.3+5	),-100,100);
		WThr->Broad.GThrOffsetH		=Clipping((int)(WThr->Broad.GThrOffsetH*1.3+5	),-100,100);
		WThr->Broad.BThrOffsetL		=Clipping((int)(WThr->Broad.BThrOffsetL*1.3+5	),-100,100);
		WThr->Broad.BThrOffsetH		=Clipping((int)(WThr->Broad.BThrOffsetH*1.3+5	),-100,100);

		if(ScratchResultPeakH>0){
			WThr->ScratchDetectLevelH=max(ceil(ScratchResultPeakH),(double)WThr->ScratchDetectLevelH);
		}
		if(ScratchResultPeakL>0){
			WThr->ScratchDetectLevelL=max(ceil(ScratchResultPeakL),(double)WThr->ScratchDetectLevelL);
		}
	}
	if(LearningMenuID==LearningMenu_DotColorMatching_OK_NarrowByBrightness){
		WThr->Narrow.BrightWidthRL	=Clipping((int)(WThr->Narrow.BrightWidthRL*1.3+5),0,255);
		WThr->Narrow.BrightWidthRH	=Clipping((int)(WThr->Narrow.BrightWidthRH*1.3+5),0,255);
		WThr->Narrow.BrightWidthGL	=Clipping((int)(WThr->Narrow.BrightWidthGL*1.3+5),0,255);
		WThr->Narrow.BrightWidthGH	=Clipping((int)(WThr->Narrow.BrightWidthGH*1.3+5),0,255);
		WThr->Narrow.BrightWidthBL	=Clipping((int)(WThr->Narrow.BrightWidthBL*1.3+5),0,255);
		WThr->Narrow.BrightWidthBH	=Clipping((int)(WThr->Narrow.BrightWidthBH*1.3+5),0,255);
		WThr->Narrow.RThrOffsetL	=Clipping((int)(WThr->Narrow.RThrOffsetL*1.3+5	),-100,100);
		WThr->Narrow.RThrOffsetH	=Clipping((int)(WThr->Narrow.RThrOffsetH*1.3+5	),-100,100);
		WThr->Narrow.GThrOffsetL	=Clipping((int)(WThr->Narrow.GThrOffsetL*1.3+5	),-100,100);
		WThr->Narrow.GThrOffsetH	=Clipping((int)(WThr->Narrow.GThrOffsetH*1.3+5	),-100,100);
		WThr->Narrow.BThrOffsetL	=Clipping((int)(WThr->Narrow.BThrOffsetL*1.3+5	),-100,100);
		WThr->Narrow.BThrOffsetH	=Clipping((int)(WThr->Narrow.BThrOffsetH*1.3+5	),-100,100);

		if(ScratchResultPeakH>0){
			WThr->ScratchDetectLevelH=max(ceil(ScratchResultPeakH),(double)WThr->ScratchDetectLevelH);
		}
		if(ScratchResultPeakL>0){
			WThr->ScratchDetectLevelL=max(ceil(ScratchResultPeakL),(double)WThr->ScratchDetectLevelL);
		}
	}
	if(LearningMenuID==LearningMenu_DotColorMatching_OK_BroadBySize){
		int	OKDot=LRes.Cause[0];
		WThr->Broad.OKDot=max((int)GetThresholdR()->Broad.OKDot,OKDot);
	}
	if(LearningMenuID==LearningMenu_DotColorMatching_OK_NarrowBySize){
		int	OKDot=LRes.Cause[0];
		WThr->Narrow.OKDot=max((int)GetThresholdR()->Narrow.OKDot,OKDot);
	}
	if(LearningMenuID==LearningMenu_DotColorMatching_OK_ByShift){
		int	AreaSearchX=abs(LRes.Hx);
		if(AreaSearchX-GetThresholdR()->AreaSearchX>2)
			AreaSearchX=GetThresholdR()->AreaSearchX;
		int	AreaSearchY=abs(LRes.Hy);
		if(AreaSearchY-GetThresholdR()->AreaSearchY>2)
			AreaSearchY=GetThresholdR()->AreaSearchY;
		WThr->AreaSearchX=max(GetThresholdR()->AreaSearchX,AreaSearchX);
		WThr->AreaSearchY=max(GetThresholdR()->AreaSearchY,AreaSearchY);
		WThr->SelfSearch+=2;
	}

	if(LearningMenuID==LearningMenu_DotColorMatching_NG_BroadByBrightness){
		WThr->Broad.BrightWidthRL	=Clipping((int)((WThr->Broad.BrightWidthRL-5)/1.3),0,255);
		WThr->Broad.BrightWidthRH	=Clipping((int)((WThr->Broad.BrightWidthRH-5)/1.3),0,255);
		WThr->Broad.BrightWidthGL	=Clipping((int)((WThr->Broad.BrightWidthGL-5)/1.3),0,255);
		WThr->Broad.BrightWidthGH	=Clipping((int)((WThr->Broad.BrightWidthGH-5)/1.3),0,255);
		WThr->Broad.BrightWidthBL	=Clipping((int)((WThr->Broad.BrightWidthBL-5)/1.3),0,255);
		WThr->Broad.BrightWidthBH	=Clipping((int)((WThr->Broad.BrightWidthBH-5)/1.3),0,255);
		WThr->Broad.RThrOffsetL		=Clipping((int)((WThr->Broad.RThrOffsetL-5  )/1.3),-100,100);
		WThr->Broad.RThrOffsetH		=Clipping((int)((WThr->Broad.RThrOffsetH-5  )/1.3),-100,100);
		WThr->Broad.GThrOffsetL		=Clipping((int)((WThr->Broad.GThrOffsetL-5  )/1.3),-100,100);
		WThr->Broad.GThrOffsetH		=Clipping((int)((WThr->Broad.GThrOffsetH-5  )/1.3),-100,100);
		WThr->Broad.BThrOffsetL		=Clipping((int)((WThr->Broad.BThrOffsetL-5  )/1.3),-100,100);
		WThr->Broad.BThrOffsetH		=Clipping((int)((WThr->Broad.BThrOffsetH-5  )/1.3),-100,100);
	}
	if(LearningMenuID==LearningMenu_DotColorMatching_NG_NarrowByBrightness){
		WThr->Narrow.BrightWidthRL	=Clipping((int)((WThr->Narrow.BrightWidthRL-5)/1.3),0,255);
		WThr->Narrow.BrightWidthRH	=Clipping((int)((WThr->Narrow.BrightWidthRH-5)/1.3),0,255);
		WThr->Narrow.BrightWidthGL	=Clipping((int)((WThr->Narrow.BrightWidthGL-5)/1.3),0,255);
		WThr->Narrow.BrightWidthGH	=Clipping((int)((WThr->Narrow.BrightWidthGH-5)/1.3),0,255);
		WThr->Narrow.BrightWidthBL	=Clipping((int)((WThr->Narrow.BrightWidthBL-5)/1.3),0,255);
		WThr->Narrow.BrightWidthBH	=Clipping((int)((WThr->Narrow.BrightWidthBH-5)/1.3),0,255);
		WThr->Narrow.RThrOffsetL	=Clipping((int)((WThr->Narrow.RThrOffsetL-5  )/1.3),-100,100);
		WThr->Narrow.RThrOffsetH	=Clipping((int)((WThr->Narrow.RThrOffsetH-5  )/1.3),-100,100);
		WThr->Narrow.GThrOffsetL	=Clipping((int)((WThr->Narrow.GThrOffsetL-5  )/1.3),-100,100);
		WThr->Narrow.GThrOffsetH	=Clipping((int)((WThr->Narrow.GThrOffsetH-5  )/1.3),-100,100);
		WThr->Narrow.BThrOffsetL	=Clipping((int)((WThr->Narrow.BThrOffsetL-5  )/1.3),-100,100);
		WThr->Narrow.BThrOffsetH	=Clipping((int)((WThr->Narrow.BThrOffsetH-5  )/1.3),-100,100);
	}
	if(LearningMenuID==LearningMenu_DotColorMatching_NG_BroadSize){
		WThr->Broad.OKDot/=1.2;
	}
	if(LearningMenuID==LearningMenu_DotColorMatching_NG_NarrowSize){
		WThr->Narrow.OKDot/=1.2;
	}
}
static	int	DbgR1;

void	DotColorMatchingItem::MoveForAlignment(void)
{
	if(GetID()==DbgID){
		DbgR1++;
	}

	int	Mx,My;
	GetAlignmentShift(Mx,My);
	MoveTo(Mx,My);
}
void	DotColorMatchingItem::BuildSubtractionMap(void)
{
	int	SearchArea=GetThresholdR()->ExpandToSubBlock;
	for(int i=0;i<PatternCount;i++){
		MasterPattern[i].BuildSubtractionMap(SearchArea);
	}
}
void	DotColorMatchingItem::ClearSubtractionMap(void)
{
	for(int i=0;i<PatternCount;i++){
		MasterPattern[i].ClearSubtractionMap();
	}
}
bool	DotColorMatchingItem::GetOutlineAttr(void)
{
	if(OutlineBlock==true)
		return true;
	return false;
}
void	DotColorMatchingItem::SetOutlineAttr(bool b)
{
	OutlineBlock=b;
	OutlineArea	=b;
}