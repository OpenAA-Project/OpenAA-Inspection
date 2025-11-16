/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\SingleExecute.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SINGLEEXECUTE_H
#define SINGLEEXECUTE_H

#include <QString>


bool SingleExecute(const QString &exeName);
bool KillDupProcess(const QString &exeName);

#endif
