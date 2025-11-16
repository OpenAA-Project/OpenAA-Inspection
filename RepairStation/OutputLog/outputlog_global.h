/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\OutputLog\outputlog_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef OUTPUTLOG_GLOBAL_H
#define OUTPUTLOG_GLOBAL_H

#include <qglobal.h>

#ifdef OUTPUTLOG_LIB
# define OUTPUTLOG_EXPORT Q_DECL_EXPORT
#else
# define OUTPUTLOG_EXPORT Q_DECL_IMPORT
#endif

#endif // OUTPUTLOG_GLOBAL_H
