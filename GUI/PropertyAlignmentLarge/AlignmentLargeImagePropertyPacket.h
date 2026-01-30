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


#if	!defined(AlignmentLargeIMAGEPROPERTYPACKET_H)
#define	AlignmentLargeIMAGEPROPERTYPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlignmentLarge.h"
#include <QIODevice>
#include "XPacketAlignmentLarge.h"

class	GUICmdAlignmentLargeDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	bool		MultiSelect;
	GUICmdAlignmentLargeDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};


class	GUICmdReqAlignmentLargeDrawMode : public GUIDirectMessage
{
public:
	AlignmentLargeDrawAttr::__DrawKind	Mode;
	ReqAlignmentLargeAreaListPack		AList;

	GUICmdReqAlignmentLargeDrawMode(LayersBase *base):GUIDirectMessage(base)
			{	Mode=AlignmentLargeDrawAttr::_Point;	}
};

class	CmdSetMultiSelectAlignmentLarge: public GUIDirectMessage
{
public:
	bool	MultiSelect;

	CmdSetMultiSelectAlignmentLarge(LayersBase *base):GUIDirectMessage(base)
			{	MultiSelect=false;	}
};

class	CmdReqAlignmentLargeSelectedAreaID: public GUIDirectMessage
{
public:
	int		Page;
	IntList	AreaIDList;

	CmdReqAlignmentLargeSelectedAreaID(LayersBase *base):GUIDirectMessage(base){}
};


#endif