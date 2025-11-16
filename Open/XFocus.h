/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XFocus.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XFOCUS_H)
#define	XFOCUS_H

class	ImageBuffer;
class	FlexArea;

double	GetFocusLevel(ImageBuffer &Img , FlexArea &Area
					  ,int FlowDot=6);

double	GetFocusLevel2(ImageBuffer &Img , FlexArea &Area
					  ,int FlowDot=6);


#endif