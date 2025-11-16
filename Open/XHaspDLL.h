/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XHaspDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XHASPDLLH
#define XHASPDLLH

#include <QtGui>
#include "XTypeDef.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	LayersBase;
class	HaspHandleContainer;

extern	"C"{

DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for HaspDLL

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void);
//	return Hasp DLL version

DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);


DEFFUNCEX	const char	*DLL_GetExplain(void);

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
//	return Copyright string

DEFFUNCEX	HaspHandleContainer		*_cdecl	DLL_Initial(LayersBase *base,const QString &HaspParamStr);
//	Initialize Hasp DLL. 
//		This function must create and open handle. 
//	return:		Hasp container handle(memory block)
//				if proocess fails, return 0

DEFFUNCEX	bool		_cdecl	DLL_Close(HaspHandleContainer *handle);
//	Release handle and close DLL
//	if process fails, it returns false

};

#endif
