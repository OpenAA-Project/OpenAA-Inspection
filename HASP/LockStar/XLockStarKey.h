/*
 * Copyright (C) 2021
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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