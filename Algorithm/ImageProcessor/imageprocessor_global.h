/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ImageProcessor\imageprocessor_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef IMAGEPROCESSOR_GLOBAL_H
#define IMAGEPROCESSOR_GLOBAL_H

#include <qglobal.h>

#ifdef IMAGEPROCESSOR_LIB
# define IMAGEPROCESSOR_EXPORT Q_DECL_EXPORT
#else
# define IMAGEPROCESSOR_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGEPROCESSOR_GLOBAL_H
