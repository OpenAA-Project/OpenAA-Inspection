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

/* �b��
    �P�F�����W�{�k�d�c�o�[
    �Q�F�R�ӂk�d�c�o�[�@���R���g���[���[
    �R�F�R�ӂk�d�c�o�[�@���R���g���[���[�@�ԗ΋t�]
    �S�F�R�ӂk�d�c�o�[�@�V�R���g���[���[
    �T�F�m���X�W�R�T�{�[�h�o�R  �����W�{�k�d�c�o�[
    �U�F�m���X�W�R�T�{�[�h�o�R  �R�ӂk�d�c�o�[�@���R���g���[���[
    �V�F�m���X�W�R�T�{�[�h�o�R  �R�ӂk�d�c�o�[�@���R���g���[���[�@�ԗ΋t�]
    �W�F�m���X�W�R�T�{�[�h�o�R  �R�ӂk�d�c�o�[�@�V�R���g���[���[
    �X�F�R�ӂk�d�c�o�[�~�Q�Z�b�g�@�V�R���g���[���[
    �P�O�F�Q�|�[�g�̋��k�d�c�R���g���[��
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
//  1.���{�ꖼ
//
//  2.�T�v
//
//  3.�@�\����
//
//  4.���l
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
	//  1.���{�ꖼ
	//
	//  2.�p�����^����
	//    id
	//
	//  3.�T�v
	//
	//  4.�@�\����
	//
	//  5.�߂��l
	//
	//  6.���l
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
