#ifndef FILTERVERTICALLINEAR_H
#define FILTERVERTICALLINEAR_H

#include "filterverticallinear_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XBoolList.h"

class	FilterVerticalLinear : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;
	bool	WholeImage;
	bool	TopSide;
	bool	BottomSide;
	BoolList	Layers;
	double	Gamma;

	FilterVerticalLinear(LayersBase *base);
	~FilterVerticalLinear(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "VerticalLinear";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterVerticalLinear.dat";	}
};

#endif // FILTERVERTICALLINEAR_H
