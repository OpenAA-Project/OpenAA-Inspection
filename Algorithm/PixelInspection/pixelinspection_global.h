/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\PixelInspection\pixelinspection_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef PIXELINSPECTION_GLOBAL_H
#define PIXELINSPECTION_GLOBAL_H

#include <qglobal.h>

#ifdef PIXELINSPECTION_LIB
# define PIXELINSPECTION_EXPORT Q_DECL_EXPORT
#else
# define PIXELINSPECTION_EXPORT Q_DECL_IMPORT
#endif

#endif // PIXELINSPECTION_GLOBAL_H
