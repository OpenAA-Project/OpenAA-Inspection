/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XHoleWallInspection\XHoleWallLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XHoleWallLIBRARY_H)
#define	XHoleWallLIBRARY_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeHoleWall		41

class	HoleWallLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//For generation
	int32	PickupL;
	int32	PickupH;
    int32	MinBlockSize;
    int32	MaxBlockSize;
    int32	MinBlockDots;
    int32	MaxBlockDots;

	WORD	NoiseSize;			//孤立点削除
	WORD	NoiseSizePinHole;	//ピンホール削除
	WORD	SpaceToOutline;

//For inspection
	double	NGSize;
	WORD	SearchDot;

public:

	HoleWallLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	HoleWallLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(int localpage
						,ImageBuffer &IBuff 
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeBlock(int localpage
			,BYTE **CurrentMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData
			,double ShiftXParamLeft[4],double ShiftXParamRight[4]
			,int ShiftY);

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	HoleWallLibraryContainer : public AlgorithmLibraryContainer
{
public:
	HoleWallLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeHoleWall;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "HoleWallLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new HoleWallLibrary(GetLibType(),GetLayersBase());	}
};


#endif
