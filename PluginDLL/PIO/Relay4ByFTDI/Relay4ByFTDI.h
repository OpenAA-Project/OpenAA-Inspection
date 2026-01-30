/*
 * Copyright (C) 2020
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