/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralHairLine\generalhairline_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GENERALHAIRLINE_GLOBAL_H
#define GENERALHAIRLINE_GLOBAL_H

#include <qglobal.h>

#ifdef GENERALHAIRLINE_LIB
# define GENERALHAIRLINE_EXPORT Q_DECL_EXPORT
#else
# define GENERALHAIRLINE_EXPORT Q_DECL_IMPORT
#endif

#endif // GENERALHAIRLINE_GLOBAL_H
