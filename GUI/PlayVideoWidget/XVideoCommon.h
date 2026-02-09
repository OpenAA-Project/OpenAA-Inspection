/*
 * Copyright (C) 2026
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

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"


class	CmdVideo_Rewind : public GUIDirectMessage
{
public:
	CmdVideo_Rewind(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_Forward : public GUIDirectMessage
{
public:
	CmdVideo_Forward(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_Play : public GUIDirectMessage
{
public:
	CmdVideo_Play(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_Pause : public GUIDirectMessage
{
public:
	CmdVideo_Pause(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_LoadFile : public GUIDirectMessage
{
public:
	QString	FileName;
	qint64	TotalTime;

	CmdVideo_LoadFile(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_SetPlaybackRate : public GUIDirectMessage
{
public:
	double	PlaybackRate;

	CmdVideo_SetPlaybackRate(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_GetPlaybackRate : public GUIDirectMessage
{
public:
	double	PlaybackRate;

	CmdVideo_GetPlaybackRate(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdVideo_GetCurrentTime : public GUIDirectMessage
{
public:
	bool	IsPlaying;
	qint64	MaxTime;
	qint64	CurrentTime;

	CmdVideo_GetCurrentTime(LayersBase* base) :GUIDirectMessage(base) {}
};
