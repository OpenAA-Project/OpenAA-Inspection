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



#include "XSeqDLLGlobal.h"
#include <string.h>
#include <QString>

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="SampleDLL";
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
	return "Sample DLL for Sequence";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"Sample DLL for Sequence");
}

bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	if(cmdstr=="DLLSeq_Cmd"){
		return true;
	}
	return false;
}

bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	if(cmdstr=="DLLSeq_CmdStr"){
		if(datastr=="123"){
			return true;
		}
	}
	return false;
}

bool	DLLSeq_CmdStrInt(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,int *data)
/*
    ���߂𑗂�
    �f�[�^�Ȃ��̋L�q�̂Ƃ������̊֐����R�[��������
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	if(cmdstr=="DLLSeq_CmdStrInt"){
		if(datastr=="123"){
			*data=345;
			return true;
		}
		else{
			*data=567;
			return false;
		}
	}
	return false;
}

bool	DLLSeq_CmdStrRet(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,QByteArray &Buff)
/*
    ���߂𑗂�
    �f�[�^�Ȃ��̋L�q�̂Ƃ������̊֐����R�[��������
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
    datastr�ɃZ�b�g�����l��Buff�ɓ����Ă���
*/
{
	if(cmdstr=="DLLSeq_CmdStrRet"){
		if(datastr=="ABC"){
			Buff="abcde";
		}
	}
	return true;
}

bool	DLLSeq_CmdStrRetInt(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,QByteArray &Buff ,int *data)
/*
    ���߂𑗂�
    �f�[�^�Ȃ��̋L�q�̂Ƃ������̊֐����R�[��������
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
    datastr�ɃZ�b�g�����l��Buff�ɓ����Ă���
*/
{
	if(cmdstr=="DLLSeq_CmdStrRetInt"){
		if(datastr=="CDE"){
			Buff="cd";
			*data=100;
		}
	}
	return true;
}


bool	DLLSeq_CmdInt(void *handle ,QApplication &App ,const QString &cmdstr , int *data)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Wxx
    �ł��̊֐����Ă΂���
    �f�[�^���Ԃ��Ƃ��A*data�ɒl���i�[�����΁A�uWxx�v�ɒl������
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	if(cmdstr=="DLLSeq_CmdInt"){
		if(*data==10){
			*data=100;
			return true;
		}
	}
	return false;
}

bool	DLLSeq_CmdInt2(void *handle ,QApplication &App ,const QString &cmdstr , int *data1 ,int *data2)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Wxx,Wxx
    �ł��̊֐����Ă΂���
    �f�[�^���Ԃ��Ƃ��A*data�ɒl���i�[�����΁A�uWxx�v�ɒl������
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	if(cmdstr=="DLLSeq_CmdInt2"){
		if(*data1==1 && *data2==2){
			*data1=200;
			*data2=300;
			return true;
		}
	}
	return false;
}

void	DLLSeq_Close(void *handle)
/*
    �I������
*/
{
}

void	DLLSeq_DebugShow(void *handle ,QApplication &App)
{}
