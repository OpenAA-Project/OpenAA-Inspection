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

#if	!defined(HookPeakingCommon_h)
#define	HookPeakingCommon_h

#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"

class	CmdSetPeaking : public GUIDirectMessage
{
public:
	double		Alpha;
	bool		Active;

	CmdSetPeaking(LayersBase *base):GUIDirectMessage(base){}
	CmdSetPeaking(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetPeaking : public GUIDirectMessage
{
public:
	double		Alpha;
	bool		Active;

	CmdGetPeaking(LayersBase *base):GUIDirectMessage(base){}
	CmdGetPeaking(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetPeakingColor : public GUIDirectMessage
{
public:
	QColor	Color;

	CmdSetPeakingColor(LayersBase *base):GUIDirectMessage(base){}
	CmdSetPeakingColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetPeakingColor : public GUIDirectMessage
{
public:
	QColor	Color;

	CmdGetPeakingColor(LayersBase *base):GUIDirectMessage(base){}
	CmdGetPeakingColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDrawPeaking : public GUIDirectMessage
{
public:
	QImage		*PntImage;
	QPainter	*Pnt;
	int		movx,movy;
	double	ZoomRate;

	CmdDrawPeaking(LayersBase *base):GUIDirectMessage(base){}
};

#endif