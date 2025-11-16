#ifndef FILTERUDCOLORSHIFT_H
#define FILTERUDCOLORSHIFT_H

#include "filterudcolorshift_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"


class	ImageBuffer;

class	FilterUDColorShift : public FilterClassBase
{
public:
	bool	ShouldExecute;
	int		ShiftR;
	int		ShiftG;
	int		ShiftB;
	int		VShift;
	bool	CheckTime;
	int		TimeRange;
	int		ShiftOffset;

	FilterUDColorShift(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	QString	GetDataText(void)			override{	return "UDColorShift";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterUDColorShift.dat";	}
};
#endif // FILTERUDCOLORSHIFT_H
