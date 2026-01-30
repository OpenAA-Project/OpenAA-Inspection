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