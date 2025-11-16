/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralLabel\generallabel_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GENERALLABEL_GLOBAL_H
#define GENERALLABEL_GLOBAL_H

#include <qglobal.h>

#ifdef GENERALLABEL_LIB
# define GENERALLABEL_EXPORT Q_DECL_EXPORT
#else
# define GENERALLABEL_EXPORT Q_DECL_IMPORT
#endif

#endif // GENERALLABEL_GLOBAL_H
