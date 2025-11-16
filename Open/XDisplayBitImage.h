/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDisplayBitImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XDISPLAYBITIMAGE_H)
#define	XDISPLAYBITIMAGE_H

#include <QImage>
#include <QColor>
#include "XTypeDef.h"

void	DrawBitImage(QImage &Pnt, const BYTE **Src ,int XLen ,int XByte ,int YLen
					,int movx ,int movy ,double ZoomRate
					,int OffsetX ,int OffsetY
					,const QColor &Col);

void	DrawBitImageOr(QImage &Pnt, const BYTE **Src ,int XLen ,int XByte ,int YLen
					,int movx ,int movy ,double ZoomRate
					,int OffsetX ,int OffsetY
					,const QColor &Col);
#endif