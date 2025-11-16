/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRing\XEulerRingLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XEULERRINGLIBRARY_H)
#define	XEULERRINGLIBRARY_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeEulerRing		9

class	EulerRingLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//生成データ

	ColorLogic				HoleColor;
	ColorLogic				CupperColor;
    int32					MinBlockSize;
    int32					MaxBlockSize;
    int32					MinBlockDots;
    int32					MaxBlockDots;

	WORD		NoiseSize;
	WORD		ExpandedDotToPad;


//検査データ
	ColorLogic	InspectionColor;
	int32		Mergin;
    WORD		ExpandedDot;
	WORD		AdjustBlack;    //輝度補正の下限幅
    WORD		AdjustWhite;    //輝度補正の上限幅

public:

	EulerRingLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	EulerRingLibrary	&operator=(const AlgorithmLibrary &src)	override;

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
private:
	bool	ExistCupper(ImagePointerContainer &ImageBuff
					  ,FlexArea &A,double s, int Len);
};

class	EulerRingLibraryContainer : public AlgorithmLibraryContainer
{
public:
	EulerRingLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeEulerRing;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "EulerRingLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new EulerRingLibrary(GetLibType(),GetLayersBase());	}
};


#endif
