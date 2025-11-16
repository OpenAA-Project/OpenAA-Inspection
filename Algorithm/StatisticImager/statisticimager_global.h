/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticImager\statisticimager_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef STATISTICIMAGER_GLOBAL_H
#define STATISTICIMAGER_GLOBAL_H

#include <qglobal.h>

#ifdef STATISTICIMAGER_LIB
# define STATISTICIMAGER_EXPORT Q_DECL_EXPORT
#else
# define STATISTICIMAGER_EXPORT Q_DECL_IMPORT
#endif

#endif // STATISTICIMAGER_GLOBAL_H
