/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBlockInspection.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XBOCKINSPECTION_H)
#define	XBOCKINSPECTION_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
//#include "XPropertyBlockPacket.h"
#include "XBlockLibrary.h"
#include "XBlockSearchWay.h"
#include "XResult.h"
#include "XLineInBlock.h"
#include "XStandardCommand.h"

#define	BlockInspectionVersion	10029
#define	Hist_BlockInspection_CenterBright	1
#define	Hist_BlockInspection_BLightNGSize	2
#define	Hist_BlockInspection_BDarkNGSize	3
#define	Hist_BlockInspection_NLightNGSize	4
#define	Hist_BlockInspection_NDarkNGSize	5
#define	Hist_BlockInspection_X_Shift		6
#define	Hist_BlockInspection_Y_Shift		7
#define	Hist_BlockInspection_BBrightnessLow		8
#define	Hist_BlockInspection_BBrightnessHigh	9
#define	Hist_BlockInspection_NBrightnessLow		10
#define	Hist_BlockInspection_NBrightnessHigh	11

const	int	BLKMergin	=4;

class   AlignmentInLayer;
class	XAlignmentArea;
class	BlockLibrary;
class	BlockBase;
class	BlockItem;
class	BlockInLayer;
class	SetThresholdBlockInfo;
class	ExecutablePointerContainer;

class	BlockInfoList;

#pragma	pack(push,1)

class	BlockThreshold : public AlgorithmThreshold
{
public:
	struct	_ThreshouldBag5
	{
	WORD	NBrightWidthL;	//‹·ˆæ‚ÌˆÃ‘¤‹P“x•
	WORD	NBrightWidthH;	//‹·ˆæ‚Ì–¾‘¤‹P“x•
	DWORD	NOKDotL;		//‹·ˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	DWORD	NOKDotH;		//‹·ˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	DWORD	NMaxNGDotL;		//‹·ˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	DWORD	NMaxNGDotH;		//‹·ˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	WORD	NOKLengthL;		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	NOKLengthH;		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	BBrightWidthL;	//Lˆæ‚ÌˆÃ‘¤‹P“x•
	WORD	BBrightWidthH;	//Lˆæ‚Ì–¾‘¤‹P“x•
	DWORD	BOKDotL;		//Lˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	DWORD	BOKDotH;		//Lˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	DWORD	BMaxNGDotL;		//Lˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	DWORD	BMaxNGDotH;		//Lˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	WORD	BOKLengthL;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	BOKLengthH;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	DiffBrightWidthL;
	WORD	DiffBrightWidthH;
	short	RegularCenterBright;

	WORD	NMinNGCountL;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	NMinNGCountH;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountL;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountH;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	int8	NConnectLen;	//‹·ˆæ‚Ì‚m‚fÚ‘±‹——£
	int8	BConnectLen;	//Lˆæ‚Ì‚m‚fÚ‘±‹——£
	WORD	ExpandForGenMask;	//Expansion dot for dynamic mask to generate in ExecuteIntialAfterEdit

	struct {
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeDiffer:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
		bool	ModeCalcBothBN:1;
		bool	ModeInvertLogic:1;
		bool	ModeMatchPosition:1;
		bool	ModeSearchDetail:1;
		bool	ModeDynamicMask:1;
		bool	ModeBindBWBroad:1;
		bool	ModeBindBWNarrow:1;
		bool	ModeAdoptBiggest:1;
		bool	ModeUseMasterImage:1;
		bool	ModeUseRegularBrightness:1;
		bool	ModePermitInverted:1;	//For outline-matching
		bool	ModeMatchPositionBW:1;	//Follow outline
										//(ModeMatchPosition,ModeMatchPositionBW)
										//(false,false)=None ,(true,false)=Ignore BW  (false,true)=Pattern W,  (true,true)=Pattern B
		bool	ModeOppositeRange:1;
		bool	ModeUseGlobalLine:1;	//Follow outline-matching
	}PointMove;

	struct __PointMoveOld{
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeDiffer:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
		bool	ModeCalcBothBN:1;
		bool	ModeInvertLogic:1;
		bool	ModeMatchPosition:1;
		bool	ModeSearchDetail:1;
		bool	ModeDynamicMask:1;
	};
	enum{
		_FromUnknown	=0
		,_FromLibrary	=1
		,_FromManual	=2
		,_FromParts		=3
		,_FromMPA		=4
		,_FromCAD		=5
	}GeneratedOriginOld;		//Don't use, This is for old data

    int32   CommonMoveID;
    WORD	CommonMoveDot;

	WORD	SpaceToOutline;	//ModeMatchPosition==true‚Ì‚Æ‚«‚µ‚©g‚í‚È‚¢
    WORD	AdjustBlack;    //‹P“x•â³‚Ì‰ºŒÀ•
    WORD	AdjustWhite;    //‹P“x•â³‚ÌãŒÀ•
    WORD	SelfSearch;     //©ŒÈ’Tõƒhƒbƒg”
	WORD	OmitVectorIndex;//’Tõ‹Ö?•ûŒü	0xFFFF‚Ì‚Æ‚«A‹Ö?‚È‚µ
	int8	FollowLineLayer;//-1:Save layer
	}ThreshouldBag;

	struct	_ThreshouldBag4
	{
	WORD	NBrightWidthL;	//‹·ˆæ‚ÌˆÃ‘¤‹P“x•
	WORD	NBrightWidthH;	//‹·ˆæ‚Ì–¾‘¤‹P“x•
	DWORD	NOKDotL;		//‹·ˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	DWORD	NOKDotH;		//‹·ˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	DWORD	NMaxNGDotL;		//‹·ˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	DWORD	NMaxNGDotH;		//‹·ˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	WORD	NOKLengthL;		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	NOKLengthH;		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	BBrightWidthL;	//Lˆæ‚ÌˆÃ‘¤‹P“x•
	WORD	BBrightWidthH;	//Lˆæ‚Ì–¾‘¤‹P“x•
	DWORD	BOKDotL;		//Lˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	DWORD	BOKDotH;		//Lˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	DWORD	BMaxNGDotL;		//Lˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	DWORD	BMaxNGDotH;		//Lˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	WORD	BOKLengthL;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	BOKLengthH;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	DiffBrightWidthL;
	WORD	DiffBrightWidthH;
	short	RegularCenterBright;

	WORD	NMinNGCountL;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	NMinNGCountH;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountL;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountH;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	int8	NConnectLen;	//‹·ˆæ‚Ì‚m‚fÚ‘±‹——£
	int8	BConnectLen;	//Lˆæ‚Ì‚m‚fÚ‘±‹——£
	WORD	ExpandForGenMask;	//Expansion dot for dynamic mask to generate in ExecuteIntialAfterEdit

	struct {
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeDiffer:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
		bool	ModeCalcBothBN:1;
		bool	ModeInvertLogic:1;
		bool	ModeMatchPosition:1;
		bool	ModeSearchDetail:1;
		bool	ModeDynamicMask:1;
		bool	ModeBindBWBroad:1;
		bool	ModeBindBWNarrow:1;
		bool	ModeAdoptBiggest:1;
		bool	ModeUseMasterImage:1;
		bool	ModeUseRegularBrightness:1;
		bool	ModePermitInverted:1;	//For outline-matching
		bool	ModeMatchPositionBW:1;	//Follow outline
										//(ModeMatchPosition,ModeMatchPositionBW)
										//(false,false)=None ,(true,false)=Ignore BW  (false,true)=Pattern W,  (true,true)=Pattern B
		bool	ModeOppositeRange:1;
		bool	ModeUseGlobalLine:1;	//Follow outline-matching
	}PointMove;

	struct __PointMoveOld{
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeDiffer:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
		bool	ModeCalcBothBN:1;
		bool	ModeInvertLogic:1;
		bool	ModeMatchPosition:1;
		bool	ModeSearchDetail:1;
		bool	ModeDynamicMask:1;
	};
	enum{
		_FromUnknown	=0
		,_FromLibrary	=1
		,_FromManual	=2
		,_FromParts		=3
		,_FromMPA		=4
		,_FromCAD		=5
	}GeneratedOriginOld;		//Don't use, This is for old data

    int32   CommonMoveID;
    WORD	CommonMoveDot;

	WORD	SpaceToOutline;	//ModeMatchPosition==true‚Ì‚Æ‚«‚µ‚©g‚í‚È‚¢
    WORD	AdjustBlack;    //‹P“x•â³‚Ì‰ºŒÀ•
    WORD	AdjustWhite;    //‹P“x•â³‚ÌãŒÀ•
    WORD	SelfSearch;     //©ŒÈ’Tõƒhƒbƒg”
	WORD	OmitVectorIndex;//’Tõ‹Ö?•ûŒü	0xFFFF‚Ì‚Æ‚«A‹Ö?‚È‚µ
	};

	struct	_ThreshouldBag3
	{
	WORD	NBrightWidthL;	//‹·ˆæ‚ÌˆÃ‘¤‹P“x•
	WORD	NBrightWidthH;	//‹·ˆæ‚Ì–¾‘¤‹P“x•
	DWORD	NOKDotL;		//‹·ˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	DWORD	NOKDotH;		//‹·ˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	DWORD	NMaxNGDotL;		//‹·ˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	DWORD	NMaxNGDotH;		//‹·ˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	WORD	NOKLengthL;		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	NOKLengthH;		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	BBrightWidthL;	//Lˆæ‚ÌˆÃ‘¤‹P“x•
	WORD	BBrightWidthH;	//Lˆæ‚Ì–¾‘¤‹P“x•
	DWORD	BOKDotL;		//Lˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	DWORD	BOKDotH;		//Lˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	DWORD	BMaxNGDotL;		//Lˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	DWORD	BMaxNGDotH;		//Lˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	WORD	BOKLengthL;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	BOKLengthH;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	DiffBrightWidthL;
	WORD	DiffBrightWidthH;
	short	RegularCenterBright;

	WORD	NMinNGCountL;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	NMinNGCountH;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountL;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountH;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	int8	NConnectLen;	//‹·ˆæ‚Ì‚m‚fÚ‘±‹——£
	int8	BConnectLen;	//Lˆæ‚Ì‚m‚fÚ‘±‹——£

	struct {
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeDiffer:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
		bool	ModeCalcBothBN:1;
		bool	ModeInvertLogic:1;
		bool	ModeMatchPosition:1;
		bool	ModeSearchDetail:1;
		bool	ModeDynamicMask:1;
		bool	ModeBindBWBroad:1;
		bool	ModeBindBWNarrow:1;
		bool	ModeAdoptBiggest:1;
		bool	ModeUseMasterImage:1;
		bool	ModeUseRegularBrightness:1;
		bool	ModePermitInverted:1;	//For outline-matching
		bool	ModeMatchPositionBW:1;	//Follow outline
										//(ModeMatchPosition,ModeMatchPositionBW)
										//(false,false)=None ,(true,false)=Ignore BW  (false,true)=Pattern W,  (true,true)=Pattern B
		bool	ModeOppositeRange:1;
		bool	ModeUseGlobalLine:1;	//Follow outline-matching
	}PointMove;

	struct __PointMoveOld{
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeDiffer:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
		bool	ModeCalcBothBN:1;
		bool	ModeInvertLogic:1;
		bool	ModeMatchPosition:1;
		bool	ModeSearchDetail:1;
		bool	ModeDynamicMask:1;
	};
	enum{
		_FromUnknown	=0
		,_FromLibrary	=1
		,_FromManual	=2
		,_FromParts		=3
		,_FromMPA		=4
		,_FromCAD		=5
	}GeneratedOriginOld;		//Don't use, This is for old data

    int32   CommonMoveID;
    WORD	CommonMoveDot;

	WORD	SpaceToOutline;	//ModeMatchPosition==true‚Ì‚Æ‚«‚µ‚©g‚í‚È‚¢
    WORD	AdjustBlack;    //‹P“x•â³‚Ì‰ºŒÀ•
    WORD	AdjustWhite;    //‹P“x•â³‚ÌãŒÀ•
    WORD	SelfSearch;     //©ŒÈ’Tõƒhƒbƒg”
	WORD	OmitVectorIndex;//’Tõ‹Ö?•ûŒü	0xFFFF‚Ì‚Æ‚«A‹Ö?‚È‚µ
	};

	struct	_ThreshouldBag2
	{
	WORD	NBrightWidthL;	//‹·ˆæ‚ÌˆÃ‘¤‹P“x•
	WORD	NBrightWidthH;	//‹·ˆæ‚Ì–¾‘¤‹P“x•
	DWORD	NOKDotL;		//‹·ˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	DWORD	NOKDotH;		//‹·ˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	DWORD	NMaxNGDotL;		//‹·ˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	DWORD	NMaxNGDotH;		//‹·ˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	WORD	NOKLengthL;		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	NOKLengthH;		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	BBrightWidthL;	//Lˆæ‚ÌˆÃ‘¤‹P“x•
	WORD	BBrightWidthH;	//Lˆæ‚Ì–¾‘¤‹P“x•
	DWORD	BOKDotL;		//Lˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	DWORD	BOKDotH;		//Lˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	DWORD	BMaxNGDotL;		//Lˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	DWORD	BMaxNGDotH;		//Lˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	WORD	BOKLengthL;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	BOKLengthH;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	DiffBrightWidthL;
	WORD	DiffBrightWidthH;

	WORD	NMinNGCountL;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	NMinNGCountH;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountL;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountH;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	int8	NConnectLen;	//‹·ˆæ‚Ì‚m‚fÚ‘±‹——£
	int8	BConnectLen;	//Lˆæ‚Ì‚m‚fÚ‘±‹——£

	struct {
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeDiffer:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
		bool	ModeCalcBothBN:1;
		bool	ModeInvertLogic:1;
		bool	ModeMatchPosition:1;	//Follow outline
		bool	ModeSearchDetail:1;
		bool	ModeDynamicMask:1;
		bool	ModeBindBWBroad:1;
		bool	ModeBindBWNarrow:1;
		bool	ModeAdoptBiggest:1;
		bool	ModeUseMasterImage:1;
		bool	ModeUseRegularBrightness:1;
	}PointMove;

	struct __PointMoveOld{
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeDiffer:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
		bool	ModeCalcBothBN:1;
		bool	ModeInvertLogic:1;
		bool	ModeMatchPosition:1;
		bool	ModeSearchDetail:1;
		bool	ModeDynamicMask:1;
	};

	enum{
		_FromUnknown	=0
		,_FromLibrary	=1
		,_FromManual	=2
		,_FromParts		=3
		,_FromMPA		=4
		,_FromCAD		=5
	}GeneratedOrigin;

    int32   CommonMoveID;
    WORD	CommonMoveDot;

	WORD	SpaceToOutline;	//ModeMatchPosition==true‚Ì‚Æ‚«‚µ‚©g‚í‚È‚¢
    WORD	AdjustBlack;    //‹P“x•â³‚Ì‰ºŒÀ•
    WORD	AdjustWhite;    //‹P“x•â³‚ÌãŒÀ•
    WORD	SelfSearch;     //©ŒÈ’Tõƒhƒbƒg”
	WORD	OmitVectorIndex;//’Tõ‹Ö?•ûŒü	0xFFFF‚Ì‚Æ‚«A‹Ö?‚È‚µ
	};

	struct	_CalculatedInfo
	{
		bool	ModeSmallCalc:1;
	}CalculatedInfo;

	BlockThreshold(BlockItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	void	CopyFrom(const AlgorithmThreshold &src,IntList &EdittedMemberID)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)				override;
    virtual	bool	Load(QIODevice *f)				override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	void	RegistHist(void)					override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

enum ThresholdMember
{
	 ID_NBrightWidthL	//‹·ˆæ‚ÌˆÃ‘¤‹P“x•
	,ID_NBrightWidthH	//‹·ˆæ‚Ì–¾‘¤‹P“x•
	,ID_NOKDotL			//‹·ˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	,ID_NOKDotH			//‹·ˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	,ID_NMaxNGDotL		//‹·ˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	,ID_NMaxNGDotH		//‹·ˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	,ID_NOKLengthL		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	,ID_NOKLengthH		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	,ID_BBrightWidthL	//Lˆæ‚ÌˆÃ‘¤‹P“x•
	,ID_BBrightWidthH	//Lˆæ‚Ì–¾‘¤‹P“x•
	,ID_BOKDotL			//Lˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	,ID_BOKDotH			//Lˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	,ID_BMaxNGDotL		//Lˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	,ID_BMaxNGDotH		//Lˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	,ID_BOKLengthL		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	,ID_BOKLengthH		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	,ID_DiffBrightWidthL
	,ID_DiffBrightWidthH
	,ID_RegularCenterBright

	,ID_NMinNGCountL	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	,ID_NMinNGCountH	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	,ID_BMinNGCountL	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	,ID_BMinNGCountH	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	,ID_NConnectLen		//‹·ˆæ‚Ì‚m‚fÚ‘±‹——£
	,ID_BConnectLen		//Lˆæ‚Ì‚m‚fÚ‘±‹——£
	,ID_ExpandForGenMask	//Expansion dot for dynamic mask to generate in ExecuteIntialAfterEdit

	,ID_ModeEnabled
	,ID_ModeAdjustable
	,ID_ModeAbsoluteBright
	,ID_ModeCommonMovable
	,ID_ModeNGCluster
	,ID_ModeDiffer
	,ID_ModeCenterBrightFromParts
	,ID_ModeOnlyMatching
	,ID_ModeWhiteMask
	,ID_ModeBlackMask
	,ID_ModeCalcBothBN
	,ID_ModeInvertLogic
	,ID_ModeMatchPosition
	,ID_ModeSearchDetail
	,ID_ModeDynamicMask
	,ID_ModeBindBWBroad
	,ID_ModeBindBWNarrow
	,ID_ModeAdoptBiggest
	,ID_ModeUseMasterImage
	,ID_ModeUseRegularBrightness
	,ID_ModePermitInverted	
	,ID_ModeMatchPositionBW	
	,ID_ModeOppositeRange
	,ID_ModeUseGlobalLine

    ,ID_CommonMoveID
    ,ID_CommonMoveDot

	,ID_SpaceToOutline		//ModeMatchPosition==true‚Ì‚Æ‚«‚µ‚©g‚í‚È‚¢
    ,ID_AdjustBlack			//‹P“x•â³‚Ì‰ºŒÀ•
    ,ID_AdjustWhite			//‹P“x•â³‚ÌãŒÀ•
    ,ID_SelfSearch			//©ŒÈ’Tõƒhƒbƒg”
	,ID_OmitVectorIndex		//’Tõ‹Ö?•ûŒü	0xFFFF‚Ì‚Æ‚«A‹Ö?‚È‚µ
	,ID_FollowLineLayer		//-1:Save layer
};

class	BlockResultPosList : public ResultPosList
{
public:
	BlockResultPosList(void);
	BlockResultPosList(ResultPosList &src) : ResultPosList(src){}
	BlockResultPosList(int px ,int py) : ResultPosList(px,py){}
	BlockResultPosList(int px ,int py ,int rx ,int ry):ResultPosList(px ,py ,rx ,ry){}

	//virtual	void	DrawResult(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
	//									,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark);
	virtual	void	DrawResultDetail(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
										,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark);
};

#pragma	pack(pop)

const int	MaxCountOfBlockShiftList=100;
class	BlockShiftList
{
public:
	struct	BlockShiftInfo
	{
		int32	ShiftX;
		int32	ShiftY;
		double	MatchResult;
	}Dim[MaxCountOfBlockShiftList];
	int	DimNumb;
	int	CurrentNumb;

	BlockShiftList(void)
	{
		DimNumb=MaxCountOfBlockShiftList;
		CurrentNumb=0;
	}	
	~BlockShiftList(void);
};


struct	TmpStruct;

class   BlockItem : public AlgorithmItemPLI
{
#pragma	pack(push,1)
public:
	enum ThresholdMode{
		_ThresholdNarrow
		,_ThresholdBroad
	};
	FlexArea    FLineBeforeShrink;
    FlexArea    FLineEdge;
    FlexArea    FLineInside;

	WORD	CenterBright;
	WORD	CenterTargetBright;

	AlignmentPacket2D	*AVector;
	int32		ShiftX;
	int32		ShiftY;

public:
	class	FollowLines
	{
	public:
		HLineInBlock	LftMatchLine0;
		HLineInBlock	LftMatchLine1;
		HLineInBlock	LftMatchLine2;
		VLineInBlock	TopMatchLine0;
		VLineInBlock	TopMatchLine1;
		VLineInBlock	TopMatchLine2;

		HLineInBlock	RgtMatchLine0;
		HLineInBlock	RgtMatchLine1;
		HLineInBlock	RgtMatchLine2;
		VLineInBlock	BtmMatchLine0;
		VLineInBlock	BtmMatchLine1;
		VLineInBlock	BtmMatchLine2;

		FollowLines(BlockItem &Parent);

		FollowLines	&operator=(FollowLines &src);
		void	MoveTo(int dx ,int dy);
		void	CalcMatchPosition(bool ModeUseMasterImage 
								,FlexArea &FLineBeforeShrink
								,FlexArea &OmitMatchLineArea
								,int FollowLinelength
								,bool Gen_Left
								,bool Gen_Top
								,bool Gen_Right
								,bool Gen_Bottom
								,ExecuteInitialAfterEditInfo &EInfo);
		bool	IsEffective(void);
		void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &LineColor);
	};
	FollowLines	*FollowLineData;
	FlexArea		OmitMatchLineArea;


private:
	//Calculated
	FlexArea	AppeUp;
	FlexArea	AppeLeft;
	FlexArea	AppeRight;
	FlexArea	AppeBottom;
	FlexArea	DisaUp;
	FlexArea	DisaLeft;
	FlexArea	DisaRight;
	FlexArea	DisaBottom;

	struct	SkipSearchAreas
	{
		FlexArea	AppeUp;
		FlexArea	AppeLeft;
		FlexArea	AppeRight;
		FlexArea	AppeBottom;
		FlexArea	DisaUp;
		FlexArea	DisaLeft;
		FlexArea	DisaRight;
		FlexArea	DisaBottom;
	};
	struct	SkipSearchAreas	*SkipSearchAreasData;
#pragma	pack(pop)

  public:

	BlockItem(void);
	BlockItem(FlexArea &area);
	BlockItem(FlexArea *area);	//Use area pointer
    virtual	~BlockItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new BlockItem();	}
    virtual	void    MoveTo(int dx ,int dy)	override;
	const	BlockThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const BlockThreshold *)GetThresholdBaseReadable(base);	}
	BlockThreshold			*GetThresholdW(LayersBase *base=NULL){	return (BlockThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new BlockThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
    BlockItem &operator=(BlockItem &src);
	void	CopyThreshold(BlockItem &src);
	void	CopyThresholdOnly(BlockItem &src,IntList &EdittedMemberID);
	void	CopyArea(BlockItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	ExeResult	ExecuteProcessingCalc(int ThreadNo,ResultInItemRoot *Res,int mx ,int my);
	bool	ExecuteProcessingSimple(int Mx ,int My);

	virtual	void	SetInvertLogic(bool b)	override;
	virtual	bool	GetInvertLogic(void)	override;

	bool	UseMatchLine(void);
	void	SetThresholdFromCommon(SetThresholdBlockInfo *Info);
	void	GetShiftByAlignemnt(int &mx,int &my);
	double	CalcMatch(int dx,int dy);
	bool	RewindDynamicMask(BlockInLayer *BL);
	bool	SetDynamicMask(BlockInLayer *BL);
	virtual	void	SetAutoThreshold(ParamAutoThreshold &Param)	override;

  private:
	void	InitialConstructor(void);
	bool    ExecuteProcessingInner(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

	bool    ExecuteProcessingInnerWithoutSubtract(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	bool    ExecuteProcessingInnerWithoutSubtractFixX(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	bool    ExecuteProcessingInnerWithoutSubtractFixY(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	bool    ExecuteProcessingInnerWithoutSubtractCalcA(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot);
	bool    ExecuteProcessingInnerWithoutSubtractCalcAFixX(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot);
	bool    ExecuteProcessingInnerWithoutSubtractCalcAFixY(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot);

	bool    ExecuteProcessingInnerWithoutSubtractCalcA_s(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot);
	bool    ExecuteProcessingInnerWithoutSubtractCalcAFixX_s(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot);
	bool    ExecuteProcessingInnerWithoutSubtractCalcAFixY_s(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot);

	bool	ExecuteProcessingInnerNoMove(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my ,int ShiftX ,int ShiftY
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	bool	ExecuteProcessingSimpleWithoutSubtract(
						   int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

	bool	ExecuteProcessingInnerDiffer(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,WORD	DiffBrightWidthL,WORD DiffBrightWidthH
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

	bool    L3Remove(int mx ,int my
                           ,FlexArea &SubFLines
                           ,FlexArea &SubFLineEdge
                           ,FlexArea &SubFLineInside);

	void	Level3Inside(int mx ,int my
					,int BrightWidthL ,int BrightWidthH
					,int &InsideSumL,int &InsideSumH);

	void	Level3Speedy(int mx,int my
					,int TmpBrightWidthL ,int TmpBrightWidthH
					,int &SumL,int &SumH);
	void	Level3Speedy(int mx,int my
					,int TmpBrightWidthL ,int TmpBrightWidthH
					,int &SumL,int &SumH
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

	bool	CheckOnNG(int mx,int my ,int hx ,int hy
				, int BrightWidthL ,int BrightWidthH
				,int &ResultBrightWidthL ,int &ResultBrightWidthH
				, int OKDotL ,int OKDotH
				,int MaxNGDotL ,int MaxNGDotH
				,int &SumL,int &SumH
				,NPListPack<ResultPosList> &PosList
				,WORD	OKLengthL	,WORD	OKLengthH
				,WORD	MinNGCountL	,WORD MinNGCountH,int8 ConnectLen
				,short &Error
				,ThresholdMode NBMode ,bool BindBW
				,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

	void	CheckOnNGInner1(int dx ,int dy
							,int LLevel ,int HLevel
							,BYTE *pMapL ,BYTE *pMapH
							,int Lx ,int Ly ,int LByte,int starty
							,int &LSum,int &HSum
							,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	void	CheckOnNGInner2(int dx ,int dy
							,int LLevel ,int HLevel
							,BYTE *pMapL ,BYTE *pMapH
							,int Lx ,int Ly ,int LByte,int starty
							,int &LSum,int &HSum
							,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	
	XYClass	*GetSWayListFirst(int ThreadNo,int selfSearch);
	void	SetSWayListToTop(int ThreadNo,int selfSearch,XYClass *w);
	bool	AboveDMask(BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen,int dx,int dy);
	BlockLibNGTypeItem	*MakeNGType(FlexArea &NGArea ,LibNGTypeInAlgorithm &NGContainer);

	bool	ExeMatchLinePosition(int mx,int my ,BlockShiftList &BlockShiftListData ,bool &FixXDir,bool &FixYDir);
	int		ExeMatchLineSwing(ImageBuffer &DBuff
								,int mx,int my ,int Sep
								,struct BlockShiftList::BlockShiftInfo	*ShiftDim
								,HLineInBlock &HLine0 ,HLineInBlock &HLine1 ,HLineInBlock &HLine2
								,VLineInBlock &VLine0 ,VLineInBlock &VLine1 ,VLineInBlock &VLine2);
	int		ExeMatchLineSwing(ImageBuffer &DBuff
								,int mx,int my ,int Sep
								,struct BlockShiftList::BlockShiftInfo	*ShiftDim
								,HLineInBlock &HLine0 ,HLineInBlock &HLine1 ,HLineInBlock &HLine2
								,HLineInBlock &HLine3 ,HLineInBlock &HLine4 ,HLineInBlock &HLine5);
	int		ExeMatchLineSwing(ImageBuffer &DBuff
								,int mx,int my ,int Sep
								,struct BlockShiftList::BlockShiftInfo	*ShiftDim
								,VLineInBlock &VLine0 ,VLineInBlock &VLine1 ,VLineInBlock &VLine2
								,VLineInBlock &VLine3 ,VLineInBlock &VLine4 ,VLineInBlock &VLine5);
	int		ExeMatchLineSwing(ImageBuffer &DBuff
								,int mx,int my ,int Sep
								,struct BlockShiftList::BlockShiftInfo	*ShiftDim
								,HLineInBlock &HLine0 ,HLineInBlock &HLine1 ,HLineInBlock &HLine2
								,HLineInBlock &HLine3 ,HLineInBlock &HLine4 ,HLineInBlock &HLine5
								,VLineInBlock &VLine0 ,VLineInBlock &VLine1 ,VLineInBlock &VLine2
								,VLineInBlock &VLine3 ,VLineInBlock &VLine4 ,VLineInBlock &VLine5);
	int		ExeMatchLineChooseBetter(ImageBuffer &DBuff
								,int mx,int my ,int Sep
								,struct BlockShiftList::BlockShiftInfo	*ShiftDim
								,HLineInBlock &HLine0 ,HLineInBlock &HLine1 ,HLineInBlock &HLine2
								,HLineInBlock &HLine3 ,HLineInBlock &HLine4 ,HLineInBlock &HLine5
								,VLineInBlock &VLine0 ,VLineInBlock &VLine1 ,VLineInBlock &VLine2
								,VLineInBlock &VLine3 ,VLineInBlock &VLine4 ,VLineInBlock &VLine5);

	void	CalcMatchPosition(ExecuteInitialAfterEditInfo &EInfo);
	void	MakeNGPointForInvertLogic(int mx ,int my
								,int TmpBrightWidthL,int TmpBrightWidthH
								,ResultInItemRoot *Res
								,ThresholdMode NBMode
								,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	double	CalcMatchLinePosition(double mx,double my);

	bool    ExecuteProcessingInnerWithoutSubtractE(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

public:
	WORD	CalcCenterBright(ImageBuffer &IBuff ,int mx ,int my);
	WORD	CalcCenterBright(ImageBuffer &IBuff ,int mx ,int my
				,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

	void	MakeInsideEdgeArea(void);

	void	EnAverage(int mx,int my
						,int &TmpBrightWidthL,int &TmpBrightWidthH);
	void	EnAverage(int mx,int my
						,WORD &TmpBrightWidthL,WORD &TmpBrightWidthH);

	void	EnAverage(int mx,int my
						,int &TmpBrightWidthL,int &TmpBrightWidthH
						,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	void	EnAverage(int mx,int my
						,WORD &TmpBrightWidthL,WORD &TmpBrightWidthH
						,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	void	EnAverage(unsigned int BrightTable[256]
						,int &TmpBrightWidthL,int &TmpBrightWidthH);
	void	EnAverage(unsigned short BrightTable[256]
						,int &TmpBrightWidthL,int &TmpBrightWidthH);

	bool	IsModeDir4(void);
	bool	JudgeDir4 (struct TmpStruct &SData,int BrightWidthL ,int BrightWidthH,int dx,int dy);
	bool	JudgeDir4S(struct TmpStruct &SData,int BrightWidthL ,int BrightWidthH,int dx,int dy);
	bool	JudgeDir4 (struct TmpStruct_s &SData,int BrightWidthL ,int BrightWidthH,int dx,int dy);
	bool	JudgeDir4S(struct TmpStruct_s &SData,int BrightWidthL ,int BrightWidthH,int dx,int dy);
	bool	IsOnDynamicMasking(BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
							,int mx,int my,int SelfSearch);
	void	MakeFLineBeforeShrink(BlockLibrary &BLib);
	void	MakeOmitArea(BYTE **OmitMap,int XByte ,int YLen);
};

class	BlockLimitedMask : public AlgorithmItemPLI
{
public:
	explicit	BlockLimitedMask(void){}
    virtual	bool    Save(QIODevice *file);
    virtual	bool    Load(QIODevice *file,LayersBase *LBase);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
};

class	AlgorithmItemPointerLCList : public AlgorithmItemPointerListContainer ,public NPList<AlgorithmItemPointerLCList>
{
public:
	int		MinX,MinY;
	int		MaxX,MaxY;
	BlockInLayer	*Parent;

	AlgorithmItemPointerLCList(BlockInLayer *p){	Parent=p;	}

	void	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
	void	ExecuteProcessingRevived(int Step ,int Shift ,int RevisedRotation);
	int		GetNGCount(void);
};

class	AlgorithmItemPointerLCListContainer : public NPListPack<AlgorithmItemPointerLCList>
{
public:
	AlgorithmItemPointerLCListContainer(void){}
};

class	BlockInLayerForItemBitImage : public NPList<BlockInLayerForItemBitImage>
{
public:
	int		LibID;
	BYTE	**Bmp;
	int		BmpXByte;
	int		BmpYLen;

	BlockInLayerForItemBitImage(void);
	~BlockInLayerForItemBitImage(void);
};

class	BlockInLayerForItemBitImageContainer : public NPListPack<BlockInLayerForItemBitImage>
{
public:
	BlockInLayerForItemBitImage	*FindByLibID(int LibID);
};

class	LineInBlockBase;
class	LineInBlockBasePointer : public NPList<LineInBlockBasePointer>
{
public:
	LineInBlockBase	*LineBase;
	BlockItem		*Item;

	LineInBlockBasePointer(BlockItem *item ,LineInBlockBase	*L){	Item=item;	LineBase=L;	}
};

class	LineInBlockBasePointerContainer : public NPListPack<LineInBlockBasePointer>
{
public:
	LineInBlockBasePointerContainer(void){}

	double	Match(ImageBuffer &IBuff ,int dx ,int dy ,int &DxBylignment,int &DyBylignment ,double &ExpectedAvrCol);
};

class	AlgorithmItemPointerListContainerContainer : public NPList<AlgorithmItemPointerListContainerContainer>
{
public:
	FlexArea							Area;
	int									LibID;
	AlgorithmItemPointerListContainer	ItemPointers;

	LineInBlockBasePointerContainer		LPointers;
	LineInBlockBasePointerContainer		RPointers;
	LineInBlockBasePointerContainer		TPointers;
	LineInBlockBasePointerContainer		BPointers;

	HLineInBlockCluster	HMatchLine0;
	HLineInBlockCluster	HMatchLine1;
	HLineInBlockCluster HMatchLine2;
	VLineInBlockCluster	VMatchLine0;
	VLineInBlockCluster	VMatchLine1;
	VLineInBlockCluster	VMatchLine2;

	AlgorithmItemPointerListContainerContainer(BlockInLayer *ParentLayer,int LibID);

	void	MakeLinePointers(BlockInLayer *ParentLayer,ExecuteInitialAfterEditInfo &EInfo);
	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2);
	void	Match(ImageBuffer &IBuff ,int CommonMoveDot ,int &Dx ,int &Dy ,bool ModeUseGlobalLine);

	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	bool	IsItemIncluded(int ItemID);
};

class	ExecutablePointerList : public NPList<ExecutablePointerList>
{
	IntList		ItemLibList;
	IntList		MaskLinkedLibList;						//For SubtractBlock library ID
	AlgorithmItemPointerListContainer	MaskLinkedItems;//For SubtractBlock 
public:
	AlgorithmItemPointerListContainer	ItemPointer;
	ExecutablePointerContainer	*Container;
	BlockInLayer				*ParentLayer;

									//This is for other SubtractBlock dynamic masking
	BYTE	**DynamicMaskMap;		//if it's necessary, this is generated in ExecuteInitialAfterEdit
	int		DynamicMaskMapXByte;	// and set bit-image automatically
	int		DynamicMaskMapYLen;

	ExecutablePointerList(void);
	~ExecutablePointerList(void);

	void	SplitSubtraction(ExecutablePointerContainer &ChildFormer,ExecutablePointerContainer &ChildLater);

	void		ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	void		ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res);
	ExeResult	ExecuteProcessing		(int ExeID ,bool ThreadMode		);

	bool	IsLinkedToMask(AlgorithmItemRoot *Item);
	void	MakeDynamicMask(void);
};

class	ExecutablePointerContainer : public NPListPack<ExecutablePointerList>
{
public:
	BlockInLayer				*ParentLayer;

	ExecutablePointerContainer(BlockInLayer *BL):ParentLayer(BL){}

	void		ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	void		ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res);
	ExeResult	ExecuteProcessing		(int ExeID ,bool ThreadMode		);

	bool	IsLinkedToMask(AlgorithmItemRoot *Item);
	ExecutablePointerList	*FindItem(AlgorithmItemRoot *Item);
};

class   BlockInLayer : public AlgorithmInLayerPLI
{
	friend class	BlockItem;

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;
	IntList	CommonMoveIDList;
public:
	BYTE	**IndexDynamicMaskMap;		//Global dynamic masking buffer. Needless to delete in this class
	int		IndexDynamicMaskMapXByte;
	int		IndexDynamicMaskMapYLen;

	BYTE	**DynamicMaskMap;		// This is index, needless to delete. For execution
	int		DynamicMaskMapXByte;
	int		DynamicMaskMapYLen;

	BlockInLayerForItemBitImageContainer	ItemBitImages;

	NPListPack<AlgorithmItemPointerListContainerContainer>	GroupForSearch;
	ExecutablePointerContainer								ExecutableContainer;
protected:
	AlgorithmItemPointerLCListContainer	RevivedGroup;
	bool	NoBrightnessInMaster;

	SearchWayList   *SWayListPerCPU;
  public:
	BlockInLayer(AlgorithmInPageRoot *parent);
	~BlockInLayer(void);

	virtual	bool		AppendItem(AlgorithmItemRoot *item)					override;
	virtual	bool		AppendItem(int Layer ,AlgorithmItemRoot *item)		override;
	virtual	bool		AppendItemFromLoad(AlgorithmItemRoot *item)			override;
	virtual	bool		AppendItem(AlgorithmItemRoot *item ,int64 itemID)	override;

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)				override
		{	
			BlockItem	*a=new BlockItem();
			//a->SetParent(this);
			return a;
		}
    virtual	bool			Save(QIODevice *f)	override;
    virtual	bool			Load(QIODevice *f)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)	override;
	bool	UseLibraryForMaskingInOtherPage(int LibID);

	void	UndoAppendManualItem(QIODevice *f);
	void	UndoGenerateItems(QIODevice *f);
	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
	void	UndoShrinkArea(QIODevice *f);

	void	PickupTest(BlockLibrary &LibData);
	void	GenerateBlocks(BlockLibrary *LibDim[],int LibDimNumb);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessingRevived(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	void	CopyItemsFormDispatcherForParts(void)	override{}	//For skip

	virtual	void	AckRentalItem(int ForOtherGlobalPage ,QByteArray &Something , NPListPack<AlgorithmItemPLI> &_RentalData)	override;
	virtual	void	AddRentalItem(int ItemID ,AlgorithmItemPLI *p)	override;
	void	MoveFromPipe(GeneralPipeInfo &Info);

	void	MakeGroup(int LibID,ExecuteInitialAfterEditInfo &EInfo);
	void	MatchBeforeExecuteProcessing(void);
	AlgorithmItemPointerListContainerContainer	*FindGroup(int ItemID);

	virtual	bool	ExecuteAutoThresholdByAlgo(AlgorithmItemPointerListContainerByLibContainer &Items ,ParamAutoThreshold &executer) override;
private:
	void	CreatePickupBmpBuff(void);
};

class   BlockInPage : public AlgorithmInPagePLI
{
public:
	BlockInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){	ModeParallel.ModeParallelExecuteInitialAfterEdit	=true;	}
	virtual	BlockInLayer	*NewChild(AlgorithmInPageRoot *parent)	override{	return(new BlockInLayer(parent));	}
	void	PickupTest(IntList &LayerList ,BlockLibrary &LibData);
	void	GenerateBlocks(IntList &LayerList, BlockLibrary *LibDim[],int LibDimNumb);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	PipeGeneration(GeneralPipeInfo &Info)		override;
};

class	BlockBase	: public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		ColorBlockNormal	;
	QColor		ColorBlockSelected	;
	QColor		ColorBlockActive	;

	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	int			OmitZoneDot;
	int			RentalZone;
	int			MoreSearchForRental;
	int			RevivedStep;
	int			RevivedShift;
	int			RevisedRotation;
	bool		ReviveOKAgain;
	double		VarLow;
	bool		UseTargetCenterInNoMaster;
	bool		ExtendFollowedOutline;
	int			LengthFollowedOutline;
	double		ExtendFollowedOutlineMult;
	int			SkipSearchDot;
	int			MaxBlockShiftCount;

	BlockBase(LayersBase *Base);
	virtual	BlockInPage	*NewChild(AlgorithmBase *parent)	override{	return(new BlockInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetDataText(void)	override{	return QString("BlockInspection");	}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigBlock.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	virtual	int	GetLearningMenu(LearningMenu MenuPointer[] ,int MaxDimCount)	override;
};

#define	LearningMenu_BlockInspection_OK_ByBrightness	1
#define	LearningMenu_BlockInspection_OK_BySize			2
#define	LearningMenu_BlockInspection_OK_ByShift			3
#define	LearningMenu_BlockInspection_NG_ByBrightness	4
#define	LearningMenu_BlockInspection_NG_Size			5

//==================================================================================
class	BlockHistogramListReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	BlockHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	BlockHistogramListSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	int		ListMaster[256];
	int		ListTarget[256];
	WORD	CenterBright;
	WORD	CenterTargetBright;
	int32	ShiftByAlignmentX;
	int32	ShiftByAlignmentY;
	int32	ShiftByCommonX;
	int32	ShiftByCommonY;
	int32	ShiftBySelfX;
	int32	ShiftBySelfY;

	BlockHistogramListSend(void);

	void	ConstructList(BlockHistogramListReq *reqPacket,BlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	BlockThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	BlockThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	BlockThresholdSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	WORD	CenterBright;
	WORD	CenterTargetBright;
	short	NBrightWidthL;		//‹·ˆæ‚ÌˆÃ‘¤‹P“x•
	short	NBrightWidthH;		//‹·ˆæ‚Ì–¾‘¤‹P“x•
	short	BBrightWidthL;		//Lˆæ‚ÌˆÃ‘¤‹P“x•
	short	BBrightWidthH;		//Lˆæ‚Ì–¾‘¤‹P“x•

	short	AbsNBrightWidthL;	//‹·ˆæ‚ÌˆÃ‘¤‹P“x•
	short	AbsNBrightWidthH;	//‹·ˆæ‚Ì–¾‘¤‹P“x•
	short	AbsBBrightWidthL;	//Lˆæ‚ÌˆÃ‘¤‹P“x•
	short	AbsBBrightWidthH;	//Lˆæ‚Ì–¾‘¤‹P“x•

	WORD	NMinNGCountL;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	NMinNGCountH;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountL;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountH;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	int8	NConnectLen;	//‹·ˆæ‚Ì‚m‚fÚ‘±‹——£
	int8	BConnectLen;	//Lˆæ‚Ì‚m‚fÚ‘±‹——£

	BlockThresholdSend(void);

	void	ConstructList(BlockThresholdReq *reqPacket,BlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	BlockReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;	
	BlockItem	Threshold;

	BlockReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	BlockSendTryThreshold : public AddedDataClass
{
public:
	int		NGDotInNDark;
	int		NGDotInNBright;
	int		NGDotInBDark;
	int		NGDotInBBright;
	int		ResultMoveDx;
	int		ResultMoveDy;
	int		Error;
	ResultInItemRoot	*Result;
	int32	ShiftByCommonX;
	int32	ShiftByCommonY;
	int32	ShiftBySelfX;
	int32	ShiftBySelfY;

	BlockSendTryThreshold(void);
	~BlockSendTryThreshold(void);

	void	ConstructList(BlockReqTryThreshold *reqPacket,BlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	BlockChangeShift
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	int32	Dx,Dy;

	BlockChangeShift(void){}

	void	Reflect(BlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	BlockHistogramListReqCommand			3
#define	BlockHistogramListSendCommand			4
#define	BlockReqThresholdReqCommand				5
#define	BlockReqThresholdSendCommand			6
#define	BlockReqTryThresholdCommand				7
#define	BlockSendTryThresholdCommand			8
#define	BlockReqChangeShiftCommand				9
#define	SetIndependentItemNameDataCommand_All	10

//===================================================================================

class	CmdGetBlockLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetBlockLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetBlockLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetBlockLibraryListInPasteLayerPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	int			Layer;
	AlgorithmLibraryListContainer	AList;
	CmdGetBlockLibraryListInPasteLayerPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetBlockLibraryListInPasteLayerPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetBlockLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetBlockLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetBlockLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearBlockLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestBlockPacket : public GUIDirectMessage
{
public:
	//BlockLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList			LayerList;
	int				Page;

	CmdPickupTestBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateBlockPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	IntList		LayerList;
	int			Page;
	CmdGenerateBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempBlockItemPacket : public GUIDirectMessage
{
public:
	BlockItem	*Point;
	CmdCreateTempBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromBlockItemPacket : public GUIDirectMessage
{
public:
	BlockItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteBlockItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	IntList		LayerList;
	int			LocalPage;
	CmdAddByteBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadBlockItemPacketFromByteArray : public GUIDirectMessage
{
public:
	BlockItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadBlockItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadBlockItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedBlockFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	IntList		LayerList;
	int			LocalPage;
	CmdModifySelectedBlockFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedBlockFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestBlockPacket: public GUIDirectMessage
{
public:
	CmdClearTestBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



class	CmdBlockInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	NPListPack<BlockInfoList>	*BlockInfos;
	CmdBlockInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdBlockInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetBlockFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	BlockItem	*BlockInfoOnMouse;

	CmdGetBlockFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetBlockFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateBlockItem: public GUIDirectMessage
{
public:
	BlockItem	*Block;
	CmdCreateBlockItem(LayersBase *base):GUIDirectMessage(base){	Block=NULL;	}
	CmdCreateBlockItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Block=NULL;	}
};

class	CmdReqShrinkArea : public GUIDirectMessage
{
public:
	IntList		LayerList;
	int			ShrinkDot;
	CmdReqShrinkArea(LayersBase *base):GUIDirectMessage(base){}
	CmdReqShrinkArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetUsedLibID : public GUIDirectMessage
{
public:
	IntList	LibIDs;

	CmdGetUsedLibID(LayersBase *base):GUIDirectMessage(base){}
	CmdGetUsedLibID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqShrinkHalf : public GUIDirectMessage
{
public:
	IntList		LayerList;

	CmdReqShrinkHalf(LayersBase *base):GUIDirectMessage(base){}
	CmdReqShrinkHalf(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqExpandHalf : public GUIDirectMessage
{
public:
	IntList		LayerList;

	CmdReqExpandHalf(LayersBase *base):GUIDirectMessage(base){}
	CmdReqExpandHalf(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdSetNGSizeInBlock : public GUIDirectMessage
{
public:
	int LibID;
	int BlockType;
	int NGSize;

	CmdSetNGSizeInBlock(LayersBase *base):GUIDirectMessage(base){}
	CmdSetNGSizeInBlock(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdSetSearchDotInBlock : public GUIDirectMessage
{
public:
	int LibID;
	int SearchDot;

	CmdSetSearchDotInBlock(LayersBase *base):GUIDirectMessage(base){}
	CmdSetSearchDotInBlock(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdTryProcess : public GUIDirectMessage
{
public:
	BlockItem	*BItemPoint;
	bool		OK;

	CmdTryProcess(LayersBase *base):GUIDirectMessage(base){}
	CmdTryProcess(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
