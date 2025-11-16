#ifndef FILTERCOLORSHIFT_H
#define FILTERCOLORSHIFT_H

#include "filtercolorshift_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterColorShift : public FilterClassBase
{
public:
	int	Length;

	FilterColorShift(LayersBase *base):FilterClassBase(base){	Length=5;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);

	virtual	QString	GetDataText(void){	return "ColorShift";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterColorShift.dat";	}
};

#endif // FILTERCOLORSHIFT_H
