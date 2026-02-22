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
#include <QString>

enum EnumAVFormat
{
	FormatMotionJPeg
	,FormatMPeg1
	,FormatMPeg2
	,FormatMPeg4
};

struct RecordStruct
{
	enum Command
	{
		_ReqDetach			= 1
		,_ReqAttach			= 2
		,_StartRecording	= 3
		,_EndRecording		= 4
		,_RestartRecording	= 5
		,_HaltRecording		= 6
		,_Ack				= 7
		,_Nack				= 8

	}Cmd;
	int		MovieXSize;
	int		MovieYSize;
	int		LayerNumb;
	double	FPS;
	int		Quality;
};

struct RecordHeaderStruct
{
	wchar_t		FileName[1024];
	int			MovieXSize;
	int			MovieYSize;
	int			LayerNumb;
	double		FPS;
	int			Quality;
	long long	CurrentTime;
	long long	Duration;
	bool		Opened;
};