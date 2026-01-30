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

#include "ContecNC3DSeq.h"
#include "XSeqDLLGlobal.h"
#include "XGeneralFunc.h"


ContecNC3DController::ContecNC3DController(QObject *parent)
	:QObject(parent)
{
	Socket=NULL;
	Received=false;
}

ContecNC3DController::~ContecNC3DController(void)
{
	if(Socket!=NULL){
		Socket->disconnectFromServer();
		delete	Socket;
		Socket=NULL;
	}
}

bool	ContecNC3DController::StartConnect(void)
{
	Socket=new QLocalSocket(parent());
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	Socket->connectToServer ("ContecNC3D");
	if(Socket->waitForConnected (3000)==false){
		Socket->deleteLater();
		Socket=NULL;
		return false;
	}
	return true;
}

void	ContecNC3DController::SlotReadyRead()
{
	QByteArray	R=Socket->readAll();
	QString	Req(R);
	RData	=Req;
	
	Received=true;
}

void	ContecNC3DController::SendCommand(const QString &Str)
{
	if(Socket==NULL){
		StartConnect();
	}
	Received=false;
	if(Socket!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,Str);
		QByteArray	Array=Buff.buffer();
		Socket->write(Array);
		Socket->flush();
	}
}
void	ContecNC3DController::SendCommand(const QString &Str ,int data)
{
	if(Socket==NULL){
		StartConnect();
	}
	Received=false;
	if(Socket!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,Str);
		::Save(&Buff,data);
		QByteArray	Array=Buff.buffer();
		Socket->write(Array);
		Socket->flush();
	}
}

bool	ContecNC3DController::WaitForRead(int WTm)
{
	if(Socket==NULL){
		StartConnect();
	}
	if(Socket!=NULL){
		Socket->waitForReadyRead(WTm);
		return Received;
	}
	return false;
}

//===========================================================================

//ContecNC3DController	*Pointer=NULL;
class	SeqPack
{
public:
	ContecNC3DController	*Pointer;

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
	str="ContecNC3D";
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
	return "ContecNC3D";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"ContecNC3D-1");
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
		LSeq->Pointer	=new ContecNC3DController(&App);
		return true;
	}
	else if(cmdstr=="GoOrigin"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("GoOrigin");
		}
		return true;
	}
	else if(cmdstr=="StartXY"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("StartXY");
		}
		return true;
	}
	else if(cmdstr=="StepXY"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("StepXY");
		}
		return true;
	}
	else if(cmdstr=="SetLightGreenON"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("SetLightGreenON");
		}
		return true;
	}

	else if(cmdstr=="SetLightGreenOFF"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("SetLightGreenOFF");
		}
		return true;
	}
	else if(cmdstr=="BlinkButton"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("BlinkButton");
		}
		return true;
	}
	else if(cmdstr=="BlinkOFF"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("BlinkOFF");
		}
		return true;
	}
	else if(cmdstr=="VacuumON"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("VacuumON");
		}
		return true;
	}
	else if(cmdstr=="VacuumOFF"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("VacuumOFF");
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
	if(cmdstr=="IsEndXY"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("IsEndXY");
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
			if(LSeq->Pointer->WaitForRead(500)==true){
				LSeq->Pointer->SendCommand("IsStartButton");
				if(LSeq->Pointer->WaitForRead(500)==true){
					*data=LSeq->Pointer->RData.toInt();
					return true;
				}
			}
		}
		return false;
	}
	if(cmdstr=="IsEndZ"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("IsEndZ");
			if(LSeq->Pointer->WaitForRead()==true){
				*data=LSeq->Pointer->RData.toInt();
				return true;
			}
		}
		return false;
	}
	if(cmdstr=="MoveZ"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("MoveZ",*data);
		}
		return true;
	}

	return false;
}