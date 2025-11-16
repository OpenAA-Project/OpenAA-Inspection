#pragma once

#include "filterdynamicbrightness_global.h"

#include "XFilterClass.h"
#include "XDLLType.h"

class    FilterDynamicBrightness : public FilterClassBase
{
	double	*CurrentBrightness;
	double	*TmpDim;
public:
	int		CheckPointX,CheckPointWidth;
	int		ExeX1,ExeX2;
	double	GainP,GainM;
	double	StaticBrightness;

 
	FilterDynamicBrightness(LayersBase *base);
	virtual	~FilterDynamicBrightness(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;

	virtual	QString	GetDataText(void)		override{	return "DynamicBrightness";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterDynamicBrightness.dat";	}
};
