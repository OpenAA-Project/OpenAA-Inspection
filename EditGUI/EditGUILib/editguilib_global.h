/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUILib\editguilib_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef EDITGUILIB_GLOBAL_H
#define EDITGUILIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EDITGUILIB_LIB
# define EDITGUILIB_EXPORT Q_DECL_EXPORT
#else
# define EDITGUILIB_EXPORT Q_DECL_IMPORT
#endif

#endif // EDITGUILIB_GLOBAL_H
