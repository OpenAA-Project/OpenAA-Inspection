/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\ListHistoryButton\ListHistoryButtonPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(LISTHISTORYBUTTONPACKET_H)
#define	LISTHISTORYBUTTONPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"

class	CmdListHistoryButtonKeyFunc : public GUIDirectMessage
{
public:
	CmdListHistoryButtonKeyFunc(LayersBase *base):GUIDirectMessage(base),KeyDeletePressRepeat(false),KeyDeleteRelease(false){}

	bool	KeyDeletePressRepeat;
	bool	KeyDeleteRelease;
};

class	CmdListHistoryButtonUpdate : public GUIDirectMessage
{
public:
	CmdListHistoryButtonUpdate(LayersBase *base):GUIDirectMessage(base){}
};

#endif
