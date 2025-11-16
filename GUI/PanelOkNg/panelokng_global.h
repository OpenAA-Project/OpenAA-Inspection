/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelOkNg\panelokng_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PANELOKNG_GLOBAL_H
#define PANELOKNG_GLOBAL_H

#include <qglobal.h>

#ifdef PANELOKNG_LIB
# define PANELOKNG_EXPORT Q_DECL_EXPORT
#else
# define PANELOKNG_EXPORT Q_DECL_IMPORT
#endif

#endif // PANELOKNG_GLOBAL_H
