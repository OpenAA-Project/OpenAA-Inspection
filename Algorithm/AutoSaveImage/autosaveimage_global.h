/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoSaveImage\autosaveimage_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef AUTOSAVEIMAGE_GLOBAL_H
#define AUTOSAVEIMAGE_GLOBAL_H

#include <qglobal.h>

#ifdef AUTOSAVEIMAGE_LIB
# define AUTOSAVEIMAGE_EXPORT Q_DECL_EXPORT
#else
# define AUTOSAVEIMAGE_EXPORT Q_DECL_IMPORT
#endif

#endif // AUTOSAVEIMAGE_GLOBAL_H
