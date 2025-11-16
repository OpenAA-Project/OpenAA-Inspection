#if	!defined(XDXFOperationLibrary_h)
#define	XDXFOperationLibrary_h

#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"
#include "XServiceForLayers.h"
#include "NListComp.h"

#define	DefLibTypeDXFOperation		28



class DXFOperationLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int		MaxEnlargeDot;
	int		MaxShrinkDot;
	int		MaxShiftDot;
	double	MaxAngleRadius;
	double	UnstableZone;

	DXFOperationLibrary(int LibType,LayersBase *Base);
	virtual	~DXFOperationLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	DXFOperationLibrary	&operator=(const AlgorithmLibrary &src)	override;
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	DXFOperationLibraryContainer : public AlgorithmLibraryContainer
{
public:
	DXFOperationLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~DXFOperationLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeDXFOperation;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "DXFOperation Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new DXFOperationLibrary(GetLibType(),GetLayersBase());	}
};



#endif