/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadAlgorithmWithMachine\loadalgorithmwithmachine_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef LOADALGORITHMWITHMACHINE_GLOBAL_H
#define LOADALGORITHMWITHMACHINE_GLOBAL_H

#include <qglobal.h>

#ifdef LOADALGORITHMWITHMACHINE_LIB
# define LOADALGORITHMWITHMACHINE_EXPORT Q_DECL_EXPORT
#else
# define LOADALGORITHMWITHMACHINE_EXPORT Q_DECL_IMPORT
#endif

#endif // LOADALGORITHMWITHMACHINE_GLOBAL_H
