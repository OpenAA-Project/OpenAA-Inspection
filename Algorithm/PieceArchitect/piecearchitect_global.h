/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\PieceArchitect\piecearchitect_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef PIECEARCHITECT_GLOBAL_H
#define PIECEARCHITECT_GLOBAL_H

#include <qglobal.h>

#ifdef PIECEARCHITECT_LIB
# define PIECEARCHITECT_EXPORT Q_DECL_EXPORT
#else
# define PIECEARCHITECT_EXPORT Q_DECL_IMPORT
#endif

#endif // PIECEARCHITECT_GLOBAL_H
