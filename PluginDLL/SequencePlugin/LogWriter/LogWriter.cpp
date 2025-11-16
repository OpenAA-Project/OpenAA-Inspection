/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\LogWriter\LogWriter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "LogWriter.h"
#include "XSeqDLLGlobal.h"
#include <string.h>
#include "ThreadLogWriter.h"
#include "XGeneralFunc.h"


//ThreadLogWriter	*ThreadLog=NULL;

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="LogWriter";
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
	return "Log writer";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"Log writer");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	ThreadLogWriter	*ThreadLog=new ThreadLogWriter();
	ThreadLog->start();
	return ThreadLog;
}

bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	if(cmdstr=="LogOutFileName"){
		ThreadLogWriter	*ThreadLog=(ThreadLogWriter	*)handle;
		if(ThreadLog!=NULL){
			QString	A=datastr;
			::QString2Char(A,ThreadLog->FileName,sizeof(ThreadLog->FileName));
			return true;
		}
	}
	return false;
}


bool	DLLSeq_CmdInt(void *handle ,QApplication &App ,const QString &cmdstr , int *data)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Wxx
    でこの関数が呼ばれる
    データを返すとき、*dataに値を格納すれば、「Wxx」に値が入る
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	if(cmdstr=="LogOutOn"){
		ThreadLogWriter	*ThreadLog=(ThreadLogWriter	*)handle;
		if(ThreadLog!=NULL){
			ThreadLog->OnWrittenTime	=XDateTime::currentDateTime ();
			ThreadLog->OnInspectionID	=*data;
			ThreadLog->OnSignalOn		=true;
			ThreadLog->OnWriteMode=true;
			return true;
		}
	}
	else if(cmdstr=="LogOutOff"){
		ThreadLogWriter	*ThreadLog=(ThreadLogWriter	*)handle;
		if(ThreadLog!=NULL){
			ThreadLog->OffWrittenTime	=XDateTime::currentDateTime ();
			ThreadLog->OffInspectionID	=*data;
			ThreadLog->OffSignalOn		=false;
			ThreadLog->OffWriteMode=true;
			return true;
		}
	}
	return false;
}

bool	DLLSeq_CmdStrInt(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,int *data)
/*
    命令を送る
    データなしの記述のときもこの関数がコールされる
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	if(cmdstr=="Print"){
		ThreadLogWriter	*ThreadLog=(ThreadLogWriter	*)handle;
		if(ThreadLog!=NULL){
			ThreadLog->PrintWrittenTime	=XDateTime::currentDateTime ();
			ThreadLog->PrintString		=datastr;
			ThreadLog->PrintNumber		=*data;
			ThreadLog->PrintWriteMode	=true;
			return true;
		}
	}
	return false;
}

void	DLLSeq_Close(void *handle)
/*
    終了処理
*/
{
	ThreadLogWriter	*ThreadLog=(ThreadLogWriter	*)handle;
	if(ThreadLog!=NULL){
		if(ThreadLog->isRunning()==true){
			ThreadLog->terminate();
			ThreadLog->wait(1000);
		}
		ThreadLog->deleteLater();
		ThreadLog=NULL;
	}
}

void	DLLSeq_DebugShow(void *handle ,QApplication &App)
{}

