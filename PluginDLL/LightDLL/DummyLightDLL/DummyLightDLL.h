/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\LightDLL\DummyLightDLL\DummyLightDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef DUMMYLIGHTDLL_H
#define DUMMYLIGHTDLL_H

#include <QIODevice>


class DummyLightDLL
{
public:
	DummyLightDLL();
	~DummyLightDLL();

	bool	Save(QIODevice &str);
	bool	Load(QIODevice &str);

private:

};

#endif // DUMMYLIGHTDLL_H
