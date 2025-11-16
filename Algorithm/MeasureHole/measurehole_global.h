/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureHole\measurehole_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef MEASUREHOLE_GLOBAL_H
#define MEASUREHOLE_GLOBAL_H

#include <qglobal.h>

#ifdef MEASUREHOLE_LIB
# define MEASUREHOLE_EXPORT Q_DECL_EXPORT
#else
# define MEASUREHOLE_EXPORT Q_DECL_IMPORT
#endif

#endif // MEASUREHOLE_GLOBAL_H
