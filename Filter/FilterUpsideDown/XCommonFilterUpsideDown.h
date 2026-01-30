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

#if	!defined(XCOMMONFILTERUPSIDEDOWN_H)
#define	XCOMMONFILTERUPSIDEDOWN_H

#include "XGUIPacketForDLL.h"

class	CmdExecuteFilter : public GUIDirectMessage
{
public:
	CmdExecuteFilter(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteFilter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdExecuteClearFilter : public GUIDirectMessage
{
public:
	CmdExecuteClearFilter(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteClearFilter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif