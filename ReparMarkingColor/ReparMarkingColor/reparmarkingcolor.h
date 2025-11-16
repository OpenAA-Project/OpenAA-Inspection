/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ReparMarkingColor\ReparMarkingColor\reparmarkingcolor.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef REPARMARKINGCOLOR_H
#define REPARMARKINGCOLOR_H

#include "reparmarkingcolor_global.h"
#include "colorform.h"
class RepairBase;
#define	DEFFUNCEX		__declspec(dllexport) 

extern	"C"{
//RepairBase		*PClass;
DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
DEFFUNCEX   void	    _cdecl  DLL_FormShow(void);
colorForm *cform;

};

#endif
