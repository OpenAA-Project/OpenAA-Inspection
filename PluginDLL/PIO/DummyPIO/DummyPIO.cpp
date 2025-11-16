/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\Contec64DLL\Contec64DLL\contec64dll.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "windows.h"
#include "AIP_IO.h"
#include "math.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "ShowIOForm.h"

//ShowIOForm	*Panel=NULL;

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="Dummy PIO";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "16Bit dummy PIO";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2012";
	return true;
}



IO_DLLFUNC int _cdecl  AIP_IO_GetIOBoardNumb(void)
    /*
        動作    ＰＩＯボードの枚数を返す
        入力    なし
        出力    ＰＩＯボード枚数を返す
        条件    AIP_IO_Initial()をコールされた後でこの関数がコールされる
                オープンされていない状態でコールされる
    */
{
	return 1;
}

int IO_DLLFUNC _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
    /*
        動作    各ＰＩＯボードの入力ビット数を返す
        入力    ＰＩＯボード番号（０から始まる数値）
        出力    各ＰＩＯボードの入力ビット数を返す
        条件    オープンされていない状態でコールされる
    */
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	return 16;
}
int IO_DLLFUNC _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
    /*
        動作    各ＰＩＯボードの出力ビット数を返す
        入力    ＰＩＯボード番号（０から始まる数値）
        出力    各ＰＩＯボードの出力ビット数を返す
        条件    オープンされていない状態でコールされる
    */
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	return 16;
}
bool  IO_DLLFUNC _cdecl AIP_IO_Initial(const QStringList &NameList)
    /*
        動作    全体のＰＩＯに対して初期化動作を行う
        入力    なし
        出力    成功したときTRUE、何らかの問題が生じたときfalse
        条件    オープンされていない状態でコールされる
        備考    ボード種類によっては、何もせずにTRUEだけを返すことができる
    */
{
	return true;
}
void  IO_DLLFUNC _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
    /*
        動作    各ＰＩＯボードに対してオープン動作を行う
        入力    mainW		呼び出した側のメインウインドウ
				boardNumber ＰＩＯボード番号（０から始まる数値）
                name        ボード名称を格納するバッファポインタ
                maxbuffsize ボード名称のバッファサイズ
				Something	定義ファイルのBRDINFOに記述している情報
        出力    成功したときTRUE、何らかの問題が生じたときfalse
                name        ボード名称を格納する
                            名称バイト数がmaxbuffsizeより大きいとき、falseを返さず、
                            maxbuffsize バイト分だけnameバッファに格納してTRUEを返す
        条件    AIP_IO_Initial()がコールされた後で呼ばれる
    */
{
	ShowIOForm	*Panel=new ShowIOForm();
	Panel->show();
	return Panel;
}
BYTE  IO_DLLFUNC _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
    /*
        動作    ＰＩＯボードから１ビットの入力を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
                bitIndex    ビット番号（０から始まる数値）
        出力    入力値に応じて、０か１を返す
        条件    スレッドセーフでなければならない
                オープンされていないボード、あるいはクローズしたボードに
                対するアクセスは無視する（独自エラー処理は必要ない）
    */
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	if(Panel!=NULL){
		if(Panel->InBit[bitIndex]==true)
			return 1;
		else
			return 0;
	}
	return 0;
}
BYTE  IO_DLLFUNC _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
    /*
        動作    ＰＩＯボードから１バイトの入力を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
                byteIndex    バイト番号（０から始まる数値）
        出力    入力値に応じて、０から２５５までの数値を返す
        条件    スレッドセーフでなければならない
                オープンされていないボード、あるいはクローズしたボードに
                対するアクセスは無視する（独自エラー処理は必要ない）
    */
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	if(Panel!=NULL){
		BYTE	Ret=0;
		for(int i=0;i<8;i++){
			if(Panel->InBit[byteIndex*8+i]==true)
				Ret |=1<<i;
		}
		return Ret;
	}
	return 0;
}
BYTE  IO_DLLFUNC _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
    /*
        動作    ＰＩＯボードへ１バイトの出力を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
                byteIndex   バイト番号（０から始まる数値）
                data        バイトデータ
        出力    設定された値を返す。
                実際の出力値を読み出すことができるボードに対しては読み込んだ値を返す
                実際の出力値を読み出すことができないボードに対しては、入力値をそのまま返す
        条件    スレッドセーフでなければならない
                オープンされていないボード、あるいはクローズしたボードに
                対するアクセスは無視する（独自エラー処理は必要ない）
    */
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	if(Panel!=NULL){
		BYTE	Ret=0;
		for(int i=0;i<8;i++){
			if((data & (1<<i))!=0){
				Panel->OutBit[byteIndex*8+i]=true;
			}
			else{
				Panel->OutBit[byteIndex*8+i]=false;
			}
		}
		Panel->ShowOut();
		return data;
	}
	return 0;
}
int  IO_DLLFUNC _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
    /*
        動作    ＰＩＯボードから１バイトの出力データの取得を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
                byteIndex    バイト番号（０から始まる数値）
        出力    取得値に応じて、０から２５５までの数値を返す
                取得できないとき、－１を返す
        条件    スレッドセーフでなければならない
                オープンされていないボード、あるいはクローズしたボードに
                対するアクセスは無視する（独自エラー処理は必要ない）
    */
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	if(Panel!=NULL){
		BYTE	Ret=0;
		for(int i=0;i<8;i++){
			if(Panel->OutBit[byteIndex*8+i]==true)
				Ret |=1<<i;
		}
		return Ret;
	}
	return 0;
}
bool  IO_DLLFUNC _cdecl AIP_IO_Close(void *handle ,int boardNumber)
    /*
        動作    各ＰＩＯボードに対してクローズ動作を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
        出力    成功したときTRUE、何らかの問題が生じたときfalse
        条件    AIP_IO_Release()の前に呼ばれる
    */
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	if(Panel!=NULL){
		Panel->close();
	}
	return true;
}
bool  IO_DLLFUNC _cdecl AIP_IO_Release(void)
    /*
        動作    全ＰＩＯボードに対して終了動作を行う
        入力    なし
        出力    成功したときTRUE、何らかの問題が生じたときfalse
        条件    最後に呼ばれる
    */
{
	return true;
}