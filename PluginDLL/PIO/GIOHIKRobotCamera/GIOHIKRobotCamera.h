#pragma once

#include "giohikrobotcamera_global.h"
#include "XIODLL.h"
#include "XServiceForLayers.h"
#include <QLocalServer>
#include <QLocalSocket>
#include <QMutex>

class CameraClass;

class GIOHIKRobotCamera: public QObject ,public PIODLLBaseClass,public ServiceForLayers
{
    Q_OBJECT

    QLocalSocket    *Socket;
    bool3    InLine0;

public:
    CameraClass *HIKRobotCamera;
	int			DeviceNo;
    QMutex      LockCommand;

    GIOHIKRobotCamera(LayersBase *base);

    virtual	void	AfterStartSequence(void)    override;

	bool	GetBitBySocket(void);
    BYTE	GetByteBySocket(void);
	BYTE	SetByteBySocket(BYTE data);
private slots:
    void    SlotReadyRead();
};
