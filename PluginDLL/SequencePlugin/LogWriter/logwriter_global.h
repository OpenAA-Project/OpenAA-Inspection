/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\LogWriter\logwriter_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef LOGWRITER_GLOBAL_H
#define LOGWRITER_GLOBAL_H

#include <qglobal.h>

#ifdef LOGWRITER_LIB
# define LOGWRITER_EXPORT Q_DECL_EXPORT
#else
# define LOGWRITER_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGWRITER_GLOBAL_H
