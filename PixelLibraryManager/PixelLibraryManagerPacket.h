/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PixelLibraryManager\PixelLibraryManagerPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(PIXELLIBRARYMANAGERPACKET_H)
#define	PIXELLIBRARYMANAGERPACKET_H

#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "swap.h"

class	CmdGetLibraryListPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetLibraryListPacket(void){}
};

#endif // PIXELLIBRARYMANAGERPACKET_H
