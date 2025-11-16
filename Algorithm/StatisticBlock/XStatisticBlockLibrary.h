/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticBlock\XStatisticBlockLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XSTATISTICBLOCKLIBRARY_H)
#define	XSTATISTICBLOCKLIBRARY_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeStatisticBlock	11

class	StatisticBlockLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//生成データ
	int32					PickupL;
	int32					PickupH;
    int32					MinBlockSize;
    int32					MaxBlockSize;
    int32					MinBlockDots;
    int32					MaxBlockDots;
    int32					LimitBlockSize;
	struct    {
		bool    Transparent:1;		
		bool    LeftPickup:1;
		bool	OverlappedGen:1;	//重複生成するブロック
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

	WORD		NoiseSize;
    WORD		SpaceToOutline;
    WORD		Priority;

//検査データ

	double	BrightWidthL;	//σに対しての暗側倍率
	double	BrightWidthH;	//σに対しての明側倍率
	DWORD	OKDotL;			//暗側ＯＫドット数
	DWORD	OKDotH;			//明側ＯＫドット数
	WORD	OKLengthL;		//明側で、この長さ以下の時ＯＫ
	WORD	OKLengthH;		//明側で、この長さ以下の時ＯＫ

	struct{
		bool	ModeEnabled:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeNGCluster:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
	}PointMove;

    WORD	AdjustBlack;    //輝度補正の下限幅
    WORD	AdjustWhite;    //輝度補正の上限幅
    WORD	OverlapDot;

	//膨張・収縮
	bool	UseMorphology;		//膨張・収縮をするかどうか
	bool	EliminateAcnode;	//孤立点の除去
	WORD	DilationDotCount;	//膨張するドット数
	WORD	ErosionDotCount;	//収縮するドット数
	enum _MorphologyApplyTo{
		MAT_Both=0,
		MAT_DarkSideOnly=1,
		MAT_LightSideOnly=2
	}MorphologyApplyTo;

public:

	StatisticBlockLibrary(int LibType,LayersBase *Base);
	virtual	~StatisticBlockLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	StatisticBlockLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer &IBuff 
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
			,NPListPack<AlgorithmItemPLI> &TmpBlockData);
};

class	StatisticBlockLibraryContainer : public AlgorithmLibraryContainer
{
public:
	StatisticBlockLibraryContainer(LayersBase *base);
	virtual	~StatisticBlockLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeStatisticBlock;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Statistic Block Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new StatisticBlockLibrary(GetLibType(),GetLayersBase());	}
};


#endif