#if	!defined(XGerberFastLibrary_h)
#define	XGerberFastLibrary_h

#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"
#include "XServiceForLayers.h"
#include "NListComp.h"

#define	DefLibTypeGerberFast		27



class GerberFastLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:

	int		MaxEnlargeDot;
	int		MaxShrinkDot;
	int		MaxShiftDot;
	double	MaxAngleRadius;
	double	UnstableZone;

	GerberFastLibrary(int LibType,LayersBase *Base);
	virtual	~GerberFastLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	GerberFastLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	GerberFastLibraryContainer : public AlgorithmLibraryContainer
{
public:
	GerberFastLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~GerberFastLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeGerberFast;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "GerberFast Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new GerberFastLibrary(GetLibType(),GetLayersBase());	}
};



#endif