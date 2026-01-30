/*
 * Copyright (C) 2023
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

#ifndef HASPLIB_H
#define HASPLIB_H

#include "hasplib_global.h"
//#include "hasp_hl.h"
#include "hasp_api.h"

class HASPLIB_EXPORT Hasplib
{
public:
    Hasplib();
    ~Hasplib();
	int decrypt(hasp_handle_t handle,  char *cday, char *cNumber);
	int haspRead(hasp_handle_t handle);
	static int HaspExecute(char *sday, char *sNumber);
private:
	hasp_handle_t   handle;
	char haspdata[256];

};

#endif // HASPLIB_H