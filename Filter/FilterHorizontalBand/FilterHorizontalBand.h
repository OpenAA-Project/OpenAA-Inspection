#ifndef FILTERHORIZONTALBAND_H
#define FILTERHORIZONTALBAND_H

#include "filterhorizontalband_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XBoolList.h"

class	FilterHorizontalBand : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Gain;
	int		CenterX;
	int		BandWidth;
	int		GradationWidth;
	BoolList	Layers;
	double	Gamma;

	FilterHorizontalBand(LayersBase *base);
	~FilterHorizontalBand(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;

	virtual	QString	GetDataText(void)		override{	return "HorizontalBand";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterHorizontalBand.dat";	}
};

#endif // FILTERHORIZONTALBAND_H
