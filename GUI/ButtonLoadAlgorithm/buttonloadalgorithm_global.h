/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadAlgorithm\buttonloadalgorithm_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONLOADALGORITHM_GLOBAL_H
#define BUTTONLOADALGORITHM_GLOBAL_H

#include <qglobal.h>

#ifdef BUTTONLOADALGORITHM_LIB
# define BUTTONLOADALGORITHM_EXPORT Q_DECL_EXPORT
#else
# define BUTTONLOADALGORITHM_EXPORT Q_DECL_IMPORT
#endif

#endif // BUTTONLOADALGORITHM_GLOBAL_H
