/*
 * Copyright (C) 2019
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
#include "NListRPi.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"


bool    EOIStruct::Save(QIODevice *f)
{
    int32   Ver=2;

    if(::Save(f,Ver)==false)
        return false;

    if(::Save(f, Conveyer1Pulse)==false)
        return false;
    if(::Save(f, MulInput)==false)
        return false;
    if(::Save(f,DelayFrameTriggerA)==false)
        return false;
    if(::Save(f,DelayFrameTriggerB)==false)
        return false;
    if(::Save(f,FrameCycle)==false)
        return false;
    if(::Save(f,DropLength)==false)
        return false;
    if(::Save(f,DropFlapONLength)==false)
        return false;
    return true;
}

bool    EOIStruct::Load(QIODevice *f)
{
    int32   Ver;

    if(::Load(f,Ver)==false)
        return false;

    if(::Load(f, Conveyer1Pulse)==false)
        return false;
    if(::Load(f, MulInput)==false)
        return false;
    if(::Load(f,DelayFrameTriggerA)==false)
        return false;
    if(::Load(f,DelayFrameTriggerB)==false)
        return false;
    if(::Load(f,FrameCycle)==false)
        return false;
    if(::Load(f,DropLength)==false)
        return false;
    if(::Load(f,DropFlapONLength)==false)
        return false;
    return true;
}

