/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DynamicMaskingPI\dynamicmaskingpi_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef DYNAMICMASKINGPI_GLOBAL_H
#define DYNAMICMASKINGPI_GLOBAL_H

#include <qglobal.h>

#ifdef DYNAMICMASKINGPI_LIB
# define DYNAMICMASKINGPI_EXPORT Q_DECL_EXPORT
#else
# define DYNAMICMASKINGPI_EXPORT Q_DECL_IMPORT
#endif

#endif // DYNAMICMASKINGPI_GLOBAL_H
