/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MatchShiftRotation\XMatchShiftRotationLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XMatchShiftRotationLibrary_h)
#define	XMatchShiftRotationLibrary_h


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeMatchShiftRotation		76

class	MatchShiftRotationLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//For generation
	int32		PickupL;
	int32		PickupH;
    int32		MinAreaSize;
    int32		MaxAreaSize;
    int32		MinAreaDots;
    int32		MaxAreaDots;
	int32		ExpansionDot;
	int32		LimitSize;

	int32		NoisePinholeSize;
	int32		NoiseIslandSize;
	int32		EdgeWidth;

//For inspection	for Area
	int32		SearchArea;
	int32		SearchAngle;
//For inspection for Item
	int32		SearchLittleInItem;
	double		MatchingRate;
	
public:

	MatchShiftRotationLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	MatchShiftRotationLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	MatchShiftRotationLibraryContainer : public AlgorithmLibraryContainer
{
public:
	MatchShiftRotationLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeMatchShiftRotation;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "MatchShiftRotationLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new MatchShiftRotationLibrary(GetLibType(),GetLayersBase());	}
};



#endif