/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\AIP_IO.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#include <windows.h>
#include "AIP_IO.h"
#include <stdio.h>
//---------------------------------------------------------------------------
//   以下は、共有 RTL DLL（CP3250MT.DLL 等）を使わない DLL を作成する
//   場合のメモリ管理に関する注意です
//
//   パラメータや戻り値として AnsiString（及び AnsiString を含む構造体/
//   クラス）を扱う関数を DLL からエクスポートする場合、その DLL と、DLL
//   を使うプロジェクトの両方に MEMMGR.LIB ライブラリを追加する必要が
//   あります。
//
//   DLL からエクスポートされた、TObject から派生されていないクラスに
//   対して new または delete を使う場合にも MEMMGR.LIB を追加しなけれ
//   ばなりません。
//
//   MEMMGR.LIB を追加することにより、DLL と DLL を参照する EXE が共
//   通のメモリマネージャを使うようになります。メモリマネージャは BORLNDMM.DLL
//   として提供されます。DLL またはアプリケーションとともに配布して
//   ください。
//
//   BORLNDMM.DLL が使われるのを避けるには、AnsiString 型の代わりに
//   "char *" または ShortString 型を使って文字列のやり取りをおこなっ
//   てください
//
//   作成する DLL が共有 RTL DLL を使う場合には、RTL の方で MEMMGR.LIB
//   をライブラリとして追加するため DLL プロジェクトに明示的に追加す
//   る必要はありません。
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    return 1;
}
//---------------------------------------------------------------------------



#if !defined(PIOMode)
  #define PIOMode 7
#endif

#if defined(PIOMode1)
  #define PIOMode 1
#endif
#if defined(PIOMode2)
  #define PIOMode 2
#endif
#if defined(PIOMode3)
  #define PIOMode 3
#endif
#if defined(PIOMode4)
  #define PIOMode 4
#endif
#if defined(PIOMode5)
  #define PIOMode 5
#endif
#if defined(PIOMode6)
  #define PIOMode 6
#endif
#if defined(PIOMode7)
  #define PIOMode 7
#endif
//  1:Dummy
//  2:ADTEK     aPCI-P31A   1枚構成
//  3:ADTEK     aPCI-P31A   2枚構成
//  4:CONTEC    PCI-16/16L  1枚構成
//  5:CONTEC    PCI-32/32L  1枚構成
//  6:CONTEC    PCI-64/64L  1枚構成
//  7:CONTEC    PCI-16/16L(PCI)H  1枚構成


#if     PIOMode==2 || PIOMode==3
    #include "apci31a.h"
    static  WORD    hPIO_DRV[16];
    static  int     BoardNumb=0;
    static  DWORD   BaseAdr[16];

#elif   PIOMode==4 || PIOMode==5 || PIOMode==6 || PIOMode==7
    #include "APIDIO.h"
    static  WORD    hPIO_DRV[16];
    static  int     BoardNumb;
    static  DWORD   BaseAdr[16];
    static  WORD    Grp[16];
#endif

int _cdecl  _export AIP_IO_GetIOBoardNumb(void)
{
  #if   PIOMode==1
    return(1);
  #elif PIOMode==2
    return(1);
  #elif PIOMode==3
    return(2);
  #elif PIOMode==4
    return(1);
  #elif PIOMode==5
    return(1);
  #elif PIOMode==6
    return(1);
  #elif PIOMode==7
    return(BoardNumb);
  #endif
}

int _cdecl  _export AIP_IO_GetIOInBitCount(int boardNumber)
{
  #if   PIOMode==1
    return(32);
  #elif PIOMode==2
    return(32);
  #elif PIOMode==3
    return(32);
  #elif PIOMode==4
    return(16);
  #elif PIOMode==5
    return(32);
  #elif PIOMode==6
    return(64);
  #elif PIOMode==7
    return(16);
  #endif
}

int _cdecl  _export AIP_IO_GetIOOutBitCount(int boardNumber)
{
  #if   PIOMode==1
    return(32);
  #elif PIOMode==2
    return(32);
  #elif PIOMode==3
    return(32);
  #elif PIOMode==4
    return(16);
  #elif PIOMode==5
    return(32);
  #elif PIOMode==6
    return(64);
  #elif PIOMode==7
    return(16);
  #endif
}

BOOL  _cdecl _export AIP_IO_Initial(void)
{
  #if   PIOMode==1
    return(TRUE);
  #elif PIOMode==2
        BoardNumb=0;

        for(int i=0;i<sizeof(BaseAdr)/sizeof(BaseAdr[0]);i++){
            BaseAdr[i]=0x7FFFFFFF;
            }
        for(int i=0;i<255;i++){
            hPIO_DRV[BoardNumb]=i;
            if(Apci31aCreate(&hPIO_DRV[BoardNumb])==TRUE){
                DWORD   id;
                Apci31aGetSwitchValue(hPIO_DRV[BoardNumb] ,&id);
                BaseAdr[BoardNumb]=id;
                BoardNumb++;
                break;
                }
            }
        if(BoardNumb==0)
            return(false);
        return(TRUE);
  #elif PIOMode==3
        BoardNumb=0;
        WORD    Hndle;
        for(int i=0;i<sizeof(BaseAdr)/sizeof(BaseAdr[0]);i++){
            BaseAdr[i]=0x7FFFFFFF;
            }
        for(int i=0;i<255;i++){
            Hndle=i;
            if(Apci31aCreate(&Hndle)==TRUE){
                DWORD   id;
                Apci31aGetSwitchValue(Hndle ,&id);
                hPIO_DRV[id]=Hndle;
                BaseAdr[id]=id;
                BoardNumb++;
                break;
                }
            }
        for(int i=0;i<255;i++){
            Hndle=i;
            if(Apci31aCreate(&Hndle)==TRUE){
                DWORD   id;
                Apci31aGetSwitchValue(Hndle ,&id);
                hPIO_DRV[id]=Hndle;
                BaseAdr[id]=id;
                BoardNumb++;
                break;
                }
            }
        if(BoardNumb<=1)
            return(false);
        return(TRUE);
  #elif PIOMode==4 || PIOMode==5 || PIOMode==6 || PIOMode==7
        BoardNumb=0;
        for(int i=0;i<255;i++){
            hPIO_DRV[BoardNumb]=i;
            WORD    DrvNumb=2;
            Grp[BoardNumb]=1+BoardNumb;

            if(DioOpen((HANDLE *)&hPIO_DRV[BoardNumb],DrvNumb,Grp[BoardNumb])==0){
                BaseAdr[BoardNumb]=DrvNumb*0x100+Grp[BoardNumb];
                BoardNumb++;
                }
            else
                break;
            }
      return(TRUE);
  #endif
}

BOOL  _cdecl _export AIP_IO_Open(int boardNumber , char *name ,int maxbuffsize)
{
  #if   PIOMode==1
    strcpy(name,"Dummied no board");
    return(TRUE);
  #elif PIOMode==2
    char    Buff[128];
    strcpy(Buff,"ADTEK aPCI-P31A : SW-");
    sprintf(strchr(Buff,0),"%d",(int)BaseAdr[0]);
    if(strlen(Buff)>=maxbuffsize)
        return(false);
    strcpy(name,Buff);
    return(true);
  #elif PIOMode==3
    char    Buff[128];
    strcpy(Buff,"ADTEK aPCI-P31A : SW-");
    sprintf(strchr(Buff,0),"%d",(int)BaseAdr[boardNumber]);
    if(strlen(Buff)>=maxbuffsize)
        return(false);
    strcpy(name,Buff);
    return(true);
  #elif PIOMode==4
    char    Buff[128];
    strcpy(Buff,"CONTEC PCI16/16L : CODE-");
    sprintf(strchr(Buff,0),"%d",BaseAdr[0]);
    if(strlen(Buff)>=maxbuffsize)
        return(false);
    strcpy(name,Buff);
    return(true);
  #elif PIOMode==5
    char    Buff[128];
    strcpy(Buff,"CONTEC PCI32/32L : CODE-");
    sprintf(strchr(Buff,0),"%d",BaseAdr[0]);
    if(strlen(Buff)>=maxbuffsize)
        return(false);
    strcpy(name,Buff);
    return(true);
  #elif PIOMode==6
    char    Buff[128];
    strcpy(Buff,"CONTEC PCI64/64L : CODE-");
    sprintf(strchr(Buff,0),"%d",BaseAdr[0]);
    if(strlen(Buff)>=maxbuffsize)
        return(false);
    strcpy(name,Buff);
    return(true);
  #elif PIOMode==7
    char    Buff[128];
    strcpy(Buff,"CONTEC PCI16/16L(PCI)H : CODE-");
    sprintf(strchr(Buff,0),"%d",BaseAdr[0]);
    if(strlen(Buff)>=maxbuffsize)
        return(false);
    strcpy(name,Buff);
    return(true);
  #endif
}

BYTE  _cdecl _export AIP_IO_GetBit(int boardNumber , BYTE bitIndex)
{
  #if   PIOMode==1
    return(0);
  #elif PIOMode==2
        BYTE    ret;
        Apci31aInPort(hPIO_DRV[0],bitIndex/8 ,&ret);
        if((ret & (0x01<<(bitIndex&7)))==0)
            return(0);
        return(1);
  #elif PIOMode==3
        BYTE    ret;
        Apci31aInPort(hPIO_DRV[boardNumber],bitIndex/8 ,&ret);
        if((ret & (0x01<<(bitIndex&7)))==0)
            return(0);
        return(1);
  #elif PIOMode==4 || PIOMode==5 || PIOMode==6 || PIOMode==7
        BYTE    ret;
        DioInpByte((HANDLE)hPIO_DRV[boardNumber],bitIndex/8 ,&ret);
        if((ret & (0x01<<(bitIndex&7)))==0)
            return(0);
        return(1);
  #endif
}

BYTE  _cdecl _export AIP_IO_GetByte(int boardNumber , BYTE byteIndex)
{
  #if   PIOMode==1
    return(0);
  #elif PIOMode==2
        BYTE    ret;
        Apci31aInPort(hPIO_DRV[0],byteIndex ,&ret);
        return(ret);
  #elif PIOMode==3
        BYTE    ret;
        Apci31aInPort(hPIO_DRV[boardNumber],byteIndex ,&ret);
        return(ret);
  #elif PIOMode==4 || PIOMode==5 || PIOMode==6 || PIOMode==7
        BYTE    ret;
        DioInpByte((HANDLE)hPIO_DRV[boardNumber],byteIndex  ,&ret);
        return(ret);
  #endif
}

BYTE  _cdecl _export AIP_IO_SetByte(int boardNumber , BYTE byteIndex , BYTE data)
{
  #if   PIOMode==1
    return(0);
  #elif PIOMode==2
        Apci31aOutPort(hPIO_DRV[0],byteIndex ,data);
        return(data);
  #elif PIOMode==3
        Apci31aOutPort(hPIO_DRV[boardNumber],byteIndex ,data);
        return(data);
  #elif PIOMode==4 || PIOMode==5 || PIOMode==6 || PIOMode==7
        DioOutByte((HANDLE)hPIO_DRV[boardNumber],byteIndex ,data);
        return(data);
  #endif
}

int  _cdecl _export AIP_IO_GetOutByte(int boardNumber , BYTE byteIndex)
{
  #if   PIOMode==1
    return(-1);
  #elif PIOMode==2
        return(-1);
  #elif PIOMode==3
        return(-1);
  #elif PIOMode==4 || PIOMode==5 || PIOMode==6 || PIOMode==7
        BYTE    data;
        DioEchoBackByte((HANDLE)hPIO_DRV[boardNumber],byteIndex ,&data);
        return(data);
  #endif
}


BOOL  _cdecl _export AIP_IO_Close(int boardNumber)
{
  #if   PIOMode==1
    return(TRUE);
  #elif PIOMode==2
    return(TRUE);
  #elif PIOMode==3
    return(TRUE);
  #elif PIOMode==4
    return(TRUE);
  #elif PIOMode==5
    return(TRUE);
  #elif PIOMode==6
    return(TRUE);
  #elif PIOMode==7
    return(TRUE);
  #endif
}

BOOL  _cdecl _export AIP_IO_Release(void)
{
  #if   PIOMode==1
    return(TRUE);
  #elif PIOMode==2
        if(BoardNumb!=0)
            Apci31aClose(hPIO_DRV[0]);
        return(TRUE);
  #elif PIOMode==3
        if(BoardNumb!=0){
            Apci31aClose(hPIO_DRV[0]);
            Apci31aClose(hPIO_DRV[1]);
            }
        return(TRUE);
  #elif PIOMode==4
        for(int i=0;i<255;i++){
            BoardNumb=0;
            DioClose((HANDLE)hPIO_DRV[BoardNumb]);
            }
        return(TRUE);
  #elif PIOMode==5
        for(int i=0;i<255;i++){
            BoardNumb=0;
            DioClose((HANDLE)hPIO_DRV[BoardNumb]);
            }
        return(TRUE);
  #elif PIOMode==6
        for(int i=0;i<255;i++){
            BoardNumb=0;
            DioClose((HANDLE)hPIO_DRV[BoardNumb]);
            }
        return(TRUE);
  #elif PIOMode==7
        for(int i=0;i<255;i++){
            BoardNumb=0;
            DioClose((HANDLE)hPIO_DRV[BoardNumb]);
            }
        return(TRUE);
  #endif
}






