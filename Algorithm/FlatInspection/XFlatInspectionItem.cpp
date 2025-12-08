#include "XFlatInspection.h"
#include "XGeneralFunc.h"
#include "XBitImageProcessor.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XCrossObj.h"
#include "XFlatInspectionLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XUndo.h"
#include "XPropertyFlatInspectionPacket.h"
#include "XFlatInspectionAlgoPacket.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlgorithmLibrary.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

FlatInspectionThreshold::MThreshold::MThreshold(void)
{
	OrgOKDot			=0;
	OrgOKLength			=99999999;

	OKDot					=0;
	OKLength				=99999999;

	RThrOffsetL		=0;
	RThrOffsetH		=0;
	GThrOffsetL		=0;
	GThrOffsetH		=0;
	BThrOffsetL		=0;
	BThrOffsetH		=0;
}

void	FlatInspectionThreshold::MThreshold::CopyFrom(const FlatInspectionThreshold::MThreshold &src)
{
	OrgOKDot			=src.OrgOKDot;
	OrgOKLength			=src.OrgOKLength;

	OKDot				=src.OKDot;
	OKLength			=src.OKLength;

	RThrOffsetL			=src.RThrOffsetL;
	RThrOffsetH			=src.RThrOffsetH;
	GThrOffsetL			=src.GThrOffsetL;
	GThrOffsetH			=src.GThrOffsetH;
	BThrOffsetL			=src.BThrOffsetL;
	BThrOffsetH			=src.BThrOffsetH;
}

bool	FlatInspectionThreshold::MThreshold::Save(QIODevice *file)
{
	WORD	Ver=FlatInspectionVersion;

	if(::Save(file,Ver)==false)
		return false;

	if(::Save(file,OrgOKDot)==false)
		return false;
	if(::Save(file,OrgOKLength)==false)
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
bool	FlatInspectionThreshold::MThreshold::Load(QIODevice *file)
{
	WORD	Ver;

	if(::Load(file,Ver)==false)
		return false;

		WORD	OrgBrightWidthRL;	//暗側輝度幅
		WORD	OrgBrightWidthRH;	//明側輝度幅
		WORD	OrgBrightWidthGL;	//暗側輝度幅
		WORD	OrgBrightWidthGH;	//明側輝度幅
		WORD	OrgBrightWidthBL;	//暗側輝度幅
		WORD	OrgBrightWidthBH;	//明側輝度幅

	if(Ver<=1){
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
	}
	if(::Load(file,OrgOKDot)==false)
		return false;
	if(::Load(file,OrgOKLength)==false)
		return false;

		WORD	BrightWidthRL;	//暗側輝度幅
		WORD	BrightWidthRH;	//明側輝度幅
		WORD	BrightWidthGL;	//暗側輝度幅
		WORD	BrightWidthGH;	//明側輝度幅
		WORD	BrightWidthBL;	//暗側輝度幅
		WORD	BrightWidthBH;	//明側輝度幅
	if(Ver<=1){
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
	}
	if(::Load(file,OKDot)==false)
		return false;
	if(::Load(file,OKLength)==false)
		return false;

	if(Ver<=1){
		char	tRThrOffsetL;
		char	tRThrOffsetH;
		char	tGThrOffsetL;
		char	tGThrOffsetH;
		char	tBThrOffsetL;
		char	tBThrOffsetH;
		if(::Load(file,tRThrOffsetL)==false)
			return false;
		if(::Load(file,tRThrOffsetH)==false)
			return false;
		if(::Load(file,tGThrOffsetL)==false)
			return false;
		if(::Load(file,tGThrOffsetH)==false)
			return false;
		if(::Load(file,tBThrOffsetL)==false)
			return false;
		if(::Load(file,tBThrOffsetH)==false)
			return false;

		RThrOffsetL=tRThrOffsetL;
		RThrOffsetH=tRThrOffsetH;
		GThrOffsetL=tGThrOffsetL;
		GThrOffsetH=tGThrOffsetH;
		BThrOffsetL=tBThrOffsetL;
		BThrOffsetH=tBThrOffsetH;
	}
	else{
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
	}
	return true;
}

void	FlatInspectionThreshold::MThreshold::FromLibrary(FlatInspectionLibrary::MLibThreshold *LSrc)
{
	OrgOKDot			=LSrc->OKDot;
	OrgOKLength			=LSrc->OKLength;

	OKDot			=LSrc->OKDot;
	OKLength		=LSrc->OKLength;

	RThrOffsetL			=LSrc->RThrOffsetL;
	RThrOffsetH			=LSrc->RThrOffsetH;
	GThrOffsetL			=LSrc->GThrOffsetL;
	GThrOffsetH			=LSrc->GThrOffsetH;
	BThrOffsetL			=LSrc->BThrOffsetL;
	BThrOffsetH			=LSrc->BThrOffsetH;
}
void	FlatInspectionThreshold::MThreshold::ToLibrary  (FlatInspectionLibrary::MLibThreshold *LDst)
{
	LDst->OKDot			=OKDot			;
	LDst->OKLength		=OKLength		;

	LDst->RThrOffsetL		=RThrOffsetL	;
	LDst->RThrOffsetH		=RThrOffsetH	;
	LDst->GThrOffsetL		=GThrOffsetL	;
	LDst->GThrOffsetH		=GThrOffsetH	;
	LDst->BThrOffsetL		=BThrOffsetL	;
	LDst->BThrOffsetH		=BThrOffsetH	;
}

void	FlatInspectionThreshold::MThreshold::SetToOrigin(void)
{
	OrgOKDot				=OKDot;
	OrgOKLength				=OKLength;
}

//=====================================================================================
FlatInspectionThreshold::FlatInspectionThreshold(FlatInspectionItem *parent)
:AlgorithmThreshold(parent)
{
	SpaceToOutline		=10;
	ExpansionRange		=0.1;
	MerginForSpecial	=20;
	OrgMultiSpotDot		=0;
	OrgMultiSpotCount	=0;

	DivLenX				=300;
	DivLenY				=300;

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
	AreaSearchX		=20;
	AreaSearchY		=20;
    SelfSearch		=4;     //自己探索ドット数
	MaxAreaSearch	=99;		//最大領域探索ドット数
    MaxSelfSearch	=99;		//最大自己探索ドット数

	RedCheckMode		=false;
	RedHighRate			=150;
	RedMinBrightness	=70;
	RedGBMerginRate		=20;
	RedGBMerginOffset	=15;
	RedOKDot			=100;
	RedShrink			=0;

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

	//SetModifierMember(ID_SpaceToOutline	,&SpaceToOutline);
	SetModifierMember(ID_BroadOKDot		,&Broad.OKDot);
	SetModifierMember(ID_BroadOKLength	,&Broad.OKLength);
	SetModifierMember(ID_NarrowOKDot	,&Narrow.OKDot);
	SetModifierMember(ID_NarrowOKLength	,&Narrow.OKLength);

	SetModifierMember(ID_BroadRThrOffsetL	,&Broad.RThrOffsetL);
	SetModifierMember(ID_BroadRThrOffsetH	,&Broad.RThrOffsetH);
	SetModifierMember(ID_BroadGThrOffsetL	,&Broad.GThrOffsetL);
	SetModifierMember(ID_BroadGThrOffsetH	,&Broad.GThrOffsetH);
	SetModifierMember(ID_BroadBThrOffsetL	,&Broad.BThrOffsetL);
	SetModifierMember(ID_BroadBThrOffsetH	,&Broad.BThrOffsetH);

	SetModifierMember(ID_NarrowRThrOffsetL	,&Narrow.RThrOffsetL);
	SetModifierMember(ID_NarrowRThrOffsetH	,&Narrow.RThrOffsetH);
	SetModifierMember(ID_NarrowGThrOffsetL	,&Narrow.GThrOffsetL);
	SetModifierMember(ID_NarrowGThrOffsetH	,&Narrow.GThrOffsetH);
	SetModifierMember(ID_NarrowBThrOffsetL	,&Narrow.BThrOffsetL);
	SetModifierMember(ID_NarrowBThrOffsetH	,&Narrow.BThrOffsetH);
}

void	FlatInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const FlatInspectionThreshold *s=(const FlatInspectionThreshold *)&src;

	Broad.CopyFrom(s->Broad);
	Narrow.CopyFrom(s->Narrow);

	SpaceToOutline			=s->SpaceToOutline;
	ExpansionRange			=s->ExpansionRange;
	MerginForSpecial		=s->MerginForSpecial;
	DivLenX					=s->DivLenX;
	DivLenY					=s->DivLenY;

	OrgMultiSpotDot			=s->OrgMultiSpotDot	;
	OrgMultiSpotCount		=s->OrgMultiSpotCount;
	OrgBackGroundOKDot		=s->OrgBackGroundOKDot;
	OrgBackGroundOKLength	=s->OrgBackGroundOKLength;
	OrgUseBackGround		=s->OrgUseBackGround;

	MultiSpotDot		=s->MultiSpotDot	;
	MultiSpotCount		=s->MultiSpotCount;
	MultiSpotDotGathered	=s->MultiSpotDotGathered	;	//密集多点
	MultiSpotCountGathered	=s->MultiSpotCountGathered	;
	MultiSpotLengthGathered	=s->MultiSpotLengthGathered	;

	BackGroundOKDot		=s->BackGroundOKDot;
	BackGroundOKLength	=s->BackGroundOKLength;
	UseBackGround		=s->UseBackGround;

	AdjustBlack			=s->AdjustBlack;
    AdjustWhite			=s->AdjustWhite;
	AreaSearchX			=s->AreaSearchX;
	AreaSearchY			=s->AreaSearchY;
    SelfSearch			=s->SelfSearch;
	MaxAreaSearch		=s->MaxAreaSearch;
    MaxSelfSearch		=s->MaxSelfSearch;

	RedCheckMode			=s->RedCheckMode		;
	RedHighRate				=s->RedHighRate		;
	RedMinBrightness		=s->RedMinBrightness	;
	RedGBMerginRate			=s->RedGBMerginRate	;
	RedGBMerginOffset		=s->RedGBMerginOffset	;
	RedOKDot				=s->RedOKDot			;
	RedShrink				=s->RedShrink			;

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

	LineMode				=s->LineMode				;
	LineOKMinLength			=s->LineOKMinLength			;
	LineMaxWidth			=s->LineMaxWidth			;
	LineMinDensityPercent	=s->LineMinDensityPercent	;
	LineMinCluster			=s->LineMinCluster			;
}

void	FlatInspectionThreshold::CopyFrom(const AlgorithmThreshold &src,IntList &EdittedMemberID)
{
	const FlatInspectionThreshold *s=(const FlatInspectionThreshold *)&src;

	
	if(EdittedMemberID.IsInclude(ID_SpaceToOutline)==true)
		SpaceToOutline		=s->SpaceToOutline;
	if(EdittedMemberID.IsInclude(ID_ExpansionRange)==true)
		ExpansionRange		=s->ExpansionRange;
	if(EdittedMemberID.IsInclude(ID_MerginForSpecial)==true)
		MerginForSpecial	=s->MerginForSpecial;

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

	if(EdittedMemberID.IsInclude(ID_DivLenX	)==true)
		DivLenX	=s->DivLenX	;
	if(EdittedMemberID.IsInclude(ID_DivLenY	)==true)
		DivLenY	=s->DivLenY	;

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


	if(EdittedMemberID.IsInclude(ID_AdjustBlack		)==true)
		AdjustBlack		=s->AdjustBlack;
 	if(EdittedMemberID.IsInclude(ID_AdjustWhite		)==true)
		AdjustWhite		=s->AdjustWhite;
	if(EdittedMemberID.IsInclude(ID_AreaSearchX)==true)
		AreaSearchX		=s->AreaSearchX;
	if(EdittedMemberID.IsInclude(ID_AreaSearchY)==true)
		AreaSearchY		=s->AreaSearchY;
 	if(EdittedMemberID.IsInclude(ID_SelfSearch		)==true)
		SelfSearch		=s->SelfSearch;
	if(EdittedMemberID.IsInclude(ID_MaxAreaSearch)==true)
		MaxAreaSearch	=s->MaxAreaSearch;
 	if(EdittedMemberID.IsInclude(ID_MaxSelfSearch		)==true)
		MaxSelfSearch	=s->MaxSelfSearch;


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
bool	FlatInspectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const FlatInspectionThreshold *s=(const FlatInspectionThreshold *)&src;

	if(Broad.OrgOKDot			!=s->Broad.OrgOKDot)			return false;
	if(Broad.OrgOKLength		!=s->Broad.OrgOKLength)			return false;
	if(Broad.OKDot				!=s->Broad.OKDot	)			return false;
	if(Broad.OKLength			!=s->Broad.OKLength	)			return false;
	if(Broad.RThrOffsetL		!=s->Broad.RThrOffsetL)			return false;
	if(Broad.RThrOffsetH		!=s->Broad.RThrOffsetH)			return false;
	if(Broad.GThrOffsetL		!=s->Broad.GThrOffsetL)			return false;
	if(Broad.GThrOffsetH		!=s->Broad.GThrOffsetH)			return false;
	if(Broad.BThrOffsetL		!=s->Broad.BThrOffsetL)			return false;
	if(Broad.BThrOffsetH		!=s->Broad.BThrOffsetH)			return false;

	if(Narrow.OrgOKDot			!=s->Narrow.OrgOKDot)			return false;
	if(Narrow.OrgOKLength		!=s->Narrow.OrgOKLength)		return false;

	if(Narrow.OKDot				!=s->Narrow.OKDot		)		return false;
	if(Narrow.OKLength			!=s->Narrow.OKLength	)		return false;
	if(Narrow.RThrOffsetL		!=s->Narrow.RThrOffsetL)		return false;
	if(Narrow.RThrOffsetH		!=s->Narrow.RThrOffsetH)		return false;
	if(Narrow.GThrOffsetL		!=s->Narrow.GThrOffsetL)		return false;
	if(Narrow.GThrOffsetH		!=s->Narrow.GThrOffsetH)		return false;
	if(Narrow.BThrOffsetL		!=s->Narrow.BThrOffsetL)		return false;
	if(Narrow.BThrOffsetH		!=s->Narrow.BThrOffsetH)		return false;

	if(SpaceToOutline		!=s->SpaceToOutline)	return false;
	if(ExpansionRange		!=s->ExpansionRange)	return false;
	if(MerginForSpecial		!=s->MerginForSpecial)	return false;
	if(DivLenX				!=s->DivLenX)			return false;
	if(DivLenY				!=s->DivLenY)			return false;

	if(OrgMultiSpotDot		!=s->OrgMultiSpotDot)	return false;
	if(OrgMultiSpotCount	!=s->OrgMultiSpotCount)	return false;
	if(OrgBackGroundOKDot	!=s->OrgBackGroundOKDot)	return false;
	if(OrgBackGroundOKLength!=s->OrgBackGroundOKLength)	return false;
	if(OrgUseBackGround		!=s->UseBackGround)		return false;

	if(MultiSpotDot				!=s->MultiSpotDot			)	return false;
	if(MultiSpotCount			!=s->MultiSpotCount			)	return false;
	if(MultiSpotDotGathered		!=s->MultiSpotDotGathered	)	return false;
	if(MultiSpotCountGathered	!=s->MultiSpotCountGathered	)	return false;
	if(MultiSpotLengthGathered	!=s->MultiSpotLengthGathered)	return false;
	if(BackGroundOKDot			!=s->BackGroundOKDot		)	return false;
	if(BackGroundOKLength		!=s->BackGroundOKLength		)	return false;
	if(UseBackGround			!=s->UseBackGround			)	return false;

	if(AdjustBlack		!=s->AdjustBlack)		return false;
    if(AdjustWhite		!=s->AdjustWhite)		return false;
	if(AreaSearchX		!=s->AreaSearchX)		return false;
	if(AreaSearchY		!=s->AreaSearchY)		return false;
    if(SelfSearch		!=s->SelfSearch	)		return false;
	if(MaxAreaSearch	!=s->MaxAreaSearch	)	return false;
    if(MaxSelfSearch	!=s->MaxSelfSearch	)	return false;

	if(RedCheckMode			!=s->RedCheckMode		)	return false;
	if(RedHighRate			!=s->RedHighRate		)	return false;
	if(RedMinBrightness		!=s->RedMinBrightness	)	return false;
	if(RedGBMerginRate		!=s->RedGBMerginRate	)	return false;
	if(RedGBMerginOffset	!=s->RedGBMerginOffset	)	return false;
	if(RedOKDot				!=s->RedOKDot			)	return false;
	if(RedShrink			!=s->RedShrink			)	return false;

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

	if(LineMode				!=s->LineMode				)	return false;
	if(LineOKMinLength		!=s->LineOKMinLength		)	return false;
	if(LineMaxWidth			!=s->LineMaxWidth			)	return false;
	if(LineMinDensityPercent!=s->LineMinDensityPercent	)	return false;
	if(LineMinCluster		!=s->LineMinCluster			)	return false;

	return true;
}
bool	FlatInspectionThreshold::Save(QIODevice *file)
{
	WORD	Ver=FlatInspectionVersion;

	if(::Save(file,Ver)==false)
		return false;

	if(Broad.Save(file)==false)
		return false;
	if(Narrow.Save(file)==false)
		return false;

	if(::Save(file,SpaceToOutline)==false)
		return false;
	if(::Save(file,ExpansionRange)==false)
		return false;
	if(::Save(file,MerginForSpecial)==false)
		return false;
	if(::Save(file,DivLenX)==false)
		return false;
	if(::Save(file,DivLenY)==false)
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
	if(::Save(file,AreaSearchX)==false)
		return false;
	if(::Save(file,AreaSearchY)==false)
		return false;
	if(::Save(file,SelfSearch)==false)
		return false;
	if(::Save(file,MaxAreaSearch)==false)
		return false;
	if(::Save(file,MaxSelfSearch)==false)
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
bool	FlatInspectionThreshold::Load(QIODevice *file)
{
	WORD	Ver;

	if(::Load(file,Ver)==false)
		return false;


	if(Broad.Load(file)==false)
		return false;
	if(Narrow.Load(file)==false)
		return false;

	if(::Load(file,SpaceToOutline)==false)
		return false;
	if(Ver>=3){
		if(::Load(file,ExpansionRange)==false)
			return false;
		if(::Load(file,MerginForSpecial)==false)
			return false;
	}
	if(Ver>=4){
		if(::Load(file,DivLenX)==false)
			return false;
		if(::Load(file,DivLenY)==false)
			return false;
	}
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
	if(::Load(file,AreaSearchX)==false)
		return false;
	if(::Load(file,AreaSearchY)==false)
		return false;
	if(::Load(file,SelfSearch)==false)
		return false;
	if(::Load(file,MaxAreaSearch)==false)
		return false;
	if(::Load(file,MaxSelfSearch)==false)
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

	return true;
}

void	FlatInspectionThreshold::FromLibrary(AlgorithmLibrary *src)
{
	FlatInspectionLibrary	*LSrc=dynamic_cast<FlatInspectionLibrary *>(src);
	if(LSrc==NULL)
		return;

	Broad.FromLibrary(&LSrc->Broad);
	Narrow.FromLibrary(&LSrc->Narrow);

	SpaceToOutline		=LSrc->SpaceToOutline;

	OrgMultiSpotDot		=LSrc->MultiSpotDot	;
	OrgMultiSpotCount	=LSrc->MultiSpotCount;
	OrgBackGroundOKDot		=LSrc->BackGroundOKDot;
	OrgBackGroundOKLength	=LSrc->BackGroundOKLength;
	OrgUseBackGround		=LSrc->UseBackGround;

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
	AreaSearchX			=LSrc->AreaSearchX;
	AreaSearchY			=LSrc->AreaSearchY;
	SelfSearch			=LSrc->SelfSearch;
	MaxAreaSearch		=LSrc->MaxAreaSearch;
	MaxSelfSearch		=LSrc->MaxSelfSearch;

	LayersBase	*LBase=GetLayersBase();
	if(LBase==NULL){
		LBase=LSrc->GetLayersBase();
	}

	RedCheckMode		=LSrc->RedCheckMode			;
	RedHighRate			=LSrc->RedHighRate			;
	RedMinBrightness	=LSrc->RedMinBrightness		;
	RedGBMerginRate		=LSrc->RedGBMerginRate		;
	RedGBMerginOffset	=LSrc->RedGBMerginOffset	;
	RedOKDot			=LSrc->RedOKDot				;
	RedShrink			=LSrc->RedShrink			;

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

	LineMode				=LSrc->LineMode				;
	LineOKMinLength			=LSrc->LineOKMinLength		;
	LineMaxWidth			=LSrc->LineMaxWidth			;
	LineMinDensityPercent	=LSrc->LineMinDensityPercent;
	LineMinCluster			=LSrc->LineMinCluster		;
}
void	FlatInspectionThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	FlatInspectionLibrary	*LDst=dynamic_cast<FlatInspectionLibrary *>(Dest);
	if(LDst==NULL)
		return;

	Broad.ToLibrary(&LDst->Broad);
	Narrow.ToLibrary(&LDst->Narrow);

	LDst->SpaceToOutline		=SpaceToOutline;

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
	LDst->AreaSearchX		=AreaSearchX	;
	LDst->AreaSearchY		=AreaSearchY	;
	LDst->SelfSearch		=SelfSearch		;
	LDst->MaxAreaSearch		=MaxAreaSearch	;
	LDst->MaxSelfSearch		=MaxSelfSearch	;

	LayersBase	*LBase=GetLayersBase();
	if(LBase==NULL){
		LBase=LDst->GetLayersBase();
	}

	LDst->RedCheckMode			=RedCheckMode			;
	LDst->RedHighRate			=RedHighRate			;
	LDst->RedMinBrightness		=RedMinBrightness		;
	LDst->RedGBMerginRate		=RedGBMerginRate		;
	LDst->RedGBMerginOffset		=RedGBMerginOffset		;
	LDst->RedOKDot				=RedOKDot				;
	LDst->RedShrink				=RedShrink				;

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

	LDst->LineMode				=LineMode				;
	LDst->LineOKMinLength		=LineOKMinLength		;
	LDst->LineMaxWidth			=LineMaxWidth			;
	LDst->LineMinDensityPercent	=LineMinDensityPercent	;
	LDst->LineMinCluster		=LineMinCluster			;
}

void	FlatInspectionThreshold::SetToOrigin(void)
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
FlatInspectionItem::FlatInspectionItem(void)
{
	MasterY1=0;
	MasterY2=0;
	ResultY1=0;
	ResultY2=0;

	NGMapXByte	=0;
	NGMapXLen	=0;
	NGMapYLen	=0;

	NGMapB=NULL;
	NGMapN=NULL;
	NGMapRed=NULL;

	Dim	=NULL;
	DimCount=0;
}

FlatInspectionItem::~FlatInspectionItem(void)
{
	if(NGMapB!=NULL){
		DeleteMatrixBuff(NGMapB,NGMapYLen);
	}
	if(NGMapN!=NULL){
		DeleteMatrixBuff(NGMapN,NGMapYLen);
	}
	if(NGMapRed!=NULL){
		DeleteMatrixBuff(NGMapRed,NGMapYLen);
	}
	NGMapXByte	=0;
	NGMapXLen	=0;
	NGMapYLen	=0;

	NGMapB=NULL;
	NGMapN=NULL;
	NGMapRed=NULL;

	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	DimCount=0;
}


bool    FlatInspectionItem::Save(QIODevice *file)
{
	if(AlgorithmItemPITemplate<FlatInspectionInPage,FlatInspectionBase>::Save(file)==false)	
		return false;
	int	d=(int)FIT_Type;
	if(::Save(file,d)==false)
		return false;

	return true;
}
bool    FlatInspectionItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPITemplate<FlatInspectionInPage,FlatInspectionBase>::Load(file,LBase)==false)	
		return false;
	int	d;
	if(::Load(file,d)==false)
		return false;
	FIT_Type=(FlatInspectionType)d;

	return true;
}

void	FlatInspectionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	FlatInspectionDrawAttr	*MAttr=dynamic_cast<FlatInspectionDrawAttr *>(Attr);
	if(MAttr!=NULL){
		if(MAttr->FIT_Type==FIT_Type){
			AlgorithmItemPITemplate<FlatInspectionInPage,FlatInspectionBase>::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			if(FIT_Type==_FIType_MasterArea){
				QRgb	MCol=qRgba(0,64,255,196);	
				MasterArea.Draw(0,0,&pnt,MCol,ZoomRate ,movx ,movy);
				QRgb	ICol=qRgba(64,0,255,196);	
				InsideArea.Draw(0,0,&pnt,ICol,ZoomRate ,movx ,movy);
				QRgb	OCol=qRgba(128,255,0,196);	
				OutsideArea.Draw(0,0,&pnt,OCol,ZoomRate ,movx ,movy);
			}
			else
			if(FIT_Type==_FIType_Window){
				QRgb	MCol=qRgba(0,64,255,196);	
				MasterAreaLeftTop		.Draw(0,0,&pnt,MCol,ZoomRate ,movx ,movy);
				MasterAreaRightTop		.Draw(0,0,&pnt,MCol,ZoomRate ,movx ,movy);
				MasterAreaLeftBottom	.Draw(0,0,&pnt,MCol,ZoomRate ,movx ,movy);
				MasterAreaRightBottom	.Draw(0,0,&pnt,MCol,ZoomRate ,movx ,movy);
				QRgb	ICol=qRgba(64,0,255,196);	
				InsideAreaLeftTop		.Draw(0,0,&pnt,ICol,ZoomRate ,movx ,movy);
				InsideAreaRightTop		.Draw(0,0,&pnt,ICol,ZoomRate ,movx ,movy);
				InsideAreaLeftBottom	.Draw(0,0,&pnt,ICol,ZoomRate ,movx ,movy);
				InsideAreaRightBottom	.Draw(0,0,&pnt,ICol,ZoomRate ,movx ,movy);
				QRgb	OCol=qRgba(128,255,0,196);	
				OutsideAreaLeftTop		.Draw(0,0,&pnt,OCol,ZoomRate ,movx ,movy);
				OutsideAreaRightTop		.Draw(0,0,&pnt,OCol,ZoomRate ,movx ,movy);
				OutsideAreaLeftBottom	.Draw(0,0,&pnt,OCol,ZoomRate ,movx ,movy);
				OutsideAreaRightBottom	.Draw(0,0,&pnt,OCol,ZoomRate ,movx ,movy);
			}
			else
			if(FIT_Type==_FIType_SpecialShape){
				QRgb	SCol=qRgba(128,64,0,192);
				SpecialArea.DrawAlpha(0 ,0 ,&pnt ,SCol
									,ZoomRate ,movx ,movy);

				int	OffsetX=GetArea().GetMinX();
				int	OffsetY=GetArea().GetMinY();
				QRgb	LCol=qRgba(0,0,255,192);
				for(XYClass *c=DarkerDots.GetFirst();c!=NULL;c=c->GetNext()){
					DrawRect(pnt, LCol	, (c->x+OffsetX-2+movx)*ZoomRate, (c->y+OffsetY-2+movy)*ZoomRate
										, (c->x+OffsetX+2+movx)*ZoomRate, (c->y+OffsetY+2+movy)*ZoomRate);
				}
				QRgb	HCol=qRgba(255,0,255,192);
				for(XYClass *c=LighterDots.GetFirst();c!=NULL;c=c->GetNext()){
					DrawRect(pnt, HCol	, (c->x+OffsetX-2+movx)*ZoomRate, (c->y+OffsetY-2+movy)*ZoomRate
										, (c->x+OffsetX+2+movx)*ZoomRate, (c->y+OffsetY+2+movy)*ZoomRate);
				}
				QRgb	LCol2=qRgba(0,80,255,192);
				for(XYClass *c=RoughDarkerDots.GetFirst();c!=NULL;c=c->GetNext()){
					DrawRect(pnt, LCol2	, (c->x+OffsetX-2+movx)*ZoomRate, (c->y+OffsetY-2+movy)*ZoomRate
										, (c->x+OffsetX+2+movx)*ZoomRate, (c->y+OffsetY+2+movy)*ZoomRate);
				}
				QRgb	HCol2=qRgba(255,80,255,192);
				for(XYClass *c=RoughLighterDots.GetFirst();c!=NULL;c=c->GetNext()){
					DrawRect(pnt, HCol2	, (c->x+OffsetX-2+movx)*ZoomRate, (c->y+OffsetY-2+movy)*ZoomRate
										, (c->x+OffsetX+2+movx)*ZoomRate, (c->y+OffsetY+2+movy)*ZoomRate);
				}
			}
		}
	}
}

void	FlatInspectionItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID() && ((FlatInspectionItem *)Data)->GetPhaseCode()==GetPhaseCode()){
			FlatInspectionInPage	*Ly=dynamic_cast<FlatInspectionInPage *>(GetParentInPage());
			UndoElement<FlatInspectionInPage>	*UPointer=new UndoElement<FlatInspectionInPage>(Ly,&FlatInspectionInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());

			FlatInspectionThreshold	*WThr=GetThresholdW();
			WThr->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CopyThresholdOnly(*((FlatInspectionItem *)Data),EdittedMemberID);
			SetItemName(((FlatInspectionItem *)Data)->GetItemName());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((FlatInspectionItem *)Data)->GetLibID()){
			FlatInspectionInPage	*Ly=dynamic_cast<FlatInspectionInPage *>(GetParentInPage());
			UndoElement<FlatInspectionInPage>	*UPointer=new UndoElement<FlatInspectionInPage>(Ly,&FlatInspectionInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			
			FlatInspectionThreshold	*WThr=GetThresholdW();
			WThr->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CopyThresholdOnly(*((FlatInspectionItem *)Data),EdittedMemberID);
		}
	}
}

void	FlatInspectionItem::CopyThresholdOnly(FlatInspectionItem &src,IntList &EdittedMemberID)
{
	GetThresholdW()->CopyFrom(*((FlatInspectionThreshold *)src.GetThresholdR()),EdittedMemberID);
	SetInvertLogic(src.GetInvertLogic());
}

WORD	FlatInspectionItem::CalcCenterBright(ImageBuffer &tIBuff ,int mx ,int my ,float &LVar ,float &HVar)
{
	BYTE	*src;
	int		XNumb;
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();

	int		BTable[256];
	memset(BTable,0,sizeof(BTable));

	ImageBufferFast	IBuff(&tIBuff);	

	int	YSep;
	int	XSep;
	FlexArea	&A=GetArea();	//MasterPattern[CurrentRotationPatternNo];
	if(A.GetFLineLen()<20)
		YSep=1;
	else if(A.GetFLineLen()<40)
		YSep=2;
	else if(A.GetFLineLen()<60)
		YSep=3;
	else if(A.GetFLineLen()<100)
		YSep=4;
	else
		YSep=5;
	
	for(int i=0;i<A.GetFLineLen();i+=YSep){
		int	y =A.GetFLineAbsY  (i)+my;
		if(y<0)
			continue;
		if(y>=MaxLines)
			break;
		int	x1=A.GetFLineLeftX (i)+mx;
		int	x2=A.GetFLineRightX(i)+mx;
		if(x1<0)
			x1=0;
		if(x2>=DotPerLine)
			x2=DotPerLine;
		if(x1>x2)
			continue;

		XNumb=x2-x1;

		if(XNumb<20)
			XSep=1;
		else if(XNumb<40)
			XSep=2;
		else if(XNumb<60)
			XSep=3;
		else if(XNumb<100)
			XSep=4;
		else
			XSep=5;

		src=IBuff.GetYWithoutDepended(y)+x1;
		for(int x=0;x<XNumb;x+=XSep){
			BTable[*(src+x)]++;
		}
	}
	int	N=0;
	for(int i=0;i<sizeof(BTable)/sizeof(BTable[0]);i++){
		N+=BTable[i];
	}
	int	AdoptedRateForCenterBrightness=50;
	int	DiscardDot=((N*(100-AdoptedRateForCenterBrightness))/100)/2;

	int	LLevel;
	int	HLevel;
	int	D=0;
	for(LLevel=0;LLevel<sizeof(BTable)/sizeof(BTable[0]);LLevel++){
		D+=BTable[LLevel];
		if(D>DiscardDot){
			break;
		}
	}
	D=0;
	for(HLevel=sizeof(BTable)/sizeof(BTable[0])-1;HLevel>=0;HLevel--){
		D+=BTable[HLevel];
		if(D>DiscardDot){
			break;
		}
	}
	N=0;
	double	DSum=0;
	for(int i=LLevel;i<=HLevel;i++){
		N+=BTable[i];
		DSum+=BTable[i]*i;
	}
	double	Avr=(N!=0)?(((double)DSum)/N):0;

	double	BBL=0;
	int		NL=0;
	for(int L=Avr;L>=0;L--){
		double	d=L-Avr;
		BBL+=d*d*BTable[L];
		NL++;
	}
	double	BBH=0;
	int		NH=0;
	for(int H=Avr;H<256;H++){
		double	d=H-Avr;
		BBH+=d*d*BTable[H];
		NH++;
	}
	if(NL!=0){
		LVar=sqrt(((double)BBL)/NL);
	}
	if(NH!=0){
		HVar=sqrt(((double)BBH)/NH);
	}
	return (WORD)Avr;
}
	

ExeResult	FlatInspectionItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	BinarizedThresholdList.RemoveAll();
	const	FlatInspectionThreshold	*RThr=GetThresholdR();

	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}

	ImageBuffer		*MasterImageList[100];
	int	LayerNumb=GetMasterBuffList(MasterImageList);
	for(int layer=0;layer<LayerNumb;layer++){
		ImageBuffer *Image=MasterImageList[layer];
		int	BTable[256];
		memset(BTable,0,sizeof(BTable));
		GetArea().MakeBrightList(BTable ,GetDotPerLine(), GetMaxLines() ,*Image);
		int	LevelH=0;
		for(int H=255-4;H>=40;H--){
			int	Ht=BTable[H+1]+BTable[H  ]+BTable[H-1];
			int	H1=BTable[H+2]+BTable[H+3]+BTable[H+4];
			int	H2=BTable[H-2]+BTable[H-3]+BTable[H-4];
			if(H1<Ht && Ht<H2){
				LevelH=H;
				break;
			}
		}
		int	LevelL=0;
		for(int L=4;L<40;L++){
			int	Lt=BTable[L+1]+BTable[L  ]+BTable[L-1];
			int	L1=BTable[L+2]+BTable[L+3]+BTable[L+4];
			int	L2=BTable[L-2]+BTable[L-3]+BTable[L-4];
			if(L1<Lt && Lt<L2){
				LevelL=L;
				break;
			}
		}
		int	Mid=(LevelH+LevelL)/2;
		BinarizedThresholdList.Add(Mid);
	}

	if(NGMapB!=NULL){
		DeleteMatrixBuff(NGMapB,NGMapYLen);
		NGMapB=NULL;
	}
	if(NGMapN!=NULL){
		DeleteMatrixBuff(NGMapN,NGMapYLen);
		NGMapN=NULL;
	}
	if(NGMapRed!=NULL){
		DeleteMatrixBuff(NGMapRed,NGMapYLen);
		NGMapRed=NULL;
	}

	if(FIT_Type==_FIType_MasterArea){
		NGMapXByte	=(GetArea().GetWidth()+7)/8;
		NGMapXLen	=GetArea().GetWidth();
		NGMapYLen	=GetArea().GetHeight();
		NGMapYLen	*=1.2;
		NGMapOffsetX=GetArea().GetMinX();
		NGMapOffsetY=GetArea().GetMinY();

		int	Layer;
		int	Mid=BinarizedThresholdList.GetMaxValue(&Layer);

		ImageBuffer *Image=MasterImageList[Layer];
		
		BYTE	**TmpMap=MakeMatrixBuff( tGetParentInPage()->MaskMapXByte
										,tGetParentInPage()->MaskMapYLen);
		BYTE	**TmpMap2=MakeMatrixBuff(tGetParentInPage()->MaskMapXByte
										,tGetParentInPage()->MaskMapYLen);
		MatrixBuffClear	(TmpMap ,0	,tGetParentInPage()->MaskMapXByte
									,tGetParentInPage()->MaskMapYLen);


		AlgorithmLibraryLevelContainer	*LibC=GetLibFromManagedCacheLib();
		if(LibC!=NULL){
			AlgorithmLibrary	*Lib=LibC->GetLibrary();
			if(Lib!=NULL){
				FlatInspectionLibrary	*DLib=(FlatInspectionLibrary *)Lib;

				FlexArea	ALarge=GetArea();
				ALarge.FatAreaN(RThr->SpaceToOutline*5);
				::PickupBitmap(ALarge,0,0
					,TmpMap , tGetParentInPage()->MaskMapXByte,tGetParentInPage()->MaskMapYLen
					,*Image
					,Mid ,255
					,0,0);
				FlexArea	A=GetArea();
				GetLayersBase()->ThinAreaN(TmpMap,TmpMap2
										,tGetParentInPage()->MaskMapXByte
										,tGetParentInPage()->MaskMapYLen
										,DLib->NoiseSize
										,&A);
				GetLayersBase()->FatAreaN(TmpMap,TmpMap2
										,tGetParentInPage()->MaskMapXByte
										,tGetParentInPage()->MaskMapYLen
										,DLib->NoiseSize
										,&A);
				GetLayersBase()->FatAreaN(TmpMap,TmpMap2
										,tGetParentInPage()->MaskMapXByte
										,tGetParentInPage()->MaskMapYLen
										,DLib->NoiseSizePinHole
										,&A);					
				GetLayersBase()->ThinAreaN(TmpMap,TmpMap2
										,tGetParentInPage()->MaskMapXByte
										,tGetParentInPage()->MaskMapYLen
										,DLib->NoiseSizePinHole
										,&A);
				MasterArea.BuildFromRaster(TmpMap
											,tGetParentInPage()->MaskMapXByte
											,tGetParentInPage()->MaskMapYLen
											,0,0);
				FlexArea	Tmp=MasterArea;
				InsideArea=Tmp;
				InsideArea.ThinAreaN(5);
				Tmp-=InsideArea;
				InsideArea=Tmp;

				OutsideArea=MasterArea;
				OutsideArea.FatAreaN(5);
				OutsideArea-=MasterArea;

				//FlexArea	AreaOutline=GetArea();
				//AreaOutline.FatAreaN(5);
				//AreaOutline-=GetArea();
				//AreaOutline.FatAreaN(1);
				//
				//Tmp=MasterArea;
				//Tmp.ThinAreaN(5);
				//FlexArea	AreaInline=GetArea();
				//AreaInline-=Tmp;
				//AreaInline.FatAreaN(1);
				//
				//InsideArea-=AreaInline;
				//OutsideArea-=AreaOutline;

				MasterArea.ThinAreaN(RThr->SpaceToOutline);

				InsideArea.ClipArea(GetArea());
				OutsideArea.ClipArea(GetArea());
				MasterArea.ClipArea(GetArea());

			}
		}

		DeleteMatrixBuff(TmpMap ,tGetParentInPage()->MaskMapYLen);
		DeleteMatrixBuff(TmpMap2,tGetParentInPage()->MaskMapYLen);

		AverageMaster.RemoveAll();
		for(int L=0;L<LayerNumb;L++){
			int	a=MasterArea.GetAverage(0,0,*MasterImageList[L],1.0,1.0);
			AverageMaster.Add(a);
		}



		DimCount=0;
		for(int dy=-RThr->AreaSearchY;dy<=RThr->AreaSearchY;dy+=3){
			for(int dx=-RThr->AreaSearchX;dx<=RThr->AreaSearchX;dx+=3){
				DimCount++;
			}
		}
		Dim=new struct SearchParam[DimCount];
		int	n=0;
		for(int dy=-RThr->AreaSearchY;dy<=RThr->AreaSearchY;dy+=3){
			for(int dx=-RThr->AreaSearchX;dx<=RThr->AreaSearchX;dx+=3){
				Dim[n].Dx=dx;
				Dim[n].Dy=dy;
				n++;
			}
		}
	}
	else
	if(FIT_Type==_FIType_InspectionArea){
		NGMapXByte	=(GetArea().GetWidth()+7)/8;
		NGMapXLen	=GetArea().GetWidth();
		NGMapYLen	=GetArea().GetHeight();
		NGMapYLen	*=1.2;
		NGMapOffsetX=GetArea().GetMinX();
		NGMapOffsetY=GetArea().GetMinY();

		int	Layer;
		int	Mid=BinarizedThresholdList.GetMaxValue(&Layer);
		ImageBuffer		*MasterImageList[100];
		int	LayerNumb=GetMasterBuffList(MasterImageList);
		ImageBuffer		*Image=MasterImageList[Layer];

		int	N=GetArea().GetFLineLen();
		for(int i=0;i<N;i++){
			int	Y	=GetArea().GetFLineAbsY(i);
			int	X1	=GetArea().GetFLineLeftX(i);
			int	Numb=GetArea().GetFLineNumb(i);

			int	Counter=0;
			BYTE	*s=Image->GetY(Y);
			for(int n=0;n<Numb;n++){
				if(*(s+X1+n)>=Mid){
					Counter++;
				}
			}
			if(Counter>100){
				MasterY1=Y;
				break;
			}
		}
		for(int i=N-1;i>=0;i--){
			int	Y	=GetArea().GetFLineAbsY(i);
			int	X1	=GetArea().GetFLineLeftX(i);
			int	Numb=GetArea().GetFLineNumb(i);

			int	Counter=0;
			BYTE	*s=Image->GetY(Y);
			for(int n=0;n<Numb;n++){
				if(*(s+X1+n)>=Mid){
					Counter++;
				}
			}
			if(Counter>100){
				MasterY2=Y;
				break;
			}
		}
		int	x1,y1,x2,y2;
		GetXY(x1,y1,x2,y2);
		int	MaxDotCount=(MasterY2-MasterY1)/4;
		for(int x=x1;x<x2;x++){
			int	Counter=0;
			for(int y=MasterY1;y<MasterY2;y++){
				BYTE	*s=Image->GetY(y);
				if(s[x]>=Mid){
					Counter++;
				}
				if(Counter>MaxDotCount){
					MasterMinX=x;
					goto	EE1;
				}
			}
		}
		EE1:;
		for(int x=x2;x>=x1;x--){
			int	Counter=0;
			for(int y=MasterY1;y<MasterY2;y++){
				BYTE	*s=Image->GetY(y);
				if(s[x]>=Mid){
					Counter++;
				}
				if(Counter>MaxDotCount){
					MasterMaxX=x;
					goto	EE2;
				}
			}
		}
		EE2:;
	}

	else
	if(FIT_Type==_FIType_Window){
		NGMapXByte	=(GetArea().GetWidth()+7)/8;
		NGMapXLen	=GetArea().GetWidth();
		NGMapYLen	=GetArea().GetHeight();
		NGMapYLen	*=1.2;

		int	Layer;
		int	Mid=BinarizedThresholdList.GetMaxValue(&Layer);
		ImageBuffer		*MasterImageList[100];
		int	LayerNumb=GetMasterBuffList(MasterImageList);
		ImageBuffer		*Image=MasterImageList[Layer];

		//double	A=((double)(TargetY2-TargetY1))/((double)(MasterY2-MasterY1));

		//int	Dy=TargetY1-MasterY1;
		BYTE	**TmpMap=MakeMatrixBuff( tGetParentInPage()->MaskMapXByte
										,tGetParentInPage()->MaskMapYLen);
		BYTE	**TmpMap2=MakeMatrixBuff(tGetParentInPage()->MaskMapXByte
										,tGetParentInPage()->MaskMapYLen);
		MatrixBuffClear	(TmpMap ,0	,tGetParentInPage()->MaskMapXByte
									,tGetParentInPage()->MaskMapYLen);

		MatrixBuffClear	(TmpMap ,0 ,tGetParentInPage()->MaskMapXByte ,tGetParentInPage()->MaskMapYLen);
		int	N=GetArea().GetFLineLen();
		for(int i=0;i<N;i++){
			int	Y	=GetArea().GetFLineAbsY(i);
			int	X1	=GetArea().GetFLineLeftX(i);
			int	Numb=GetArea().GetFLineNumb(i);
			BYTE	*s=Image->GetY(Y);
			BYTE	*d=TmpMap[Y];
			for(int n=0;n<Numb;n++){
				if(s[X1+n]<=Mid){
					SetBmpBitOnY1(d,X1+n);
				}
			}
		}
		GetLayersBase()->FatAreaN (TmpMap,TmpMap2,tGetParentInPage()->MaskMapXByte ,tGetParentInPage()->MaskMapYLen,5);
		GetLayersBase()->ThinAreaN(TmpMap,TmpMap2,tGetParentInPage()->MaskMapXByte ,tGetParentInPage()->MaskMapYLen,5);
		GetLayersBase()->ThinAreaN(TmpMap,TmpMap2,tGetParentInPage()->MaskMapXByte ,tGetParentInPage()->MaskMapYLen,5);
		GetLayersBase()->FatAreaN (TmpMap,TmpMap2,tGetParentInPage()->MaskMapXByte ,tGetParentInPage()->MaskMapYLen,5);

		PureFlexAreaListContainer FPack;
		::PickupFlexArea(TmpMap	,tGetParentInPage()->MaskMapXByte
								,tGetParentInPage()->MaskMapXByte*8
								,tGetParentInPage()->MaskMapYLen ,FPack);
		PureFlexAreaList	*MaxP=NULL;
		int64	MaxD=0;
		for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
			int64	d=p->GetPatternByte();
			if(d>MaxD){
				MaxD=d;
				MaxP=p;
			}
		}
		if(MaxP!=NULL){
			MasterArea=*MaxP;
			OutsideArea=*MaxP;
			OutsideArea.FatAreaN(20);
			OutsideArea-=MasterArea;
			FlexArea	TmpA=*MaxP;
			TmpA.ThinAreaN(20);
			InsideArea=*MaxP;
			InsideArea-=TmpA;
			MasterArea.FatAreaN(RThr->SpaceToOutline);
		}

		int	W=MasterArea.GetWidth()/4;
		int	H=MasterArea.GetHeight()/4;

		InsideAreaLeftTop		=InsideArea;
		InsideAreaRightTop		=InsideArea;
		InsideAreaLeftBottom	=InsideArea;
		InsideAreaRightBottom	=InsideArea;
		OutsideAreaLeftTop		=OutsideArea;
		OutsideAreaRightTop		=OutsideArea;
		OutsideAreaLeftBottom	=OutsideArea;
		OutsideAreaRightBottom	=OutsideArea;
		MasterAreaLeftTop		=MasterArea;
		MasterAreaRightTop		=MasterArea;
		MasterAreaLeftBottom	=MasterArea;
		MasterAreaRightBottom	=MasterArea;

		int	Cx,Cy;
		GetArea().GetCenter(Cx,Cy);
		InsideAreaLeftTop		.ClipArea(0		,0		,Cx+W+2			,Cy+H+2);
		OutsideAreaLeftTop		.ClipArea(0		,0		,Cx+W+2			,Cy+H+2);
		MasterAreaLeftTop		.ClipArea(0		,0		,Cx+W+2			,Cy+H+2);
		InsideAreaRightTop		.ClipArea(Cx-W-2,0		,GetDotPerLine(),Cy+H+2);
		OutsideAreaRightTop		.ClipArea(Cx-W-2,0		,GetDotPerLine(),Cy+H+2);
		MasterAreaRightTop		.ClipArea(Cx-W-2,0		,GetDotPerLine(),Cy+H+2);
		InsideAreaLeftBottom	.ClipArea(0		,Cy-H-2	,Cx+W+2			,GetMaxLines());
		OutsideAreaLeftBottom	.ClipArea(0		,Cy-H-2	,Cx+W+2			,GetMaxLines());
		MasterAreaLeftBottom	.ClipArea(0		,Cy-H-2	,Cx+W+2			,GetMaxLines());
		InsideAreaRightBottom	.ClipArea(Cx-W-2,Cy-H-2	,GetDotPerLine(),GetMaxLines());
		OutsideAreaRightBottom	.ClipArea(Cx-W-2,Cy-H-2	,GetDotPerLine(),GetMaxLines());
		MasterAreaRightBottom	.ClipArea(Cx-W-2,Cy-H-2	,GetDotPerLine(),GetMaxLines());

		DeleteMatrixBuff(TmpMap ,tGetParentInPage()->MaskMapYLen);
		DeleteMatrixBuff(TmpMap2,tGetParentInPage()->MaskMapYLen);


		DimCount=0;
		for(int dy=-RThr->AreaSearchY;dy<=RThr->AreaSearchY;dy+=3){
			for(int dx=-RThr->AreaSearchX;dx<=RThr->AreaSearchX;dx+=3){
				DimCount++;
			}
		}
		Dim=new struct SearchParam[DimCount];
		int	n=0;
		for(int dy=-RThr->AreaSearchY;dy<=RThr->AreaSearchY;dy+=3){
			for(int dx=-RThr->AreaSearchX;dx<=RThr->AreaSearchX;dx+=3){
				Dim[n].Dx=dx;
				Dim[n].Dy=dy;
				n++;
			}
		}
	}

	else
	if(FIT_Type==_FIType_SpecialShape){
		FlexArea	AUp=GetArea();
		AUp.ClipArea(0,0,GetDotPerLine(),(GetArea().GetMinY()+GetArea().GetMaxY())/2);
		FlexArea	ADn=GetArea();
		ADn.ClipArea(0,(GetArea().GetMinY()+GetArea().GetMaxY())/2,GetDotPerLine(),GetMaxLines());
		DarkerDots .RemoveAll();
		LighterDots.RemoveAll();
		AddDarkLightDot(AUp);
		AddDarkLightDot(ADn);
		MakeRoughDots();

		SpecialArea=GetArea();
		AlgorithmLibraryLevelContainer	*LibC=GetLibFromManagedCacheLib();
		if(LibC!=NULL){
			AlgorithmLibrary	*Lib=LibC->GetLibrary();
			if(Lib!=NULL){
				FlatInspectionLibrary	*DLib=(FlatInspectionLibrary *)Lib;
				SpecialArea.FatAreaN(DLib->SpaceToOutline);
			}
		}
		NGMapXByte	=(SpecialArea.GetWidth()+7)/8;
		NGMapXLen	=SpecialArea.GetWidth();
		NGMapYLen	=SpecialArea.GetHeight();
		NGMapYLen	*=1.2;
		NGMapOffsetX=SpecialArea.GetMinX();
		NGMapOffsetY=SpecialArea.GetMinY();	


		int	x1,y1,x2,y2;
		GetXY(x1,y1,x2,y2);

		double	dd		=tGetParentBase()->SearchDot4SpecialArea/(y2-y1);
		double	ERange	=RThr->ExpansionRange;
		double	MinD=1.0-ERange;
		double	MaxD=1.0+ERange;

		int	Sep=RThr->SelfSearch-1;
		if(Sep<2)
			Sep=2;
		DimCount=0;
		for(double	E=MinD;E<=MaxD;E+=dd){
			for(int dy=-RThr->AreaSearchY;dy<=RThr->AreaSearchY;dy+=Sep){
				for(int dx=-RThr->AreaSearchX;dx<=RThr->AreaSearchX;dx+=Sep){
					DimCount++;
				}
			}
		}

		Dim=new struct SearchParam[DimCount];
		int	K=0;
		for(double	E=MinD;E<=MaxD;E+=dd){
			for(int dy=-RThr->AreaSearchY;dy<=RThr->AreaSearchY;dy+=Sep){
				for(int dx=-RThr->AreaSearchX;dx<=RThr->AreaSearchX;dx+=Sep){
					Dim[K].Dx=dx;
					Dim[K].Dy=dy;
					Dim[K].E =E;
					K++;
				}
			}
		}
	}
	NGMapB=MakeMatrixBuff(NGMapXByte,NGMapYLen);
	NGMapN=MakeMatrixBuff(NGMapXByte,NGMapYLen);
	NGMapRed=MakeMatrixBuff(NGMapXByte,NGMapYLen);
}

void	FlatInspectionItem::CopyFrom(FlatInspectionItem *src)
{
	SetArea(src->GetArea());

	FIT_Type	=src->FIT_Type;

	MasterArea	=src->MasterArea;		//FIT_Type==_FIType_MasterArea or _FIType_Window
	InsideArea	=src->InsideArea;
	OutsideArea	=src->OutsideArea;
	SpecialArea	=src->SpecialArea;

	MasterAreaLeftTop		=src->MasterAreaLeftTop		;		
	InsideAreaLeftTop		=src->InsideAreaLeftTop		;
	OutsideAreaLeftTop		=src->OutsideAreaLeftTop	;
	MasterAreaRightTop		=src->MasterAreaRightTop	;		
	InsideAreaRightTop		=src->InsideAreaRightTop	;
	OutsideAreaRightTop		=src->OutsideAreaRightTop	;
	MasterAreaLeftBottom	=src->MasterAreaLeftBottom	;	
	InsideAreaLeftBottom	=src->InsideAreaLeftBottom	;
	OutsideAreaLeftBottom	=src->OutsideAreaLeftBottom	;
	MasterAreaRightBottom	=src->MasterAreaRightBottom	;	
	InsideAreaRightBottom	=src->InsideAreaRightBottom	;
	OutsideAreaRightBottom	=src->OutsideAreaRightBottom;

	DarkerDots	=src->DarkerDots ;
	LighterDots	=src->LighterDots;
	RoughDarkerDots	=src->RoughDarkerDots	;
	RoughLighterDots=src->RoughLighterDots	;

	ResultDx		=src->ResultDx		;
	ResultDy		=src->ResultDy		;	//For _FIType_MasterArea

	ResultDxLeftTop		=src->ResultDxLeftTop		;
	ResultDyLeftTop		=src->ResultDyLeftTop		;	//For _FIType_MasterArea
	ResultDxRightTop	=src->ResultDxRightTop		;
	ResultDyRightTop	=src->ResultDyRightTop		;	//For _FIType_MasterArea
	ResultDxLeftBottom	=src->ResultDxLeftBottom	;
	ResultDyLeftBottom	=src->ResultDyLeftBottom	;	//For _FIType_MasterArea
	ResultDxRightBottom	=src->ResultDxRightBottom	;
	ResultDyRightBottom	=src->ResultDyRightBottom	;	//For _FIType_MasterArea

	ResultExpansion	=src->ResultExpansion	;
	AverageMaster	=src->AverageMaster	;
	AverageTarget	=src->AverageTarget	;

	MasterY1	=src->MasterY1	;
	MasterY2	=src->MasterY2	;
	MasterMinX	=src->MasterMinX;
	MasterMaxX	=src->MasterMaxX;
	ResultY1	=src->ResultY1	;
	ResultY2	=src->ResultY2	;
	ResultMinX	=src->ResultMinX;
	ResultMaxX	=src->ResultMaxX;

	CenterBrightR		=src->CenterBrightR;
	CenterBrightG		=src->CenterBrightG;
	CenterBrightB		=src->CenterBrightB;
	CenterTargetBrightR	=src->CenterTargetBrightR;
	CenterTargetBrightG	=src->CenterTargetBrightG;
	CenterTargetBrightB	=src->CenterTargetBrightB;

	BinarizedThresholdList	=src->BinarizedThresholdList;

	if(NGMapB!=NULL){
		DeleteMatrixBuff(NGMapB,NGMapYLen);
		NGMapB=NULL;
	}
	if(NGMapN!=NULL){
		DeleteMatrixBuff(NGMapN,NGMapYLen);
		NGMapN=NULL;
	}
	if(NGMapRed!=NULL){
		DeleteMatrixBuff(NGMapRed,NGMapYLen);
		NGMapRed=NULL;
	}
	NGMapXByte	=src->NGMapXByte;	
	NGMapXLen	=src->NGMapXLen	;
	NGMapYLen	=src->NGMapYLen	;

	NGMapB	=MakeMatrixBuff(NGMapXByte,NGMapYLen);
	NGMapN	=MakeMatrixBuff(NGMapXByte,NGMapYLen);
	NGMapRed=MakeMatrixBuff(NGMapXByte,NGMapYLen);
	NGMapOffsetX=src->NGMapOffsetX;
	NGMapOffsetY=src->NGMapOffsetY;
}

