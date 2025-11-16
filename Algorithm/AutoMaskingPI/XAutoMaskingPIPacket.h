/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoMaskingPI\XAutoMaskingPIPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XAUTOMASKINGPIPACKET_H)
#define	XAUTOMASKINGPIPACKET_H

#include "XDataInLayer.h"
#include "swap.h"


class	CmdGenerateAutoMaskingPILibraryPacket: public GUIDirectMessage
{
public:
	int	LibID;

	CmdGenerateAutoMaskingPILibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

#endif