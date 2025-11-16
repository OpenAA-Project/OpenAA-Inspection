/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XImageBufferFunctions.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XIMAGEBUFFERFUNCTIONS_H)
#define	XIMAGEBUFFERFUNCTIONS_H

class	ImageBuffer;

void	TransColorToMono(ImageBuffer *ColorBuff[3] ,ImageBuffer *Dest);
bool	ShrinkImage(ImageBuffer &IBuff,double Rate);

#endif