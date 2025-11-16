/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GraphicPanel\graphicpanel_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GRAPHICPANEL_GLOBAL_H
#define GRAPHICPANEL_GLOBAL_H

#include <qglobal.h>

#ifdef GRAPHICPANEL_LIB
# define GRAPHICPANEL_EXPORT Q_DECL_EXPORT
#else
# define GRAPHICPANEL_EXPORT Q_DECL_IMPORT
#endif

#endif // GRAPHICPANEL_GLOBAL_H
