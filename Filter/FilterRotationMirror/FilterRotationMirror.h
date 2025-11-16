#ifndef FILTERROTATIONMIRROR_H
#define FILTERROTATIONMIRROR_H

#include "filterrotationmirror_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterRotationMirror : public FilterClassBase
{
public:
	bool	UpsideDown;
	bool	LeftRight;
	int		Angle;

	FilterRotationMirror(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	QString	GetDataText(void)			override{	return "RotationMirror";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterRotationMirror.dat";	}
};

#endif // FILTERROTATIONMIRROR_H
