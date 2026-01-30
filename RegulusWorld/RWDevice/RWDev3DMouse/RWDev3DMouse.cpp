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

#include "RWDev3DMouse.h"
#include "XRWDeviceDLL.h"
#include "XDLLType.h"

DEFFUNCEX	WORD	DLL_GetDLLType(void)
//	return	DLL type for DeviceDLL
{
	return DLLRWDeviceMode;
}

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str=/**/"3D Mouse for robot(6 axis)";
	return true;
}

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void)
//	return Device DLL version
{
	return 1;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return /**/"3D mouse by 3DConnexion";
}

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString=/**/"MEGATRADE 2021.8";
	return true;
}

DEFFUNCEX	RWDeviceBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &DeviceParamStr)
//	Initialize Device DLL. 
//		This function must create and open handle. 
//	return:		Device handle(memory block)
//				if proocess fails, return 0
{
	RWDev3DMouse	*inst=new RWDev3DMouse(base,DeviceParamStr,NULL);
	return inst;
}

DEFFUNCEX	bool		_cdecl	DLL_Close(RWDeviceBaseClass *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	RWDev3DMouse	*d=dynamic_cast<RWDev3DMouse *>(handle);
	if(d!=NULL){
		delete	d;
	}
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_Load(RWDeviceBaseClass *handle ,QIODevice &str)
//	Load Device attribution(setting) information of handle
//	This function must load information from stream
//	In this function, Device attribution information must be set to a handle
//	if process fails, it returns false
{
	RWDev3DMouse	*d=dynamic_cast<RWDev3DMouse *>(handle);
	if(d!=NULL){
		return d->Load(&str);
	}
	return false;
}

DEFFUNCEX	bool		_cdecl	DLL_Save(RWDeviceBaseClass *handle ,QIODevice &str)
//	Save Device attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	RWDev3DMouse	*d=dynamic_cast<RWDev3DMouse *>(handle);
	if(d!=NULL){
		return d->Save(&str);
	}
	return false;
}

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(RWDeviceBaseClass *handle, QWidget *parent)
//	This function shows dialog to set Device(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Deviceing pattern(Which Device is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false
{
	RWDev3DMouse	*d=dynamic_cast<RWDev3DMouse *>(handle);
	if(d!=NULL){
		return d->ShowSettingDialog(parent);
	}
	return false;
}