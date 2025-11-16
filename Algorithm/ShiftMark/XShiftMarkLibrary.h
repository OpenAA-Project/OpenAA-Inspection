#pragma once

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeShiftMark	87

class	ShiftMarkLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int		SearchDotEdge;
	int		SearchDotMarkMin;
	int		SearchDotMarkMax;
	bool	NGByLosingMark;
	int		ThresholdLost;		//è¡é∏îªíËÇµÇ´Ç¢ílÅi0-100)
	bool	EnableMark;
	bool	ColorMatch;
public:

	ShiftMarkLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	ShiftMarkLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	ShiftMarkLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ShiftMarkLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeShiftMark;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "ShiftMarkLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new ShiftMarkLibrary(GetLibType(),GetLayersBase());	}
};


