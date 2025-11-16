/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MakeAverageImage\XStatisticPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XSTATISTICPACKET_H)
#define	XSTATISTICPACKET_H

#include "XDataInLayer.h"
#include "swap.h"

class	CmdSetAverageToMaster : public GUIDirectMessage
{
public:
	CmdSetAverageToMaster(LayersBase *base):GUIDirectMessage(base){}
	CmdSetAverageToMaster(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif