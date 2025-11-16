/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinel\SentinelWrite_3\SentinelWrite_3\sentinellib_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SentinelLIB_GLOBAL_H
#define SentinelLIB_GLOBAL_H

#include <qglobal.h>

#ifdef SentinelLIB_LIB
# define SentinelLIB_EXPORT Q_DECL_EXPORT
#else
# define SentinelLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // SentinelLIB_GLOBAL_H
