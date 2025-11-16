/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Naming\naming_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef NAMING_GLOBAL_H
#define NAMING_GLOBAL_H

#include <qglobal.h>

#ifdef NAMING_LIB
# define NAMING_EXPORT Q_DECL_EXPORT
#else
# define NAMING_EXPORT Q_DECL_IMPORT
#endif

#endif // NAMING_GLOBAL_H
