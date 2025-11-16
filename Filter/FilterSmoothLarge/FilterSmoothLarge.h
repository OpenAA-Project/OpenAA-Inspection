#ifndef FILTERSMOOTHLARGE_H
#define FILTERSMOOTHLARGE_H

#include "filtersmoothlarge_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"


class	FilterSmoothLarge : public FilterClassBase
{
	int	**TmpBuff;
	int	AllocLines;
	int	*FormerLineSum;
	ImageBuffer	TmpImage;
public:
	int	WindowSize;

	FilterSmoothLarge(LayersBase *base);
	~FilterSmoothLarge(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "SmoothLarge";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterSmoothLarge.dat";	}

	void	MakeOneSum(int *TBuff ,BYTE *Source);
};

#endif // FILTERSMOOTHLARGE_H
