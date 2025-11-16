/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Alignment\alignment_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef ALIGNMENT_GLOBAL_H
#define ALIGNMENT_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef ALIGNMENT_LIB
# define ALIGNMENT_EXPORT Q_DECL_EXPORT
#else
# define ALIGNMENT_EXPORT Q_DECL_IMPORT
#endif

#endif // ALIGNMENT_GLOBAL_H
