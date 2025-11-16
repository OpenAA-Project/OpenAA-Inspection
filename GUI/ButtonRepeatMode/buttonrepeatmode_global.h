/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonRepeatMode\buttonrepeatmode_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONREPEATMODE_GLOBAL_H
#define BUTTONREPEATMODE_GLOBAL_H

#include <qglobal.h>

#ifdef BUTTONREPEATMODE_LIB
# define BUTTONREPEATMODE_EXPORT Q_DECL_EXPORT
#else
# define BUTTONREPEATMODE_EXPORT Q_DECL_IMPORT
#endif

#endif // BUTTONREPEATMODE_GLOBAL_H
