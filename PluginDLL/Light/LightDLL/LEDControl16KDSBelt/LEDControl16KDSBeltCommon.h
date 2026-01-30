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

#pragma once
#include "XGUIPacketForDLL.h"

class	CmdReqIsConnected : public GUIDirectMessage
{
public:
	bool	Connected;

	CmdReqIsConnected(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdStartSequence : public GUIDirectMessage
{
public:
	CmdStartSequence(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdEndSequence : public GUIDirectMessage
{
public:
	CmdEndSequence(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdReqEncoderPulse : public GUIDirectMessage
{
public:
	int		EncoderPulse;

	CmdReqEncoderPulse(LayersBase *base)
		:GUIDirectMessage(base){}
};