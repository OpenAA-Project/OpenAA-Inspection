/*
 * Copyright (C) 2025
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

#include "buttonaddsubpage_global.h"
#include "XGUIPacketForDLL.h"

//--------------------------------------------------------------------------
class	CmdAddPage : public GUIDirectMessage
{
public:
	CmdAddPage(LayersBase *base):GUIDirectMessage(base){}
	CmdAddPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdSubPage : public GUIDirectMessage
{
public:
	CmdSubPage(LayersBase *base):GUIDirectMessage(base){}
	CmdSubPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertPage : public GUIDirectMessage
{
public:
	int	IndexPage;	//Insert forwarder

	CmdInsertPage(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRemovePage : public GUIDirectMessage
{
public:
	int	IndexPage;

	CmdRemovePage(LayersBase *base):GUIDirectMessage(base){}
	CmdRemovePage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};