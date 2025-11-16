#ifndef FILTERREVERSELENSSOMELAYER_H
#define FILTERREVERSELENSSOMELAYER_H

#include "filterreverselensonelayer_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterReverseLensSomeLayer : public FilterClassBase
{
	BYTE	*MultiplyTable;
public:
	bool	LayerEnable[3];
	double	Strength;
	double	Width;
	bool	LeftSide;
	bool	RightSide;

	FilterReverseLensSomeLayer(LayersBase *base);
	~FilterReverseLensSomeLayer(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "FilterReverseLensSomeLayer";		}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterReverseLensSomeLayer.dat";	}
};
#endif // FILTERREVERSELENSSOMELAYER_H
