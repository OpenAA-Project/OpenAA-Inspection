#ifndef FILTERLINEARHORIZONTAL_H
#define FILTERLINEARHORIZONTAL_H

#include "filterlinearhorizontal_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterLinearHorizontal : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;	//Gain/Pixel
	bool	LeftSide;
	bool	RightSide;

	FilterLinearHorizontal(LayersBase *base);
	~FilterLinearHorizontal(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "ReverseLens";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterReverseLens.dat";	}
};
#endif // FILTERLINEARHORIZONTAL_H
