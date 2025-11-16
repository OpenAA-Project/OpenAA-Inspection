#ifndef FILTERVERTICALREVERSE_H
#define FILTERVERTICALREVERSE_H

#include "filterverticalreverse_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XBoolList.h"

class	FilterVerticalReverse : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;
	double	Width;
	bool	TopSide;
	bool	BottomSide;
	BoolList	Layers;
	double	Gamma;

	FilterVerticalReverse(LayersBase *base);
	~FilterVerticalReverse(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "VerticalReverse";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterVerticalReverse.dat";	}
};

#endif // FILTERVERTICALREVERSE_H
