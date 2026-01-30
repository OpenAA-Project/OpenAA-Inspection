/*
 * Copyright (C) 2015
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

#if	!defined(XCommonFilterMoveImage_h)
#define	XCommonFilterMoveImage_h


#include "XGUIPacketForDLL.h"
#include "XDateTime.h"

class	CmdFilterReqXY : public GUIDirectMessage
{
public:
	int		MovX,MovY;
	CmdFilterReqXY(LayersBase *base):GUIDirectMessage(base){	MovX=MovY=0;		}
	CmdFilterReqXY(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	MovX=MovY=0;	}
};

class	CmdFilterSetXY : public GUIDirectMessage
{
public:
	int		MovX,MovY;
	CmdFilterSetXY(LayersBase *base):GUIDirectMessage(base){	MovX=MovY=0;	}
	CmdFilterSetXY(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	MovX=MovY=0;	}
};


#endif