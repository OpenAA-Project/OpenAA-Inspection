/*
 * Copyright (C) 2014
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

#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "ReviewStructureItems.h"
#include "../XGUIReviewCommonPacket.h"

class GUICmdReqStaticMachineID : public GUIDirectMessage
{
public:
	// Send
	int32		DefaultTopMachineID;
	int32		DefaultBottomMachineID;	

public:
	GUICmdReqStaticMachineID(LayersBase *base):GUIDirectMessage(base),DefaultTopMachineID(-1),DefaultBottomMachineID(-1){}
	GUICmdReqStaticMachineID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase),DefaultTopMachineID(-1),DefaultBottomMachineID(-1){}
};