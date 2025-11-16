/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ModelPageItem\modelpageitem_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef MODELPAGEITEM_GLOBAL_H
#define MODELPAGEITEM_GLOBAL_H

#include <qglobal.h>

#ifdef MODELPAGEITEM_LIB
# define MODELPAGEITEM_EXPORT Q_DECL_EXPORT
#else
# define MODELPAGEITEM_EXPORT Q_DECL_IMPORT
#endif

#endif // MODELPAGEITEM_GLOBAL_H
