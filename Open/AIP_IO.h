/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\AIP_IO.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef AIO_IOH
#define AIO_IOH

#include "XTypeDef.h"
#include<QString>
#include<QStringList>
#include "XDLLType.h"

class	QWidget;

extern "C"
{


#ifdef _MSC_VER
#define	IO_DLLFUNC __declspec(dllexport) 

IO_DLLFUNC WORD		DLL_GetDLLType	(void);
IO_DLLFUNC bool		DLL_GetName		(QString &str);
IO_DLLFUNC const char	*DLL_GetExplain	(void);
IO_DLLFUNC WORD		DLL_GetVersion	(void);
IO_DLLFUNC bool		DLL_CheckCopyright(QString &CopyrightString);

IO_DLLFUNC int _cdecl  AIP_IO_GetIOBoardNumb(void);
    /*
        動作    ＰＩＯボードの枚数を返す
        入力    なし
        出力    ＰＩＯボード枚数を返す
        条件    AIP_IO_Initial()をコールされた後でこの関数がコールされる
                オープンされていない状態でコールされる
    */

int IO_DLLFUNC _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber);
    /*
        動作    各ＰＩＯボードの入力ビット数を返す
        入力    ＰＩＯボード番号（０から始まる数値）
        出力    各ＰＩＯボードの入力ビット数を返す
        条件    オープンされていない状態でコールされる
    */

int IO_DLLFUNC _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber);
    /*
        動作    各ＰＩＯボードの出力ビット数を返す
        入力    ＰＩＯボード番号（０から始まる数値）
        出力    各ＰＩＯボードの出力ビット数を返す
        条件    オープンされていない状態でコールされる
    */

bool IO_DLLFUNC _cdecl AIP_IO_Initial(const QStringList &NameList);
    /*
        動作    全体のＰＩＯに対して初期化動作を行う
        入力    なし
        出力    成功したときTRUE、何らかの問題が生じたときFALSE
        条件    オープンされていない状態でコールされる
        備考    ボード種類によっては、何もせずにTRUEだけを返すことができる
    */

void IO_DLLFUNC *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something);
    /*
        動作    各ＰＩＯボードに対してオープン動作を行う
        入力    mainW		呼び出した側のメインウインドウ
				boardNumber ＰＩＯボード番号（０から始まる数値）
                name        ボード名称を格納するバッファポインタ
                maxbuffsize ボード名称のバッファサイズ
				Something	定義ファイルのBRDINFOに記述している情報
        出力    成功したときTRUE、何らかの問題が生じたときFALSE
                name        ボード名称を格納する
                            名称バイト数がmaxbuffsizeより大きいとき、FALSEを返さず、
                            maxbuffsize バイト分だけnameバッファに格納してTRUEを返す
        条件    AIP_IO_Initial()がコールされた後で呼ばれる
    */

BYTE  IO_DLLFUNC _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex);
    /*
        動作    ＰＩＯボードから１ビットの入力を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
                bitIndex    ビット番号（０から始まる数値）
        出力    入力値に応じて、０か１を返す
        条件    スレッドセーフでなければならない
                オープンされていないボード、あるいはクローズしたボードに
                対するアクセスは無視する（独自エラー処理は必要ない）
    */

BYTE  IO_DLLFUNC _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex);
    /*
        動作    ＰＩＯボードから１バイトの入力を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
                byteIndex    バイト番号（０から始まる数値）
        出力    入力値に応じて、０から２５５までの数値を返す
        条件    スレッドセーフでなければならない
                オープンされていないボード、あるいはクローズしたボードに
                対するアクセスは無視する（独自エラー処理は必要ない）
    */

void  IO_DLLFUNC _cdecl AIP_IO_SetBit(void *handle ,int boardNumber , BYTE bitIndex ,BYTE data);
    /*
        動作    ＰＩＯボードから１ビットの出力を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
                bitIndex    ビット番号（０から始まる数値）
				data        ビットデータ
        出力    なし
        条件    スレッドセーフでなければならない
                オープンされていないボード、あるいはクローズしたボードに
                対するアクセスは無視する（独自エラー処理は必要ない）
    */
BYTE  IO_DLLFUNC _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data);
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

int  IO_DLLFUNC _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex);
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

int  IO_DLLFUNC _cdecl AIP_IO_GetOutBit(void *handle ,int boardNumber , BYTE bitIndex);
    /*
        動作    ＰＩＯボードから１ビットの出力データの取得を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
                bitIndex    ビット番号（０から始まる数値）
        出力    入力値に応じて、０か１を返す
                取得できないとき、－１を返す
        条件    スレッドセーフでなければならない
                オープンされていないボード、あるいはクローズしたボードに
                対するアクセスは無視する（独自エラー処理は必要ない）
    */

bool  IO_DLLFUNC _cdecl AIP_IO_Close(void *handle ,int boardNumber);
    /*
        動作    各ＰＩＯボードに対してクローズ動作を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
        出力    成功したときTRUE、何らかの問題が生じたときFALSE
        条件    AIP_IO_Release()の前に呼ばれる
    */

bool  IO_DLLFUNC _cdecl AIP_IO_Release(void);
    /*
        動作    全ＰＩＯボードに対して終了動作を行う
        入力    なし
        出力    成功したときTRUE、何らかの問題が生じたときFALSE
        条件    最後に呼ばれる
    */
void  IO_DLLFUNC _cdecl AIP_IO_LoopOnIdle(void *handle ,int boardNumber);

#else
int		AIP_IO_GetIOBoardNumb(void);
int		AIP_IO_GetIOInBitCount(int boardNumber);
int		AIP_IO_GetIOOutBitCount(int boardNumber);
bool	AIP_IO_Initial(void);
bool	AIP_IO_Open(int boardNumber , char *name ,int maxbuffsize);
BYTE	AIP_IO_GetBit(int boardNumber , BYTE bitIndex);
BYTE	AIP_IO_GetByte(int boardNumber , BYTE byteIndex);
BYTE	AIP_IO_SetByte(int boardNumber , BYTE byteIndex , BYTE data);
int		AIP_IO_GetOutByte(int boardNumber , BYTE byteIndex);
bool	AIP_IO_Close(int boardNumber);
bool	AIP_IO_Release(void);
#endif
};

#endif