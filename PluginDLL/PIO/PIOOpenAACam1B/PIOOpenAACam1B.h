#pragma once

#include "XIODLL.h"
#include "XServiceForLayers.h"
#include <QMutex>
#include "XSocket.h"

class	XLightOpenAACam1B;

class PIOOpenAACam1B: public QObject ,public PIODLLBaseClass,public ServiceForLayers
{
    Q_OBJECT

public:
    XLightOpenAACam1B *LightPointer;
    struct  SocketPacket	DataPacket;
	int			DeviceNo;

    PIOOpenAACam1B(LayersBase *base);

	bool	GetBitBySocket(void);
	BYTE	SetByteBySocket(BYTE data);

    bool	FindLight(void);
};