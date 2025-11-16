#if	!defined(XLEARNINGLIBHIDE_H)
#define	XLEARNINGLIBHIDE_H

#include "XGUIPacketForDLL.h"


class	GUICmdReqImageForPaint : public GUICmdPacketBase
{
public:
	int		LocalX1,LocalY1;
	int		LocalX2,LocalY2;
	double	ZoomRate;
	int		ScrWidth;
	int		ScrHeight;

	GUICmdReqImageForPaint(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckImageForPaint : public GUICmdPacketBase
{
public:
	QImage	Image;

	GUICmdAckImageForPaint(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif