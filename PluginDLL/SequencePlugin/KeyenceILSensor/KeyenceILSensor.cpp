/*
 * Copyright (C) 2022
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

#include "KeyenceILSensor.h"
#include "XSeqDLLGlobal.h"
#include <string.h>
#include <QFileInfo>
#include "XDateTime.h"
#include "XGeneralFunc.h"
#include "XForWindows.h"

#include <qextserialport.h>

//static QextSerialPort *port;
/*
    �����Ɉ��x�Ă΂���
*/

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"KeyenceILSensor 1.0");
}
WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="KeyenceILSensor";
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


const char	*DLL_GetExplain(void)
{
	return "DL-RS1A command operator for KeyenceILSensor";
}

void	DLLSeq_Close(void *handle)
/*
    �I������
*/
{
}

void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	QextSerialPort	*port = new QextSerialPort(Param);
	port->setBaudRate(BAUD9600);
	port->setFlowControl(FLOW_OFF);
	port->setParity(PAR_NONE);
	port->setDataBits(DATA_8);
	port->setStopBits(STOP_1);
	if(port->open(QIODevice::ReadWrite)==false){
		delete	port;
		port=NULL;
	}
}

bool	SendData(QextSerialPort *port,char *fp)
{

	if(port->write(*fp,Len)!=Len)
		return false;
	return true;
}


bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
{
	if(cmdstr=="Zero"){
		if(port!=NULL){
			SendData("SW,00,001,0\x0d\x0a");
		}
	}

}



bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QString &datastr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Cxx
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	if(cmdstr=="Open"){
		port = new QextSerialPort(datastr);
		port->setBaudRate(BAUD9600);
		port->setFlowControl(FLOW_OFF);
		port->setParity(PAR_NONE);
		port->setDataBits(DATA_8);
		port->setStopBits(STOP_1);
		if(port->open(QIODevice::ReadWrite))
			return true;
		return false;

	}
	return false;
}
