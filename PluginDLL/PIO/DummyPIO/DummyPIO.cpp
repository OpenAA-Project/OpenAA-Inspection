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
        ����    �o�h�n�{�[�h�̖������Ԃ�
        ����    �Ȃ�
        �o��    �o�h�n�{�[�h�������Ԃ�
        ����    AIP_IO_Initial()���R�[�����ꂽ���ł��̊֐����R�[��������
                �I�[�v�������Ă��Ȃ����ԂŃR�[��������
    */
{
	return 1;
}

int IO_DLLFUNC _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
    /*
        ����    �e�o�h�n�{�[�h�̓��̓r�b�g�����Ԃ�
        ����    �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
        �o��    �e�o�h�n�{�[�h�̓��̓r�b�g�����Ԃ�
        ����    �I�[�v�������Ă��Ȃ����ԂŃR�[��������
    */
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	return 16;
}
int IO_DLLFUNC _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
    /*
        ����    �e�o�h�n�{�[�h�̏o�̓r�b�g�����Ԃ�
        ����    �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
        �o��    �e�o�h�n�{�[�h�̏o�̓r�b�g�����Ԃ�
        ����    �I�[�v�������Ă��Ȃ����ԂŃR�[��������
    */
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	return 16;
}
bool  IO_DLLFUNC _cdecl AIP_IO_Initial(const QStringList &NameList)
    /*
        ����    �S�̂̂o�h�n�ɑ΂��ď������������s��
        ����    �Ȃ�
        �o��    ���������Ƃ�TRUE�A���炩�̖��肪�������Ƃ�false
        ����    �I�[�v�������Ă��Ȃ����ԂŃR�[��������
        ���l    �{�[�h���ނɂ����ẮA����������TRUE�������Ԃ����Ƃ��ł���
    */
{
	return true;
}
void  IO_DLLFUNC _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
    /*
        ����    �e�o�h�n�{�[�h�ɑ΂��ăI�[�v���������s��
        ����    mainW		�Ăяo�������̃��C���E�C���h�E
				boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                name        �{�[�h���̂��i�[�����o�b�t�@�|�C���^
                maxbuffsize �{�[�h���̂̃o�b�t�@�T�C�Y
				Something	���`�t�@�C����BRDINFO�ɋL�q���Ă�������
        �o��    ���������Ƃ�TRUE�A���炩�̖��肪�������Ƃ�false
                name        �{�[�h���̂��i�[����
                            ���̃o�C�g����maxbuffsize�����傫���Ƃ��Afalse���Ԃ����A
                            maxbuffsize �o�C�g������name�o�b�t�@�Ɋi�[����TRUE���Ԃ�
        ����    AIP_IO_Initial()���R�[�����ꂽ���ŌĂ΂���
    */
{
	ShowIOForm	*Panel=new ShowIOForm();
	Panel->show();
	return Panel;
}
BYTE  IO_DLLFUNC _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
    /*
        ����    �o�h�n�{�[�h�����P�r�b�g�̓��͂��s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                bitIndex    �r�b�g�ԍ��i�O�����n�܂鐔�l�j
        �o��    ���͒l�ɉ����āA�O���P���Ԃ�
        ����    �X���b�h�Z�[�t�łȂ����΂Ȃ��Ȃ�
                �I�[�v�������Ă��Ȃ��{�[�h�A���邢�̓N���[�Y�����{�[�h��
                �΂����A�N�Z�X�͖��������i�Ǝ��G���[�����͕K�v�Ȃ��j
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
        ����    �o�h�n�{�[�h�����P�o�C�g�̓��͂��s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                byteIndex    �o�C�g�ԍ��i�O�����n�܂鐔�l�j
        �o��    ���͒l�ɉ����āA�O�����Q�T�T�܂ł̐��l���Ԃ�
        ����    �X���b�h�Z�[�t�łȂ����΂Ȃ��Ȃ�
                �I�[�v�������Ă��Ȃ��{�[�h�A���邢�̓N���[�Y�����{�[�h��
                �΂����A�N�Z�X�͖��������i�Ǝ��G���[�����͕K�v�Ȃ��j
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
        ����    �o�h�n�{�[�h�����P�o�C�g�̏o�̓f�[�^�̎擾���s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
                byteIndex    �o�C�g�ԍ��i�O�����n�܂鐔�l�j
        �o��    �擾�l�ɉ����āA�O�����Q�T�T�܂ł̐��l���Ԃ�
                �擾�ł��Ȃ��Ƃ��A�|�P���Ԃ�
        ����    �X���b�h�Z�[�t�łȂ����΂Ȃ��Ȃ�
                �I�[�v�������Ă��Ȃ��{�[�h�A���邢�̓N���[�Y�����{�[�h��
                �΂����A�N�Z�X�͖��������i�Ǝ��G���[�����͕K�v�Ȃ��j
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
        ����    �e�o�h�n�{�[�h�ɑ΂��ăN���[�Y�������s��
        ����    boardNumber �o�h�n�{�[�h�ԍ��i�O�����n�܂鐔�l�j
        �o��    ���������Ƃ�TRUE�A���炩�̖��肪�������Ƃ�false
        ����    AIP_IO_Release()�̑O�ɌĂ΂���
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
        ����    �S�o�h�n�{�[�h�ɑ΂��ďI���������s��
        ����    �Ȃ�
        �o��    ���������Ƃ�TRUE�A���炩�̖��肪�������Ƃ�false
        ����    �Ō��ɌĂ΂���
    */
{
	return true;
}