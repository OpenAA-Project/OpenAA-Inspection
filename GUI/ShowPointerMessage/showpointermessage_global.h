/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowPointerMessage\showpointermessage_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWPOINTERMESSAGE_GLOBAL_H
#define SHOWPOINTERMESSAGE_GLOBAL_H

#include <qglobal.h>

#ifdef SHOWPOINTERMESSAGE_LIB
# define SHOWPOINTERMESSAGE_EXPORT Q_DECL_EXPORT
#else
# define SHOWPOINTERMESSAGE_EXPORT Q_DECL_IMPORT
#endif

#endif // SHOWPOINTERMESSAGE_GLOBAL_H
