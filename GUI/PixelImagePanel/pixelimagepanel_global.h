/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PixelImagePanel\pixelimagepanel_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PIXELIMAGEPANEL_GLOBAL_H
#define PIXELIMAGEPANEL_GLOBAL_H

#include <qglobal.h>

#ifdef PIXELIMAGEPANEL_LIB
# define PIXELIMAGEPANEL_EXPORT Q_DECL_EXPORT
#else
# define PIXELIMAGEPANEL_EXPORT Q_DECL_IMPORT
#endif

#endif // PIXELIMAGEPANEL_GLOBAL_H
