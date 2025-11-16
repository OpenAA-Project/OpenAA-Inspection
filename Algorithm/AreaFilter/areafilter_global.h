/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\areafilter_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef AREAFILTER_GLOBAL_H
#define AREAFILTER_GLOBAL_H

#include <qglobal.h>

#ifdef AREAFILTER_LIB
# define AREAFILTER_EXPORT Q_DECL_EXPORT
#else
# define AREAFILTER_EXPORT Q_DECL_IMPORT
#endif

#endif // AREAFILTER_GLOBAL_H
