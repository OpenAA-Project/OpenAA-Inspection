#pragma once

#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"
#include "XServiceForLayers.h"
#include "NListComp.h"

#define	DefLibTypeMultiSpectral		30

class	AlgorithmItemPLI;

class MultiSpectralLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int		SearchDot		;
	double	ThresholdLength	;
	int		OKDot			;

	MultiSpectralLibrary(int LibType,LayersBase *Base);
	virtual	~MultiSpectralLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	MultiSpectralLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	MultiSpectralLibraryContainer : public AlgorithmLibraryContainer
{
public:
	MultiSpectralLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~MultiSpectralLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeMultiSpectral;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "MultiSpectral Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new MultiSpectralLibrary(GetLibType(),GetLayersBase());	}
};
