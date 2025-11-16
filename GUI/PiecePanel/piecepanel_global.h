/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PiecePanel\piecepanel_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PIECEPANEL_GLOBAL_H
#define PIECEPANEL_GLOBAL_H

#include <qglobal.h>

#ifdef PIECEPANEL_LIB
# define PIECEPANEL_EXPORT Q_DECL_EXPORT
#else
# define PIECEPANEL_EXPORT Q_DECL_IMPORT
#endif

#endif // PIECEPANEL_GLOBAL_H
