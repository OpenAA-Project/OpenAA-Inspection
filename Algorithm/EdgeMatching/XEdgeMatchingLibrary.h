#pragma once

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeEdgeMatching		73

class	EdgeMatchingLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	WORD		SearchDotX;
	WORD		SearchDotY;
	WORD		SearchByPixel;
	double		ThresholdDiv;
	double		ThresholdDirection;
	WORD		FocusRadius	;
	short		Layer;		//-1:Automatic,0~:Layer
public:

	EdgeMatchingLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	EdgeMatchingLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	EdgeMatchingLibraryContainer : public AlgorithmLibraryContainer
{
public:
	EdgeMatchingLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)					override{	return DefLibTypeEdgeMatching;	}
	virtual	const char	*GetLibTypeName(void)		override{	return "EdgeMatchingLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)	override{	return new EdgeMatchingLibrary(GetLibType(),GetLayersBase());	}
};

