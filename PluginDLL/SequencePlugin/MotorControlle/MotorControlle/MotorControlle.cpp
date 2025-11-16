/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\MotorControlle\MotorControlle\MotorControlle.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//////////////////////////////////////////////////////////////////
//
// 64卓上機モーターコントロール用DLL(RS232C)
//
//	１．原点→撮像完了位置まで移動
//	MotionStage1Data.TargetCount=70;	//等速区間の速度になるカウンター数
//	MotionStage1Data.Direction  =0;		//回転方向　0 or 1
//	MotionStage1Data.StartPulse =100;  	//加速区間のパルス数
//	MotionStage1Data.MiddlePulse=2600;	//等速区間のパルス数
//	MotionStage1Data.EndPulse   =200;  	//減速区間のパルス数
//
//	２．原点→プラスリミットまで移動
//	MotionStage2Data.TargetCount=70;	//等速区間の速度になるカウンター数
//	MotionStage2Data.Direction  =0;		//回転方向　0 or 1
//	MotionStage2Data.StartPulse =100;  	//加速区間のパルス数
//	MotionStage2Data.MiddlePulse=3000;	//等速区間のパルス数
//	MotionStage2Data.EndPulse   =20;  	//減速区間のパルス数
//
//	３．撮像完了位置→プラスリミットまで移動
//	MotionStage3Data.TargetCount=100;	//等速区間の速度になるカウンター数
//	MotionStage3Data.Direction  =0;		//回転方向　0 or 1
//	MotionStage3Data.StartPulse =50;  	//加速区間のパルス数
//	MotionStage3Data.MiddlePulse=150;	//等速区間のパルス数
//	MotionStage3Data.EndPulse   =10;  	//減速区間のパルス数
//
//	４．マイナスリミットまで移動
//	MotionStage4Data.TargetCount=70;	//等速区間の速度になるカウンター数
//	MotionStage4Data.Direction  =1;		//回転方向　0 or 1
//	MotionStage4Data.StartPulse =200;  	//加速区間のパルス数
//	MotionStage4Data.MiddlePulse=3000;	//等速区間のパルス数
//	MotionStage4Data.EndPulse   =100;  	//減速区間のパルス数
//
//	５．原点復帰移動２(プラス方向)
//	MotionStage5Data.TargetCount=500;	//等速区間の速度になるカウンター数
//	MotionStage5Data.Direction  =0;		//回転方向　0 or 1
//	MotionStage5Data.StartPulse =10;  	//加速区間のパルス数
//	MotionStage5Data.MiddlePulse=50;	//等速区間のパルス数
//	MotionStage5Data.EndPulse   =10;  	//減速区間のパルス数
//
//	６．原点復帰移動　電源ＯＮ後の動作
//	MotionStage6Data.TargetCount=500;	//等速区間の速度になるカウンター数
//	MotionStage6Data.Direction  =0;		//回転方向　0 or 1
//	MotionStage6Data.StartPulse =10;  	//加速区間のパルス数
//	MotionStage6Data.MiddlePulse=200;	//等速区間のパルス数
//	MotionStage6Data.EndPulse   =10;  	//減速区間のパルス数
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

	//各種設定コマンド
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
	//等速区間の速度になるカウンター数
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
	//回転方向　0 or 1
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
	//加速区間のパルス数
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
	//等速区間のパルス数
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
	//減速区間のパルス数
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
    バージョンを返す
    buffは２５６バイト以内
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
    命令を送る
    DLLCmd   dllVar,CommandString,Wxx
    でこの関数が呼ばれる
    データを返すとき、*dataに値を格納すれば、「Wxx」に値が入る
    この関数の戻り値が、DLLCmdの結果フラグに反映される
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
    命令を送る
    DLLCmd   dllVar,CommandString,Wxx,Wxx
    でこの関数が呼ばれる
    データを返すとき、*dataに値を格納すれば、「Wxx」に値が入る
    この関数の戻り値が、DLLCmdの結果フラグに反映される
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
    終了処理
*/
{
	ControlMotioner	*ControlM=(ControlMotioner *)handle;
	delete	ControlM;
}

void	DLLSeq_DebugShow(void *handle ,QApplication &App)
{}
