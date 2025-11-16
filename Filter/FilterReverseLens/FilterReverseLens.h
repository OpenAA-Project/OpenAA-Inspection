#ifndef FILTERREVERSELENS_H
#define FILTERREVERSELENS_H

#include "filterreverselens_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterReverseLens : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;
	double	Width;
	int32	StartX;
	int32	EndX;

	FilterReverseLens(LayersBase *base);
	~FilterReverseLens(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "ReverseLens";			}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterReverseLens.dat";	}
};

#endif // FILTERREVERSELENS_H
