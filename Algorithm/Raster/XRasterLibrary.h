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
#include <QImage>
#include <QColor>
#include <QIODevice>
#include <QByteArray>
#include "XTypeDef.h"
#include "XIntClass.h"
#include "XDataAlgorithm.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "NListComp.h"
#include <QBuffer>
#include "XRaster.h"

//========================================================================================
class	RasterLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int	MaxShrinkDot;
	int	MaxShiftDot;
	int	ShrinkDot;
	int	InsideEdgeWidth;
	int	OutsideEdgeWidth;
	AlgorithmLibraryListContainer	AllocatedStaticLib;
	AlgorithmLibraryListContainer	AllocatedInsideEdgeLib;
	AlgorithmLibraryListContainer	AllocatedOutsideEdgeLib;

	RasterLibrary(int LibType,LayersBase *Base);
	virtual	~RasterLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	RasterLibrary	&operator=(const AlgorithmLibrary &src)				override;
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};


class	RasterLibraryContainer : public AlgorithmLibraryContainer
{
public:
	RasterLibraryContainer(LayersBase *base);
	virtual	~RasterLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeRaster;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Raster Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new RasterLibrary(GetLibType(),GetLayersBase());	}
};