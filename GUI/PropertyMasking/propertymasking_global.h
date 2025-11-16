/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMasking\propertymasking_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYMASKING_GLOBAL_H
#define PROPERTYMASKING_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYMASKING_LIB
# define PROPERTYMASKING_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYMASKING_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYMASKING_GLOBAL_H
