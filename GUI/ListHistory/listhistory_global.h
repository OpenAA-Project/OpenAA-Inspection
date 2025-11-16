/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListHistory\listhistory_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LISTHISTORY_GLOBAL_H
#define LISTHISTORY_GLOBAL_H

#include <qglobal.h>

#ifdef LISTHISTORY_LIB
# define LISTHISTORY_EXPORT Q_DECL_EXPORT
#else
# define LISTHISTORY_EXPORT Q_DECL_IMPORT
#endif

#endif // LISTHISTORY_GLOBAL_H
