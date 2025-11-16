/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AlignmentImagePanel\AlignmentImagePropertyPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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