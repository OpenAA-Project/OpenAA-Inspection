/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Hasplib\Hasplib\hasplib_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef HASPLIB_GLOBAL_H
#define HASPLIB_GLOBAL_H

#include <qglobal.h>

#ifdef HASPLIB_LIB
# define HASPLIB_EXPORT Q_DECL_EXPORT
#else
# define HASPLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // HASPLIB_GLOBAL_H
