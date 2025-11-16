/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTunnelCrack\propertytunnelcrack_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYTUNNELCRACK_GLOBAL_H
#define PROPERTYTUNNELCRACK_GLOBAL_H

#include <qglobal.h>

#ifdef PROPERTYTUNNELCRACK_LIB
# define PROPERTYTUNNELCRACK_EXPORT Q_DECL_EXPORT
#else
# define PROPERTYTUNNELCRACK_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTYTUNNELCRACK_GLOBAL_H
