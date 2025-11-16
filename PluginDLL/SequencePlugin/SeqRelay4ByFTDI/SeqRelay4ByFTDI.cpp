/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\SeqRelay4ByFTDI\SeqRelay4ByFTDI.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QSound>
#include "XSeqDLLGlobal.h"
#include <string.h>
#include "SeqRelay4ByFTDI.h"

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="SeqRelay4ByFTDI";
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


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Sequence Relay4 by FTDI";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"SeqRelay4ByFTDI-1");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
/*
	初期化する必要のあるときに記述する
	Param : Sequence.datに記述したパラメータ文字列
*/
{
	long Ret;

	bool	ok;
	int	DeviceNumber=Param.toInt(&ok);
	if(ok==false)
		DeviceNumber=0;

	Relay4ByFTDI	*H=new Relay4ByFTDI;
	H->OutD=0;

	FT_STATUS ret=FT_Open (DeviceNumber, &H->Handle);
	if(ret!=FT_OK){
		delete	H;
		return NULL;
	}
	ret=FT_SetBitMode(H->Handle, 0xF, 1);
	if(ret!=FT_OK){
		delete	H;
		return NULL;
	}
	ret=FT_SetBaudRate(H->Handle, 9600);
	if(ret!=FT_OK){
		delete	H;
		return NULL;
	}
	return H;
}
bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	if(cmdstr=="ON1"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD |= 0x01;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="ON2"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD |= 0x02;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="ON3"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD |= 0x04;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="ON4"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD |= 0x08;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="OFF1"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD &=~0x01;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="OFF2"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD &=~0x02;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="OFF3"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD &=~0x04;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="OFF4"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD &=~0x08;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	return false;
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
/*
    終了処理
*/
{
	Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
	FT_STATUS ret=FT_Close (PIO->Handle);
}
