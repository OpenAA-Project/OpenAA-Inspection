#ifndef FILTERSHRINKIMAGE_H
#define FILTERSHRINKIMAGE_H

#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class	FilterShrinkImage : public FilterClassBase
{
public:
	int			ShrinkRate;
	int			ShrinkMethod;	//ÇOÅFíPèÉèkè¨	ÇPÅFçÇãPìxçÃóp	ÇQÅFí·ãPìxçÃóp	ÇRÅFïΩãœâªèkè¨
	int			*IndexTable;
	int			AllocSize;

	FilterShrinkImage(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "Shrink";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterShrink.dat";	}
private:
	bool	ExecuteSimple(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteHighest(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteLowest(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteAverage(ImageBuffer *Buff[],int BufferDimCounts);
};

#endif // FILTERSHRINKIMAGE_H
