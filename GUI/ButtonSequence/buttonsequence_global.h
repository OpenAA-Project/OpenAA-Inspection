/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSequence\buttonsequence_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSEQUENCE_GLOBAL_H
#define BUTTONSEQUENCE_GLOBAL_H

#include <qglobal.h>

#ifdef BUTTONSEQUENCE_LIB
# define BUTTONSEQUENCE_EXPORT Q_DECL_EXPORT
#else
# define BUTTONSEQUENCE_EXPORT Q_DECL_IMPORT
#endif

#endif // BUTTONSEQUENCE_GLOBAL_H
