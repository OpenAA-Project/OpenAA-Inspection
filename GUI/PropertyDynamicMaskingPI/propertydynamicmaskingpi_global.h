/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicMaskingPI\propertydynamicmaskingpi_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYDYNAMICMASKINGPI_GLOBAL_H
#define PROPERTYDYNAMICMASKINGPI_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYDYNAMICMASKINGPI_LIB
# define PROPERTYDYNAMICMASKINGPI_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYDYNAMICMASKINGPI_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYDYNAMICMASKINGPI_GLOBAL_H
