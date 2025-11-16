/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\blockinspection_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef BLOCKINSPECTION_GLOBAL_H
#define BLOCKINSPECTION_GLOBAL_H

#include <qglobal.h>

#ifdef BLOCKINSPECTION_LIB
# define BLOCKINSPECTION_EXPORT Q_DECL_EXPORT
#else
# define BLOCKINSPECTION_EXPORT Q_DECL_IMPORT
#endif

#endif // BLOCKINSPECTION_GLOBAL_H
