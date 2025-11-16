/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AlignmentLargeImagePanel\AlignmentLargeImagePropertyPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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