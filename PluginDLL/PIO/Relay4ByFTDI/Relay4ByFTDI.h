#ifndef RELAY4BYFTDI_H
#define RELAY4BYFTDI_H

#include "relay4byftdi_global.h"
#include <QString>
#include "ftd2xx.h"

class	Relay4ByFTDI
{
public:
	FT_HANDLE Handle;
	bool	Error;
	BYTE	OutD;

	Relay4ByFTDI()	{	Handle=0;	Error=false;	}

private:

};

#endif // RELAY4BYFTDI_H
