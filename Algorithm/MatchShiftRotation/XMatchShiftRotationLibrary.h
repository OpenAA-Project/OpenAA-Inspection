/*
 * Copyright (C) 2023
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