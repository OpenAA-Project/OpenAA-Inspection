/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\propertyalignment_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYALIGNMENT_GLOBAL_H
#define PROPERTYALIGNMENT_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYALIGNMENT_LIB
# define PROPERTYALIGNMENT_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYALIGNMENT_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYALIGNMENT_GLOBAL_H
