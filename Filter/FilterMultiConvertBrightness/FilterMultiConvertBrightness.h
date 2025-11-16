#ifndef FILTERMULTICONVERTBRIGHTNESS_H
#define FILTERMULTICONVERTBRIGHTNESS_H

#include "filtermulticonvertbrightness_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterMultiConvertBrightness : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	StrengthL;
	double	WidthL;
	double	InclineL;
	double	AddVL;
	double	AddBL;

	double	StrengthR;
	double	WidthR;
	double	InclineR;
	double	AddVR;
	double	AddBR;

	FilterMultiConvertBrightness(LayersBase *base);
	~FilterMultiConvertBrightness(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "FilterMultiConvertBrightness";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterMultiConvertBrightness.dat";	}
};
#endif // FILTERMULTICONVERTBRIGHTNESS_H
