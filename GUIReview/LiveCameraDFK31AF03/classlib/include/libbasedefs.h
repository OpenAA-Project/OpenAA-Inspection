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

#ifndef LIBBASEDEFS_H_INC
#define LIBBASEDEFS_H_INC

#define _DSHOWLIB_NAMESPACE DShowLib
namespace DShowLib
{
};

namespace _DSHOWLIB_NAMESPACE	// define for certain code completion tools
{
};


#pragma warning( disable : 4786 ) // too long debug info // may be ignored

#define _DLL_EXPORT_WARNING_DISABLE warning ( disable : 4251 ) // ... needs to have dll-interface to be used by clients of class ...
#define _DLL_EXPORT_WARNING_ENABLE  warning ( default : 4251 )

#define UDSHL_NAME_BASE "TIS_UDSHL09"

#endif // LIBBASEDEFS_H_INC