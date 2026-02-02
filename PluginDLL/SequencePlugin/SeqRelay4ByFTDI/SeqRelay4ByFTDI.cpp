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


#include <QSoundEffect>
#include "XSeqDLLGlobal.h"
#include <string.h>
#include "SeqRelay4ByFTDI.h"

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="SeqRelay4ByFTDI";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Light DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2007.9";
	return true;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Sequence Relay4 by FTDI";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"SeqRelay4ByFTDI-1");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
/*
	�����������K�v�̂����Ƃ��ɋL�q����
	Param : Sequence.dat�ɋL�q�����p�����[�^������
*/
{
	long Ret;

	bool	ok;
	int	DeviceNumber=Param.toInt(&ok);
	if(ok==false)
		DeviceNumber=0;

	Relay4ByFTDI	*H=new Relay4ByFTDI;
	H->OutD=0;

	FT_STATUS ret=FT_Open (DeviceNumber, &H->Handle);
	if(ret!=FT_OK){
		delete	H;
		return NULL;
	}
	ret=FT_SetBitMode(H->Handle, 0xF, 1);
	if(ret!=FT_OK){
		delete	H;
		return NULL;
	}
	ret=FT_SetBaudRate(H->Handle, 9600);
	if(ret!=FT_OK){
		delete	H;
		return NULL;
	}
	return H;
}
bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	if(cmdstr=="ON1"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD |= 0x01;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="ON2"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD |= 0x02;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="ON3"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD |= 0x04;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="ON4"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD |= 0x08;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="OFF1"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD &=~0x01;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="OFF2"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD &=~0x02;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="OFF3"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD &=~0x04;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	else
	if(cmdstr=="OFF4"){
		Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
		DWORD	BytesWriten;

		PIO->OutD &=~0x08;
		FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=1){
			PIO->Error=true;
		}
		return true;
	}
	return false;
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
/*
    �I������
*/
{
	Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
	FT_STATUS ret=FT_Close (PIO->Handle);
}