/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\SampleDLL\sampledll_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SAMPLEDLL_GLOBAL_H
#define SAMPLEDLL_GLOBAL_H

#include <qglobal.h>

#ifdef SAMPLEDLL_LIB
# define SAMPLEDLL_EXPORT Q_DECL_EXPORT
#else
# define SAMPLEDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // SAMPLEDLL_GLOBAL_H
