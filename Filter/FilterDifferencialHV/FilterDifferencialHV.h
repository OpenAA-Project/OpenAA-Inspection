#ifndef FILTERDIFFERENCIALHV_H
#define FILTERDIFFERENCIALHV_H

#include "filterdifferencialhv_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XBoolList.h"

class	FilterDifferencialHV : public FilterClassBase
{
public:
	BoolList	Layers;
	double	Gain;
	int		Length;
	bool	Vertical;
	bool	BPF;
	int		PassWidth;
	double	*MutBPF;
	double	A;
	double	AA;

	FilterDifferencialHV(LayersBase *base);
	~FilterDifferencialHV(void);

	bool	Initial(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;

	virtual	QString	GetDataText(void)		override{	return "FilterDifferencialHV";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterDifferencialHV.dat";	}
};


#endif // FILTERDIFFERENCIALHV_H
