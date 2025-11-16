#ifndef SEQRELAY4BYFTDI_H
#define SEQRELAY4BYFTDI_H

#include "seqrelay4byftdi_global.h"
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

#endif // SEQRELAY4BYFTDI_H
