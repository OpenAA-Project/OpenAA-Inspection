/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinellib\Sentinellib\Sentinellib_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SENTINELLIB_GLOBAL_H
#define SENTINELLIB_GLOBAL_H

#include <qglobal.h>

#ifdef SENTINELLIB_LIB
#define SENTINELLIB_EXPORT Q_DECL_EXPORT
#else
#define SENTINELLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // SENTINELLIB_GLOBAL_H
