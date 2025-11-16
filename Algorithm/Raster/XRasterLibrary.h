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
