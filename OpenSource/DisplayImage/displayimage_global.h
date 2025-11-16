/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\displayimage_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef DISPLAYIMAGE_GLOBAL_H
#define DISPLAYIMAGE_GLOBAL_H

#include <qglobal.h>

#ifdef DISPLAYIMAGE_LIB
# define DISPLAYIMAGE_EXPORT Q_DECL_EXPORT
#else
# define DISPLAYIMAGE_EXPORT Q_DECL_IMPORT
#endif

#endif // DISPLAYIMAGE_GLOBAL_H
