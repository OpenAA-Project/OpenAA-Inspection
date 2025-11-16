/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\XTrueColorBlockLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XTRUECOLORBLOCKLIBRARY_H)
#define	XTRUECOLORBLOCKLIBRARY_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeTrueColor		4

class	TrueColorBlockLibNGTypeItem : public LibNGTypeItem
{
	AlgorithmLibraryContainer	*Lib;
public:
	ColorLogic	ColorZone;
	int			MinSize,MaxSize;
	int			MinRoundRate,MaxRoundRate;

	TrueColorBlockLibNGTypeItem(LayersBase *base,AlgorithmLibraryContainer *lib);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSetting(void);
};

#pragma	pack(push,1)
class	TrueColorBlockLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//¶¬ƒf[ƒ^
    IntList					SubtractBlock; //œ‹ƒ‰ƒCƒuƒ‰ƒŠ

	ColorLogic				PickupColor;
    int32					MinBlockSize;
    int32					MaxBlockSize;
    int32					MinBlockDots;
    int32					MaxBlockDots;
    int32					LimitBlockSize;
	struct    {
		bool    Transparent:1;
		bool    LeftPickup:1;
		bool	OverlappedGen:1;	//d•¡¶¬‚·‚éƒuƒƒbƒN
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

	WORD		NoiseSize;			//ŒÇ—§“_íœ
	WORD		NoiseSizePinHole;	//ƒsƒ“ƒz[ƒ‹íœ
    WORD		SpaceToOutline;
    WORD		Priority;

//ŒŸ¸ƒf[ƒ^
	//RGBStock	NInsOKSamples;	//‹·ˆæ‚Ì‚n‚jŒŸ¸—á¦
	//RGBStock	NInsNGSamples;	//‹·ˆæ‚Ì‚m‚fŒŸ¸—á¦
	ColorLogic	NInsColor;
	DWORD		NOKDot;			//‹·ˆæ‚Ì‚n‚jƒhƒbƒg”
	int32		NMergin;		//‹·ˆæ”»’è‚Ì‹–—e‹P“x—Ê

	//RGBStock	BInsOKSamples;	//Lˆæ‚Ì‚n‚jŒŸ¸—á¦
	//RGBStock	BInsNGSamples;	//Lˆæ‚Ì‚m‚fŒŸ¸—á¦
	ColorLogic	BInsColor;
	DWORD		BOKDot;			//Lˆæ‚Ì‚n‚jƒhƒbƒg”
	int32		BMergin;		//‹·ˆæ”»’è‚Ì‹–—e‹P“x—Ê

	WORD	NMinNGCount;	//‹·ˆæ‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
	WORD	BMinNGCount;	//Lˆæ‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é

	WORD	BOKLength;		//Lˆæ‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
	WORD	NOKLength;		//‹·ˆæ‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j

	struct{
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool	ModeInvertLogic:1;
	}PointMove;

    WORD	AdjustBlack;    //‹P“x•â³‚Ì‰ºŒÀ•
    WORD	AdjustWhite;    //‹P“x•â³‚ÌãŒÀ•
    WORD	SelfSearch;     //©ŒÈ’Tõƒhƒbƒg”
    WORD	CommonMoveDot;

public:

	TrueColorBlockLibrary(int LibType,LayersBase *Base);
	virtual	~TrueColorBlockLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	TrueColorBlockLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImagePointerContainer &ImageBuff
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int Page
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			 ,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &TmpBlockData);

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

#pragma	pack(pop)


class	TrueColorBlockLibraryContainer : public AlgorithmLibraryContainer
{
public:
	TrueColorBlockLibraryContainer(LayersBase *base);
	virtual	~TrueColorBlockLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeTrueColor;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "TrueColor Block Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new TrueColorBlockLibrary(GetLibType(),GetLayersBase());	}
	virtual	LibNGTypeItem	*CreateLibNGTypeItem(LayersBase *base)	override{	return new TrueColorBlockLibNGTypeItem(base ,this);	}
};


#endif
