/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\XSequenceRepairLocal.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#define	_USE_MATH_DEFINES
#include <math.h>
#include "XSequenceRepairLocal.h"
#include "XParamGlobal.h"
#include "XDataInExe.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"
#include "XFormOperator.h"

//---------------------------------------------------------------------------


SeqControlParam *SeqControlParamData;

SeqControlParam::SeqControlParam(LayersBase *Base,QWidget *Form) 
:SeqLocalParam(Base)
{
	// 移動位置設定レジスタ設定
	// モーター移動要求
	SetSpecialOperand(&MoterRequire		,0		,200	,"Moter Requirest"			,_ReadWrite	);

	// アフィン変換等などにより得られた結果を送信する(計算は外部で行う)
	SetSpecialOperand(&XPosition		,0		,201	,"X Absolute distance"			,_ReadWrite	);
	SetSpecialOperand(&YPosition		,0		,202	,"Y Absolute distance"			,_ReadWrite	);
	SetSpecialOperand(&ZPosition		,0		,203	,"Z Absolute distance"			,_ReadWrite	);

	// 読み込み専用のミリあたりのパルス数
	// 微動に関して使用する
	SetSpecialOperand(&XMoterPulsePerMM	,0		,204	,"X Palus per millimeter"				,_ReadWrite	);
	SetSpecialOperand(&YMoterPulsePerMM	,0		,205	,"Y Palus per millimeter"				,_ReadWrite	);
	SetSpecialOperand(&ZMoterPulsePerMM	,0		,206	,"Z Palus per millimeter"				,_ReadWrite	);
	SetSpecialOperand(&Side				,0		,207	,"Target side (1:Top ,2:Bottom ...)"	,_ReadWrite	);
	SetSpecialOperand(&InspectionID		,0		,208	,"Current inspection ID"				,_ReadWrite	);
	SetSpecialOperand(&MasterID			,0		,209	,"Current Master ID"					,_ReadWrite	);
	SetSpecialOperand(&LotAutoCount		,0		,210	,"Current Lot AutoCount in Front side"	,_ReadWrite	);

	// モーターステータス設定
	// trueの時設定可能と判断
	SetSpecialOperand(&XMoterStatus		,false		,100	,"Get X status"					,_ReadWrite	);
	SetSpecialOperand(&YMoterStatus		,false		,101	,"Get Y status"					,_ReadWrite	);
	SetSpecialOperand(&ZMoterStatus		,false		,102	,"Get Z status"					,_ReadWrite	);

	SetSpecialOperand(&MoveMode			,0		,107	,"Indicates move mode"			,_ReadWrite	);
	SetSpecialOperand(&ReviewResult		,0		,110	,"Result of review"				,_ReadWrite	);
	SetSpecialOperand(&NGPieceNumbers	,0		,111	,"NG piece numbers of review"	,_ReadWrite	);
	SetSpecialOperand(&ErrorCount		,0		,150	,"Error count"					,_ReadWrite);
	SetSpecialOperand(&ErrorIndex		,0		,151	,"Index for Error"				,_ReadWrite);
	SetSpecialOperand(&ErrorCode		,0		,153	,"Error Code"					,_ReadWrite);
	SetSpecialOperand(&MacErrorCode		,0		,154	,"Machine Error Code"			,_ReadWrite);
	SetSpecialOperand(&InspectionNumb	,0		,160	,"Current Inspection Numb"		,_ReadWrite);
	SetSpecialOperand(&PCStandBy		,false	,10		,"PC Standby flag"				,_ReadWrite	);
	SetSpecialOperand(&ErrNextBS		,false	,32		,"Error next button SW"			,_ReadWrite	);
	SetSpecialOperand(&NGBS				,false	,33		,"NG button SW"					,_ReadWrite	);
	SetSpecialOperand(&BackBS			,false	,34		,"Back button SW"				,_ReadWrite	);
	SetSpecialOperand(&ReviewFinished	,true	,35		,"One review finished"			,_ReadWrite	);
	SetSpecialOperand(&UnloadDone		,false	,36		,"Unload Done"					,_ReadWrite	);
	SetSpecialOperand(&UnloadCloseDone	,false	,37		,"Unload close Done"			,_ReadWrite	);
	SetSpecialOperand(&MaxOver			,false	,38		,"Inspecte result is MaxOver"	,_ReadWrite	);
	SetSpecialOperand(&MacEmergency		,false	,40		,"Machine Emergency"			,_ReadWrite	);
	SetSpecialOperand(&SoftEmergency	,false	,41		,"Software Emergency"			,_ReadWrite	);
	SetSpecialOperand(&MacIDMismatch	,false	,42		,"Machine ID Mismatch"			,_ReadWrite	);
//	SetSpecialOperand(&WaitTime			,0		,220	,"Wait time (ms)"				,_ReadWrite	);
	SetSpecialOperand(NULL				,0		,143	,"Finish mode. 1:All PC reboot, 2: Only this PC reboots");

	SetSpecialOperand(&DoneControlGUI	,true	,30		,"Done to control GUI(Q10-)");
	SetSpecialOperand(NULL				,false	,31		,"If true(1) , found Form indexed Q17");
	SetSpecialOperand(&LotName			,/**/""		,2		,"Lot Name"						,_ReadWrite	);
	SetSpecialOperand(NULL				,/**/""		,10		,"Click button"					,_WriteOnly	);
	SetSpecialOperand(NULL				,/**/""		,11		,"Select TableWidget "			,_WriteOnly	);
	SetSpecialOperand(NULL				,/**/""		,12		,"Input data in lineEdit"		,_WriteOnly	);
	SetSpecialOperand(NULL				,/**/""		,13		,"Input value in spinEdit"		,_WriteOnly	);
	SetSpecialOperand(NULL				,/**/""		,14		,"Check down"					,_WriteOnly	);
	SetSpecialOperand(NULL				,/**/""		,15		,"Check up"						,_WriteOnly	);
	SetSpecialOperand(NULL				,/**/""		,16		,"Check toggle"					,_WriteOnly	);
	SetSpecialOperand(NULL				,/**/""		,17		,"Form name for search"			,_ReadWrite	);
//	SetSpecialOperand(NULL				,/**/""		,18		,"Select TableWidget by search"	,_WriteOnly	);
	SetSpecialOperand(NULL				,/**/""		,18		,"Widget visible"				,_ReadWrite	);
	SetSpecialOperand(NULL				,/**/""		,19		,"Widget invisible"				,_ReadWrite	);
	SetSpecialOperand(NULL				,/**/""		,20		,"Widget enable"				,_ReadWrite	);
	SetSpecialOperand(NULL				,/**/""		,21		,"Widget disable"				,_ReadWrite	);
	SetSpecialOperand(NULL				,/**/""		,22		,"Search & Select TableWidget "	,_WriteOnly	);

	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalButtonClick(QString ,QString))				,this,SLOT(SlotButtonClick(QString,QString))				,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalTableWidgetSelect(QString,QString,int,int))	,this,SLOT(SlotTableWidgetSelect(QString,QString,int,int))	,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalInputEdit(QString,QString,QString))			,this,SLOT(SlotInputEdit(QString,QString,QString))			,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalInputValue(QString,QString,int))			,this,SLOT(SlotInputValue(QString,QString,int))				,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalCheckDown(QString ,QString))				,this,SLOT(SlotCheckDown(QString,QString))					,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalCheckUp(QString ,QString))					,this,SLOT(SlotCheckUp(QString,QString))					,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalCheckToggle(QString ,QString))				,this,SLOT(SlotCheckToggle(QString,QString))				,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalSearchForm(QString))						,this,SLOT(SlotSearchForm(QString))							,Qt::QueuedConnection);
	
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalFinishMode(int))							,this,SLOT(SlotFinishMode(int))								,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalVisilize(QString ,QString))					,this,SLOT(SlotVisilize(QString,QString))					,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalInvisilize(QString ,QString))				,this,SLOT(SlotInvisilize(QString,QString))					,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalEnable(QString ,QString))					,this,SLOT(SlotEnable(QString,QString))						,Qt::QueuedConnection);
	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalDisable(QString ,QString))					,this,SLOT(SlotDisable(QString,QString))					,Qt::QueuedConnection);

	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalTableItemSearchSelect(QString,QString,int,QString))	,this,SLOT(SlotTableItemSearchSelect(QString,QString,int,QString)),Qt::QueuedConnection);

	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalFinishMode(int)),this,SLOT(SlotFinishMode(int)),Qt::QueuedConnection);
	DoneControlGUI=true;

	RepairMainForm=Form;
}

void	SeqControlParam::SetDataSpecialOperand(int ID, int d)
{
	switch(ID){
//		case 107:	break;
//		case 158:	break;
//		case 200:	break;
//		case 201:	break;
//		case 202:	break;
		case 143:
			emit	SignalFinishMode(d);
			break;
		default:	SeqLocalParam::SetDataSpecialOperand(ID, d);
	}
}

int		SeqControlParam::GetDataSpecialOperand(int ID)
{
	switch(ID){
//		case 107:	return;
//		case 158:	return;
//		case 200:	return;
//		case 201:	return;
//		case 202:	return;
		default:	return SeqLocalParam::GetDataSpecialOperand(ID);
	}
}

void	SeqControlParam::SetDataSpecialBitOperand(int ID, bool d)
{
	switch(ID){
//		case 107:	break;
//		case 158:	break;
//		case 200:	break;
//		case 201:	break;
//		case 202:	break;
		default:	SeqLocalParam::SetDataSpecialBitOperand(ID, d);
	}
}

bool	SeqControlParam::GetDataSpecialBitOperand(int ID)
{
	switch(ID){
		case 31:return FoundForm;
		default:	return SeqLocalParam::GetDataSpecialBitOperand(ID);
	}
}

void	SeqControlParam::SetDataSpecialStringOperand(int ID, QString d)
{
	if(ID==10){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		DoneControlGUI=false;
		emit	SignalButtonClick(formname ,controlname);
	}
	else if(ID==11){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		bool	ok;
		int	row=d.section(',',2,2).toInt(&ok);
		if(ok==true){
			int	col=d.section(',',3,3).toInt(&ok);
			if(ok==true){
				DoneControlGUI=false;
				emit	SignalTableWidgetSelect(formname ,controlname,row,col);
			}
		}
	}
	else if(ID==12){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		QString	Data		=d.section(',',2);
		DoneControlGUI=false;
		emit	SignalInputEdit(formname ,controlname,Data);
	}
	else if(ID==13){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		bool	ok;
		int	Value			=d.section(',',2,2).toInt(&ok);
		if(ok==true){
			DoneControlGUI=false;
			emit	SignalInputValue(formname ,controlname,Value);
		}
	}
	else if(ID==14){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		DoneControlGUI=false;
		emit	SignalCheckDown(formname ,controlname);
	}
	else if(ID==15){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		DoneControlGUI=false;
		emit	SignalCheckUp(formname ,controlname);
	}
	else if(ID==16){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		DoneControlGUI=false;
		emit	SignalCheckToggle(formname ,controlname);
	}
	else if(ID==17){
		FoundForm=false;
		DoneControlGUI=false;
		emit	SignalSearchForm(d);
	}
	else if(ID==18){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		DoneControlGUI=false;
		emit	SignalVisilize(formname ,controlname);
	}
	else if(ID==19){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		DoneControlGUI=false;
		emit	SignalInvisilize(formname ,controlname);
	}
	else if(ID==20){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		DoneControlGUI=false;
		emit	SignalEnable(formname ,controlname);
	}
	else if(ID==21){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		DoneControlGUI=false;
		emit	SignalDisable(formname ,controlname);
	}
	else if(ID==22){
		QString	formname	=d.section(',',0,0);
		QString	controlname	=d.section(',',1,1);
		bool	ok;
		int	col=d.section(',',2,2).toInt(&ok);
		if(ok==true){
			QString	searchstr	=d.section(',',3,3);
			emit	SignalTableItemSearchSelect(formname ,controlname,col,searchstr);
		}
	}
	else{
		SeqLocalParam::SetDataSpecialStringOperand(ID, d);
	}
}

QString SeqControlParam::GetDataSpecialStringOperand(int ID)
{
	return SeqLocalParam::GetDataSpecialStringOperand(ID);
}

void	SeqControlParam::SlotButtonClick(QString formname ,QString controlname)
{
	FormOperator	F(RepairMainForm);
	F.ButtonPush(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotTableWidgetSelect(QString formname ,QString controlname,int row ,int col)
{
	FormOperator	F(RepairMainForm);
	F.TableSelect(formname ,controlname,row ,col);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotInputEdit(QString formname ,QString controlname,QString data)
{
	FormOperator	F(RepairMainForm);
	F.InputEdit(formname ,controlname,data);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotInputValue(QString formname ,QString controlname,int data)
{
	FormOperator	F(RepairMainForm);
	F.InputValue(formname ,controlname,data);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotCheckDown(QString formname ,QString controlname)
{
	FormOperator	F(RepairMainForm);
	F.CheckboxChecked(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotCheckUp(QString formname ,QString controlname)
{
	FormOperator	F(RepairMainForm);
	F.CheckboxUnchecked(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotCheckToggle(QString formname ,QString controlname)
{
	FormOperator	F(RepairMainForm);
	F.CheckboxToggle(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotVisilize(QString formname ,QString controlname)
{
	FormOperator	F(RepairMainForm);
	F.SetVisible(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotInvisilize(QString formname ,QString controlname)
{
	FormOperator	F(RepairMainForm);
	F.SetInvisible(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotEnable(QString formname ,QString controlname)
{
	FormOperator	F(RepairMainForm);
	F.SetEnabled(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotDisable(QString formname ,QString controlname)
{
	FormOperator	F(RepairMainForm);
	F.SetDisabled(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotTableItemSearchSelect(QString formname ,QString controlname,int col,QString serachstr)
{
	FormOperator	F(RepairMainForm);
	F.TableItemSearchSelect(formname ,controlname,col ,serachstr);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotFinishMode(int mode)
{
	if(mode==1){
		GetLayersBase()->CloseAll();
	}
	else if(mode==2){
		GetLayersBase()->CloseOne();
	}
}

void	SeqControlParam::SlotSearchForm(QString formname)
{
	FormOperator	F(RepairMainForm);
	if(F.ExistForm(formname)==true)
		FoundForm=true;
	else
		FoundForm=false;
}

//FifoIntPacket     SeqControlParam::SeqWriteID;

void    _XSeqLocalInit(SeqLocalParam *param ,SeqControl *seqControl)
{
	param->XSeqLocalInit(seqControl);
}

void    _SetDataSpecialOperand(SeqLocalParam *param ,int ID, int d)
{
	param->SetDataSpecialOperand(ID, d);
}

int     _GetDataSpecialOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialOperand(ID));
}

void    _SetDataSpecialBitOperand(SeqLocalParam *param ,int ID,bool d)
{
	param->SetDataSpecialBitOperand(ID, d);
}
bool     _GetDataSpecialBitOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialBitOperand(ID));
}

void _SetDataSpecialStringOperand(SeqLocalParam *param ,int ID, QString d)
{
	param->SetDataSpecialStringOperand(ID, d);
}

QString  _GetDataSpecialStringOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialStringOperand(ID));
}

void _SetDataSpecialFloatOperand(SeqLocalParam *param ,int ID, double d)
{
	param->SetDataSpecialFloatOperand(ID, d);
}

double  _GetDataSpecialFloatOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialFloatOperand(ID));
}