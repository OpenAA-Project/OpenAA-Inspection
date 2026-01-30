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

#if	!defined(XCommonFilterUDColorShift_h)
#define	XCommonFilterUDColorShift_h


#include "XGUIPacketForDLL.h"
#include "XDateTime.h"

class	CmdExecuteFilter : public GUIDirectMessage
{
public:
	int		VShift;
	CmdExecuteFilter(LayersBase *base):GUIDirectMessage(base){	VShift=0;	}
	CmdExecuteFilter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	VShift=0;	}
};

class	CmdExecuteClearFilter : public GUIDirectMessage
{
public:
	int		VShift;
	CmdExecuteClearFilter(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteClearFilter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecuteFilterEveryTime : public GUIDirectMessage
{
public:
	XDateTime	MasterTime;
	CmdExecuteFilterEveryTime(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteFilterEveryTime(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecuteClearFilterEveryTime : public GUIDirectMessage
{
public:
	XDateTime	MasterTime;
	CmdExecuteClearFilterEveryTime(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteClearFilterEveryTime(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif