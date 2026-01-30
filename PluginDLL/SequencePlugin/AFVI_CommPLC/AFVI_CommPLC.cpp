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
#include "AFVI_CommPLC.h"
#include "XGeneralFunc.h"

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="AFVI_CommPLC";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2018.8";
	return true;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "LAN commuynication between PLC and PC";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"AFVI_CommPLC");
}

QString AFVI_CommPLC::CommParam="Address=192.168.1.39;Port=6000;ConnectionTimeout=2000;ConnectionRetryTime=2000;Timeout=1000;Retry=1;";

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
/*
	�����������K�v�̂����Ƃ��ɋL�q����
	Param : Sequence.dat�ɋL�q�����p�����[�^������
*/
{
	AFVI_CommPLC	*LSeq=new AFVI_CommPLC();
	LSeq->CommParam=Param;
	return LSeq;
}

DEFFUNCEX		bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	AFVI_CommPLC	*Seq=(AFVI_CommPLC *)handle;
    if(cmdstr=="GetStatus"){
		int Ret=SwPlcComStatus(Seq->CommHandle);
		if(Ret==SWPLC_PORT_OPEN || Ret==SWPLC_PORT_CONNECTED){
			return true;
		}
	}
    if(cmdstr=="Close"){
		SwPlcClear		(Seq->CommHandle);
		SwPlcClosePort	(Seq->CommHandle);
		return true;
	}
    return(false);
}

bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	AFVI_CommPLC	*Seq=(AFVI_CommPLC *)handle;
    if(cmdstr=="InitPort"){
		char	FileName[256];
		::QString2Char(datastr ,FileName ,sizeof(FileName));
		char	ParamStr[256];
		::QString2Char(Seq->CommParam ,ParamStr ,sizeof(ParamStr));

        int	Ret=SwPlcLoadFile(&Seq->CommHandle
								,FileName
								//,/**/"AFVI"			//PortName
								//,/**/"McCom.dll"	//libFileName
								//,SWPLC_TYPE_TCP
								//,ParamStr
								//,""
								);
		if(Ret==SWPLC_OK){
			return true;
		}
	}
	return(false);
}

DEFFUNCEX		bool	DLLSeq_CmdStrInt(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,int *data)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Wxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	int	Ret;
	AFVI_CommPLC	*Seq=(AFVI_CommPLC *)handle;
	if(cmdstr=="GetRegInt"){
		bool	ok;
		int	TagID=datastr.toInt(&ok);
		if(ok==true){
			Ret=SwPlcRead(Seq->CommHandle, TagID);
			if(Ret!=SWPLC_OK)
				return false;
			Ret=SwPlcExecute(Seq->CommHandle);
			if(Ret!=SWPLC_OK)
				return false;
			Ret=SwPlcResponse(Seq->CommHandle,-1);
			if(Ret!=SWPLC_OK && Ret!=SWPLC_RESPONSE_DONE)
				return false;
			Ret=SwPlcGetInt(Seq->CommHandle, TagID,data);
			if(Ret==SWPLC_OK)
				return true;
		}
	}
	else if(cmdstr=="SetRegInt"){
		bool	ok;
		int	TagID=datastr.toInt(&ok);
		if(ok==true){
			Ret=SwPlcWriteInt(Seq->CommHandle, TagID,*data);
			if(Ret!=SWPLC_OK)
				return false;
			Ret=SwPlcExecute(Seq->CommHandle);
			if(Ret!=SWPLC_OK)
				return false;
			Ret=SwPlcResponse(Seq->CommHandle,-1);
			if(Ret!=SWPLC_OK && Ret!=SWPLC_RESPONSE_DONE)
				return false;
			return true;
		}
	}
	return false;
}
DEFFUNCEX		bool	DLLSeq_CmdInt2(void *handle ,QApplication &App ,const QString &cmdstr , int *data1 ,int *data2)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Wxx,Wxx
    �ł��̊֐����Ă΂���
    �f�[�^���Ԃ��Ƃ��A*data�ɒl���i�[�����΁A�uWxx�v�ɒl������
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	AFVI_CommPLC	*Seq=(AFVI_CommPLC *)handle;
	if(cmdstr=="GetRegInt"){
		int	TagID=*data1;
		int	Ret=SwPlcGetInt(Seq->CommHandle, TagID,data2);
		if(Ret==SWPLC_OK){
			return true;
		}
	}
	else if(cmdstr=="SetRegInt"){
		int	TagID=*data1;
		int	Ret=SwPlcWriteInt(Seq->CommHandle, TagID,*data2);
		if(Ret==SWPLC_OK){
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
	//AFVI_CommPLC	*Seq=(AFVI_CommPLC *)handle;
	//delete	Seq;
}

void	DLLSeq_DebugShow(void *handle ,QApplication &App)
{}