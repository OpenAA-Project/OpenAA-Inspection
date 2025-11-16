#pragma once

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypePalletize		75


class	PalletizeLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	double	AngleRange;		//Degree
	double	MinZoomSize;
	double	MaxZoomSize;
	int		PieceSize;
	int		SearchDotPiece;
	double	ThresholdV;
	int		MaxCountOfPiece;
	double	ThreshCoeff;
	int		SearchNearBy;
	int		MaxShift;

public:

	PalletizeLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	PalletizeLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	PalletizeLibraryContainer : public AlgorithmLibraryContainer
{
public:
	PalletizeLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypePalletize;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "PalletizeLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new PalletizeLibrary(GetLibType(),GetLayersBase());	}
};
