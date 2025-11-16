/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\LightDLL\DummyLightDLL\DummyLightDLL.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "DummyLightDLL.h"
#include "XLightDLL.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "DummyLightForm.h"

DummyLightDLL::DummyLightDLL()
{
}
DummyLightDLL::~DummyLightDLL()
{
}
bool	DummyLightDLL::Save(QIODevice &str)
{
	return true;
}
bool	DummyLightDLL::Load(QIODevice &str)
{
	return true;
}

//=================================================================================================

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLLightMode;
}


bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="DummyLight";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Light DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2007.9";
	return true;
}

void		*_cdecl	DLL_Initial(void)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	return new DummyLightDLL();
}

bool		_cdecl	DLL_Close(void *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	delete	handle;
	return true;
}

bool		_cdecl	DLL_Load(void *handle ,QIODevice &str)
//	Load light attribution(setting) information of handle
//	This function must load information from stream
//	In this function, light attribution information must be set to a handle
//	if process fails, it returns false
{
	return ((DummyLightDLL *)handle)->Load(str);
}

bool		_cdecl	DLL_Save(void *handle ,QIODevice &str)
//	Save light attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return ((DummyLightDLL *)handle)->Save(str);
}

bool		_cdecl	DLL_ShowSetting(void *handle, QWidget *parent)
//	This function shows dialog to set light(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Lighting pattern(Which light is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false
{
	DummyLightForm	*D=new DummyLightForm(parent);
	D->exec();
	return true;
}

int		_cdecl	DLL_GetLightPatternCount(void *handle)
//	This function must return Pattern-Count on handle
{
	return 1;
}

bool		_cdecl	DLL_LightOn(void *handle)
//	Turn on handle-light
//	This function must return soon
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	return true;
}

bool		_cdecl	DLL_LightOff(void *handle)
//	Turn off handle-light
//	This function must return soon
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	return true;
}

bool		_cdecl	DLL_SetPattern(void *handle ,int PatternNo)
//	This function set Light-pattern
//	This function must return as soon as possible
//	If LightOff was set before this function, Light must be enlightened with this pattern when LightOn function is called
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	return true;
}

bool		_cdecl	DLL_ReqLightError(void *handle ,QStringList &Msg)
//	Request light error from system
//	This function must set error message into Msg when any errors occur
//	this function is called after any functions return false
{
	return true;
}
