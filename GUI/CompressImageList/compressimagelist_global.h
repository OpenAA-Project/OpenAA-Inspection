/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CompressImageList\compressimagelist_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef COMPRESSIMAGELIST_GLOBAL_H
#define COMPRESSIMAGELIST_GLOBAL_H

#include <qglobal.h>

#ifdef COMPRESSIMAGELIST_LIB
# define COMPRESSIMAGELIST_EXPORT Q_DECL_EXPORT
#else
# define COMPRESSIMAGELIST_EXPORT Q_DECL_IMPORT
#endif

#endif // COMPRESSIMAGELIST_GLOBAL_H
