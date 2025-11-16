#ifndef FILTERHSV_H
#define FILTERHSV_H

#include "filterhsv_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterHSV : public FilterClassBase
{
	BYTE	**STable;
	float	**HTable;
public:

	FilterHSV(LayersBase *base);
	~FilterHSV(void);

	virtual	bool	Save(QIODevice *f)	override	{	return true;	}
	virtual	bool	Load(QIODevice *f)	override	{	return true;	}
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "HSV";			}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterHSV.dat";	}
};
#endif // FILTERHSV_H
