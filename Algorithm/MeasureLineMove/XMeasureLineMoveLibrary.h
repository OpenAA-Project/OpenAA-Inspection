#pragma once

#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"

#define	DefLibTypeMeasureLineMove			22


class	MeasureLineMoveLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int			SearchDot;
	double		ThresholdM;
	double		ThresholdP;
	int			EdgeWidth;
	bool		PrevailRight;
	bool		PrevailLeft;
	int			UsageLayer;
	bool		ModeToSetInInitial;
	double		OKRangeInInitial;
	int			OutputType;		//0:real distance	,1:Difference from Threshold center
	int			SearchType;		//0:Separated ideal area	1:Simple left/right area	2:Distance-Inside=High-Variance
	double		ThresholdRate;

public:
	MeasureLineMoveLibrary(int LibType,LayersBase *Base);
	virtual	~MeasureLineMoveLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	MeasureLineMoveLibrary	&operator=(const AlgorithmLibrary &src)				override;
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	MeasureLineMoveLibraryContainer : public AlgorithmLibraryContainer
{
public:
	MeasureLineMoveLibraryContainer(LayersBase *base);
	virtual	~MeasureLineMoveLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeMeasureLineMove;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "MeasureLineMove Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new MeasureLineMoveLibrary(GetLibType(),GetLayersBase());	}
};
