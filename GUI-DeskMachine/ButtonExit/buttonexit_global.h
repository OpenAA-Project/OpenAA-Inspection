/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExit\buttonexit_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONEXIT_GLOBAL_H
#define BUTTONEXIT_GLOBAL_H

#include <qglobal.h>

#ifdef BUTTONEXIT_LIB
# define BUTTONEXIT_EXPORT Q_DECL_EXPORT
#else
# define BUTTONEXIT_EXPORT Q_DECL_IMPORT
#endif

#endif // BUTTONEXIT_GLOBAL_H
