#ifndef FILTERIMAGESHADINGAREA_H
#define FILTERIMAGESHADINGAREA_H

#include "filterimageshadingarea_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class	FilterImageShadingArea : public FilterClassBase
{
public:
	short	***MultiplePerDot;
	int32	LayerNumb;
	int32	XLen;
	int32	YLen;

	double	MagR;
	double	MagG;
	double	MagB;
	int		UsagePhaseNumber;
	int		UsagePageNumber;
	QStringList	FileList;

	FilterImageShadingArea(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "ImageShadingArea";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterImageShadingArea.dat";	}
private:
};
#endif // FILTERIMAGESHADINGAREA_H
