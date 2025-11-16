#if	!defined(SharedPIOCommon_h)
#define	SharedPIOCommon_h

#include "XTypeDef.h"

struct	SharedPIOInfo
{
	unsigned short	InBitCount;
	unsigned short	OutBitCount;

	BYTE	InData[16];
	BYTE	OutData[16];
};


#endif