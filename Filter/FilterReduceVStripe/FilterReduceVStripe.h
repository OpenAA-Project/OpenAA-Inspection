#pragma once

#include "filterreducevstripe_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterReduceVStripe : public FilterClassBase
{
public:
	bool	FirstMode;
	double	IdealBrightness[100][2][3];
	double	CurrentBrightness[100][2][3];
	int		AddBrightness[100][3];
	int		Step;	//=1024
	int		TopY;
	int		YLen;
	int		BoxSize;	//=50


	FilterReduceVStripe(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "ReduceVStripe";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterReduceVStripe.dat";	}

private:
	double	GetBoxBrightness(int x1 ,int y1 ,int x2,int y2, ImageBuffer *Buff);
};
