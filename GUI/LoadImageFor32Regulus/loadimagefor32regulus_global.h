/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadImageFor32Regulus\loadimagefor32regulus_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LOADIMAGEFOR32REGULUS_GLOBAL_H
#define LOADIMAGEFOR32REGULUS_GLOBAL_H

#include <qglobal.h>

#ifdef LOADIMAGEFOR32REGULUS_LIB
# define LOADIMAGEFOR32REGULUS_EXPORT Q_DECL_EXPORT
#else
# define LOADIMAGEFOR32REGULUS_EXPORT Q_DECL_IMPORT
#endif

#endif // LOADIMAGEFOR32REGULUS_GLOBAL_H
