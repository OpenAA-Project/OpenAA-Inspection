#pragma once

#include "XFilterClass.h"
#include "XDLLType.h"
#include "NListComp.h"

class	ImageBuffer;


class VBandInfo : public NPListSaveLoad<VBandInfo>
{
public:
	int		XPos;
	int		ShiftY;

	VBandInfo(void){}
	VBandInfo(const VBandInfo &src);

	bool	Save(QIODevice *f)	override;
	bool	Load(QIODevice *f)	override;

	virtual	int	Compare(VBandInfo &src)	override;
};

class VBandInfoContainer : public NPListPackSaveLoad<VBandInfo>
{
public:
	VBandInfoContainer(void){}
	VBandInfoContainer(const VBandInfoContainer &src);

	virtual	VBandInfo	*Create(void)	override;
};



class	FilterShiftVBand : public FilterClassBase
{
public:
	VBandInfoContainer  VBands;

	FilterShiftVBand(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "ShiftVBand";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterShiftVBand.dat";	}

private:
	void	ExeShiftY(ImageBuffer *Buff,int LeftX,int RightX,int AddedShiftY);
};