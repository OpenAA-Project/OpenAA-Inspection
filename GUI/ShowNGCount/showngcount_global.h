/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowNGCount\showngcount_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWNGCOUNT_GLOBAL_H
#define SHOWNGCOUNT_GLOBAL_H

#include <qglobal.h>

#ifdef SHOWNGCOUNT_LIB
# define SHOWNGCOUNT_EXPORT Q_DECL_EXPORT
#else
# define SHOWNGCOUNT_EXPORT Q_DECL_IMPORT
#endif

#endif // SHOWNGCOUNT_GLOBAL_H
