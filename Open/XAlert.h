/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XAlert.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XALERT_H)
#define	XALERT_H

#include <QMessageBox>

#define	Alert(str)	QMessageBox::critical (NULL, "Alert", str) 

#endif