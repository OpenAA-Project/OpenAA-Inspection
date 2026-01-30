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
        ����    �o�h�n�{�[�h�̖������Ԃ�
        ����    �Ȃ�
        �o��    �o�h�n�{�[�h�������Ԃ�
        ����    AIP_IO_Initial()���R�[�����ꂽ���ł��̊֐����R�[��������
                �I�[�v�������Ă��Ȃ����ԂŃR�[��������
    */

int IO_DLLFUNC _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber);
    /*
        ����    �e�o�h�n�{�[�h�̓��̓r�b�g�����Ԃ�
        ����    �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
        �o��    �e�o�h�n�{�[�h�̓��̓r�b�g�����Ԃ�
        ����    �I�[�v�������Ă��Ȃ����ԂŃR�[��������
    */

int IO_DLLFUNC _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber);
    /*
        ����    �e�o�h�n�{�[�h�̏o�̓r�b�g�����Ԃ�
        ����    �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
        �o��    �e�o�h�n�{�[�h�̏o�̓r�b�g�����Ԃ�
        ����    �I�[�v�������Ă��Ȃ����ԂŃR�[��������
    */

bool IO_DLLFUNC _cdecl AIP_IO_Initial(const QStringList &NameList);
    /*
        ����    �S�̂̂o�h�n�ɑ΂��ď������������s��
        ����    �Ȃ�
        �o��    ���������Ƃ�TRUE�A���炩�̖��肪�������Ƃ�FALSE
        ����    �I�[�v�������Ă��Ȃ����ԂŃR�[��������
        ���l    �{�[�h���ނɂ����ẮA����������TRUE�������Ԃ����Ƃ��ł���
    */

void IO_DLLFUNC *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something);
    /*
        ����    �e�o�h�n�{�[�h�ɑ΂��ăI�[�v���������s��
        ����    mainW		�Ăяo�������̃��C���E�C���h�E
				boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                name        �{�[�h���̂��i�[�����o�b�t�@�|�C���^
                maxbuffsize �{�[�h���̂̃o�b�t�@�T�C�Y
				Something	���`�t�@�C����BRDINFO�ɋL�q���Ă�������
        �o��    ���������Ƃ�TRUE�A���炩�̖��肪�������Ƃ�FALSE
                name        �{�[�h���̂��i�[����
                            ���̃o�C�g����maxbuffsize�����傫���Ƃ��AFALSE���Ԃ����A
                            maxbuffsize �o�C�g������name�o�b�t�@�Ɋi�[����TRUE���Ԃ�
        ����    AIP_IO_Initial()���R�[�����ꂽ���ŌĂ΂���
    */

BYTE  IO_DLLFUNC _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex);
    /*
        ����    �o�h�n�{�[�h�����P�r�b�g�̓��͂��s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                bitIndex    �r�b�g�ԍ��i�O�����n�܂鐔�l�j
        �o��    ���͒l�ɉ����āA�O���P���Ԃ�
        ����    �X���b�h�Z�[�t�łȂ����΂Ȃ��Ȃ�
                �I�[�v�������Ă��Ȃ��{�[�h�A���邢�̓N���[�Y�����{�[�h��
                �΂����A�N�Z�X�͖��������i�Ǝ��G���[�����͕K�v�Ȃ��j
    */

BYTE  IO_DLLFUNC _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex);
    /*
        ����    �o�h�n�{�[�h�����P�o�C�g�̓��͂��s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                byteIndex    �o�C�g�ԍ��i�O�����n�܂鐔�l�j
        �o��    ���͒l�ɉ����āA�O�����Q�T�T�܂ł̐��l���Ԃ�
        ����    �X���b�h�Z�[�t�łȂ����΂Ȃ��Ȃ�
                �I�[�v�������Ă��Ȃ��{�[�h�A���邢�̓N���[�Y�����{�[�h��
                �΂����A�N�Z�X�͖��������i�Ǝ��G���[�����͕K�v�Ȃ��j
    */

void  IO_DLLFUNC _cdecl AIP_IO_SetBit(void *handle ,int boardNumber , BYTE bitIndex ,BYTE data);
    /*
        ����    �o�h�n�{�[�h�����P�r�b�g�̏o�͂��s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                bitIndex    �r�b�g�ԍ��i�O�����n�܂鐔�l�j
				data        �r�b�g�f�[�^
        �o��    �Ȃ�
        ����    �X���b�h�Z�[�t�łȂ����΂Ȃ��Ȃ�
                �I�[�v�������Ă��Ȃ��{�[�h�A���邢�̓N���[�Y�����{�[�h��
                �΂����A�N�Z�X�͖��������i�Ǝ��G���[�����͕K�v�Ȃ��j
    */
BYTE  IO_DLLFUNC _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data);
    /*
        ����    �o�h�n�{�[�h�ւP�o�C�g�̏o�͂��s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                byteIndex   �o�C�g�ԍ��i�O�����n�܂鐔�l�j
                data        �o�C�g�f�[�^
        �o��    �ݒ肳�ꂽ�l���Ԃ��B
                ���ۂ̏o�͒l���ǂݏo�����Ƃ��ł����{�[�h�ɑ΂��Ă͓ǂݍ��񂾒l���Ԃ�
                ���ۂ̏o�͒l���ǂݏo�����Ƃ��ł��Ȃ��{�[�h�ɑ΂��ẮA���͒l�����̂܂ܕԂ�
        ����    �X���b�h�Z�[�t�łȂ����΂Ȃ��Ȃ�
                �I�[�v�������Ă��Ȃ��{�[�h�A���邢�̓N���[�Y�����{�[�h��
                �΂����A�N�Z�X�͖��������i�Ǝ��G���[�����͕K�v�Ȃ��j
    */

int  IO_DLLFUNC _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex);
    /*
        ����    �o�h�n�{�[�h�����P�o�C�g�̏o�̓f�[�^�̎擾���s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                byteIndex    �o�C�g�ԍ��i�O�����n�܂鐔�l�j
        �o��    �擾�l�ɉ����āA�O�����Q�T�T�܂ł̐��l���Ԃ�
                �擾�ł��Ȃ��Ƃ��A�|�P���Ԃ�
        ����    �X���b�h�Z�[�t�łȂ����΂Ȃ��Ȃ�
                �I�[�v�������Ă��Ȃ��{�[�h�A���邢�̓N���[�Y�����{�[�h��
                �΂����A�N�Z�X�͖��������i�Ǝ��G���[�����͕K�v�Ȃ��j
    */

int  IO_DLLFUNC _cdecl AIP_IO_GetOutBit(void *handle ,int boardNumber , BYTE bitIndex);
    /*
        ����    �o�h�n�{�[�h�����P�r�b�g�̏o�̓f�[�^�̎擾���s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                bitIndex    �r�b�g�ԍ��i�O�����n�܂鐔�l�j
        �o��    ���͒l�ɉ����āA�O���P���Ԃ�
                �擾�ł��Ȃ��Ƃ��A�|�P���Ԃ�
        ����    �X���b�h�Z�[�t�łȂ����΂Ȃ��Ȃ�
                �I�[�v�������Ă��Ȃ��{�[�h�A���邢�̓N���[�Y�����{�[�h��
                �΂����A�N�Z�X�͖��������i�Ǝ��G���[�����͕K�v�Ȃ��j
    */

bool  IO_DLLFUNC _cdecl AIP_IO_Close(void *handle ,int boardNumber);
    /*
        ����    �e�o�h�n�{�[�h�ɑ΂��ăN���[�Y�������s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
        �o��    ���������Ƃ�TRUE�A���炩�̖��肪�������Ƃ�FALSE
        ����    AIP_IO_Release()�̑O�ɌĂ΂���
    */

bool  IO_DLLFUNC _cdecl AIP_IO_Release(void);
    /*
        ����    �S�o�h�n�{�[�h�ɑ΂��ďI���������s��
        ����    �Ȃ�
        �o��    ���������Ƃ�TRUE�A���炩�̖��肪�������Ƃ�FALSE
        ����    �Ō��ɌĂ΂���
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