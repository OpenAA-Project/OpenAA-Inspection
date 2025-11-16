/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayNGList\displaynglist_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef DISPLAYNGLIST_GLOBAL_H
#define DISPLAYNGLIST_GLOBAL_H

#include <qglobal.h>

#ifdef DISPLAYNGLIST_LIB
# define DISPLAYNGLIST_EXPORT Q_DECL_EXPORT
#else
# define DISPLAYNGLIST_EXPORT Q_DECL_IMPORT
#endif

#endif // DISPLAYNGLIST_GLOBAL_H
