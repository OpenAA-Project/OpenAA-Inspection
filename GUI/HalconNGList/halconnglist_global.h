/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\HalconNGList\halconnglist_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef HALCONNGLIST_GLOBAL_H
#define HALCONNGLIST_GLOBAL_H

#include <qglobal.h>

#ifdef HALCONNGLIST_LIB
# define HALCONNGLIST_EXPORT Q_DECL_EXPORT
#else
# define HALCONNGLIST_EXPORT Q_DECL_IMPORT
#endif

#endif // HALCONNGLIST_GLOBAL_H
