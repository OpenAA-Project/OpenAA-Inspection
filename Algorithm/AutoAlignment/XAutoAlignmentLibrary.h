#pragma once

#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"

#define	DefLibTypeAutoAlignment			12


class	AutoAlignmentLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	ColorLogic	PickupColor;
	int			PicoShift;
	bool		StartupExecute;
	int			Priority;
	int			PickupExpansion;
	int			NoiseShrink;
	int			ExpandForPickup;
	int			MinDot;			
	int			FringeWidth;	
	double		AdptedMatchingRate;
	double		CompletelyMatchingRate;
public:

	AutoAlignmentLibrary(int LibType,LayersBase *Base);
	virtual	~AutoAlignmentLibrary(void){}

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AutoAlignmentLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	AutoAlignmentLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AutoAlignmentLibraryContainer(LayersBase *base);
	virtual	~AutoAlignmentLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeAutoAlignment;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "AutoAlignment Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new AutoAlignmentLibrary(GetLibType(),GetLayersBase());	}
};
