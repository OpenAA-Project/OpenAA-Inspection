/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyZRegulation\XPropertyZRegulationPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPropertyZRegulationPacket_H)
#define	XPropertyZRegulationPacket_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XZAxisRegulation.h"
#include "XFlexArea.h"

class	AddZRegulationAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		Layers;

	AddZRegulationAreaPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqLayersListPacket : public GUIDirectMessage
{
public:
	IntList		Layers;

	CmdReqLayersListPacket(LayersBase *base):GUIDirectMessage(base){}
};

#endif