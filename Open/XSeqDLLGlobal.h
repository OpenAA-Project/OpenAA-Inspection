/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XSeqDLLGlobal.h
** Author : YYYYYYYYYY
****************************************************************************-**/
//---------------------------------------------------------------------------

#ifndef XSeqDLLGlobalH
#define XSeqDLLGlobalH
//---------------------------------------------------------------------------

//#include <QApplication>
#include "XDLLType.h"
#include "XTypeDef.h"
#include <QByteArray>

class   LayersBase;
class	QApplication;
class	GUIDirectMessage;

extern "C"{

#ifdef _MSC_VER

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif



DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for LightDLL

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void);
//	return Light DLL version

DEFFUNCEX	const char	*DLL_GetExplain(void);

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
//	return Copyright string


DEFFUNCEX		void	DLLSeq_GetDLLVersion(char *buff);
/*
    バージョンを返す
    buffは２５６バイト以内
*/

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param);
/*
	初期化する必要のあるときに記述する
	Param : Sequence.datに記述したパラメータ文字列
*/

DEFFUNCEX		bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr);
/*
    命令を送る
    DLLCmd   dllVar,CommandString
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/

DEFFUNCEX		bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr ,const QByteArray &datastr );
/*
    命令を送る
    DLLCmd   dllVar,CommandString,fixedstring
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/

DEFFUNCEX		bool	DLLSeq_CmdStrInt(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,int *data);
/*
    命令を送る
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Wxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/

DEFFUNCEX		bool	DLLSeq_CmdFloat(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,double *data);
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Fxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
DEFFUNCEX		bool	DLLSeq_CmdStrRet(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,QByteArray &Buff);
/*
    命令を送る
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
    datastrにセットする値をBuffに入れておく
*/

DEFFUNCEX		bool	DLLSeq_CmdStrRetInt(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,QByteArray &Buff ,int *data);
/*
    命令を送る
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
    datastrにセットする値をBuffに入れておく
*/


DEFFUNCEX		bool	DLLSeq_CmdInt(void *handle ,QApplication &App ,const QString &cmdstr , int *data);
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Wxx
    でこの関数が呼ばれる
    データを返すとき、*dataに値を格納すれば、「Wxx」に値が入る
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/

DEFFUNCEX		bool	DLLSeq_CmdInt2(void *handle ,QApplication &App ,const QString &cmdstr , int *data1 ,int *data2);
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Wxx,Wxx
    でこの関数が呼ばれる
    データを返すとき、*dataに値を格納すれば、「Wxx」に値が入る
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/

DEFFUNCEX		void DLL_TransmitDirectly(void *handle ,GUIDirectMessage *packet);

DEFFUNCEX		void	DLLSeq_Close(void *handle);
/*
    終了処理
*/

DEFFUNCEX		void	DLLSeq_DebugShow(void *handle ,QApplication &App);

#else
void DLLSeq_GetDLLVersion(char *buff);
bool DLLSeq_CmdStr(char *cmdstr , char *datastr);
bool DLLSeq_CmdStrInt(char *cmdstr , char *datastr ,int *data);
bool DLLSeq_CmdStrRet(char *cmdstr , char *datastr ,char Buff[]);
bool DLLSeq_CmdStrRetInt(char *cmdstr , char *datastr ,char Buff[] ,int *data);
bool DLLSeq_CmdInt(char *cmdstr , int *data);
bool DLLSeq_CmdInt2(char *cmdstr , int *data1 ,int *data2);
void DLLSeq_Close(void);
void DLLSeq_DebugShow(void);
#endif
};



#endif
