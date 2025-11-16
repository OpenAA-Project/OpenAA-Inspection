/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveNewMaster\savenewmaster_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SAVENEWMASTER_GLOBAL_H
#define SAVENEWMASTER_GLOBAL_H

#include <qglobal.h>

#ifdef SAVENEWMASTER_LIB
# define SAVENEWMASTER_EXPORT Q_DECL_EXPORT
#else
# define SAVENEWMASTER_EXPORT Q_DECL_IMPORT
#endif

#endif // SAVENEWMASTER_GLOBAL_H
