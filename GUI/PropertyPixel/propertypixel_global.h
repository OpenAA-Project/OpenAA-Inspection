/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyPixel\propertypixel_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYPIXEL_GLOBAL_H
#define PROPERTYPIXEL_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYPIXEL_LIB
# define PROPERTYPIXEL_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYPIXEL_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYPIXEL_GLOBAL_H
