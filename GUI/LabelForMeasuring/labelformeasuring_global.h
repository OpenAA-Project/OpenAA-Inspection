/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LabelForMeasuring\labelformeasuring_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LABELFORMEASURING_GLOBAL_H
#define LABELFORMEASURING_GLOBAL_H

#include <qglobal.h>

#ifdef LABELFORMEASURING_LIB
# define LABELFORMEASURING_EXPORT Q_DECL_EXPORT
#else
# define LABELFORMEASURING_EXPORT Q_DECL_IMPORT
#endif

#endif // LABELFORMEASURING_GLOBAL_H
