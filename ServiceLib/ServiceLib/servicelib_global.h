/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\servicelib_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SERVICELIB_GLOBAL_H
#define SERVICELIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SERVICELIB_LIB
# define SERVICELIB_EXPORT Q_DECL_EXPORT
#else
# define SERVICELIB_EXPORT Q_DECL_IMPORT
#endif

#endif // SERVICELIB_GLOBAL_H
