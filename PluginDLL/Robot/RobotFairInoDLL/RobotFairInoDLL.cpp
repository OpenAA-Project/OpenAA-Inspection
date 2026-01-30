/*
 * Copyright (C) 2025
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

#include "RobotFairInoDLL.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XRobotDLL.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>

//=================================================================================================

WORD	DLL_GetDLLType(void)
//	return	DLL type for RobotDLL
{
	return	DLLRobotMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="RobotRairIno";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Robot DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2025.5";
	return true;
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Robot control DLL for FairIno";
}

RobotDLLBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &RobotParamStr)
//	Initialize Robot DLL. 
//		This function must create and open handle. 
//	return:		Robot handle(memory block)
//				if proocess fails, return 0
{
	RobotFairInoDLL	*H=new RobotFairInoDLL(NULL,base);
	if(H->Initial()==false){
		QMessageBox::warning(NULL,"�G���["
							 ,"RairIno robot�ƒʐM�ł��܂���");
		return NULL;
	}
	return H;
}

bool		_cdecl	DLL_Close(RobotDLLBaseClass *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	RobotFairInoDLL	*H=dynamic_cast<RobotFairInoDLL *>(handle);
	if(H!=NULL){
		H->Close();
		delete	H;
	}

	return true;
}

bool		_cdecl	DLL_Load(RobotDLLBaseClass *handle ,QIODevice &str)
//	Load Robot attribution(setting) information of handle
//	This function must load information from stream
//	In this function, Robot attribution information must be set to a handle
//	if process fails, it returns false
{
	RobotFairInoDLL	*p=static_cast<RobotFairInoDLL *>(handle);
	bool	Ret=p->Load(&str);
	return Ret;
}

bool		_cdecl	DLL_Save(RobotDLLBaseClass *handle ,QIODevice &str)
//	Save Robot attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	RobotFairInoDLL	*p=static_cast<RobotFairInoDLL *>(handle);
	return p->Save(&str);
}

bool		_cdecl	DLL_ShowSetting(RobotDLLBaseClass *handle, QWidget *parent)
//	This function shows dialog to set Robot(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Roboting pattern(Which Robot is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false
{
	RobotFairInoDLL	*p=static_cast<RobotFairInoDLL *>(handle);
	bool	Ret=p->ShowSettingDialog();
	return Ret;
}

int		_cdecl	DLL_GetRobotPatternCount(RobotDLLBaseClass *handle)
//	This function must return Pattern-Count on handle
{
	return 1;
}