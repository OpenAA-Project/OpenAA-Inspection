/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonAutoMode\buttonautomode_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONAUTOMODE_GLOBAL_H
#define BUTTONAUTOMODE_GLOBAL_H

#include <qglobal.h>

#ifdef BUTTONAUTOMODE_LIB
# define BUTTONAUTOMODE_EXPORT Q_DECL_EXPORT
#else
# define BUTTONAUTOMODE_EXPORT Q_DECL_IMPORT
#endif

#endif // BUTTONAUTOMODE_GLOBAL_H
