#if	!defined(XFrameDefPacket_h)
#define	XFrameDefPacket_h

#include "NList.h"
#include "XTypeDef.h"
#include <QIODevice>
#include "XIntClass.h"
#include "XDirectCommPacket.h"


class	SlaveCommReqMasterImage : public DirectCommPacketBase
{
public:
	int		GroupNumber;
	double	ZoomRate;
	int		Gx1,Gy1,Gx2,Gy2;
	int		DestGCx,DestGCy;

	SlaveCommReqMasterImage(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckMasterImage : public DirectCommPacketBase
{
public:
	QImage	MasterImage;

	SlaveCommAckMasterImage(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif