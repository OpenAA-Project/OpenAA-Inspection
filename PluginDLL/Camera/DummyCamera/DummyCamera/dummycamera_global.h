/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\DummyCamera\DummyCamera\dummycamera_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef DUMMYCAMERA_GLOBAL_H
#define DUMMYCAMERA_GLOBAL_H

#include <qglobal.h>

#ifdef DUMMYCAMERA_LIB
# define DUMMYCAMERA_EXPORT Q_DECL_EXPORT
#else
# define DUMMYCAMERA_EXPORT Q_DECL_IMPORT
#endif

#endif // DUMMYCAMERA_GLOBAL_H
