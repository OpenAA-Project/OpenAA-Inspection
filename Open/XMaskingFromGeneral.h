/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMaskingFromGeneral.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XMASKINGFROMGENERAL_H)
#define	XMASKINGFROMGENERAL_H

#include "XDataInLayer.h"


class	CmdCreateMaskingBitmapWithLibPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	int		LibType;
	int		LibID;
	BYTE	**BmpMap;

	CmdCreateMaskingBitmapWithLibPacket(LayersBase *base):GUIDirectMessage(base){	BmpMap=NULL;	}
};

class	CmdCoverLimitedMaskWithLibPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	int		LibType;
	int		LibID;
	BYTE	**BmpMap;

	CmdCoverLimitedMaskWithLibPacket(LayersBase *base):GUIDirectMessage(base){	BmpMap=NULL;	}
};

class	CmdCreateCutLineBitmapPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	BYTE	**BmpMap;

	CmdCreateCutLineBitmapPacket(LayersBase *base):GUIDirectMessage(base){	BmpMap=NULL;	}
};

class	CmdCreateMaskingPIBitmapWithLibPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	int		LibType;
	int		LibID;
	BYTE	**BmpMap;

	CmdCreateMaskingPIBitmapWithLibPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateMaskingPIAutoBitmapWithLibPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	int		LibType;
	int		LibID;
	BYTE	**AutoBmpMap;

	CmdCreateMaskingPIAutoBitmapWithLibPacket(LayersBase *base):GUIDirectMessage(base){}
};
#endif