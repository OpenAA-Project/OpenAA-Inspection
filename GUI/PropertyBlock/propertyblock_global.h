/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\propertyblock_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYBLOCK_GLOBAL_H
#define PROPERTYBLOCK_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYBLOCK_LIB
# define PROPERTYBLOCK_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYBLOCK_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYBLOCK_GLOBAL_H
