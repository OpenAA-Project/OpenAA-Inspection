/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImagePanelTools\imagepaneltools_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef IMAGEPANELTOOLS_GLOBAL_H
#define IMAGEPANELTOOLS_GLOBAL_H

#include <qglobal.h>

#ifdef IMAGEPANELTOOLS_LIB
# define IMAGEPANELTOOLS_EXPORT Q_DECL_EXPORT
#else
# define IMAGEPANELTOOLS_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGEPANELTOOLS_GLOBAL_H
