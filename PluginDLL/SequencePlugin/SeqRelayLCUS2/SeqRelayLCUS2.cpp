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


#include <QSound>
#include "XSeqDLLGlobal.h"
#include <string.h>
#include "SeqRelayLCUS2.h"
#include <qextserialport.h>

#include <QWidget>
#include <QString>
#include "windows.h"
#include "math.h"
#include <QStringList>
#include <QFile>
#include <QMessageBox>
#include <QThread>

class	TmpThread : public QThread
{
public:
	void run (){}

	static	void	TmpGSleep(unsigned int milisec){	msleep(milisec);	}
};


void	GSleep(unsigned int milisec)
{
	TmpThread::TmpGSleep(milisec);
}

//==
void	SeqRelayLCUS2::Push(char *fp)
{
	for(int i=0;i<4;i++){
		port->write(&fp[i],1);
		GSleep(1);
	}
}


WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="SeqRelayLCUS2";
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
	CopyrightString="Copyright(c) MEGATRADE 2020.5";
	return true;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Sequence Sequence Relay LCUS2";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"SeqRelayLCUS2-1");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
/*
	�����������K�v�̂����Ƃ��ɋL�q����
	Param : Sequence.dat�ɋL�q�����p�����[�^������
*/
{
	long Ret;
	SeqRelayLCUS2	*H=new SeqRelayLCUS2;

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
	if(cmdstr=="Open"){
		SeqRelayLCUS2	*H=(SeqRelayLCUS2 *)handle;
		QString COM="COM"+QString::number(H->ComPort);
	
		H->port = new QextSerialPort(COM);
		H->port->setBaudRate(BAUD9600);
		H->port->setFlowControl(FLOW_OFF);
		H->port->setParity(PAR_NONE);
		H->port->setDataBits(DATA_8);
		H->port->setStopBits(STOP_1_5);
		if(H->port->open(QIODevice::ReadWrite)==false){
			QMessageBox::warning(NULL,"Error","can not open Com");
		}
	}
	if(cmdstr=="ON1"){
		SeqRelayLCUS2	*H=(SeqRelayLCUS2 *)handle;
		char	*fp="\xa0\x01\x01\xa2\r\n";
		H->Push(fp);
		H->port->flush();
		return true;
	}
	else
	if(cmdstr=="ON2"){
		SeqRelayLCUS2	*H=(SeqRelayLCUS2 *)handle;
		char	*fp="\xa0\x02\x01\xa3\r\n";
		H->Push(fp);
		H->port->flush();
		return true;
	}
	else
	if(cmdstr=="OFF1"){
		SeqRelayLCUS2	*H=(SeqRelayLCUS2 *)handle;
		char	*fp="\xa0\x01\x00\xa1\r\n";
		H->Push(fp);
		H->port->flush();
		return true;
	}
	else
	if(cmdstr=="OFF2"){
		SeqRelayLCUS2	*H=(SeqRelayLCUS2 *)handle;
		char	*fp="\xa0\x02\x00\xa2\r\n";
		H->Push(fp);
		H->port->flush();
		return true;
	}

	return false;
}

DEFFUNCEX		bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr ,const QByteArray &datastr )
{
	if(cmdstr=="Open"){
		SeqRelayLCUS2	*H=(SeqRelayLCUS2 *)handle;
		QString COM=datastr;
	
		H->port = new QextSerialPort(COM);
		H->port->setBaudRate(BAUD9600);
		H->port->setFlowControl(FLOW_OFF);
		H->port->setParity(PAR_NONE);
		H->port->setDataBits(DATA_8);
		H->port->setStopBits(STOP_1_5);
		if(H->port->open(QIODevice::ReadWrite)==false){
			QMessageBox::warning(NULL,"Error","can not open Com");
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
	SeqRelayLCUS2	*H=(SeqRelayLCUS2 *)handle;
	H->port->close();
}