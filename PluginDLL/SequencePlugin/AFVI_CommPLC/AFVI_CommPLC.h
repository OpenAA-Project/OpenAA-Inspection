/*
 * Copyright (C) 2018
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