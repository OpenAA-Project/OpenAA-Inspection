/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListboxAlgorithm\listboxalgorithm_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LISTBOXALGORITHM_GLOBAL_H
#define LISTBOXALGORITHM_GLOBAL_H

#include <qglobal.h>

#ifdef LISTBOXALGORITHM_LIB
# define LISTBOXALGORITHM_EXPORT Q_DECL_EXPORT
#else
# define LISTBOXALGORITHM_EXPORT Q_DECL_IMPORT
#endif

#endif // LISTBOXALGORITHM_GLOBAL_H
