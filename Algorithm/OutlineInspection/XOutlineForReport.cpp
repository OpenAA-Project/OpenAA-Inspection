/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\OutlineInspection\XOutlineForReport.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "OutlineInspectionResource.h"

#define	_USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XOutlineInspect.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XParamGlobal.h"
#include "XPSpline.h"



void	OutlineInspectLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	if(GetLayerNumb(0)==1){

		int	L,H;
		PickupColor.GetMonoColorRange(L, H);
		RetContainer.Add("PickupColorL"		,L);
		RetContainer.Add("PickupColorH"		,H);

		RetContainer.Add("TransDot"			,TransDot);
		RetContainer.Add("InsideWidth"		,InsideWidth);
		RetContainer.Add("OutsideWidth"		,OutsideWidth);
		RetContainer.Add("NoiseDot"			,NoiseDot);
		RetContainer.Add("ChoppedLength"	,ChoppedLength);
		RetContainer.Add("Priority"			,Priority);
		RetContainer.Add("MinAreaDot"		,MinAreaDot);
		RetContainer.Add("MaxAreaDot"		,MaxAreaDot);
		RetContainer.Add("MinAreaSize"		,MinAreaSize);
		RetContainer.Add("MaxAreaSize"		,MaxAreaSize);
		RetContainer.Add("MatchSlideOnMaster",MatchSlideOnMaster);

		RetContainer.Add("InsideTrWidth"	,InsideTrWidth);
		RetContainer.Add("OutsideTrWidth"	,OutsideTrWidth);
		
		InsideNOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("InsideNOKColorL"	,L);
		RetContainer.Add("InsideNOKColorH"	,H);

		InsideNTrOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("InsideNTrOKColorL"	,L);
		RetContainer.Add("InsideNTrOKColorH"	,H);

		RetContainer.Add("InsideNOKDot"		,InsideNOKDot);
		RetContainer.Add("InsideNMergin"	,InsideNMergin);

		OutsideNOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("OutsideNOKColorL"	,L);
		RetContainer.Add("OutsideNOKColorH"	,H);

		OutsideNTrOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("OutsideNTrOKColorL"	,L);
		RetContainer.Add("OutsideNTrOKColorH"	,H);

		RetContainer.Add("OutsideNOKDot"	,OutsideNOKDot);
		RetContainer.Add("OutsideNMergin"	,OutsideNMergin);


		InsideBOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("InsideBOKColorL"	,L);
		RetContainer.Add("InsideBOKColorH"	,H);

		InsideBTrOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("InsideBTrOKColorL"	,L);
		RetContainer.Add("InsideBTrOKColorH"	,H);

		RetContainer.Add("InsideBOKDot"		,InsideNOKDot);
		RetContainer.Add("InsideBMergin"	,InsideNMergin);

		OutsideBOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("OutsideBOKColorL"	,L);
		RetContainer.Add("OutsideBOKColorH"	,H);

		OutsideBTrOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("OutsideBTrOKColorL"	,L);
		RetContainer.Add("OutsideBTrOKColorH"	,H);

		RetContainer.Add("OutsideBOKDot"	,OutsideNOKDot);
		RetContainer.Add("OutsideBMergin"	,OutsideNMergin);
	}
	else if(GetLayerNumb(0)>=3){
		//ColorLogic	PickupColor;

		RetContainer.Add("TransDot"			,TransDot);
		RetContainer.Add("InsideWidth"		,InsideWidth);
		RetContainer.Add("OutsideWidth"		,OutsideWidth);
		RetContainer.Add("NoiseDot"			,NoiseDot);
		RetContainer.Add("ChoppedLength"	,ChoppedLength);
		RetContainer.Add("Priority"			,Priority);
		RetContainer.Add("MinAreaDot"		,MinAreaDot);
		RetContainer.Add("MaxAreaDot"		,MaxAreaDot);
		RetContainer.Add("MinAreaSize"		,MinAreaSize);
		RetContainer.Add("MaxAreaSize"		,MaxAreaSize);
		RetContainer.Add("MatchSlideOnMaster",MatchSlideOnMaster);

		RetContainer.Add("InsideTrWidth"	,InsideTrWidth);
		RetContainer.Add("OutsideTrWidth"	,OutsideTrWidth);
		
		int	RL,RH;
		int	GL,GH;
		int	BL,BH;
		InsideNOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("InsideNOKColorRL"	,RL);
		RetContainer.Add("InsideNOKColorRH"	,RH);
		RetContainer.Add("InsideNOKColorGL"	,GL);
		RetContainer.Add("InsideNOKColorGH"	,GH);
		RetContainer.Add("InsideNOKColorBL"	,BL);
		RetContainer.Add("InsideNOKColorBH"	,BH);

		InsideNTrOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("InsideNTrOKColorRL"	,RL);
		RetContainer.Add("InsideNTrOKColorRH"	,RH);
		RetContainer.Add("InsideNTrOKColorGL"	,GL);
		RetContainer.Add("InsideNTrOKColorGH"	,GH);
		RetContainer.Add("InsideNTrOKColorBL"	,BL);
		RetContainer.Add("InsideNTrOKColorBH"	,BH);

		RetContainer.Add("InsideNOKDot"		,InsideNOKDot);
		RetContainer.Add("InsideNMergin"	,InsideNMergin);

		OutsideNOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("OutsideNOKColorRL"	,RL);
		RetContainer.Add("OutsideNOKColorRH"	,RH);
		RetContainer.Add("OutsideNOKColorGL"	,GL);
		RetContainer.Add("OutsideNOKColorGH"	,GH);
		RetContainer.Add("OutsideNOKColorBL"	,BL);
		RetContainer.Add("OutsideNOKColorBH"	,BH);

		OutsideNTrOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("OutsideNTrOKColorRL"	,RL);
		RetContainer.Add("OutsideNTrOKColorRH"	,RH);
		RetContainer.Add("OutsideNTrOKColorGL"	,GL);
		RetContainer.Add("OutsideNTrOKColorGH"	,GH);
		RetContainer.Add("OutsideNTrOKColorBL"	,BL);
		RetContainer.Add("OutsideNTrOKColorBH"	,BH);

		RetContainer.Add("OutsideNOKDot"	,OutsideNOKDot);
		RetContainer.Add("OutsideNMergin"	,OutsideNMergin);


		InsideBOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("InsideBOKColorRL"	,RL);
		RetContainer.Add("InsideBOKColorRH"	,RH);
		RetContainer.Add("InsideBOKColorGL"	,GL);
		RetContainer.Add("InsideBOKColorGH"	,GH);
		RetContainer.Add("InsideBOKColorBL"	,BL);
		RetContainer.Add("InsideBOKColorBH"	,BH);

		InsideBTrOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("InsideBTrOKColorRL"	,RL);
		RetContainer.Add("InsideBTrOKColorRH"	,RH);
		RetContainer.Add("InsideBTrOKColorGL"	,GL);
		RetContainer.Add("InsideBTrOKColorGH"	,GH);
		RetContainer.Add("InsideBTrOKColorBL"	,BL);
		RetContainer.Add("InsideBTrOKColorBH"	,BH);

		RetContainer.Add("InsideBOKDot"		,InsideNOKDot);
		RetContainer.Add("InsideBMergin"	,InsideNMergin);

		OutsideBOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("OutsideBOKColorRL"	,RL);
		RetContainer.Add("OutsideBOKColorRH"	,RH);
		RetContainer.Add("OutsideBOKColorGL"	,GL);
		RetContainer.Add("OutsideBOKColorGH"	,GH);
		RetContainer.Add("OutsideBOKColorBL"	,BL);
		RetContainer.Add("OutsideBOKColorBH"	,BH);

		OutsideBTrOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("OutsideBTrOKColorRL"	,RL);
		RetContainer.Add("OutsideBTrOKColorRH"	,RH);
		RetContainer.Add("OutsideBTrOKColorGL"	,GL);
		RetContainer.Add("OutsideBTrOKColorGH"	,GH);
		RetContainer.Add("OutsideBTrOKColorBL"	,BL);
		RetContainer.Add("OutsideBTrOKColorBH"	,BH);
	
		RetContainer.Add("OutsideBOKDot"	,OutsideNOKDot);
		RetContainer.Add("OutsideBMergin"	,OutsideNMergin);
	}

	RetContainer.Add("EffectiveNInside"		,EffectiveNInside);
	RetContainer.Add("EffectiveNOutside"	,EffectiveNOutside);
	RetContainer.Add("EffectiveBInside"		,EffectiveBInside);
	RetContainer.Add("EffectiveBOutside"	,EffectiveBOutside);

	RetContainer.Add("SelfSearch"			,SelfSearch);
	RetContainer.Add("AdjustMode"			,AdjustMode);
	RetContainer.Add("AdjustLimitLInside"	,AdjustLimitLInside);
	RetContainer.Add("AdjustLimitHInside"	,AdjustLimitHInside);
	RetContainer.Add("AdjustLimitLOutside"	,AdjustLimitLOutside);
	RetContainer.Add("AdjustLimitHOutside"	,AdjustLimitHOutside);
	RetContainer.Add("DiffMode"				,DiffMode);
	RetContainer.Add("AbsMode"				,AbsMode);
}

void	OutlineThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	if(GetLayersBase()->GetLayerNumb(0)==1){

		int	L,H;
		
		InsideNOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("InsideNOKColorL"	,L);
		RetContainer.Add("InsideNOKColorH"	,H);

		InsideNTrOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("InsideNTrOKColorL"	,L);
		RetContainer.Add("InsideNTrOKColorH"	,H);

		RetContainer.Add("InsideNOKDot"		,InsideNOKDot);
		RetContainer.Add("InsideNMergin"	,InsideNMergin);

		OutsideNOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("OutsideNOKColorL"	,L);
		RetContainer.Add("OutsideNOKColorH"	,H);

		OutsideNTrOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("OutsideNTrOKColorL"	,L);
		RetContainer.Add("OutsideNTrOKColorH"	,H);

		RetContainer.Add("OutsideNOKDot"	,OutsideNOKDot);
		RetContainer.Add("OutsideNMergin"	,OutsideNMergin);


		InsideBOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("InsideBOKColorL"	,L);
		RetContainer.Add("InsideBOKColorH"	,H);

		InsideBTrOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("InsideBTrOKColorL"	,L);
		RetContainer.Add("InsideBTrOKColorH"	,H);

		RetContainer.Add("InsideBOKDot"		,InsideNOKDot);
		RetContainer.Add("InsideBMergin"	,InsideNMergin);

		OutsideBOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("OutsideBOKColorL"	,L);
		RetContainer.Add("OutsideBOKColorH"	,H);

		OutsideBTrOKColor.GetRelMonoRange(L ,H);
		RetContainer.Add("OutsideBTrOKColorL"	,L);
		RetContainer.Add("OutsideBTrOKColorH"	,H);

		RetContainer.Add("OutsideBOKDot"	,OutsideNOKDot);
		RetContainer.Add("OutsideBMergin"	,OutsideNMergin);
	}
	else if(GetLayersBase()->GetLayerNumb(0)>=3){
		int	RL,RH;
		int	GL,GH;
		int	BL,BH;
		InsideNOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("InsideNOKColorRL"	,RL);
		RetContainer.Add("InsideNOKColorRH"	,RH);
		RetContainer.Add("InsideNOKColorGL"	,GL);
		RetContainer.Add("InsideNOKColorGH"	,GH);
		RetContainer.Add("InsideNOKColorBL"	,BL);
		RetContainer.Add("InsideNOKColorBH"	,BH);

		InsideNTrOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("InsideNTrOKColorRL"	,RL);
		RetContainer.Add("InsideNTrOKColorRH"	,RH);
		RetContainer.Add("InsideNTrOKColorGL"	,GL);
		RetContainer.Add("InsideNTrOKColorGH"	,GH);
		RetContainer.Add("InsideNTrOKColorBL"	,BL);
		RetContainer.Add("InsideNTrOKColorBH"	,BH);

		RetContainer.Add("InsideNOKDot"		,InsideNOKDot);
		RetContainer.Add("InsideNMergin"	,InsideNMergin);

		OutsideNOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("OutsideNOKColorRL"	,RL);
		RetContainer.Add("OutsideNOKColorRH"	,RH);
		RetContainer.Add("OutsideNOKColorGL"	,GL);
		RetContainer.Add("OutsideNOKColorGH"	,GH);
		RetContainer.Add("OutsideNOKColorBL"	,BL);
		RetContainer.Add("OutsideNOKColorBH"	,BH);

		OutsideNTrOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("OutsideNTrOKColorRL"	,RL);
		RetContainer.Add("OutsideNTrOKColorRH"	,RH);
		RetContainer.Add("OutsideNTrOKColorGL"	,GL);
		RetContainer.Add("OutsideNTrOKColorGH"	,GH);
		RetContainer.Add("OutsideNTrOKColorBL"	,BL);
		RetContainer.Add("OutsideNTrOKColorBH"	,BH);

		RetContainer.Add("OutsideNOKDot"	,OutsideNOKDot);
		RetContainer.Add("OutsideNMergin"	,OutsideNMergin);


		InsideBOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("InsideBOKColorRL"	,RL);
		RetContainer.Add("InsideBOKColorRH"	,RH);
		RetContainer.Add("InsideBOKColorGL"	,GL);
		RetContainer.Add("InsideBOKColorGH"	,GH);
		RetContainer.Add("InsideBOKColorBL"	,BL);
		RetContainer.Add("InsideBOKColorBH"	,BH);

		InsideBTrOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("InsideBTrOKColorRL"	,RL);
		RetContainer.Add("InsideBTrOKColorRH"	,RH);
		RetContainer.Add("InsideBTrOKColorGL"	,GL);
		RetContainer.Add("InsideBTrOKColorGH"	,GH);
		RetContainer.Add("InsideBTrOKColorBL"	,BL);
		RetContainer.Add("InsideBTrOKColorBH"	,BH);

		RetContainer.Add("InsideBOKDot"		,InsideNOKDot);
		RetContainer.Add("InsideBMergin"	,InsideNMergin);

		OutsideBOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("OutsideBOKColorRL"	,RL);
		RetContainer.Add("OutsideBOKColorRH"	,RH);
		RetContainer.Add("OutsideBOKColorGL"	,GL);
		RetContainer.Add("OutsideBOKColorGH"	,GH);
		RetContainer.Add("OutsideBOKColorBL"	,BL);
		RetContainer.Add("OutsideBOKColorBH"	,BH);

		OutsideBTrOKColor.GetRelColorRange(RL,RH ,GL,GH ,BL,BH);
		RetContainer.Add("OutsideBTrOKColorRL"	,RL);
		RetContainer.Add("OutsideBTrOKColorRH"	,RH);
		RetContainer.Add("OutsideBTrOKColorGL"	,GL);
		RetContainer.Add("OutsideBTrOKColorGH"	,GH);
		RetContainer.Add("OutsideBTrOKColorBL"	,BL);
		RetContainer.Add("OutsideBTrOKColorBH"	,BH);
	
		RetContainer.Add("OutsideBOKDot"	,OutsideNOKDot);
		RetContainer.Add("OutsideBMergin"	,OutsideNMergin);
	}

	RetContainer.Add("EffectiveNInside"		,EffectiveNInside);
	RetContainer.Add("EffectiveNOutside"	,EffectiveNOutside);
	RetContainer.Add("EffectiveBInside"		,EffectiveBInside);
	RetContainer.Add("EffectiveBOutside"	,EffectiveBOutside);

	RetContainer.Add("SelfSearch"			,SelfSearch);
	RetContainer.Add("AdjustMode"			,AdjustMode);
	RetContainer.Add("AdjustLimitLInside"	,AdjustLimitLInside);
	RetContainer.Add("AdjustLimitHInside"	,AdjustLimitHInside);
	RetContainer.Add("AdjustLimitLOutside"	,AdjustLimitLOutside);
	RetContainer.Add("AdjustLimitHOutside"	,AdjustLimitHOutside);
	RetContainer.Add("DiffMode"				,DiffMode);
	RetContainer.Add("AbsMode"				,AbsMode);
}
