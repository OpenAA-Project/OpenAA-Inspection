#ifndef FILTERMOVEIMAGE_H
#define FILTERMOVEIMAGE_H

#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterMoveImage : public FilterClassBase
{
public:
	int	Dx,Dy;

	FilterMoveImage(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	QString	GetDataText(void)			override{	return "MoveImage";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterMoveImage.dat";	}
};
#endif // FILTERMOVEIMAGE_H
