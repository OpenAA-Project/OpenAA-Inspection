#ifndef AFVI_COMMPLC_H
#define AFVI_COMMPLC_H

#include "afvi_commplc_global.h"
#include <windows.h>
#include "SwPlcCom.h"
#include <QString>

class	AFVI_CommPLC
{
public:
	static	QString		CommParam;
	SWPLC_HANDLE	CommHandle;

	AFVI_CommPLC(void){}
	~AFVI_CommPLC(void){}
};

#endif // AFVI_COMMPLC_H
