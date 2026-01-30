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

//---------------------------------------------------------------------------

#ifndef XSeqDLLGlobalH
#define XSeqDLLGlobalH
//---------------------------------------------------------------------------

//#include <QApplication>
#include "XDLLType.h"
#include "XTypeDef.h"
#include <QByteArray>

class   LayersBase;
class	QApplication;
class	GUIDirectMessage;

extern "C"{

#ifdef _MSC_VER

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif



DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for LightDLL

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void);
//	return Light DLL version

DEFFUNCEX	const char	*DLL_GetExplain(void);

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
//	return Copyright string


DEFFUNCEX		void	DLLSeq_GetDLLVersion(char *buff);
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param);
/*
	�����������K�v�̂����Ƃ��ɋL�q����
	Param : Sequence.dat�ɋL�q�����p�����[�^������
*/

DEFFUNCEX		bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr);
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/

DEFFUNCEX		bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr ,const QByteArray &datastr );
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,fixedstring
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/

DEFFUNCEX		bool	DLLSeq_CmdStrInt(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,int *data);
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Wxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/

DEFFUNCEX		bool	DLLSeq_CmdFloat(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,double *data);
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Fxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
DEFFUNCEX		bool	DLLSeq_CmdStrRet(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,QByteArray &Buff);
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
    datastr�ɃZ�b�g�����l��Buff�ɓ����Ă���
*/

DEFFUNCEX		bool	DLLSeq_CmdStrRetInt(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,QByteArray &Buff ,int *data);
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
    datastr�ɃZ�b�g�����l��Buff�ɓ����Ă���
*/


DEFFUNCEX		bool	DLLSeq_CmdInt(void *handle ,QApplication &App ,const QString &cmdstr , int *data);
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Wxx
    �ł��̊֐����Ă΂���
    �f�[�^���Ԃ��Ƃ��A*data�ɒl���i�[�����΁A�uWxx�v�ɒl������
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/

DEFFUNCEX		bool	DLLSeq_CmdInt2(void *handle ,QApplication &App ,const QString &cmdstr , int *data1 ,int *data2);
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Wxx,Wxx
    �ł��̊֐����Ă΂���
    �f�[�^���Ԃ��Ƃ��A*data�ɒl���i�[�����΁A�uWxx�v�ɒl������
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/

DEFFUNCEX		void DLL_TransmitDirectly(void *handle ,GUIDirectMessage *packet);

DEFFUNCEX		void	DLLSeq_Close(void *handle);
/*
    �I������
*/

DEFFUNCEX		void	DLLSeq_DebugShow(void *handle ,QApplication &App);

#else
void DLLSeq_GetDLLVersion(char *buff);
bool DLLSeq_CmdStr(char *cmdstr , char *datastr);
bool DLLSeq_CmdStrInt(char *cmdstr , char *datastr ,int *data);
bool DLLSeq_CmdStrRet(char *cmdstr , char *datastr ,char Buff[]);
bool DLLSeq_CmdStrRetInt(char *cmdstr , char *datastr ,char Buff[] ,int *data);
bool DLLSeq_CmdInt(char *cmdstr , int *data);
bool DLLSeq_CmdInt2(char *cmdstr , int *data1 ,int *data2);
void DLLSeq_Close(void);
void DLLSeq_DebugShow(void);
#endif
};



#endif