/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XColorBlockLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XCOLORBLOCKLIBRARY_H)
#define	XCOLORBLOCKLIBRARY_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeColorBlock	2

class	ColorBlockLibNGTypeItem : public LibNGTypeItem
{
public:
	BYTE	MinColorR, MaxColorR;
	BYTE	MinColorG, MaxColorG;
	BYTE	MinColorB, MaxColorB;
	int		MinSize,MaxSize;
	int		MinRoundRate,MaxRoundRate;

	ColorBlockLibNGTypeItem(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSetting(void);
};

class	ColorBlockLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//¶¬ƒf[ƒ^
#pragma	pack(push,1)
    IntList					SubtractBlock; //œ‹ƒ‰ƒCƒuƒ‰ƒŠ
	int32					PickupRL;
	int32					PickupRH;
	int32					PickupGL;
	int32					PickupGH;
	int32					PickupBL;
	int32					PickupBH;
    int32					MinBlockSize;
    int32					MaxBlockSize;
    int32					MinBlockDots;
    int32					MaxBlockDots;
    int32					LimitBlockSize;
#pragma	pack(pop)
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

#pragma	pack(push,1)
	WORD		NoiseSize;			//ŒÇ—§“_íœ
	WORD		NoiseSizePinHole;	//ƒsƒ“ƒz[ƒ‹íœ
    WORD		SpaceToOutline;
    WORD		Priority;
#pragma	pack(pop)

//ŒŸ¸ƒf[ƒ^

	class	InspectionData
	{
	public:
	#pragma	pack(push,1)
		WORD	NBrightWidthL;	//‹·ˆæ‚ÌˆÃ‘¤‹P“x•
		WORD	NBrightWidthH;	//‹·ˆæ‚Ì–¾‘¤‹P“x•
		WORD	BBrightWidthL;	//Lˆæ‚ÌˆÃ‘¤‹P“x•
		WORD	BBrightWidthH;	//Lˆæ‚Ì–¾‘¤‹P“x•

		DWORD	NOKDotL;		//‹·ˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
		DWORD	NOKDotH;		//‹·ˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”
		DWORD	BOKDotL;		//Lˆæ‚ÌˆÃ‘¤‚n‚jƒhƒbƒg”
		DWORD	BOKDotH;		//Lˆæ‚Ì–¾‘¤‚n‚jƒhƒbƒg”

		WORD	NMinNGCountL;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
		WORD	NMinNGCountH;	//‹·ˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
		WORD	BMinNGCountL;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é
		WORD	BMinNGCountH;	//Lˆæ‚ÌˆÃ‘¤‚Å‚±‚ÌŒÂ”ˆÈã‚Ì‚m‚fŒÂ”‚ª‚ ‚ê‚Î‚m‚f‚É‚·‚é

		WORD	BOKLengthL;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
		WORD	BOKLengthH;		//Lˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
		WORD	NOKLengthL;		//‹·ˆæ‚ÌˆÃ‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j
		WORD	NOKLengthH;		//‹·ˆæ‚Ì–¾‘¤‚ÅA‚±‚Ì’·‚³ˆÈ‰º‚Ì‚n‚j

	    WORD	AdjustBlack;    //‹P“x•â³‚Ì‰ºŒÀ•
		WORD	AdjustWhite;    //‹P“x•â³‚ÌãŒÀ•
	#pragma	pack(pop)

		InspectionData(void);
		InspectionData	&operator=(InspectionData &src);
		virtual	bool	Save(QIODevice *f);
		virtual	bool	Load(QIODevice *f);
	};
	InspectionData	InsR,InsG,InsB;

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
	}PointMove;

	#pragma	pack(push,1)
    WORD	SelfSearch;     //©ŒÈ’Tõƒhƒbƒg”
	WORD	CommonMoveDot;
	#pragma	pack(pop)

public:

	ColorBlockLibrary(int LibType,LayersBase *Base);
	virtual	~ColorBlockLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	ColorBlockLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer &IBuffR ,ImageBuffer &IBuffG ,ImageBuffer &IBuffB 
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
			,NPListPack<AlgorithmItemPI> &TmpBlockData
			,int SelfSearch);
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};


class	ColorBlockLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ColorBlockLibraryContainer(LayersBase *base);
	virtual	~ColorBlockLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeColorBlock;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Color Block Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new ColorBlockLibrary(GetLibType(),GetLayersBase());	}
	virtual	LibNGTypeItem	*CreateLibNGTypeItem(LayersBase *base)	override{	return new ColorBlockLibNGTypeItem(base);	}
};




#endif