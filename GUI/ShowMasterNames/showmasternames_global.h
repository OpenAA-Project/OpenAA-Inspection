/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowMasterNames\showmasternames_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWMASTERNAMES_GLOBAL_H
#define SHOWMASTERNAMES_GLOBAL_H

#include <qglobal.h>

#ifdef SHOWMASTERNAMES_LIB
# define SHOWMASTERNAMES_EXPORT Q_DECL_EXPORT
#else
# define SHOWMASTERNAMES_EXPORT Q_DECL_IMPORT
#endif

#endif // SHOWMASTERNAMES_GLOBAL_H
