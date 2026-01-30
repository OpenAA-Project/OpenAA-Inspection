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


#ifndef VCDPROPERTYDEF_H_INC_
#define VCDPROPERTYDEF_H_INC_

#pragma once

#include "IVCDPropertyInterfaces.h"

namespace _DSHOWLIB_NAMESPACE
{
    static const GUID VCDInterface_Range	=	IID_IVCDRangeProperty;
	static const GUID VCDInterface_Switch =	IID_IVCDSwitchProperty;
	static const GUID VCDInterface_Button =	IID_IVCDButtonProperty;
	static const GUID VCDInterface_MapStrings =	IID_IVCDMapStringsProperty;
	static const GUID VCDInterface_AbsoluteValue =	IID_IVCDAbsoluteValueProperty;
};

#endif // VCDPROPERTYDEF_H_INC_