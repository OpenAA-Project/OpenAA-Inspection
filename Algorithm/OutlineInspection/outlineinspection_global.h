/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\OutlineInspection\outlineinspection_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef OUTLINEINSPECTION_GLOBAL_H
#define OUTLINEINSPECTION_GLOBAL_H

#include <qglobal.h>

#ifdef OUTLINEINSPECTION_LIB
# define OUTLINEINSPECTION_EXPORT Q_DECL_EXPORT
#else
# define OUTLINEINSPECTION_EXPORT Q_DECL_IMPORT
#endif

#endif // OUTLINEINSPECTION_GLOBAL_H
