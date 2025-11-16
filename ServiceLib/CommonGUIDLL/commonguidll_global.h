/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\CommonGUIDLL\commonguidll_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef COMMONGUIDLL_GLOBAL_H
#define COMMONGUIDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef COMMONGUIDLL_LIB
# define COMMONGUIDLL_EXPORT Q_DECL_EXPORT
#else
# define COMMONGUIDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // COMMONGUIDLL_GLOBAL_H
