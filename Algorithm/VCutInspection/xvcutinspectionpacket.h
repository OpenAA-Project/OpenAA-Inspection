/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\VCutInspection\XVCutInspectionPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XVCUTINSPECTIONPACKET_H)
#define	XVCUTINSPECTIONPACKET_H

#include "XDataInLayer.h"
#include "swap.h"


class	CmdMakeResultVCutMapPacket: public GUIDirectMessage
{
public:
	int		LibID;
	BYTE	**BmpMap;

	CmdMakeResultVCutMapPacket(LayersBase *base):GUIDirectMessage(base){}
};

#endif