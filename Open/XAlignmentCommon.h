/*
 * Copyright (C) 2020
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

#if	!defined(XAlignmentCommon_h)
#define	XAlignmentCommon_h

class	CmdGetAlignmentAreas : public GUIDirectMessage
{
public:
	FlexAreaPointerContainer	Areas;

	CmdGetAlignmentAreas(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlignmentAreas(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAlignmentSetSearchDot : public GUIDirectMessage
{
public:
	int32	SearchDotX;
	int32	SearchDotY;

	CmdAlignmentSetSearchDot(LayersBase *base):GUIDirectMessage(base){}
	CmdAlignmentSetSearchDot(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif