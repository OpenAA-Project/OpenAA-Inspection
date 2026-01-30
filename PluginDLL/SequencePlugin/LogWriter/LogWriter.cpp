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



#include "LogWriter.h"
#include "XSeqDLLGlobal.h"
#include <string.h>
#include "ThreadLogWriter.h"
#include "XGeneralFunc.h"


//ThreadLogWriter	*ThreadLog=NULL;

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="LogWriter";
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
	return "Log writer";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"Log writer");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	ThreadLogWriter	*ThreadLog=new ThreadLogWriter();
	ThreadLog->start();
	return ThreadLog;
}

bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	if(cmdstr=="LogOutFileName"){
		ThreadLogWriter	*ThreadLog=(ThreadLogWriter	*)handle;
		if(ThreadLog!=NULL){
			QString	A=datastr;
			::QString2Char(A,ThreadLog->FileName,sizeof(ThreadLog->FileName));
			return true;
		}
	}
	return false;
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
	if(cmdstr=="LogOutOn"){
		ThreadLogWriter	*ThreadLog=(ThreadLogWriter	*)handle;
		if(ThreadLog!=NULL){
			ThreadLog->OnWrittenTime	=XDateTime::currentDateTime ();
			ThreadLog->OnInspectionID	=*data;
			ThreadLog->OnSignalOn		=true;
			ThreadLog->OnWriteMode=true;
			return true;
		}
	}
	else if(cmdstr=="LogOutOff"){
		ThreadLogWriter	*ThreadLog=(ThreadLogWriter	*)handle;
		if(ThreadLog!=NULL){
			ThreadLog->OffWrittenTime	=XDateTime::currentDateTime ();
			ThreadLog->OffInspectionID	=*data;
			ThreadLog->OffSignalOn		=false;
			ThreadLog->OffWriteMode=true;
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
	if(cmdstr=="Print"){
		ThreadLogWriter	*ThreadLog=(ThreadLogWriter	*)handle;
		if(ThreadLog!=NULL){
			ThreadLog->PrintWrittenTime	=XDateTime::currentDateTime ();
			ThreadLog->PrintString		=datastr;
			ThreadLog->PrintNumber		=*data;
			ThreadLog->PrintWriteMode	=true;
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
	ThreadLogWriter	*ThreadLog=(ThreadLogWriter	*)handle;
	if(ThreadLog!=NULL){
		if(ThreadLog->isRunning()==true){
			ThreadLog->terminate();
			ThreadLog->wait(1000);
		}
		ThreadLog->deleteLater();
		ThreadLog=NULL;
	}
}

void	DLLSeq_DebugShow(void *handle ,QApplication &App)
{}
