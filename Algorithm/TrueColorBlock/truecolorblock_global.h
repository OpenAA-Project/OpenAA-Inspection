/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\truecolorblock_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef TRUECOLORBLOCK_GLOBAL_H
#define TRUECOLORBLOCK_GLOBAL_H

#include <qglobal.h>

#ifdef TRUECOLORBLOCK_LIB
# define TRUECOLORBLOCK_EXPORT Q_DECL_EXPORT
#else
# define TRUECOLORBLOCK_EXPORT Q_DECL_IMPORT
#endif

#endif // TRUECOLORBLOCK_GLOBAL_H
