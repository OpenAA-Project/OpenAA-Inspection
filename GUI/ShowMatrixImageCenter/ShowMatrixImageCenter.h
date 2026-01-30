/*
 * Copyright (C) 2016
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

#ifndef SHOWMATRIXIMAGECENTER_H
#define SHOWMATRIXIMAGECENTER_H

#include "showmatriximagecenter_global.h"
#include "XGUIPacketForDLL.h"

class	CmdSetCenterInImage : public GUIDirectMessage
{
public:
	int	x,y;

	CmdSetCenterInImage(LayersBase *base):GUIDirectMessage(base){}
	CmdSetCenterInImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqCenterInImage : public GUIDirectMessage
{
public:
	int	x,y;

	CmdReqCenterInImage(LayersBase *base):GUIDirectMessage(base){	x=y=0;	}
	CmdReqCenterInImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	x=y=0;	}
};

#endif // SHOWMATRIXIMAGECENTER_H