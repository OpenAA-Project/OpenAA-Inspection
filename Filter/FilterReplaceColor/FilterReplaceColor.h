#ifndef FILTERREPLACECOLOR_H
#define FILTERREPLACECOLOR_H

#include "filterreplacecolor_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class FilterReplaceColor : public FilterClassBase
{
public:
	short	SourceLayer;
	short	AdaptedLayer;
	short	ProcessType;	//0:Replace brightness , 1:Add brightness

	short	PickupBrightnessLToReplace;
	short	PickupBrightnessHToReplace;
	short	AdaptedBrightnessToReplace;

	short	PickupBrightnessLToShift;
	short	PickupBrightnessHToShift;
	short	AddedBrightnessToShift;

	FilterReplaceColor(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "ReplaceColor";				}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterReplaceColor.dat";	}

private:
	bool	ExecuteReplace(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteAdd(ImageBuffer *Buff[],int BufferDimCounts);
};

#endif // FILTERREPLACECOLOR_H
