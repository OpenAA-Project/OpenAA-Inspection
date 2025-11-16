/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDFSFilterDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XDFSFilterDLLH
#define XDFSFilterDLLH

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	FileSaveAttr;
class	XDFSFilterBase;

extern	"C"{

DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for XDFSFilterDLL

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void);
//	return XDFSFilter DLL version

DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);


DEFFUNCEX	const char	*DLL_GetExplain(void);

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
//	return Copyright string

DEFFUNCEX	XDFSFilterBase		*_cdecl	DLL_Initial(const QString &ParamStr);
//	Initialize XDFSFilter DLL. 
//		This function must create and open handle. 
//	return:		XDFSFilter handle(memory block)
//				if proocess fails, return 0

DEFFUNCEX	bool		_cdecl	DLL_Close(XDFSFilterBase *handle);
//	Release handle and close DLL
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Load(XDFSFilterBase *handle ,QIODevice &str);
//	Load XDFSFilter attribution(setting) information of handle
//	This function must load information from stream
//	In this function, XDFSFilter attribution information must be set to a handle
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Save(XDFSFilterBase *handle ,QIODevice &str);
//	Save XDFSFilter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(XDFSFilterBase *handle, QWidget *parent);
//	This function shows dialog to set handle information


DEFFUNCEX	bool		_cdecl	DLL_ExecuteSaveFileInDFS(XDFSFilterBase *handle ,FileSaveAttr *SavedAttr 
														,const QString &Provider ,const QString &LocalPath
														,int &Permit);
//	Permit : -1:Deny  , 0:Strongest , 1,,,Priority decreased


};

#endif
