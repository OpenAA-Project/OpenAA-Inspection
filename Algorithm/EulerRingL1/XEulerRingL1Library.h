/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRingL1\XEulerRingL1Library.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XEulerRingL1LIBRARY_H)
#define	XEulerRingL1LIBRARY_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeEulerRingL1		69

class	EulerRingL1Library : public AlgorithmLibrary , public ServiceForLayers
{
public:
//For generation
	bool	LockFirst;		
	int32	PickupL;
	int32	PickupH;
    int32	MinBlockSize;
    int32	MaxBlockSize;
    int32	MinBlockDots;
    int32	MaxBlockDots;

	WORD	NoiseSize;			//孤立点削除
	WORD	NoiseSizePinHole;	//ピンホール削除
	int32	SpaceToOutline;		//Plus:Shrink Plus:Expand
    WORD	Priority;
	WORD	OutlineGeneration;	//輪郭に生成するドット数	1000以上で通常生成
	WORD	ExpandedDotToPad;	//Expanded dot from hole to pad

//For inspection
	double	StandardHoleDiameter;
	double	MerginForRing;

	struct{
		bool	ModeEnabled:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeMakeDynamicMask:1;
		bool	ModeEnableHoleCheck:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeEnableOpenRingCheck:1;
		bool	ModeEnableInRound:1;			//When hole is round in generation , it's TRUE
		int		Dummy:25;
	}PointMove;

	short		DarkWidth;		//For ring brightness
	short		LightWidth;
	int32		MinHoleDiameter;
	int32		MaxHoleDiameter;
	double		MaxShiftHole;
	int8		ConnectLen;		//ＮＧ接続距離
	int32		ExpandForDynamicMask;

    WORD		AdjustBlack;	//For ring brightness
    WORD		AdjustWhite; 
	WORD		SearchDot;
	short		HoleBrightnessAsReference;

public:

	EulerRingL1Library(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	EulerRingL1Library	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(int localpage
						,ImageBuffer &IBuff 
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeBlock(int localpage
			,BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData
			,int tExpandedDotToPad);
	void	MakeBlockOnly(int localpage
			,BYTE **CurrentMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData
			,double RoundRateInHole);
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	EulerRingL1LibraryContainer : public AlgorithmLibraryContainer
{
public:
	EulerRingL1LibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeEulerRingL1;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "EulerRingL1Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new EulerRingL1Library(GetLibType(),GetLayersBase());	}
};


#endif
