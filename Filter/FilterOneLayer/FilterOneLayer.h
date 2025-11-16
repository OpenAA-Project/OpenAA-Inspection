#ifndef FILTERONELAYER_H
#define FILTERONELAYER_H

#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterOneLayer : public FilterClassBase
{
public:
	ImageBuffer TmpImage;
	int	Layer;
	int	MethodValue;
	int	Param;

	FilterOneLayer(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "OneLayer";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterOneLayer.dat";	}

private:
	bool	ExecuteAverage(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteXAverage(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteMedian(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteMulAverage(ImageBuffer *Buff[],int BufferDimCounts);
};

#endif // FILTERONELAYER_H
