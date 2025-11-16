/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentFlexArea\XAlignmentFlexAreaLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XAlignmentFlexAreaLibrary_h)
#define	XAlignmentFlexAreaLibrary_h


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeAlignmentFlexArea		71

class	AlignmentFlexAreaLibrary : public AlgorithmLibrary , public ServiceForLayers
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
	int32		AdaptedPriority;
	bool		PickUpEdge;
	int32		PickUpEdgeMinDiff;
	double		MaxCoeffInNeighbor;		//-1 - +1

//For inspection
	int32		GlobalSearchDot;
	int32		SearchDot;
	int32		GroupAreaSize;
	double		CloserRate;		//0-0.2
	int32		SmallSearch;
	bool		KeepBW;			//Keep black/white side in target image
	
public:

	AlignmentFlexAreaLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AlignmentFlexAreaLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	AlignmentFlexAreaLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AlignmentFlexAreaLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeAlignmentFlexArea;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "AlignmentFlexAreaLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new AlignmentFlexAreaLibrary(GetLibType(),GetLayersBase());	}
};



#endif