/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\colorblockinspection_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef COLORBLOCKINSPECTION_GLOBAL_H
#define COLORBLOCKINSPECTION_GLOBAL_H

#include <qglobal.h>

#ifdef COLORBLOCKINSPECTION_LIB
# define COLORBLOCKINSPECTION_EXPORT Q_DECL_EXPORT
#else
# define COLORBLOCKINSPECTION_EXPORT Q_DECL_IMPORT
#endif

#endif // COLORBLOCKINSPECTION_GLOBAL_H
