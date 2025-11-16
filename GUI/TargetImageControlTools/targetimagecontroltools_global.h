/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\TargetImageControlTools\targetimagecontroltools_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef TARGETIMAGECONTROLTOOLS_GLOBAL_H
#define TARGETIMAGECONTROLTOOLS_GLOBAL_H

#include <qglobal.h>

#ifdef TARGETIMAGECONTROLTOOLS_LIB
# define TARGETIMAGECONTROLTOOLS_EXPORT Q_DECL_EXPORT
#else
# define TARGETIMAGECONTROLTOOLS_EXPORT Q_DECL_IMPORT
#endif

#endif // TARGETIMAGECONTROLTOOLS_GLOBAL_H
