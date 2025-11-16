/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\LED64CTRLib.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
#pragma hdrstop

#include "LED64CTRLib.h"
#include "wdc_lib.h"
//#include <stdio.h>
//#include <windows.h>
//#include <mmsystem.h>

//---------------------------------------------------------------------------

int		LED64ctr::InitialNumb=0;
WDC_DEVICE_HANDLE	LED64ctr::hWD;
bool	LED64ctr::OpenMode=true;
int		LED64ctr::LEDWaitTime=180;	//10000;
struct	InitializedMicrosecTimerStruct LED64ctr::IWaitFunc;

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void RegisterWinDriver(void)
{
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    lednumb
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
LED64ctr::LED64ctr(int lednumb)
{
    BTable=NULL;
    LEDNumb=lednumb;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
LED64ctr::LED64ctr(void)
{
    BTable=NULL;
    LEDNumb=0;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
LED64ctr::~LED64ctr(void)
{
    if(BTable!=NULL)
        delete  []BTable;
    InitialNumb--;
    if(InitialNumb==0){
        if(OpenMode==true){
            if(hWD!=NULL){
                WD_REGISTER_DeviceClose(hWD);
			}
            OpenMode=false;
		}
	}
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    lednumb
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::Initial(int lednumb)
{
    LEDNumb=lednumb;
    Initial();
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    LED64ctr::IsHandleOK(void)
{
    if(hWD==0)
        return(false);
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::InitialOnly(void)
{
    if(InitialNumb==0 || hWD==NULL){
        RegisterWinDriver();
        InitialNumb++;
        OpenMode=true;
	}
	InitialMicrosecTimer(IWaitFunc);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::Initial(void)
{
    InitialOnly();

    if(BTable!=NULL)
        delete  []BTable;

    BTable=new BYTE[LEDNumb];

    Strobe(false);
    Clock(false);
    Enable(true);
    Enable(false);
    Enable(true);
    Reset(true);
    WaitLoop();
    Reset(false);
    Enable(false);
    Enable(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
LED64ctr    &LED64ctr::operator=(LED64ctr &src)
{
    ID=src.ID;
    LEDNumb=src.LEDNumb;
    if(BTable!=NULL)
        delete  []BTable;
    BTable=new BYTE[LEDNumb];
    memcpy(BTable,src.BTable,LEDNumb*sizeof(BYTE));
    data=src.data;
    return(*this);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    n
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::OutData(int n ,double rate)
{
		WaitLoop();
	Enable(false);
	Reset(true);
	WaitLoop();
	Reset(false);
		WaitLoop();
	Clock(false);
	WaitLoop();
	Strobe(true);
	WaitLoop();
	OutBits(ID,8);

	WaitLoop();
	OutBits((BYTE)n,8);
	int d=(BYTE)(BTable[n]*rate);
	if(d<0)
		d=0;
	if(d>=LEDLevels)
		d=LEDLevels-1;

	WaitLoop();
	OutBits((BYTE)d,8);

	WaitLoop();
	Clock(false);
	WaitLoop();
	Strobe(false);
	WaitLoop();

	Reset(false);
	Enable(true);
	WaitLoop();
}

void    __fastcall LED64ctr::OutNullForHasp(void)
{
    OutBits(0,8);
}

void    LED64ctr::SetAllMode(bool modeOn)
{
    Enable(modeOn);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    H
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::Strobe(bool H)
{
    if(H==true)
        data|=4;
    else
        data &=0xfb;

    if(hWD!=NULL)
		WDC_WriteAddr8 (hWD, Address, 0, data);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    H
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::Clock(bool H)
{
    if(H==true)
        data |=1;
    else
        data &=0xfe;

    if(hWD!=NULL)
		WDC_WriteAddr8 (hWD, Address, 0, data);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    H
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::Reset(bool H)
{
    if(H==true)
        data |=0x10;
    else
        data &=0xef;

    if(hWD!=NULL)
		WDC_WriteAddr8 (hWD, Address, 0, data);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    H
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::Enable(bool H)
{
    if(H==true)
        data |=0x08;
    else
        data &=0xf7;

    if(hWD!=NULL)
		WDC_WriteAddr8 (hWD, Address, 0, data);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    H
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::Din(bool H)
{
    if(H==true)
        data |=2;
    else
        data &=0xfd;

    if(hWD!=NULL)
		WDC_WriteAddr8 (hWD, Address, 0, data);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    d
//    bitnumb
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::OutBits(BYTE d,int bitnumb)
{
	WaitLoop();
	for(int i=bitnumb-1;i>=0;i--){
		if((d&(((BYTE)0x01)<<i))!=0)
			Din(true);
		else
			Din(false);
		WaitLoop();
			WaitLoop();
		Clock(true);
			WaitLoop();
		WaitLoop();
		Clock(false);
		WaitLoop();
	}
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    n
//    brightness
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::Change(int n ,BYTE brightness)
{
    if(BTable!=NULL)
        BTable[n]=brightness;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::WaitLoop(void)
{
//	Sleep(10);

	WaitMicrosec(IWaitFunc,LEDWaitTime);
	return;

	DWORD	oTime;
	oTime = timeGetTime();
	for(;;){
	//		Application->ProcessMessages();
		DWORD  wTime=timeGetTime();
		wTime-=oTime;
		if(wTime>LEDWaitTime)
			break;
	}
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    Port
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::MOutBytePrinterPort(int Port ,unsigned char d)
{
	data=d;
	switch(Port){
		case 0:
			if(hWD!=NULL)
				WDC_WriteAddr8(hWD, WD_REGISTER_status_SPACE, 0, data);
			break;
		case 1:
//			if(hWD!=NULL)
//				WDC_WriteAddr8(hWD, WD_REGISTER_status_SPACE, 0, data);
			break;
		case 2:
//			if(hWD!=NULL)
//				WDC_WriteAddr8(hWD, WD_REGISTER_status_SPACE, 0, data);
			break;
	}
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    Port
//    offset
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::MOutBytePrinterPort(int Port ,int offset ,unsigned char d)
{
	data=d;
	switch(Port){
		case 0:
			if(hWD!=NULL)
				WDC_WriteAddr8(hWD, WD_REGISTER_status_SPACE, offset, data);
			break;
		case 1:
//			if(hWD!=NULL)
//				WDC_WriteAddr8(hWD, WD_REGISTER_status_SPACE, offset, data);
			break;
		case 2:
//			if(hWD!=NULL)
//				WDC_WriteAddr8(hWD, WD_REGISTER_status_SPACE, offset, data);
			break;
	}
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    Port
//    BitN
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::MOutBitPrinterPort(int Port ,int BitN ,unsigned char d)
{
    if(d==0)
        data &= (BYTE)(~(0x01<<BitN));
    else
        data |=  (BYTE)(0x01<<BitN);

    MOutBytePrinterPort(Port,data);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    Port
//    offset
//    BitN
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    __fastcall LED64ctr::MOutBitPrinterPort(int Port ,int offset ,int BitN ,unsigned char d)
{
    if(d==0)
        data &= (BYTE)(~(0x01<<BitN));
    else
        data |= (BYTE)(0x01<<BitN);

    MOutBytePrinterPort(Port,offset,data);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void __fastcall LED64ctr::SetShiftRegister(BYTE d)
{
    MOutBitPrinterPort(0,0,6,1);
    for(int i=0;i<8;i++){
        if((d&(0x80>>i))!=0)
            MOutBitPrinterPort(0,0,5,1);
        else
            MOutBitPrinterPort(0,0,5,0);

        Sleep(10);
        MOutBitPrinterPort(0,0,6,0);
        Sleep(10);
        MOutBitPrinterPort(0,0,6,1);
        Sleep(10);
        }
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void __fastcall LED64ctr::Reset(void)
{
    MOutBitPrinterPort(0,2,1,0);
    Sleep(10);
    MOutBitPrinterPort(0,2,1,1);
    Sleep(10);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    n
//    brightness
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void __fastcall LED64ctr::StrobeIt(int n ,int brightness)
{
    int d=(brightness<<4)+n;

    SetShiftRegister((BYTE)d);
    MOutBitPrinterPort(0,0,7,0);
    Sleep(10);
    MOutBitPrinterPort(0,0,7,1);
    Sleep(10);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    b
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void __fastcall LED64ctr::SHEnable(bool b)
{
    if(b==true)
        MOutBitPrinterPort(0,2,3,0);
    else
        MOutBitPrinterPort(0,2,3,1);
}

