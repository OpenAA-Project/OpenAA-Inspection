/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Masking\masking_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef MASKING_GLOBAL_H
#define MASKING_GLOBAL_H

#include <qglobal.h>

#ifdef MASKING_LIB
# define MASKING_EXPORT Q_DECL_EXPORT
#else
# define MASKING_EXPORT Q_DECL_IMPORT
#endif

#endif // MASKING_GLOBAL_H
