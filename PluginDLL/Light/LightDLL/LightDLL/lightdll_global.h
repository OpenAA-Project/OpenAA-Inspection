/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Light\LightDLL\LightDLL\lightdll_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef LIGHTDLL_GLOBAL_H
#define LIGHTDLL_GLOBAL_H

#include <qglobal.h>

#ifdef LIGHTDLL_LIB
# define LIGHTDLL_EXPORT Q_DECL_EXPORT
#else
# define LIGHTDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // LIGHTDLL_GLOBAL_H
