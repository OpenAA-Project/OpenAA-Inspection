/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraMightex\CameraMightex\dummycamera_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CAMERAXTIUM_GLOBAL_H
#define CAMERAXTIUM_GLOBAL_H

#include <qglobal.h>

#ifdef CAMERAXTIUMLIB
# define CAMERAXTIUM_EXPORT Q_DECL_EXPORT
#else
# define CAMERAXTIUM_EXPORT Q_DECL_IMPORT
#endif

#endif // CAMERAMIGHTEX_GLOBAL_H
