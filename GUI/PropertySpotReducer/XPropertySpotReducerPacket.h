#if	!defined(XPROPERTYSPOTREDUCERPACKET_H)
#define	XPROPERTYSPOTREDUCERPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XSpotReducer.h"

class	GUICmdAddSpotReducerArea : public GUICmdPacketBase
{
public:
	FlexArea		Area;
	IntList			LayerList;
	int				SpotBrightness;
	double			ReductionLevel;
	int				SpotArea;
	int				SpotCount;

	GUICmdAddSpotReducerArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif

