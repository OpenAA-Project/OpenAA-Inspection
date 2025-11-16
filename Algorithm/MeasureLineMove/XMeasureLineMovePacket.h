#if	!defined(XMeasureLineMovePacket_H)
#define	XMeasureLineMovePacket_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XColorSpace.h"
#include "XVector.h"
#include "XFlexAreaImage.h"
#include "XMeasureCommon.h"
#include "NList.h"
#include "XTypeDef.h"
#include <QIODevice>
#include "XIntClass.h"
#include "XDirectCommPacket.h"

//=================================================================================

class	SlaveCommReqPosition : public DirectCommPacketBase
{
public:
	int		ItemID;
	double	DrawPoint;

	SlaveCommReqPosition(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckPosition : public DirectCommPacketBase
{
public:
	double	MasterLocalX,MasterLocalY;
	bool	Found;

	SlaveCommAckPosition(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//=================================================================================
class	SlaveCommReqResultPosition : public DirectCommPacketBase
{
public:
	int		ItemID;
	double	DrawPoint;

	SlaveCommReqResultPosition(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckResultPosition : public DirectCommPacketBase
{
public:
	double	MasterLocalX,MasterLocalY;
	double	ShiftX,ShiftY;
	bool	Found;
	bool	CalcDone;

	SlaveCommAckResultPosition(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdReqConvertUnitPixel : public GUICmdPacketBase
{
public:
	int		Phase;
	int		ItemID;
	bool	PixelToUnit;
	double	Value;

	GUICmdReqConvertUnitPixel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckConvertUnitPixel : public GUICmdPacketBase
{
public:
	double	Value;

	GUICmdAckConvertUnitPixel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif