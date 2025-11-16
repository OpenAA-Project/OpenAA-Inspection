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
