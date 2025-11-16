/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralTabSheet\generaltabsheet_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GENERALTABSHEET_GLOBAL_H
#define GENERALTABSHEET_GLOBAL_H

#include <qglobal.h>

#ifdef GENERALTABSHEET_LIB
# define GENERALTABSHEET_EXPORT Q_DECL_EXPORT
#else
# define GENERALTABSHEET_EXPORT Q_DECL_IMPORT
#endif

#endif // GENERALTABSHEET_GLOBAL_H
