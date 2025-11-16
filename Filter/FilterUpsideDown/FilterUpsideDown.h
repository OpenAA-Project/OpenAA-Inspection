#ifndef FILTERUPSIDEDOWN_H
#define FILTERUPSIDEDOWN_H

#include "filterupsidedown_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class	FilterUpsideDown : public FilterClassBase
{
public:
	bool	ShouldExecute;
	bool	UseShouldExecute;

	FilterUpsideDown(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	QString	GetDataText(void)			override{	return "UpsideDown";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterUpsideDown.dat";	}
};
#endif // FILTERUPSIDEDOWN_H
