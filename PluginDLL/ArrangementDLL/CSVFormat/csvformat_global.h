/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\ArrangementDLL\CSVFormat\csvformat_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CSVFORMAT_GLOBAL_H
#define CSVFORMAT_GLOBAL_H

#include <qglobal.h>

#ifdef CSVFORMAT_LIB
# define CSVFORMAT_EXPORT Q_DECL_EXPORT
#else
# define CSVFORMAT_EXPORT Q_DECL_IMPORT
#endif

#endif // CSVFORMAT_GLOBAL_H
