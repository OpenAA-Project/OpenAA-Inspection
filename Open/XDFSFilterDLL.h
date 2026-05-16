/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef XDFSFilterDLLH
#define XDFSFilterDLLH

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#define _cdecl
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