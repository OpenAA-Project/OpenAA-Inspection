/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayMasterImage\displaymasterimage_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef DISPLAYMASTERIMAGE_GLOBAL_H
#define DISPLAYMASTERIMAGE_GLOBAL_H

#include <qglobal.h>

#ifdef DISPLAYMASTERIMAGE_LIB
# define DISPLAYMASTERIMAGE_EXPORT Q_DECL_EXPORT
#else
# define DISPLAYMASTERIMAGE_EXPORT Q_DECL_IMPORT
#endif

#endif // DISPLAYMASTERIMAGE_GLOBAL_H
