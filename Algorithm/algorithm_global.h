/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\algorithm_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef ALGORITHM_GLOBAL_H
#define ALGORITHM_GLOBAL_H

#include <qglobal.h>

#ifdef ALGORITHM_LIB
# define ALGORITHM_EXPORT Q_DECL_EXPORT
#else
# define ALGORITHM_EXPORT Q_DECL_IMPORT
#endif

#endif // ALGORITHM_GLOBAL_H
