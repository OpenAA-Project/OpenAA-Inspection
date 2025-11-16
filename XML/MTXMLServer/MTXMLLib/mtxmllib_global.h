/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XML\MTXMLServer\MTXMLLib\mtxmllib_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef MTXMLLIB_GLOBAL_H
#define MTXMLLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MTXMLLIB_LIB
# define MTXMLLIB_EXPORT Q_DECL_EXPORT
#else
# define MTXMLLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // MTXMLLIB_GLOBAL_H
