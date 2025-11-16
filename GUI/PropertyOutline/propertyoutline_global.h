/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyOutline\propertyoutline_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYOUTLINE_GLOBAL_H
#define PROPERTYOUTLINE_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYOUTLINE_LIB
# define PROPERTYOUTLINE_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYOUTLINE_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYOUTLINE_GLOBAL_H
