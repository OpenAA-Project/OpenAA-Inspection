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

#pragma once

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeRasterInspection		77


class	RasterInspectionLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	double	GenColorDistance;	//	Color distance in generation
	int		Priority;
	bool	EnableOverlap;
	int		LimitSize;

	int		SearchAreaDot;
	double	SearchWaveDiv;
	double	WaveDistance;
	int		OKDot;
public:

	RasterInspectionLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	RasterInspectionLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakeRasterInspection(
				ImageBufferListContainer &ImageContainer
				,BYTE **MaskBitmap,BYTE **LastOcupyMap
				,int XByte ,int XLen,int YLen
				,int OmitZoneDot
				,int Page
				,NPListPack<AlgorithmItemPI> &TmpRasterInspectionData);

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	RasterInspectionLibraryContainer : public AlgorithmLibraryContainer
{
public:
	RasterInspectionLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeRasterInspection;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "RasterInspectionLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new RasterInspectionLibrary(GetLibType(),GetLayersBase());	}
};