/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\Contec64DLL\Contec64DLL\contec64dll_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CONTEC64DLL_GLOBAL_H
#define CONTEC64DLL_GLOBAL_H

#include <qglobal.h>

#ifdef CONTEC64DLL_LIB
# define CONTEC64DLL_EXPORT Q_DECL_EXPORT
#else
# define CONTEC64DLL_EXPORT Q_DECL_IMPORT
#endif

#endif // CONTEC64DLL_GLOBAL_H
