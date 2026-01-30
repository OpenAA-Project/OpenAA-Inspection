/*
 * Copyright (C) 2012
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

#ifndef UDSHL_DEFS_H_INC
#define UDSHL_DEFS_H_INC

#include "libbasedefs.h"

#ifdef UDSHL_GENERATE_DLL_EXPORTS
	#define _UDSHL_EXP_API	__declspec(dllexport)
#else
	#define _UDSHL_EXP_API	__declspec(dllimport)
#endif

#define UDSHL_LIB_VERSION_MAJOR	3
#define UDSHL_LIB_VERSION_MINOR	2


#define _DLL_EXPORT_WARNING_DISABLE warning ( disable : 4251 ) // ... needs to have dll-interface to be used by clients of class ...
#define _DLL_EXPORT_WARNING_ENABLE  warning ( default : 4251 )


#endif // UDSHL_DEFS_H_INC