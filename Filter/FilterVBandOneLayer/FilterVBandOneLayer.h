#ifndef FILTERVBANDONELAYER_H
#define FILTERVBANDONELAYER_H

#include "filtervbandonelayer_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterVBandOneLayer : public FilterClassBase
{
	int		BandTable[256];
	int		BandTable1[256];
	int		BandTable2[256];
	int		BandTable3[256];
public:
	int		Layer;
	double	MultipleRate;
	int		Offset;
	int		X1,X2;

	FilterVBandOneLayer(LayersBase *base);
	~FilterVBandOneLayer(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	QString	GetDataText(void)			override{	return "FilterVBand";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterVBand.dat";	}
};
#endif // FILTERVBANDONELAYER_H
