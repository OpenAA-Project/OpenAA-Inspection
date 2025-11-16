#if	!defined(XLockStarKey)
#define	XLockStarKey

#define	_AMD64_

#include <ObjBase.h>
#include <WTypes.h>
#include <Guiddef.h>         // MFC core and standard components
#include <WinDef.h>         // MFC core and standard components

#include "SKAPI.h"
#define	MaxProductNumb	14

#pragma	pack(push,1)
struct	LockStartKeyStruct
{
	BYTE	DataNumb;
	BYTE	Customer;
	BYTE	IssuedYear;
	BYTE	IssuedMonth;

	BYTE	IssuedDay;
	BYTE	IssuedCount;
	WORD	Serial;

	struct	ProductIndo
	{
		WORD	ProductCode;
		WORD	ProductVersion;
	};

	struct	ProductIndo	ProductData[MaxProductNumb];
};

#pragma	pack(pop)


#endif