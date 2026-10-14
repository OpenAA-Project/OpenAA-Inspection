#pragma once


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"
#include "XAlignmentShiftRotationCommon.h"

#define	DefLibTypeAlignmentShiftRotation		73

class	AlignmentShiftRotationLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	WORD		Threshold;
	WORD		LineCount;
	short		TargetLayer;
	WORD		LineLen		;
	WORD		SearchDotX	;
	WORD		SearchDotY	;
	DWORD		SparseAngle	;
	RotationRangeContainer	Rotation;

public:

	AlignmentShiftRotationLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AlignmentShiftRotationLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	AlignmentShiftRotationLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AlignmentShiftRotationLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)					override{	return DefLibTypeAlignmentShiftRotation;	}
	virtual	const char	*GetLibTypeName(void)		override{	return "AlignmentShiftRotationLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)	override{	return new AlignmentShiftRotationLibrary(GetLibType(),GetLayersBase());	}
};

