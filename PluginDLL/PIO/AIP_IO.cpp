/*
 * Copyright (C) 2025
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



//---------------------------------------------------------------------------

#include <windows.h>
#include "AIP_IO.h"
#include <stdio.h>
//---------------------------------------------------------------------------
//   �ȉ��́A���L RTL DLL�iCP3250MT.DLL ���j���g���Ȃ� DLL ���쐬����
//   �ꍇ�̃������Ǘ��Ɋւ��钍�ӂł�
//
//   �p�����[�^���߂��l�Ƃ��� AnsiString�i�y�� AnsiString ���܂ލ\����/
//   �N���X�j�������֐��� DLL �����G�N�X�|�[�g�����ꍇ�A���� DLL �ƁADLL
//   ���g���v���W�F�N�g�̗����� MEMMGR.LIB ���C�u�������ǉ������K�v��
//   �����܂��B
//
//   DLL �����G�N�X�|�[�g���ꂽ�ATObject �����h�������Ă��Ȃ��N���X��
//   �΂��� new �܂��� delete ���g���ꍇ�ɂ� MEMMGR.LIB ���ǉ����Ȃ���
//   �΂Ȃ��܂����B
//
//   MEMMGR.LIB ���ǉ����邱�Ƃɂ����ADLL �� DLL ���Q�Ƃ��� EXE ����
//   �ʂ̃������}�l�[�W�����g���悤�ɂȂ��܂��B�������}�l�[�W���� BORLNDMM.DLL
//   �Ƃ��Ē񋟂����܂��BDLL �܂��̓A�v���P�[�V�����ƂƂ��ɔz�z����
//   ���������B
//
//   BORLNDMM.DLL ���g�������̂��������ɂ́AAnsiString �^�̑�������
//   "char *" �܂��� ShortString �^���g���ĕ������̂��������������Ȃ�
//   �Ă�������
//
//   �쐬���� DLL �����L RTL DLL ���g���ꍇ�ɂ́ARTL �̕��� MEMMGR.LIB
//   �����C�u�����Ƃ��Ēǉ����邽�� DLL �v���W�F�N�g�ɖ����I�ɒǉ���
//   ���K�v�͂����܂����B
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
//  2:ADTEK     aPCI-P31A   1���\��
//  3:ADTEK     aPCI-P31A   2���\��
//  4:CONTEC    PCI-16/16L  1���\��
//  5:CONTEC    PCI-32/32L  1���\��
//  6:CONTEC    PCI-64/64L  1���\��
//  7:CONTEC    PCI-16/16L(PCI)H  1���\��


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





