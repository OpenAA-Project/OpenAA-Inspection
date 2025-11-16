/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonCloseOnly\buttoncloseonly_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONCLOSEONLY_GLOBAL_H
#define BUTTONCLOSEONLY_GLOBAL_H

#include <qglobal.h>

#ifdef BUTTONCLOSEONLY_LIB
# define BUTTONCLOSEONLY_EXPORT Q_DECL_EXPORT
#else
# define BUTTONCLOSEONLY_EXPORT Q_DECL_IMPORT
#endif

#endif // BUTTONCLOSEONLY_GLOBAL_H
