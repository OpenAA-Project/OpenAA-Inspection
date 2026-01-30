/*
 * Copyright (C) 2022
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

#include "DeviceStruct.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include <QIODevice>


bool    KDSBeltPIOFixedStruct::Save(QIODevice *f)
{
    int32   Ver=1;

    if(::Save(f,Ver)==false)
        return false;

	if(::Save(f, MulInput)==false)
		return false;

	if(::Save(f, TriggerFilterMinOFF)==false)
		return false;
	if(::Save(f, TriggerFilterMinON)==false)
		return false;

    return true;
}

bool    KDSBeltPIOFixedStruct::Load(QIODevice *f)
{
    int32   Ver;

    if(::Load(f,Ver)==false)
        return false;

    if(::Load(f, MulInput)==false)
		return false;
	if(::Load(f, TriggerFilterMinOFF)==false)
		return false;
	if(::Load(f, TriggerFilterMinON)==false)
		return false;

    return true;
}


bool    KDSBeltPIOStruct::Save(QIODevice *f)
{
    if(KDSBeltPIOFixedData.Save(f)==false)
		return false;
    return true;
}

bool    KDSBeltPIOStruct::Load(QIODevice *f)
{
    if(KDSBeltPIOFixedData.Load(f)==false)
		return false;
    return true;
}
