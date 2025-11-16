/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayGrayLower\displaygraylower_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef DISPLAYGRAYLOWER_GLOBAL_H
#define DISPLAYGRAYLOWER_GLOBAL_H

#include <qglobal.h>

#ifdef DISPLAYGRAYLOWER_LIB
# define DISPLAYGRAYLOWER_EXPORT Q_DECL_EXPORT
#else
# define DISPLAYGRAYLOWER_EXPORT Q_DECL_IMPORT
#endif

#endif // DISPLAYGRAYLOWER_GLOBAL_H
