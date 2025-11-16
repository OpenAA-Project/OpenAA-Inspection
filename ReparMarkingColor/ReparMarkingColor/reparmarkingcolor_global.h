/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ReparMarkingColor\ReparMarkingColor\reparmarkingcolor_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef REPARMARKINGCOLOR_GLOBAL_H
#define REPARMARKINGCOLOR_GLOBAL_H

#include <qglobal.h>

#ifdef REPARMARKINGCOLOR_LIB
# define REPARMARKINGCOLOR_EXPORT Q_DECL_EXPORT
#else
# define REPARMARKINGCOLOR_EXPORT Q_DECL_IMPORT
#endif

#endif // REPARMARKINGCOLOR_GLOBAL_H
