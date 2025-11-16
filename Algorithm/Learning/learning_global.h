/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Learning\learning_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef LEARNING_GLOBAL_H
#define LEARNING_GLOBAL_H

#include <qglobal.h>

#ifdef LEARNING_LIB
# define LEARNING_EXPORT Q_DECL_EXPORT
#else
# define LEARNING_EXPORT Q_DECL_IMPORT
#endif

#endif // LEARNING_GLOBAL_H
