#include "XRWDevice.h"

RWDeviceBaseClass::RWDeviceBaseClass(LayersBase *base,QWidget *parent)
	:QWidget(parent),ServiceForLayers(base)
{
	DeviceID=-1;
}

void	RWDeviceBaseClass::SetDeviceID(int d)
{
	DeviceID=d;
}
int		RWDeviceBaseClass::GetDeviceID(void)
{
	return DeviceID;
}