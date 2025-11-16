/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\propertycolorblock_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYCOLORBLOCK_GLOBAL_H
#define PROPERTYCOLORBLOCK_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYCOLORBLOCK_LIB
# define PROPERTYCOLORBLOCK_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYCOLORBLOCK_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYCOLORBLOCK_GLOBAL_H
