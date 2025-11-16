/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoMaskingPI\propertyautomaskingpi_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYAUTOMASKINGPI_GLOBAL_H
#define PROPERTYAUTOMASKINGPI_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYAUTOMASKINGPI_LIB
# define PROPERTYAUTOMASKINGPI_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYAUTOMASKINGPI_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYAUTOMASKINGPI_GLOBAL_H
