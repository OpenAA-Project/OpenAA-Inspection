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



#if	!defined(XMASKINGFROMGENERAL_H)
#define	XMASKINGFROMGENERAL_H

#include "XDataInLayer.h"


class	CmdCreateMaskingBitmapWithLibPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	int		LibType;
	int		LibID;
	BYTE	**BmpMap;

	CmdCreateMaskingBitmapWithLibPacket(LayersBase *base):GUIDirectMessage(base){	BmpMap=NULL;	}
};

class	CmdCoverLimitedMaskWithLibPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	int		LibType;
	int		LibID;
	BYTE	**BmpMap;

	CmdCoverLimitedMaskWithLibPacket(LayersBase *base):GUIDirectMessage(base){	BmpMap=NULL;	}
};

class	CmdCreateCutLineBitmapPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	BYTE	**BmpMap;

	CmdCreateCutLineBitmapPacket(LayersBase *base):GUIDirectMessage(base){	BmpMap=NULL;	}
};

class	CmdCreateMaskingPIBitmapWithLibPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	int		LibType;
	int		LibID;
	BYTE	**BmpMap;

	CmdCreateMaskingPIBitmapWithLibPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateMaskingPIAutoBitmapWithLibPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	int		LibType;
	int		LibID;
	BYTE	**AutoBmpMap;

	CmdCreateMaskingPIAutoBitmapWithLibPacket(LayersBase *base):GUIDirectMessage(base){}
};
#endif