#ifndef FILTEREVENODD_H
#define FILTEREVENODD_H

#include "filterevenodd_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterEvenOdd : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	ALeftEven;
	double	ALeftOdd;
	double	ARightEven;
	double	ARightOdd;

	FilterEvenOdd(LayersBase *base);
	~FilterEvenOdd(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;

	virtual	QString	GetDataText(void)		override{	return "EvenOdd";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterEvenOdd.dat";	}
};

#endif // FILTEREVENODD_H
