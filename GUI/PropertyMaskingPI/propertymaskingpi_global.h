/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMaskingPI\propertymaskingpi_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYMASKINGPI_GLOBAL_H
#define PROPERTYMASKINGPI_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYMASKINGPI_LIB
# define PROPERTYMASKINGPI_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYMASKINGPI_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYMASKINGPI_GLOBAL_H
