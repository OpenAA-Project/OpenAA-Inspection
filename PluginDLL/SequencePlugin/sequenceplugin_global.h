/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\sequenceplugin_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SEQUENCEPLUGIN_GLOBAL_H
#define SEQUENCEPLUGIN_GLOBAL_H

#include <qglobal.h>

#ifdef SEQUENCEPLUGIN_LIB
# define SEQUENCEPLUGIN_EXPORT Q_DECL_EXPORT
#else
# define SEQUENCEPLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // SEQUENCEPLUGIN_GLOBAL_H
