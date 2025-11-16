/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelSaveImage\panelsaveimage_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PANELSAVEIMAGE_GLOBAL_H
#define PANELSAVEIMAGE_GLOBAL_H

#include <qglobal.h>

#ifdef PANELSAVEIMAGE_LIB
# define PANELSAVEIMAGE_EXPORT Q_DECL_EXPORT
#else
# define PANELSAVEIMAGE_EXPORT Q_DECL_IMPORT
#endif

#endif // PANELSAVEIMAGE_GLOBAL_H
