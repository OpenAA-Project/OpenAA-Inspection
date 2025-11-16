/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImageProcessorPanel\imageprocessorpanel_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef IMAGEPROCESSORPANEL_GLOBAL_H
#define IMAGEPROCESSORPANEL_GLOBAL_H

#include <qglobal.h>

#ifdef IMAGEPROCESSORPANEL_LIB
# define IMAGEPROCESSORPANEL_EXPORT Q_DECL_EXPORT
#else
# define IMAGEPROCESSORPANEL_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGEPROCESSORPANEL_GLOBAL_H
