#pragma once

#include "filterconvertresolution_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	FilterConvertResolution : public FilterClassBase
{
	ImageBuffer	TmpImage;
public:
	double	XZoom;
	double	YZoom;
	int		Cx,Cy;

	FilterConvertResolution(LayersBase *base);
	virtual	~FilterConvertResolution(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;

	virtual	QString	GetDataText(void)			override{	return "ConvertResolution";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterConvertResolution.dat";	}
};