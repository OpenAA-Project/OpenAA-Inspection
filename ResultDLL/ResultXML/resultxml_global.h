/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ResultDLL\ResultXML\resultxml_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef RESULTXML_GLOBAL_H
#define RESULTXML_GLOBAL_H

#include <qglobal.h>

#ifdef RESULTXML_LIB
# define RESULTXML_EXPORT Q_DECL_EXPORT
#else
# define RESULTXML_EXPORT Q_DECL_IMPORT
#endif

#endif // RESULTXML_GLOBAL_H
