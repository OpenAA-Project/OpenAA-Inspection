/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\HASP\HaspWrite_3\HaspWrite_3\hasplib.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef HASPLIB_H
#define HASPLIB_H

#include "hasplib_global.h"
//#include "hasp_hl.h"
#include "hasp_api.h"

class HASPLIB_EXPORT Hasplib
{
public:
    Hasplib();
    ~Hasplib();
	int decrypt(hasp_handle_t handle,  char *cday, char *cNumber);
	int haspRead(hasp_handle_t handle);
	static int HaspExecute(char *sday, char *sNumber);
private:
	hasp_handle_t   handle;
	char haspdata[256];

};

#endif // HASPLIB_H
