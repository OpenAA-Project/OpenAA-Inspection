/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\LED64CTRLib.h
** Author : YYYYYYYYYY
****************************************************************************-**/
/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
#ifndef LED64CTRLibH
#define LED64CTRLibH
//---------------------------------------------------------------------------

#include "wd_register_lib.h"
#include "XCriticalFunc.h"

#if	defined(KindOfLightDef)

	#if	defined(KindOfLight1)
		#define KindOfLight 1
	#elif	defined(KindOfLight2)
		#define KindOfLight 2
	#elif	defined(KindOfLight3)
		#define KindOfLight 3
	#elif	defined(KindOfLight4)
		#define KindOfLight 4
	#elif	defined(KindOfLight5)
		#define KindOfLight 5
#endif
#else

#define KindOfLight 1

#endif

/* 暫定
    １：旧式８本ＬＥＤバー
    ２：３φＬＥＤバー　旧コントローラー
    ３：３φＬＥＤバー　旧コントローラー　赤緑逆転
    ４：３φＬＥＤバー　新コントローラー
    ５：Ｎｍ９８３５ボード経由  旧式８本ＬＥＤバー
    ６：Ｎｍ９８３５ボード経由  ３φＬＥＤバー　旧コントローラー
    ７：Ｎｍ９８３５ボード経由  ３φＬＥＤバー　旧コントローラー　赤緑逆転
    ８：Ｎｍ９８３５ボード経由  ３φＬＥＤバー　新コントローラー
    ９：３φＬＥＤバー×２セット　新コントローラー
    １０：２ポートの旧ＬＥＤコントローラ
*/

#if KindOfLight==1
	#define LEDBARNUMB	6	//3
	#define LEDBarCommentNumb	20
	#define LEDsNumb	32
	#define LEDBars		1	//2
	#define LEDLevels	32
	#define LEDNumbPerLine	(LEDsNumb/LEDBars)
	#define LEDBarNumb	(LEDBars*LEDBARNUMB)
	#define LEDConditionDivide	4
	#define LEDConditionNumb	(LEDLevels/LEDConditionDivide)

#elif   KindOfLight==2
	#define LEDBARNUMB  2
	#define LEDBarCommentNumb   16
	#define LEDsNumb    64
	#define LEDBars     2
	#define LEDLevels   32
	#define LEDNumbPerLine  (LEDsNumb/LEDBars)
	#define LEDBarNumb  (LEDBars*LEDBARNUMB)
	#define LEDConditionDivide  4
	#define LEDConditionNumb    (LEDLevels/LEDConditionDivide)

#elif KindOfLight==10
	#define LEDBARNUMB	3	//10
	#define LEDBarCommentNumb	20
	#define LEDsNumb	64
	#define LEDBars		1	//2
	#define LEDLevels	32
	#define LEDNumbPerLine	(LEDsNumb/LEDBars)
	#define LEDBarNumb	(LEDBars*LEDBARNUMB)
	#define LEDConditionDivide	4
	#define LEDConditionNumb	(LEDLevels/LEDConditionDivide)

#elif KindOfLight==3
	#define LEDBARNUMB	6	//10	//3
	#define LEDBarCommentNumb	20
	#define LEDsNumb	64
	#define LEDBars		1	//2
	#define LEDLevels	32
	#define LEDNumbPerLine	(LEDsNumb/LEDBars)
	#define LEDBarNumb	(LEDBars*LEDBARNUMB)
	#define LEDConditionDivide	4
	#define LEDConditionNumb	(LEDLevels/LEDConditionDivide)


#elif KindOfLight==4
	#define LEDBARNUMB	8	
	#define LEDBarCommentNumb	20
	#define LEDsNumb	64
	#define LEDBars		1	//2
	#define LEDLevels	32
	#define LEDNumbPerLine	(LEDsNumb/LEDBars)
	#define LEDBarNumb	(LEDBars*LEDBARNUMB)
	#define LEDConditionDivide	4
	#define LEDConditionNumb	(LEDLevels/LEDConditionDivide)

#elif KindOfLight==5
	#define LEDBARNUMB	4	//10	//3
	#define LEDBarCommentNumb	20
	#define LEDsNumb	64
	#define LEDBars		1	//2
	#define LEDLevels	32
	#define LEDNumbPerLine	(LEDsNumb/LEDBars)
	#define LEDBarNumb	(LEDBars*LEDBARNUMB)
	#define LEDConditionDivide	4
	#define LEDConditionNumb	(LEDLevels/LEDConditionDivide)


#endif



/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   LED64ctr
{
	BYTE    ID;
	DWORD	Address;
	BYTE    *BTable;
	int     LEDNumb;

	static  WDC_DEVICE_HANDLE  hWD;
	static  int InitialNumb;

	static  struct	InitializedMicrosecTimerStruct IWaitFunc;

public:
    static  int		LEDWaitTime;
    static  bool    OpenMode;

public:
    LED64ctr(int lednumb);
    LED64ctr(void);
    ~LED64ctr(void);

    void    __fastcall Initial(int lednumb);
    void    __fastcall Initial(void);
    static  void    __fastcall InitialOnly(void);
    static  bool    IsHandleOK(void);
    void    __fastcall OutData(int n,double rate);
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    id
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
    void    __fastcall SetDevice(WDC_DEVICE_HANDLE dev){  hWD=dev;  }
    void    __fastcall SetID(BYTE id){  ID=id;  }
    void    __fastcall SetAddress(DWORD addr){  Address=addr;  }
    void    __fastcall Change(int n ,BYTE brightness);

    void    __fastcall SetShiftRegister(BYTE d);
    void    __fastcall Reset(void);
    void    __fastcall StrobeIt(int n ,int brightness);
    void    __fastcall SHEnable(bool b);

    LED64ctr    &operator=(LED64ctr &src);

    void    SetAllMode(bool modeOn);
    void    __fastcall OutNullForHasp(void);

  protected:
    void    __fastcall Strobe(bool H);
    void    __fastcall Clock(bool H);
    void    __fastcall Reset(bool H);
    void    __fastcall Enable(bool H);
    void    __fastcall Din(bool H);

    void    __fastcall WaitLoop(void);

    BYTE    data;

    void    __fastcall OutBits(BYTE d,int bitnumb);

    void    __fastcall MOutBytePrinterPort(int Port ,unsigned char d);
    void    __fastcall MOutBytePrinterPort(int Port ,int offset ,unsigned char d);
    void    __fastcall MOutBitPrinterPort(int Port ,int BitN ,unsigned char d);
    void    __fastcall MOutBitPrinterPort(int Port ,int offset ,int BitN ,unsigned char d);
};

#endif

