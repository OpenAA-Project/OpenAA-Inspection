/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\ListHistoryButton\ListHistoryButtonPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(SHOWTHRESHOLDFILENAMEPACKET_H)
#define	SHOWTHRESHOLDFILENAMEPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"

class	CmdShowThresholdFileName : public GUIDirectMessage
{
public:
	CmdShowThresholdFileName(LayersBase *base):GUIDirectMessage(base){}

	QString ThresholdFileName;
};

#endif
