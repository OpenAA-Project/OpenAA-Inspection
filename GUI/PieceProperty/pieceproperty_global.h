/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PieceProperty\pieceproperty_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PIECEPROPERTY_GLOBAL_H
#define PIECEPROPERTY_GLOBAL_H

#include <qglobal.h>

#ifdef PIECEPROPERTY_LIB
# define PIECEPROPERTY_EXPORT Q_DECL_EXPORT
#else
# define PIECEPROPERTY_EXPORT Q_DECL_IMPORT
#endif

#endif // PIECEPROPERTY_GLOBAL_H
