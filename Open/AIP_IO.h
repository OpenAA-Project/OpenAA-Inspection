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



#ifndef AIO_IOH
#define AIO_IOH

#include "XTypeDef.h"
#include<QString>
#include<QStringList>
#include "XDLLType.h"

class	QWidget;
class	PIODLLBaseClass;
class	LayersBase;

extern "C"
{


#ifdef _MSC_VER
#else
#define _cdecl
#endif

DEFFUNCEX WORD		DLL_GetDLLType	(void);
DEFFUNCEX bool		DLL_GetName		(QString &str);
DEFFUNCEX const char	*DLL_GetExplain	(void);
DEFFUNCEX WORD		DLL_GetVersion	(void);
DEFFUNCEX bool		DLL_CheckCopyright(QString &CopyrightString);

DEFFUNCEX int _cdecl  AIP_IO_GetIOBoardNumb(void);
    /*
        動作    ＰＩＯボードの枚数を返す
        入力    なし
        出力    ＰＩＯボード枚数を返す
        条件    AIP_IO_Initial()をコールされた後でこの関数がコールされる
                オープンされていない状態でコールされる
    */

int DEFFUNCEX _cdecl  AIP_IO_GetIOInBitCount(PIODLLBaseClass *handle ,int boardNumber);
    /*
        動作    各ＰＩＯボードの入力ビット数を返す
        入力    ＰＩＯボード番号（０から始まる数値）
        出力    各ＰＩＯボードの入力ビット数を返す
        条件    オープンされていない状態でコールされる
    */

int DEFFUNCEX _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber);
    /*
        動作    各ＰＩＯボードの出力ビット数を返す
        入力    ＰＩＯボード番号（０から始まる数値）
        出力    各ＰＩＯボードの出力ビット数を返す
        条件    オープンされていない状態でコールされる
    */

bool DEFFUNCEX _cdecl AIP_IO_Initial(const QStringList &NameList);
    /*
        動作    全体のＰＩＯに対して初期化動作を行う
        入力    なし
        出力    成功したときTRUE、何らかの問題が生じたときFALSE
        条件    オープンされていない状態でコールされる
        備考    ボード種類によっては、何もせずにTRUEだけを返すことができる
    */

PIODLLBaseClass DEFFUNCEX *AIP_IO_Open(LayersBase *Base,int boardNumber , char *name ,int maxbuffsize,const QString &Something);
    /*
        動作    各ＰＩＯボードに対してオープン動作を行う
        入力    Base		呼び出した側のBase
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

BYTE  DEFFUNCEX _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex);
    /*
        動作    ＰＩＯボードから１ビットの入力を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
                bitIndex    ビット番号（０から始まる数値）
        出力    入力値に応じて、０か１を返す
        条件    スレッドセーフでなければならない
                オープンされていないボード、あるいはクローズしたボードに
                対するアクセスは無視する（独自エラー処理は必要ない）
    */

BYTE  DEFFUNCEX _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex);
    /*
        動作    ＰＩＯボードから１バイトの入力を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
                byteIndex    バイト番号（０から始まる数値）
        出力    入力値に応じて、０から２５５までの数値を返す
        条件    スレッドセーフでなければならない
                オープンされていないボード、あるいはクローズしたボードに
                対するアクセスは無視する（独自エラー処理は必要ない）
    */

void  DEFFUNCEX _cdecl AIP_IO_SetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex ,BYTE data);
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
BYTE  DEFFUNCEX _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data);
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

int  DEFFUNCEX _cdecl AIP_IO_GetOutByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex);
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

int  DEFFUNCEX _cdecl AIP_IO_GetOutBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex);
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

bool  DEFFUNCEX _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber);
    /*
        動作    各ＰＩＯボードに対してクローズ動作を行う
        入力    boardNumber ＰＩＯボード番号（０から始まる数値）
        出力    成功したときTRUE、何らかの問題が生じたときFALSE
        条件    AIP_IO_Release()の前に呼ばれる
    */

bool  DEFFUNCEX _cdecl AIP_IO_Release(void);
    /*
        動作    全ＰＩＯボードに対して終了動作を行う
        入力    なし
        出力    成功したときTRUE、何らかの問題が生じたときFALSE
        条件    最後に呼ばれる
    */
void  DEFFUNCEX _cdecl AIP_IO_LoopOnIdle(PIODLLBaseClass *handle ,int boardNumber);

};

#endif