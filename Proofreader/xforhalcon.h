/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Proofreader\xforhalcon.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XFORHALCON_H
#define XFORHALCON_H

#include "XMainSchemeMemory.h"
#include "ExecuteHalcon.h"

class XForHalcon
{
public:
	XForHalcon();
	~XForHalcon();

	void CreateImage(ImageBuffer *Buff[],int LayerNumb);

private:
	ExecuteHalcon ExeHalcon;
};
#endif
