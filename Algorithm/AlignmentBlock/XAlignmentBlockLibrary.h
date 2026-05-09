/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

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
	int32		NeighborArea;
	double		NeighborMatchingRate;
	double		FlatnessLimit;
	int32		LaplaceFilterSize;
	bool		UseRemover;
	int			DustSize;
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