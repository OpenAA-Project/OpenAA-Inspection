/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\PixelInspection\XPixelInspectionPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPIXELINSPECTIONPACKET_H)
#define	XPIXELINSPECTIONPACKET_H
/*
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
*/

#include "XDataInLayer.h"
#include "swap.h"

class	CmdPixelNGDrawMode : public GUIDirectMessage
{
public:
	CmdPixelNGDrawMode(LayersBase *base)
		:GUIDirectMessage(base)
		,ShowOnlyDetail(true)
		,ShowOnlyCircle(true)
		,GeneralInfo2(0)
		,Ret(-1)
		{}

	bool	ShowOnlyDetail;
	bool	ShowOnlyCircle;
	int		GeneralInfo2;

	int		Ret;
};

class	CmdPixelNGSize : public GUIDirectMessage
{
public:
	CmdPixelNGSize(LayersBase *base):GUIDirectMessage(base),NGSize(-1){}

	int		NGSize;
	QColor	NGSizeColor;
};

#endif
