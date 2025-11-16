/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureLineMove\measurelinemove_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef MEASURELINEMOVE_GLOBAL_H
#define MEASURELINEMOVE_GLOBAL_H

#include <qglobal.h>

#ifdef MEASURELINEMOVE_LIB
# define MEASURELINEMOVE_EXPORT Q_DECL_EXPORT
#else
# define MEASURELINEMOVE_EXPORT Q_DECL_IMPORT
#endif

#endif // MEASURELINEMOVE_GLOBAL_H
