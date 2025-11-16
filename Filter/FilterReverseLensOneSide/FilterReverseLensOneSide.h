#ifndef FILTERREVERSELENSONESIDE_H
#define FILTERREVERSELENSONESIDE_H

#include "filterreverselensoneside_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterReverseLensOneSide : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;
	double	Width;
	bool	LeftSide;
	bool	RightSide;

	FilterReverseLensOneSide(LayersBase *base);
	~FilterReverseLensOneSide(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "ReverseLens";			}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterReverseLens.dat";	}
};

#endif // FILTERREVERSELENSONESIDE_H
