#ifndef FILTERHORIZONTALLINEAR_H
#define FILTERHORIZONTALLINEAR_H

#include "filterhorizontallinear_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XBoolList.h"

class	FilterHorizontalLinear : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;
	bool	WholeImage;
	bool	LeftSide;
	bool	RightSide;
	BoolList	Layers;
	double	Gamma;

	FilterHorizontalLinear(LayersBase *base);
	~FilterHorizontalLinear(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;

	virtual	QString	GetDataText(void)		override{	return "HorizontalLinear";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterHorizontalLinear.dat";	}
};

#endif // FILTERHORIZONTALLINEAR_H
