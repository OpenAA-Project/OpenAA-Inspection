#ifndef FILTERBRIGHTNESSTHRESHOLDCONVERT_H
#define FILTERBRIGHTNESSTHRESHOLDCONVERT_H

#include "filterbrightnessthresholdconvert_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterBrightnessThresholdConvert : public FilterClassBase
{
	BYTE	TransTable[256];

public:
	double ThresholdBrightness;
	double ThresholdWidth;

	FilterBrightnessThresholdConvert(LayersBase *base);
	virtual	~FilterBrightnessThresholdConvert(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)									override;
	virtual	bool	Load(QIODevice *f)									override;
	virtual	bool	Initial(void)				override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;

	virtual	QString	GetDataText(void)			override	{	return "BrightnessThresholdConvert";	}
	virtual	QString	GetDefaultFileName(void)	override	{	return "FilterBrightnessThresholdConvert.dat";	}
};
#endif // FILTERBRIGHTNESSTHRESHOLDCONVERT_H
