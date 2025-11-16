#if	!defined(XColorDifferenceLibrary_h)
#define	XColorDifferenceLibrary_h

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include <QColor>
#include <QPainter>
#include <QByteArray>
#include <QIODevice>

//========================================================================================

#define	DefLibTypeColorDifference	59

class	ColorDifferenceLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	//Generation
	int			MaxLength;
	double		GenDeltaE;
	int			GenBlockResolution;
	int			GenMinArea;
	int			GenMaxArea;
	double		GenMaxVariable;
	double		GenMaxBrightDifference;
	int			GenSurroundMergin;

	//Inspection
	double		AdoptedRate;	//Percentage
	double		THDeltaE;
	int32		JudgeMethod;	//0:OK/NG	1:DeltaE	2:FlowSample/HSV threshold
	int			ItemClass;
	double		dH;
	double		dSL;
	double		dSH;
	double		dVL;
	double		dVH;
	bool		AdaptAlignment;	//AlignmentÇÃâeãøÇéÛÇØÇƒåüç∏Ç≤Ç∆Ç…ÉVÉtÉg

public:

	ColorDifferenceLibrary(int LibType,LayersBase *Base);
	virtual	~ColorDifferenceLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	ColorDifferenceLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;

private:
	bool	LoadBlobNew(QIODevice *f);
	bool	LoadBlobOld(QIODevice *f);
};

class	ColorDifferenceLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ColorDifferenceLibraryContainer(LayersBase *base);
	virtual	~ColorDifferenceLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeColorDifference;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "ColorDifference Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new ColorDifferenceLibrary(GetLibType(),GetLayersBase());	}

};

#endif