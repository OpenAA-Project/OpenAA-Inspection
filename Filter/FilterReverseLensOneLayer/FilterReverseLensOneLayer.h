#ifndef FILTERREVERSELENSONELAYER_H
#define FILTERREVERSELENSONELAYER_H

#include "filterreverselensonelayer_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterReverseLensOneLayer : public FilterClassBase
{
	int		*MultiplyTable;
public:
	int		Layer;
	double	Strength;
	double	Width;
	bool	LeftSide;
	bool	RightSide;

	FilterReverseLensOneLayer(LayersBase *base);
	~FilterReverseLensOneLayer(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "FilterReverseLensOneLayer";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterReverseLensOneLayer.dat";	}
};
#endif // FILTERREVERSELENSONELAYER_H
