/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\SeqFor64Connector\seqfor64connector_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SEQFOR64CONNECTOR_GLOBAL_H
#define SEQFOR64CONNECTOR_GLOBAL_H

#include <qglobal.h>

#ifdef SEQFOR64CONNECTOR_LIB
# define SEQFOR64CONNECTOR_EXPORT Q_DECL_EXPORT
#else
# define SEQFOR64CONNECTOR_EXPORT Q_DECL_IMPORT
#endif

#endif // SEQFOR64CONNECTOR_GLOBAL_H
