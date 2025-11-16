/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MaskingImagePanel\SelectLibraryInMask\selectlibraryinmask_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTLIBRARYINMASK_GLOBAL_H
#define SELECTLIBRARYINMASK_GLOBAL_H

#include <qglobal.h>

#ifdef SELECTLIBRARYINMASK_LIB
# define SELECTLIBRARYINMASK_EXPORT Q_DECL_EXPORT
#else
# define SELECTLIBRARYINMASK_EXPORT Q_DECL_IMPORT
#endif

#endif // SELECTLIBRARYINMASK_GLOBAL_H
