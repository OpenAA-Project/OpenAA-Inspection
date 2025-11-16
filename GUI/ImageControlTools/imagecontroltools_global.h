/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImageControlTools\imagecontroltools_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef IMAGECONTROLTOOLS_GLOBAL_H
#define IMAGECONTROLTOOLS_GLOBAL_H

#include <qglobal.h>

#ifdef IMAGECONTROLTOOLS_LIB
# define IMAGECONTROLTOOLS_EXPORT Q_DECL_EXPORT
#else
# define IMAGECONTROLTOOLS_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGECONTROLTOOLS_GLOBAL_H
