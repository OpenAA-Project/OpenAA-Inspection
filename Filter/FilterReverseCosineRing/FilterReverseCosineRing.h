#ifndef FILTERREVERSECOSINERING_H
#define FILTERREVERSECOSINERING_H

#include "filterreversecosinering_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterReverseCosineRing : public FilterClassBase
{
	unsigned short	**MultiplyTable;
	int				AllocatedLines;
	int				AllocatedWidth;
public:
	double	Strength;
	double	Width;

	FilterReverseCosineRing(LayersBase *base);
	~FilterReverseCosineRing(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "ReverseCosineRing";		}
	virtual	QString	GetDefaultFileName(void)override{	return "ReverseCosineRing.dat";	}
};
#endif // FILTERREVERSECOSINERING_H
