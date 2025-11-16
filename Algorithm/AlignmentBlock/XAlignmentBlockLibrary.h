#pragma once
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentBlock\XAlignmentBlockLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeAlignmentBlock		72

class	AlignmentBlockLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//For generation
    int32		MinAreaSize;
    int32		MaxAreaSize;
    int32		MinAreaDots;
    int32		MaxAreaDots;
	int32		OverlapDot;
	int32		LimitSize;
	int32		NoisePinholeSize;
	int32		NoiseIslandSize ;
	int32		DeadZone;
	int32		ExpandArea;

//For inspection
	int		SearchDot ;
	double	MaxDegree ;
	int		LineLength;
	double	MinVar	  ;
	double	ThreDiv	;
public:

	AlignmentBlockLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AlignmentBlockLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	AlignmentBlockLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AlignmentBlockLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeAlignmentBlock;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "AlignmentBlockLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new AlignmentBlockLibrary(GetLibType(),GetLayersBase());	}
};
