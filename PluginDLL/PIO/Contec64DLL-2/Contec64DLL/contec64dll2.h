/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\Contec64DLL\Contec64DLL\contec64dll.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CONTEC64DLL2_H
#define CONTEC64DLL2_H

#include "contec64dll2_global.h"
#include <QString>

class	Contec2boards
{
public:
	short	Id;
	QString	DeviceName;
	QString	Device;
	//int		BitCountIN;
	//int		BitCountOut;
};


#endif // CONTEC64DLL_H
