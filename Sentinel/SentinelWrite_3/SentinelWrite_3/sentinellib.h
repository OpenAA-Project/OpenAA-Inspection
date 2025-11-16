/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinel\SentinelWrite_3\SentinelWrite_3\sentinellib.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SentinelLIB_H
#define SentinelLIB_H

#include "sentinellib_global.h"
#include "hasp_hl.h"

class SentinelLIB_EXPORT Sentinellib
{
public:
    Sentinellib();
    ~Sentinellib();
	int decrypt(hasp_handle_t handle,  char *cday, char *cNumber);
	int SentinelRead(hasp_handle_t handle);
	static int SentinelExecute(char *sday, char *sNumber);
private:
	hasp_handle_t   handle;
	char Sentineldata[256];

};

#endif // SentinelLIB_H
