#ifndef FILTERBRIGHTNESSLOGCONVERT_H
#define FILTERBRIGHTNESSLOGCONVERT_H

#include "filterbrightnesslogconvert_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterBrightnessLogConvert : public FilterClassBase
{
	BYTE	TransTable[256];

public:
	int		Position;
	double	Strength;

	FilterBrightnessLogConvert(LayersBase *base);
	virtual	~FilterBrightnessLogConvert(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;

	virtual	QString	GetDataText(void)			override	{	return "BrightnessLogConvert";	}
	virtual	QString	GetDefaultFileName(void)	override	{	return "FilterBrightnessLogConvert.dat";	}
};


#endif // FILTERBRIGHTNESSLOGCONVERT_H
