/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XVIALibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XVIALIBRARY_H)
#define	XVIALIBRARY_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeVIAInspect	44



class	VIALibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//生成データ
#pragma	pack(push,1)
	int32					PickupL;
	int32					PickupH;
    int32					MinVIASize;
    int32					MaxVIASize;
    int32					MinVIADots;
    int32					MaxVIADots;
    int32					LimitVIASize;
#pragma	pack(pop)

#pragma	pack(push,1)
	WORD		NoiseSize;			//孤立点削除
	WORD		NoiseSizePinHole;	//ピンホール削除
    short		SpaceToOutline;
    WORD		Priority;
#pragma	pack(pop)

//検査データ
#pragma	pack(push,1)
	WORD	BrightWidthL;	//暗側輝度幅
	WORD	BrightWidthH;	//明側輝度幅
	DWORD	OKDotL;			//暗側ＯＫドット数
	DWORD	OKDotH;			//明側ＯＫドット数
	WORD	OKLengthL;		//暗側で、この長さ以下の時ＯＫ
	WORD	OKLengthH;		//明側で、この長さ以下の時ＯＫ
	DWORD	MaxNGDotL;		//暗側最大ＮＧドット数
	DWORD	MaxNGDotH;		//明側最大ＮＧドット数
	BYTE	ShrinkDot;
	BYTE	EnlargeDot;
#pragma	pack(pop)
	
public:

	VIALibrary(int LibType,LayersBase *Base);
	virtual	~VIALibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	VIALibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer &IBuff 
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int Page
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeVIA(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpVIAData);

private:
};

class	VIALibraryContainer : public AlgorithmLibraryContainer
{
public:
	VIALibraryContainer(LayersBase *base);
	virtual	~VIALibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeVIAInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "VIA Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new VIALibrary(GetLibType(),GetLayersBase());	}
};


#endif