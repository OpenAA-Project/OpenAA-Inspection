#if	!defined(XProcess3DLibrary_h)
#define	XProcess3DLibrary_h



#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeProcess3D		80

class	Process3DLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	double	BaseCycleDot;
	int		VFilterLength;
	double	HeightPerShift;

	double	LargeTilt;
	double	LargeFlatness;
	double	SmallFlatness;
	int		SmallAreaSize;

public:

	Process3DLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	Process3DLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	Process3DLibraryContainer : public AlgorithmLibraryContainer
{
public:
	Process3DLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeProcess3D;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Process3DLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new Process3DLibrary(GetLibType(),GetLayersBase());	}
};




#endif
