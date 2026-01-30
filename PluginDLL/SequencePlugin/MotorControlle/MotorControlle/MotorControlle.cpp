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



//////////////////////////////////////////////////////////////////
//
// 64�����@���[�^�[�R���g���[���pDLL(RS232C)
//
//	�P�D���_���B�������ʒu�܂ňړ�
//	MotionStage1Data.TargetCount=70;	//�������Ԃ̑��x�ɂȂ��J�E���^�[��
//	MotionStage1Data.Direction  =0;		//���]�����@0 or 1
//	MotionStage1Data.StartPulse =100;  	//�������Ԃ̃p���X��
//	MotionStage1Data.MiddlePulse=2600;	//�������Ԃ̃p���X��
//	MotionStage1Data.EndPulse   =200;  	//�������Ԃ̃p���X��
//
//	�Q�D���_���v���X���~�b�g�܂ňړ�
//	MotionStage2Data.TargetCount=70;	//�������Ԃ̑��x�ɂȂ��J�E���^�[��
//	MotionStage2Data.Direction  =0;		//���]�����@0 or 1
//	MotionStage2Data.StartPulse =100;  	//�������Ԃ̃p���X��
//	MotionStage2Data.MiddlePulse=3000;	//�������Ԃ̃p���X��
//	MotionStage2Data.EndPulse   =20;  	//�������Ԃ̃p���X��
//
//	�R�D�B�������ʒu���v���X���~�b�g�܂ňړ�
//	MotionStage3Data.TargetCount=100;	//�������Ԃ̑��x�ɂȂ��J�E���^�[��
//	MotionStage3Data.Direction  =0;		//���]�����@0 or 1
//	MotionStage3Data.StartPulse =50;  	//�������Ԃ̃p���X��
//	MotionStage3Data.MiddlePulse=150;	//�������Ԃ̃p���X��
//	MotionStage3Data.EndPulse   =10;  	//�������Ԃ̃p���X��
//
//	�S�D�}�C�i�X���~�b�g�܂ňړ�
//	MotionStage4Data.TargetCount=70;	//�������Ԃ̑��x�ɂȂ��J�E���^�[��
//	MotionStage4Data.Direction  =1;		//���]�����@0 or 1
//	MotionStage4Data.StartPulse =200;  	//�������Ԃ̃p���X��
//	MotionStage4Data.MiddlePulse=3000;	//�������Ԃ̃p���X��
//	MotionStage4Data.EndPulse   =100;  	//�������Ԃ̃p���X��
//
//	�T�D���_���A�ړ��Q(�v���X����)
//	MotionStage5Data.TargetCount=500;	//�������Ԃ̑��x�ɂȂ��J�E���^�[��
//	MotionStage5Data.Direction  =0;		//���]�����@0 or 1
//	MotionStage5Data.StartPulse =10;  	//�������Ԃ̃p���X��
//	MotionStage5Data.MiddlePulse=50;	//�������Ԃ̃p���X��
//	MotionStage5Data.EndPulse   =10;  	//�������Ԃ̃p���X��
//
//	�U�D���_���A�ړ��@�d���n�m���̓���
//	MotionStage6Data.TargetCount=500;	//�������Ԃ̑��x�ɂȂ��J�E���^�[��
//	MotionStage6Data.Direction  =0;		//���]�����@0 or 1
//	MotionStage6Data.StartPulse =10;  	//�������Ԃ̃p���X��
//	MotionStage6Data.MiddlePulse=200;	//�������Ԃ̃p���X��
//	MotionStage6Data.EndPulse   =10;  	//�������Ԃ̃p���X��
//
//////////////////////////////////////////////////////////////////

#include <QIODevice>
#include "XSeqDLLGlobal.h"
//#include <string.h>
#include <qextserialport.h>

#include "ControlMotion1A.h"

//static QextSerialPort *port;

class   ControlMotioner : public ControlMotion1A
{
	QextSerialPort	*port;
	bool	Initialed;
	int		ComNumb;

public:
	ControlMotioner(void);
	~ControlMotioner(void);

	void	SetIndex(int Index);
	virtual	bool	Initial(void)				;
	virtual	bool	IsInitialed(void){  return Initialed;   }
	virtual	int		GetChar(void)				;
	virtual	void	SendChar(unsigned char d)	;
	virtual	unsigned int	GetCPUMilisec(void)	;

	//�e���ݒ��R�}���h
	void	SetTargetCount	(int Index,int data);
	void	SetDirection	(int Index,int data);
	void	SetStartPulse	(int Index,int data);
	void	SetMiddlePulse	(int Index,int data);
	void	SetEndPulse		(int Index,int data);
};

ControlMotioner::ControlMotioner(void)
:ControlMotion1A()
{
	ComNumb=0;
    Initialed=false;
}

ControlMotioner::~ControlMotioner(void)
{
	port->close();
}
void	ControlMotioner::SetIndex(int Index)
{
	ComNumb=Index;
}
bool	ControlMotioner::Initial(void)
{
	QString COM="COM";
	COM.append(QString::number(ComNumb));
	port = new QextSerialPort(COM);
	port->setBaudRate(BAUD38400);
	port->setFlowControl(FLOW_OFF);
	port->setParity(PAR_NONE);
	port->setDataBits(DATA_8);
	port->setStopBits(STOP_1);
	if(port->open(QIODevice::ReadWrite)==false)
		return false;
    Initialed=true;
	return true;
}

int		ControlMotioner::GetChar(void)
{
	char data;
    port->read(&data,1);
    return data;
}

void	ControlMotioner::SendChar(unsigned char d)
{
	port->write((char *)&d,1);
}

unsigned int	ControlMotioner::GetCPUMilisec(void)
{
    return ::GetTickCount();
}

void	ControlMotioner::SetTargetCount(int Index,int data)
{
	//�������Ԃ̑��x�ɂȂ��J�E���^�[��
	switch(Index){
		case 1:
			MotionStage1Data.TargetCount=data;
			break;
		case 2:
			MotionStage2Data.TargetCount=data;
			break;
		case 3:
			MotionStage3Data.TargetCount=data;
			break;
		case 4:
			MotionStage4Data.TargetCount=data;
			break;
		case 5:
			MotionStage5Data.TargetCount=data;
			break;
		case 6:
			MotionStage6Data.TargetCount=data;
			break;
	}
}

void	ControlMotioner::SetDirection(int Index,int data)
{
	//���]�����@0 or 1
	switch(Index){
		case 1:
			MotionStage1Data.Direction=data;
			break;
		case 2:
			MotionStage2Data.Direction=data;
			break;
		case 3:
			MotionStage3Data.Direction=data;
			break;
		case 4:
			MotionStage4Data.Direction=data;
			break;
		case 5:
			MotionStage5Data.Direction=data;
			break;
		case 6:
			MotionStage6Data.Direction=data;
			break;
	}
}

void	ControlMotioner::SetStartPulse(int Index,int data)
{
	//�������Ԃ̃p���X��
	switch(Index){
		case 1:
			MotionStage1Data.StartPulse=data;
			break;
		case 2:
			MotionStage2Data.StartPulse=data;
			break;
		case 3:
			MotionStage3Data.StartPulse=data;
			break;
		case 4:
			MotionStage4Data.StartPulse=data;
			break;
		case 5:
			MotionStage5Data.StartPulse=data;
			break;
		case 6:
			MotionStage6Data.StartPulse=data;
			break;
	}
}

void	ControlMotioner::SetMiddlePulse(int Index,int data)
{
	//�������Ԃ̃p���X��
	switch(Index){
		case 1:
			MotionStage1Data.MiddlePulse=data;
			break;
		case 2:
			MotionStage2Data.MiddlePulse=data;
			break;
		case 3:
			MotionStage3Data.MiddlePulse=data;
			break;
		case 4:
			MotionStage4Data.MiddlePulse=data;
			break;
		case 5:
			MotionStage5Data.MiddlePulse=data;
			break;
		case 6:
			MotionStage6Data.MiddlePulse=data;
			break;
	}
}

void	ControlMotioner::SetEndPulse(int Index,int data)
{
	//�������Ԃ̃p���X��
	switch(Index){
		case 1:
			MotionStage1Data.EndPulse=data;
			break;
		case 2:
			MotionStage2Data.EndPulse=data;
			break;
		case 3:
			MotionStage3Data.EndPulse=data;
			break;
		case 4:
			MotionStage4Data.EndPulse=data;
			break;
		case 5:
			MotionStage5Data.EndPulse=data;
			break;
		case 6:
			MotionStage6Data.EndPulse=data;
			break;
	}
}

//static ControlMotioner *ControlM;

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="MotorControlle";
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
	return "Serial Command DLL for MEGATRADE Desk-top Machine";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    �o�[�W�������Ԃ�
    buff�͂Q�T�U�o�C�g�ȓ�
*/
{
	strcpy(buff,"Serial Command DLL for MEGATRADE Desk-top Machine");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	ControlMotioner	*LSeq=new ControlMotioner();
	return LSeq;
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
	if(cmdstr=="SetCommand"){
		ControlMotioner	*ControlM=(ControlMotioner *)handle;
	    ControlM->SendMotionCommand	(*data);
		return true;
	}
	else if(cmdstr=="Open"){
		ControlMotioner	*ControlM=(ControlMotioner *)handle;
		ControlM->SetIndex(*data);
		if(ControlM->Initial		()==false)
			return false;
		if(ControlM->SetMotionData1	()==false)
			return false;
		if(ControlM->SetMotionData2	()==false)
			return false;
		if(ControlM->SetMotionData3	()==false)
			return false;
		if(ControlM->SetMotionData4	()==false)
			return false;
		if(ControlM->SetMotionData5	()==false)
			return false;
		if(ControlM->SetMotionData6	()==false)
			return false;
		return true;
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
	if(cmdstr=="SetTargetCount"){
		ControlMotioner	*ControlM=(ControlMotioner *)handle;
	    ControlM->SetTargetCount(*data1,*data2);
		return true;
	}
	else if(cmdstr=="SetDirection"){
		ControlMotioner	*ControlM=(ControlMotioner *)handle;
	    ControlM->SetDirection(*data1,*data2);
		return true;
	}
	else if(cmdstr=="SetStartPulse"){
		ControlMotioner	*ControlM=(ControlMotioner *)handle;
	    ControlM->SetStartPulse(*data1,*data2);
		return true;
	}
	else if(cmdstr=="SetMiddlePulse"){
		ControlMotioner	*ControlM=(ControlMotioner *)handle;
	    ControlM->SetMiddlePulse(*data1,*data2);
		return true;
	}
	else if(cmdstr=="SetEndPulse"){
		ControlMotioner	*ControlM=(ControlMotioner *)handle;
	    ControlM->SetEndPulse(*data1,*data2);
		return true;
	}
	return false;
}

void	DLLSeq_Close(void *handle)
/*
    �I������
*/
{
	ControlMotioner	*ControlM=(ControlMotioner *)handle;
	delete	ControlM;
}

void	DLLSeq_DebugShow(void *handle ,QApplication &App)
{}