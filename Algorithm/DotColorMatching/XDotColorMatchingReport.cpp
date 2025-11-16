#include "DotColorMatchingResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DotColorMatching\XDotColorMatchingReport.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XDotColorMatchingLibrary.h"
#include "XDataAlgorithm.h"

void	DotColorMatchingLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_85)/*"PickupRL"*/		,PickupRL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_86)/*"PickupRH"*/		,PickupRH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_87)/*"PickupGL"*/		,PickupGL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_88)/*"PickupGH"*/		,PickupGH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_89)/*"PickupBL"*/		,PickupBL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_90)/*"PickupBH"*/		,PickupBH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_91)/*"EvenWidth0"*/	,EvenWidth0);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_92)/*"EvenWidth255"*/	,EvenWidth255);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_93)/*"MinDotColorMatchingSize"*/		,MinDotColorMatchingSize);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_94)/*"MaxDotColorMatchingSize"*/		,MaxDotColorMatchingSize);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_95)/*"MinDotColorMatchingDots"*/		,MinDotColorMatchingDots);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_96)/*"MaxDotColorMatchingDots"*/		,MaxDotColorMatchingDots);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_97)/*"LimitDotColorMatchingSize"*/	,LimitDotColorMatchingSize);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_98)/*"GenerateOnEdgeWidth"*/			,GenerateOnEdgeWidth);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_99)/*"OutlineAroundPriorItems"*/		,OutlineAroundPriorItems);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_100)/*"SearchDotForBrightnessRange"*/	,SearchDotForBrightnessRange);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_101)/*"BindGroupArea"*/				,BindGroupArea);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_102)/*"PriorityToShow"*/				,PriorityToShow);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_103)/*"NoiseSize"*/			,NoiseSize);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_104)/*"NoiseSizePinHole"*/		,NoiseSizePinHole);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_105)/*"SpaceToOutline"*/		,SpaceToOutline);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_106)/*"Priority"*/				,Priority);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_107)/*"AreaType"*/				,AreaType);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_108)/*"EnableOverlap"*/		,EnableOverlap);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_109)/*"GenerateOutlineMode"*/	,GenerateOutlineMode);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_110)/*"GenerateHalfPitch"*/	,GenerateHalfPitch);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_111)/*"ThresholdPickupEdge"*/	,ThresholdPickupEdge);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_112)/*"ThresholdFlatPattern"*/	,ThresholdFlatPattern);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_113)/*"UseBackGround"*/		,UseBackGround);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_203)/*"BrightWidthBRL"*/	,Broad.BrightWidthRL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_216)/*"BrightWidthBRH"*/	,Broad.BrightWidthRH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_217)/*"BrightWidthBGL"*/	,Broad.BrightWidthGL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_218)/*"BrightWidthBGH"*/	,Broad.BrightWidthGH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_267)/*"BrightWidthBBL"*/	,Broad.BrightWidthBL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_268)/*"BrightWidthBBH"*/	,Broad.BrightWidthBH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_269)/*"OKDotB"*/			,Broad.OKDot);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_270)/*"OKLengthB"*/		,Broad.OKLength);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_271)/*"RThrOffsetBL"*/		,Broad.RThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_272)/*"RThrOffsetBH"*/		,Broad.RThrOffsetH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_273)/*"GThrOffsetBL"*/		,Broad.GThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_274)/*"GThrOffsetBH"*/		,Broad.GThrOffsetH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_275)/*"BThrOffsetBL"*/		,Broad.BThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_276)/*"BThrOffsetBH"*/		,Broad.BThrOffsetH);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_277)/*"BrightWidthNRL"*/	,Narrow.BrightWidthRL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_278)/*"BrightWidthNRH"*/	,Narrow.BrightWidthRH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_279)/*"BrightWidthNGL"*/	,Narrow.BrightWidthGL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_280)/*"BrightWidthNGH"*/	,Narrow.BrightWidthGH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_281)/*"BrightWidthNBL"*/	,Narrow.BrightWidthBL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_282)/*"BrightWidthNBH"*/	,Narrow.BrightWidthBH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_283)/*"OKDotN"*/			,Narrow.OKDot);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_284)/*"OKLengthN"*/		,Narrow.OKLength);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_285)/*"RThrOffsetNL"*/		,Narrow.RThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_286)/*"RThrOffsetNH"*/		,Narrow.RThrOffsetH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_287)/*"GThrOffsetNL"*/		,Narrow.GThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_288)/*"GThrOffsetNH"*/		,Narrow.GThrOffsetH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_289)/*"BThrOffsetNL"*/		,Narrow.BThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_290)/*"BThrOffsetNH"*/		,Narrow.BThrOffsetH);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_120)/*"VarietySigma"*/		,VarietySigma);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_123)/*"MultiSpotDot"*/		,MultiSpotDot);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_124)/*"MultiSpotCount"*/	,MultiSpotCount);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_125)/*"MultiSpotDotGathered"*/		,MultiSpotDotGathered);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_126)/*"MultiSpotCountGathered"*/	,MultiSpotCountGathered);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_127)/*"MultiSpotLengthGathered"*/	,MultiSpotLengthGathered);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_128)/*"BackGroundOKDot"*/	,BackGroundOKDot);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_129)/*"BackGroundOKLength"*/,BackGroundOKLength);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_130)/*"AdjustBlack"*/		,AdjustBlack);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_131)/*"AdjustWhite"*/		,AdjustWhite);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_263)/*"AreaSearchX"*/		,AreaSearchX);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_264)/*"AreaSearchY"*/		,AreaSearchY);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_133)/*"SelfSearch"*/		,SelfSearch);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_134)/*"Clusterize"*/		,Clusterize);
	//RetContainer.Add("SmoothCluster"	,SmoothCluster);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_135)/*"EnableT2M"*/		,EnableT2M);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_136)/*"EnableM2T"*/		,EnableM2T);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_137)/*"UseMaster2"*/		,UseMaster2);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_144)/*"ScratchEnable"*/		,ScratchEnable);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_145)/*"ScratchStartDirection"*/,ScratchStartDirection);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_146)/*"ScratchRotationAngle"*/	,ScratchRotationAngle);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_147)/*"ScratchDiff"*/			,ScratchDiff);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_148)/*"ScratchVariety"*/		,ScratchVariety);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_149)/*"ScratchDetectLevelL"*/	,ScratchDetectLevelL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_150)/*"ScratchDetectLevelH"*/	,ScratchDetectLevelH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_151)/*"ScratchMaxWidth"*/		,ScratchMaxWidth);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_152)/*"ScratchUseMaster"*/		,ScratchUseMaster);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_153)/*"ScratchVOffset"*/		,ScratchVOffset);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_154)/*"RedCheckMode"*/			,RedCheckMode);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_155)/*"RedHighRate"*/			,RedHighRate);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_156)/*"RedMinBrightness"*/		,RedMinBrightness);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_157)/*"RedGBMerginRate"*/		,RedGBMerginRate);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_158)/*"RedGBMerginOffset"*/	,RedGBMerginOffset);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_159)/*"RedShrink"*/			,RedShrink);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_160)/*"RedOKDot"*/				,RedOKDot);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_161)/*"UseOneLayer"*/				,UseOneLayer);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_162)/*"MatchBrightnessByLayerH"*/	,MatchBrightnessByLayerH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_163)/*"MatchBrightnessByLayerL"*/	,MatchBrightnessByLayerL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_164)/*"MasterNoOriginCode"*/		,MasterNoOriginCode);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_165)/*"HsvCheckMode"*/		,HsvCheckMode);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_166)/*"HsvFixedColorMode"*/,HsvFixedColorMode);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_167)/*"HsvH"*/				,HsvH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_168)/*"HsvS"*/				,HsvS);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_169)/*"HsvV"*/				,HsvV);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_170)/*"HsvPHL"*/			,HsvPHL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_171)/*"HsvPHH"*/			,HsvPHH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_172)/*"HsvPSL"*/			,HsvPSL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_173)/*"HsvPSH"*/			,HsvPSH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_174)/*"HsvPVL"*/			,HsvPVL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_175)/*"HsvPVH"*/			,HsvPVH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_176)/*"HsvDHL"*/			,HsvDHL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_177)/*"HsvDHH"*/			,HsvDHH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_178)/*"HsvDSL"*/			,HsvDSL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_179)/*"HsvDSH"*/			,HsvDSH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_180)/*"HsvDVL"*/			,HsvDVL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_181)/*"HsvDVH"*/			,HsvDVH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_182)/*"HsvOKDot"*/			,HsvOKDot);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_183)/*"HsvOKLength"*/		,HsvOKLength);
}

void	DotColorMatchingThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_291)/*"BrightWidthBRL"*/	,Broad.BrightWidthRL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_292)/*"BrightWidthBRH"*/	,Broad.BrightWidthRH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_293)/*"BrightWidthBGL"*/	,Broad.BrightWidthGL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_294)/*"BrightWidthBGH"*/	,Broad.BrightWidthGH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_295)/*"BrightWidthBBL"*/	,Broad.BrightWidthBL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_296)/*"BrightWidthBBH"*/	,Broad.BrightWidthBH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_297)/*"OKDotB"*/			,Broad.OKDot);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_298)/*"OKLengthB"*/		,Broad.OKLength);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_299)/*"RThrOffsetBL"*/		,Broad.RThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_300)/*"RThrOffsetBH"*/		,Broad.RThrOffsetH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_301)/*"GThrOffsetBL"*/		,Broad.GThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_302)/*"GThrOffsetBH"*/		,Broad.GThrOffsetH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_303)/*"BThrOffsetBL"*/		,Broad.BThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_304)/*"BThrOffsetBH"*/		,Broad.BThrOffsetH);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_305)/*"BrightWidthNRL"*/	,Narrow.BrightWidthRL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_306)/*"BrightWidthNRH"*/	,Narrow.BrightWidthRH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_307)/*"BrightWidthNGL"*/	,Narrow.BrightWidthGL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_308)/*"BrightWidthNGH"*/	,Narrow.BrightWidthGH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_309)/*"BrightWidthNBL"*/	,Narrow.BrightWidthBL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_310)/*"BrightWidthNBH"*/	,Narrow.BrightWidthBH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_311)/*"OKDotN"*/			,Narrow.OKDot);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_312)/*"OKLengthN"*/		,Narrow.OKLength);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_313)/*"RThrOffsetNL"*/		,Narrow.RThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_314)/*"RThrOffsetNH"*/		,Narrow.RThrOffsetH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_315)/*"GThrOffsetNL"*/		,Narrow.GThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_316)/*"GThrOffsetNH"*/		,Narrow.GThrOffsetH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_317)/*"BThrOffsetNL"*/		,Narrow.BThrOffsetL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_318)/*"BThrOffsetNH"*/		,Narrow.BThrOffsetH);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_190)/*"VarietySigma"*/		,VarietySigma);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_193)/*"MultiSpotDot"*/		,MultiSpotDot);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_194)/*"MultiSpotCount"*/	,MultiSpotCount);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_195)/*"MultiSpotDotGathered"*/		,MultiSpotDotGathered);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_196)/*"MultiSpotCountGathered"*/	,MultiSpotCountGathered);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_197)/*"MultiSpotLengthGathered"*/	,MultiSpotLengthGathered);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_198)/*"BackGroundOKDot"*/	,BackGroundOKDot);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_199)/*"BackGroundOKLength"*/,BackGroundOKLength);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_200)/*"UseBackGround"*/	,UseBackGround);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_201)/*"AdjustBlack"*/		,AdjustBlack);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_202)/*"AdjustWhite"*/		,AdjustWhite);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_265)/*"AreaSearchX"*/		,AreaSearchX);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_266)/*"AreaSearchY"*/		,AreaSearchY);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_204)/*"SelfSearch"*/		,SelfSearch);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_205)/*"Clusterize"*/		,Clusterize);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_206)/*"SmoothCluster"*/	,SmoothCluster);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_207)/*"EnableT2M"*/		,EnableT2M);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_208)/*"EnableM2T"*/		,EnableM2T);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_209)/*"UseMaster2"*/		,UseMaster2);

	//RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_216)/*"AddedBrightness"*/		,(int)AddedBrightness);
	//RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_217)/*"AddedOffset"*/			,(int)AddedOffset);
	//RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_218)/*"AddedShift"*/			,(int)AddedShift);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_219)/*"ScratchEnable"*/		,ScratchEnable);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_220)/*"ScratchStartDirection"*/,ScratchStartDirection);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_221)/*"ScratchRotationAngle"*/	,ScratchRotationAngle);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_222)/*"ScratchDiff"*/			,ScratchDiff);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_223)/*"ScratchVariety"*/		,ScratchVariety);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_224)/*"ScratchDetectLevelL"*/	,ScratchDetectLevelL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_225)/*"ScratchDetectLevelH"*/	,ScratchDetectLevelH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_226)/*"ScratchMaxWidth"*/		,ScratchMaxWidth);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_227)/*"ScratchUseMaster"*/		,ScratchUseMaster);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_228)/*"ScratchVOffset"*/		,ScratchVOffset);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_229)/*"RedCheckMode"*/			,RedCheckMode);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_230)/*"RedHighRate"*/			,RedHighRate);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_231)/*"RedMinBrightness"*/		,RedMinBrightness);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_232)/*"RedGBMerginRate"*/		,RedGBMerginRate);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_233)/*"RedGBMerginOffset"*/	,RedGBMerginOffset);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_234)/*"RedShrink"*/			,RedShrink);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_235)/*"RedOKDot"*/				,RedOKDot);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_236)/*"UseOneLayer"*/			,UseOneLayer);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_237)/*"MatchBrightnessByLayerH"*/	,MatchBrightnessByLayerH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_238)/*"MatchBrightnessByLayerL"*/	,MatchBrightnessByLayerL);

	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_239)/*"HsvCheckMode"*/		,HsvCheckMode);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_240)/*"HsvFixedColorMode"*/,HsvFixedColorMode);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_241)/*"HsvH"*/				,HsvH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_242)/*"HsvS"*/				,HsvS);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_243)/*"HsvV"*/				,HsvV);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_244)/*"HsvPHL"*/			,HsvPHL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_245)/*"HsvPHH"*/			,HsvPHH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_246)/*"HsvPSL"*/			,HsvPSL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_247)/*"HsvPSH"*/			,HsvPSH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_248)/*"HsvPVL"*/			,HsvPVL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_249)/*"HsvPVH"*/			,HsvPVH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_250)/*"HsvDHL"*/			,HsvDHL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_251)/*"HsvDHH"*/			,HsvDHH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_252)/*"HsvDSL"*/			,HsvDSL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_253)/*"HsvDSH"*/			,HsvDSH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_254)/*"HsvDVL"*/			,HsvDVL);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_255)/*"HsvDVH"*/			,HsvDVH);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_256)/*"HsvOKDot"*/			,HsvOKDot);
	RetContainer.Add(LangSolver.GetString(XDotColorMatchingReport_LS,LID_257)/*"HsvOKLength"*/		,HsvOKLength);
}
