/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\SampleDLL\SampleDLL.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XSeqDLLGlobal.h"
#include <string.h>
#include <QString>

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="SampleDLL";
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
	return "Sample DLL for Sequence";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"Sample DLL for Sequence");
}

bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	if(cmdstr=="DLLSeq_Cmd"){
		return true;
	}
	return false;
}

bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	if(cmdstr=="DLLSeq_CmdStr"){
		if(datastr=="123"){
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
	if(cmdstr=="DLLSeq_CmdStrInt"){
		if(datastr=="123"){
			*data=345;
			return true;
		}
		else{
			*data=567;
			return false;
		}
	}
	return false;
}

bool	DLLSeq_CmdStrRet(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,QByteArray &Buff)
/*
    命令を送る
    データなしの記述のときもこの関数がコールされる
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
    datastrにセットする値をBuffに入れておく
*/
{
	if(cmdstr=="DLLSeq_CmdStrRet"){
		if(datastr=="ABC"){
			Buff="abcde";
		}
	}
	return true;
}

bool	DLLSeq_CmdStrRetInt(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,QByteArray &Buff ,int *data)
/*
    命令を送る
    データなしの記述のときもこの関数がコールされる
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
    datastrにセットする値をBuffに入れておく
*/
{
	if(cmdstr=="DLLSeq_CmdStrRetInt"){
		if(datastr=="CDE"){
			Buff="cd";
			*data=100;
		}
	}
	return true;
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
	if(cmdstr=="DLLSeq_CmdInt"){
		if(*data==10){
			*data=100;
			return true;
		}
	}
	return false;
}

bool	DLLSeq_CmdInt2(void *handle ,QApplication &App ,const QString &cmdstr , int *data1 ,int *data2)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Wxx,Wxx
    でこの関数が呼ばれる
    データを返すとき、*dataに値を格納すれば、「Wxx」に値が入る
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	if(cmdstr=="DLLSeq_CmdInt2"){
		if(*data1==1 && *data2==2){
			*data1=200;
			*data2=300;
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
}

void	DLLSeq_DebugShow(void *handle ,QApplication &App)
{}

