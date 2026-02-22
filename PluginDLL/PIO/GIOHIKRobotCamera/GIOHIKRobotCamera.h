#pragma once

#include "giohikrobotcamera_global.h"
#include "XIODLL.h"
#include "XServiceForLayers.h"

class CameraClass;

class GIOHIKRobotCamera: public PIODLLBaseClass,public ServiceForLayers
{
public:
    CameraClass *HIKRobotCamera;
	int			DeviceNo;   

    GIOHIKRobotCamera(LayersBase *base);

    virtual	void	AfterStartSequence(void)    override;
};
