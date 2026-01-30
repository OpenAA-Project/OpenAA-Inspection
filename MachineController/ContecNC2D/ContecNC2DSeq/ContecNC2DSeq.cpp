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

#include "ContecNC2DSeq.h"
#include "XSeqDLLGlobal.h"


ContecNC2DController::ContecNC2DController(QObject *parent)
	:QObject(parent)
{
	Socket=NULL;
	Received=false;
}

ContecNC2DController::~ContecNC2DController(void)
{
	if(Socket!=NULL){
		Socket->disconnectFromServer();
		delete	Socket;
		Socket=NULL;
	}
}

bool	ContecNC2DController::StartConnect(void)
{
	Socket=new QLocalSocket(parent());
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	Socket->connectToServer ("ContecNC2D");
	if(Socket->waitForConnected (3000)==false){
		Socket->deleteLater();
		Socket=NULL;
		return false;
	}
	return true;
}

void	ContecNC2DController::SlotReadyRead()
{
	QByteArray	R=Socket->readAll();
	QString	Req(R);
	RData	=Req;
	
	Received=true;
}

void	ContecNC2DController::SendCommand(const QString &Str)
{
	if(Socket==NULL){
		StartConnect();
	}
	Received=false;
	if(Socket!=NULL){
		QByteArray	Array;
		Array+=Str;
		Socket->write(Array);
		Socket->flush();
	}
}

bool	ContecNC2DController::WaitForRead(void)
{
	if(Socket==NULL){
		StartConnect();
	}
	if(Socket!=NULL){
		Socket->waitForReadyRead(1);
		return Received;
	}
	return false;
}

//===========================================================================

//ContecNC2DController	*Pointer=NULL;

class	SeqPack
{
public:
	ContecNC2DController	*Pointer;

	SeqPack(void)	{	Pointer=NULL;	}
};

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="ContecNC2D";
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
	CopyrightString="Copyright(c) MEGATRADE 2015.1";
	return true;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "ContecNC2D";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"ContecNC2D-1");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	SeqPack	*LSeq=new SeqPack();
	return LSeq;
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
{
	SeqPack	*LSeq=(SeqPack *)handle;
	delete	LSeq;
}

bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString
    �ł��̊֐����Ă΂���
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	SeqPack	*LSeq=(SeqPack *)handle;
	if(cmdstr=="Init"){
		LSeq->Pointer	=new ContecNC2DController(&App);
		return true;
	}
	else if(cmdstr=="Start"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("Start");
		}
		return true;
	}
	else if(cmdstr=="Step"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("Start");
		}
		return true;
	}

	return false;
}
DEFFUNCEX		bool	DLLSeq_CmdInt(void *handle ,QApplication &App ,const QString &cmdstr , int *data)
/*
    ���߂𑗂�
    DLLCmd   dllVar,CommandString,Wxx
    �ł��̊֐����Ă΂���
    �f�[�^���Ԃ��Ƃ��A*data�ɒl���i�[�����΁A�uWxx�v�ɒl������
    ���̊֐��̖߂��l���ADLLCmd�̌��ʃt���O�ɔ��f������
*/
{
	SeqPack	*LSeq=(SeqPack *)handle;
	if(cmdstr=="IsEnd"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("IsEnd");
			if(LSeq->Pointer->WaitForRead()==true){
				*data=LSeq->Pointer->RData.toInt();
				return true;
			}
		}
		return false;
	}
	if(cmdstr=="IsStart"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("IsStartButton");
			if(LSeq->Pointer->WaitForRead()==true){
				*data=LSeq->Pointer->RData.toInt();
				return true;
			}
		}
		return false;
	}

	return false;
}