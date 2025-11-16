#ifndef USB_CONTROL8ARMV2PIO_H
#define USB_CONTROL8ARMV2PIO_H

#include "usb_control8armv2pio_global.h"

class	LayersBase;

class	PioAccessor
{
public:
	LayersBase	*Layers;
	int			LightNumber;

	PioAccessor(void)	{	Layers=NULL; LightNumber=0;	}
};

#endif // USB_CONTROL8ARMV2PIO_H
