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
#include "IOLogger.h"
#include "XIOLogThread.h"
#include <string.h>
#include <QFileInfo>
#include "XDateTime.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}

//ThreadIOLogger	*ThreadLog=NULL;


DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base,const QString &Param)
{
	ThreadIOLogger	*ThreadLog=new ThreadIOLogger(Base->GetSeqControl());
	return ThreadLog;
}

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="IOLogger";
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
	return "I/O Log writer";
}

/*
    �����Ɉ��x�Ă΂���
*/

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"I/O Log writer");
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
/*
    �I������
*/
{
	ThreadIOLogger	*ThreadLog=(ThreadIOLogger	*)handle;
	if(ThreadLog!=NULL && ThreadLog->isFinished()==false){
		ThreadLog->terminate();
		ThreadLog->wait(1000);
	}
	if(ThreadLog!=NULL){
		delete	ThreadLog;
		ThreadLog=NULL;
	}
}
bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	QByteArray Buff;
	return DLLSeq_CmdStrRet(handle,App ,cmdstr , datastr ,Buff);
}

bool	DLLSeq_CmdStrRet(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,QByteArray &Buff)
{
	ThreadIOLogger	*ThreadLog=(ThreadIOLogger	*)handle;

	if(cmdstr=="Start"){
		QString	A=datastr;
		QFileInfo	FInfo(A);
		QString	Suf		=FInfo.suffix();
		QString	Path	=FInfo.path();
		QString	BaseName=FInfo.completeBaseName();
		XDateTime	Now=XDateTime::currentDateTime ();
		QString	PathSpace=::GetSeparator();
		if(Path.right(1)==QString('/') || Path.right(1)==QString('\\')){
			PathSpace=/**/"";
		}
		ForceDirectories(Path);
		QString	LogFileName=Path+PathSpace+BaseName+Now.toString("_yyMMdd-hhmmss")+QString(".")+Suf;

		::QString2Char(LogFileName,ThreadLog->FileName,sizeof(ThreadLog->FileName));
		ThreadLog->start();
		return true;
	}
	if(cmdstr=="AddReg"){
		ThreadLog->AddReg(datastr);
		return true;
	}
	if(cmdstr=="AddMsg"){
		ThreadLog->AddMessage(datastr);
		return true;
	}
	return false;
}