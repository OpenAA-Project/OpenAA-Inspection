#ifndef FILTERREMOVENOISELINE_H
#define FILTERREMOVENOISELINE_H

#include "filterremovenoiseline_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterRemoveNoiseLine : public FilterClassBase
{
public:
	bool	NoiseLineH;
	int		NoiseLineWidth;
	int		ThresholdL,ThresholdH;

	FilterRemoveNoiseLine(LayersBase *base);
	~FilterRemoveNoiseLine(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "RemoveNoiseLine";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterRemoveNoiseLine.dat";	}
};

#endif // FILTERREMOVENOISELINE_H
