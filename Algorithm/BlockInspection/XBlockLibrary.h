/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBlockLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XBLOCKLIBRARY_H)
#define	XBLOCKLIBRARY_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeBlockInspect	1


class	BlockLibNGTypeItem : public LibNGTypeItem
{
public:
	int	MinColor, MaxColor;
	int	MinSize,MaxSize;
	int	MinRoundRate,MaxRoundRate;

	BlockLibNGTypeItem(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSetting(void);
};


class	BlockLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//¶¬ƒf[ƒ^
    IntList					SubtractBlock; //Removal library
#pragma	pack(push,1)
	int32					PickupL;
	int32					PickupH;
    int32					MinBlockSize;
    int32					MaxBlockSize;
    int32					MinBlockDots;
    int32					MaxBlockDots;
    int32					LimitBlockSize;
	int32					RegularBrightness;	//Šî€‹P“x -1‚Ì‚Æ‚«ƒ}ƒXƒ^[‹P“x‚ğÌ—p
	int32					FollowLineLength;
#pragma	pack(pop)
	struct{
		bool	Gen_Left:1;
		bool	Gen_Top:1;
		bool	Gen_Right:1;
		bool	Gen_Bottom:1;
	}GenFollowLine;

	struct    {
		bool    Transparent:1;		
		bool    LeftPickup:1;
		bool	OverlappedGen:1;	//d•¡¶¬‚·‚éƒuƒƒbƒN
		bool	PlusHalfDotIsolation:1;
		bool	LockFirst:1;		//¶¬‚ÉƒƒbƒN‚ğ‚©‚¯‚é
		bool	BindSmallBlock:1;
	}GenerationMode;
	enum    _GenerationCategory
	{
	     _AutoSetting_PAD       =0
		,_AutoSetting_HOLE      =1
	    ,_AutoSetting_SILK      =2
		,_AutoSetting_REGIST    =3
		,_AutoSetting_OTHERMASK =4
	    ,_AutoSetting_FINEPAD   =5
		,_AutoSetting_SURROUND  =6
	    ,_AutoSetting_ANY       =7
	}GenerationCategory;

#pragma	pack(push,1)
	WORD		NoiseSize;			//ŒÇ—§“_íœ
	WORD		NoiseSizePinHole;	//ƒsƒ“ƒz[ƒ‹íœ
    WORD		SpaceToOutline;
    WORD		Priority;
	WORD		OutlineGeneration;	//—ÖŠs‚É¶¬‚·‚éƒhƒbƒg”	1000ˆÈã‚Å’Êí¶¬
#pragma	pack(pop)

//ŒŸ¸ƒf[ƒ^
#pragma	pack(push,1)
	WORD	NBrightWidthL;	//‹·ˆæ‚ÌˆÃ‘¤‹P“x•
	WORD	NBrightWidthH;	//‹·ˆæ‚Ì–¾‘¤‹P“x•
	DWORD	NOKDotL;		//‹·ˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	DWORD	NOKDotH;		//‹·ˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	WORD	NOKLengthL;		//‹·ˆæ‚ÌˆÃ‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	NOKLengthH;		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	DWORD	NMaxNGDotL;		//‹·ˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	DWORD	NMaxNGDotH;		//‹·ˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	WORD	NMinNGCountL;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	NMinNGCountH;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BBrightWidthL;	//Lˆæ‚ÌˆÃ‘¤‹P“x•
	WORD	BBrightWidthH;	//Lˆæ‚Ì–¾‘¤‹P“x•
	DWORD	BOKDotL;		//Lˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
	DWORD	BOKDotH;		//Lˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
	DWORD	BMaxNGDotL;		//Lˆæ‚ÌˆÃ‘¤Å‘å‚m‚fƒhƒbƒg”
	DWORD	BMaxNGDotH;		//Lˆæ‚Ì–¾‘¤Å‘å‚m‚fƒhƒbƒg”
	WORD	BOKLengthL;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	BOKLengthH;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	BMinNGCountL;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCountH;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	int8	NConnectLen;	//‹·ˆæ‚Ì‚m‚fÚ‘±‹——£
	int8	BConnectLen;	//Lˆæ‚Ì‚m‚fÚ‘±‹——£
	WORD	DiffBrightWidthL;
	WORD	DiffBrightWidthH;
	WORD	ExpandForGenMask;	//Expansion dot for dynamic mask to generate in ExecuteIntialAfterEdit
	int8	FollowLineLayer;	//-1:Save layer
#pragma	pack(pop)
	
	struct{
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
		bool	ModeInvertLogic:1;
		bool	ModeMatchPosition:1;	//Follow outline
		bool	ModeSearchDetail:1;
		bool	ModeDynamicMask:1;
		bool	ModeBindBWBroad:1;
		bool	ModeBindBWNarrow:1;
		bool	ModeAdoptBiggest:1;
		bool	ModeUseMasterImage:1;	//Use master image in Outline-following
		bool	ModePermitInverted:1;	//For outline-matching
		bool	ModeMatchPositionBW:1;	//Follow outline	
										//(ModeMatchPosition,ModeMatchPositionBW)
										//(false,false)=None ,(true,false)=Ignore BW  (false,true)=Pattern W,  (true,true)=Pattern B
		bool	ModeOppositeRange:1;
		bool	ModeUseGlobalLine:1;	//Follow outline
	}PointMove;

#pragma	pack(push,1)
    WORD	AdjustBlack;    //‹P“x•â³‚Ì‰ºŒÀ•
    WORD	AdjustWhite;    //‹P“x•â³‚ÌãŒÀ•
    WORD	SelfSearch;     //©ŒÈ’Tõƒhƒbƒg”
    WORD	CommonMoveDot;
#pragma	pack(pop)

public:

	BlockLibrary(int LibType,LayersBase *Base);
	virtual	~BlockLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	BlockLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(int localpage
						,ImageBuffer &IBuff 
						,const BYTE **MaskBitmap,const BYTE **LastOcupyMap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeBlock(int localpage
			,BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData);
	void	MakeBlockOnly(int localpage
			,BYTE **CurrentMap,const BYTE **MaskMap ,BYTE **DriftMap 
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData
			,int OmitZoneDot);
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:
	bool	LoadBlobNew(QIODevice *f);
	bool	LoadBlobOld(QIODevice *f);
};

class	BlockLibraryContainer : public AlgorithmLibraryContainer
{
public:
	BlockLibraryContainer(LayersBase *base);
	virtual	~BlockLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeBlockInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Block Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new BlockLibrary(GetLibType(),GetLayersBase());	}

	virtual	LibNGTypeItem	*CreateLibNGTypeItem(LayersBase *base)	override{	return new BlockLibNGTypeItem(base);	}
};


#endif