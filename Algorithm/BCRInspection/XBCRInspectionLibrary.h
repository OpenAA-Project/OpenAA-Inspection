#pragma once

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"

#define	DefLibTypeBCRInspection		52	


class	BCRInspectionLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:

	BCRInspectionLibrary(int LibType,LayersBase *Base);

	//virtual	BCRInspectionLibrary	&operator=(const AlgorithmLibrary &src)	override;

private:
};

class	BCRInspectionLibraryContainer : public AlgorithmLibraryContainer
{
public:
	BCRInspectionLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeBCRInspection;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "BCRInspection Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new BCRInspectionLibrary(GetLibType(),GetLayersBase());	}

};
