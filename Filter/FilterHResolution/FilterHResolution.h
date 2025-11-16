#ifndef FILTERHRESOLUTION_H
#define FILTERHRESOLUTION_H

#include "filterhresolution_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterHResolution : public FilterClassBase
{
	int		*IndxRoot;
	int		*MultA;
	int		*MultB;

public:
	double	Rate;

	FilterHResolution(LayersBase *base);
	~FilterHResolution(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	QString	GetDataText(void)			override{	return "FilterHResolution";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterHResolution.dat";	}
};
#endif // FILTERHRESOLUTION_H
