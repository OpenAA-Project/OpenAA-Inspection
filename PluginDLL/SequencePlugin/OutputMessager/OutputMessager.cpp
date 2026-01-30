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

#include "OutputMessager.h"
#include "XSeqDLLGlobal.h"
#include <string.h>
#include "XGeneralFunc.h"
#include "XMessagerClient.h"
#include <QApplication>


class	OutputMessager
{
public:
	MessagerClient	*MessagerInst;

	OutputMessager(void)
	{
		MessagerInst=NULL;
	}
};



WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="OutputMessager";
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
	return "Output messager";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"Output messager");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	OutputMessager	*Messager=new OutputMessager();
	return Messager;
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
/*
    �I������
*/
{
	OutputMessager	*Messager=(OutputMessager *)handle;

	if(Messager->MessagerInst!=NULL){
		delete	Messager->MessagerInst;
	}
	delete	Messager;
}
bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	OutputMessager	*Messager=(OutputMessager *)handle;

	if(cmdstr=="Start"){
		if(Messager->MessagerInst==NULL){
			QString	IPAddress=datastr;
			Messager->MessagerInst=new MessagerClient(&App);
			Messager->MessagerInst->Initial(IPAddress);
			Messager->MessagerInst->Start();
		}
		return true;
	}
	else if(cmdstr=="ShowOn"){
		if(Messager->MessagerInst!=NULL){
			Messager->MessagerInst->Send(2,0,datastr);
			return true;
		}
	}
	else if(cmdstr=="ShowOff"){
		if(Messager->MessagerInst!=NULL){
			Messager->MessagerInst->Send(3,0,datastr);
			return true;
		}
	}
	return false;
}
