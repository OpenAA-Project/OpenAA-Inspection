/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyNaming\propertynaming_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYNAMING_GLOBAL_H
#define PROPERTYNAMING_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYNAMING_LIB
# define PROPERTYNAMING_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYNAMING_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYNAMING_GLOBAL_H
