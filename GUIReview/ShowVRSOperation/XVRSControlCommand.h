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

#if	!defined(XVRSCONTROLCOMMAND_H)
#define	XVRSCONTROLCOMMAND_H

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QString>
#include "XGUIPacketForDLL.h"

class	CmdVRSOrigin : public GUIDirectMessage
{
public:

	CmdVRSOrigin(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdVRSEscape : public GUIDirectMessage
{
public:

	CmdVRSEscape(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdVRSMoveX : public GUIDirectMessage
{
public:
	int	Dx;

	CmdVRSMoveX(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdVRSMoveY : public GUIDirectMessage
{
public:
	int	Dy;

	CmdVRSMoveY(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdVRSMoveZ : public GUIDirectMessage
{
public:
	int	Dz;

	CmdVRSMoveZ(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdVRSMoveXY : public GUIDirectMessage
{
public:
	int	Dx;
	int	Dy;

	CmdVRSMoveXY(LayersBase *base)
		:GUIDirectMessage(base){}
};

#endif