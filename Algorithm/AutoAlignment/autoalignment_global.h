/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoAlignment\autoalignment_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef AUTOALIGNMENT_GLOBAL_H
#define AUTOALIGNMENT_GLOBAL_H

#include <qglobal.h>

#ifdef AUTOALIGNMENT_LIB
# define AUTOALIGNMENT_EXPORT Q_DECL_EXPORT
#else
# define AUTOALIGNMENT_EXPORT Q_DECL_IMPORT
#endif

#endif // AUTOALIGNMENT_GLOBAL_H
