/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticBlock\statisticblock_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef STATISTICBLOCK_GLOBAL_H
#define STATISTICBLOCK_GLOBAL_H

#include <qglobal.h>

#ifdef STATISTICBLOCK_LIB
# define STATISTICBLOCK_EXPORT Q_DECL_EXPORT
#else
# define STATISTICBLOCK_EXPORT Q_DECL_IMPORT
#endif

#endif // STATISTICBLOCK_GLOBAL_H
