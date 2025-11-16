/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyHalcon\propertyhalcon_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYHALCON_GLOBAL_H
#define PROPERTYHALCON_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYHALCON_LIB
# define PROPERTYHALCON_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYHALCON_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYHALCON_GLOBAL_H
