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


#if	!defined(ALIGNMENTIMAGEPROPERTYPACKET_H)
#define	ALIGNMENTIMAGEPROPERTYPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlignment.h"
#include <QIODevice>
#include "XPacketAlignment.h"

class	GUICmdAlignmentDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	GUICmdAlignmentDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};


class	GUICmdReqAlignmentDrawMode : public GUIDirectMessage
{
public:
	AlignmentDrawAttr::__DrawKind	Mode;
	ReqAlignmentAreaListPack		AList;

	GUICmdReqAlignmentDrawMode(LayersBase *base):GUIDirectMessage(base)
			{	Mode=AlignmentDrawAttr::_Point;	}
};

#endif