/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraGraphinXCM8040\CameraGraphin\cameragraphin_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CAMERAGRAPHIN_GLOBAL_H
#define CAMERAGRAPHIN_GLOBAL_H

#include <qglobal.h>

#ifdef CAMERAGRAPHIN_LIB
# define CAMERAGRAPHIN_EXPORT Q_DECL_EXPORT
#else
# define CAMERAGRAPHIN_EXPORT Q_DECL_IMPORT
#endif

#endif // CAMERAGRAPHIN_GLOBAL_H
