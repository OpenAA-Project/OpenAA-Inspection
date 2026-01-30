/*
 * Copyright (C) 2024
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

#ifndef XRWDeviceDLLH
#define XRWDeviceDLLH

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	LayersBase;
class	RWDeviceBaseClass;

extern	"C"{

DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for DeviceDLL

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void);
//	return Device DLL version

DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	void		DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	const char	*DLL_GetExplain(void);

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
//	return Copyright string

DEFFUNCEX	RWDeviceBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &DeviceParamStr);
//	Initialize Device DLL. 
//		This function must create and open handle. 
//	return:		Device handle(memory block)
//				if proocess fails, return 0

DEFFUNCEX	bool		_cdecl	DLL_Close(RWDeviceBaseClass *handle);
//	Release handle and close DLL
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Load(RWDeviceBaseClass *handle ,QIODevice &str);
//	Load Device attribution(setting) information of handle
//	This function must load information from stream
//	In this function, Device attribution information must be set to a handle
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Save(RWDeviceBaseClass *handle ,QIODevice &str);
//	Save Device attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(RWDeviceBaseClass *handle, QWidget *parent);
//	This function shows dialog to set Device(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Deviceing pattern(Which Device is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false

};

#endif