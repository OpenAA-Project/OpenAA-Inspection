#ifndef FILTERREVERSELENSONESIDE2_H
#define FILTERREVERSELENSONESIDE2_H

#include "filterreverselensoneside2_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterReverseLensOneSide2 : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;
	double	Width;
	bool	LeftSide;
	bool	RightSide;

	FilterReverseLensOneSide2(LayersBase *base);
	~FilterReverseLensOneSide2(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "ReverseLens2";				}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterReverseLens2.dat";	}
};

#endif // FILTERREVERSELENSONESIDE2_H
