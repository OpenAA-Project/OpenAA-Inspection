#ifndef FILTERMEDIANSMOOTH_H
#define FILTERMEDIANSMOOTH_H

#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class	FilterMedianSmooth : public FilterClassBase
{
public:
	ImageBuffer **TmpImage;
	int			AllocatedLayerCount;
	int			FilterDot;

	FilterMedianSmooth(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "MedianSmooth";				}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterMedianSmooth.dat";	}
private:
};
#endif // FILTERMEDIANSMOOTH_H
