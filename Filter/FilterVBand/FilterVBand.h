#ifndef FILTERVBAND_H
#define FILTERVBAND_H

#include "filtervband_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterVBand : public FilterClassBase
{
	int		BandTable[256];
	int		BandTable1[256];
	int		BandTable2[256];
	int		BandTable3[256];
public:
	double	MultipleRate;
	int		Offset;
	int		X1,X2;

	FilterVBand(LayersBase *base);
	~FilterVBand(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	QString	GetDataText(void)			override{	return "FilterVBand";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterVBand.dat";	}
};
#endif // FILTERVBAND_H
