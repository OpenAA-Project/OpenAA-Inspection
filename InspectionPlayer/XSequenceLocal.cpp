/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\InspectionPlayer\XSequenceLocal.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#define	_USE_MATH_DEFINES
#include <math.h>
#include "XSequenceLocal.h"
#include "XParamGlobal.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"
#include "XLightClass.h"
#include "XFormOperator.h"
#include "XLotInformation.h"
#include "XWriteResultThread.h"
#include "XResult.h"
#include "XEntryPoint.h"
//---------------------------------------------------------------------------


SeqControlParam::SeqControlParam(LayersBase *Base) 
:SeqLocalParam(Base)
{
	CaptureBeginFlag	=new bool[Base->GetPageNumb()];

	AllFinishInProcess=false;
	DoneCapture		=false;
	NotOutputResult	=false;

	SetSpecialOperand(&RepeatMode			,false	,1		,"Repeat Mode in true(1)");
	SetSpecialOperand(&StartInspection		,false	,2		,"Start Inspection in true(1). Sequence must reset this at the end of inspection");
	SetSpecialOperand(&StartScanOnly		,false	,3		,"Start scanning in true(1). Sequence must reset this at the end of scanning state");
	SetSpecialOperand(&ExecuteInspection	,false	,12		,"Start Inspection in true(1) from Sequence");
	SetSpecialOperand(&ExecuteScanMaster	,false	,13		,"Start Scan master in true(1) from Sequence");
	SetSpecialOperand(&InspectionStrategy	,0		,80		,"Current inspection Strategy number");
	SetSpecialOperand(&ReadyForScan			,false	,4		,"This indicates Ready-state for scanning and inspection. Sequence must wait till true(1).");
	SetSpecialOperand(&InspectionResult		,0		,101	,"This indicates OK:1 or NG:2. Sequence must set 0 at the end of inspection");
	SetSpecialOperand(&InspectionResultSub	,0		,105	,"This indicates OK:1 NG:2 3:TimeOver 4:MaxError 5:Halt."	,_ReadOnly);
	SetSpecialOperand(&InspectionFinalResult,0		,166	,"This indicates final OK:1 or NG:2. Sequence must set 0 at the end of inspection");
	SetSpecialOperand(&InspectionRemark		,0		,103	,"Remark number written in each inspection. Sequence can set");
	SetSpecialOperand(NULL					,false	,5		,"In true(1), sequence can stop inspection/scanning process anytime.");
	SetSpecialOperand(NULL					,false	,6		,"When HALT inspection occurs, this returns true(1)");
	SetSpecialOperand(NULL					,false	,7		,"Indicates automatic inspection mode."	,_ReadOnly);
	SetSpecialOperand(NULL					,false	,8		,"Indicate InspectionID changed."	,_ReadWrite);

	SetSpecialOperand(NULL					,0		,108	,"Light pattern No"									,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,21		,"Light turns on in true"							,_ReadWrite	);

	SetSpecialOperand(&InspectionID			,0		,102	,"Inspection ID."									,_ReadOnly	);
	SetSpecialOperand(&StageCode			,0		,104	,"Indicates inner process stage number."			,_ReadOnly	);
	SetSpecialOperand(NULL					,0		,106	,"Indicates inner State."							,_ReadOnly	);
	SetSpecialOperand(&CaptureMode			,0		,107	,"Indicate capture mode"							,_ReadWrite	);
	SetSpecialOperand(&WorkLeft				,0		,110	,"Indicates left position(micron) of work."			,_ReadOnly);
	SetSpecialOperand(&WorkTop				,0		,111	,"Indicates top position(micron) of work."			,_ReadOnly);
	SetSpecialOperand(&WorkRight			,1000	,112	,"Indicates right position(micron) of work."		,_ReadOnly);
	SetSpecialOperand(&WorkBottom			,1000	,113	,"Indicates bottom position(micron) of work."		,_ReadOnly);
	SetSpecialOperand(NULL					,0		,114	,"Indicates Lot ID number."							,_ReadOnly);
	SetSpecialOperand(NULL					,0		,115	,"Indicates Lot unique autocount number. Can set LOT information from sequence");
	SetSpecialOperand(NULL					,0		,116	,"Indicates Master data ID number. Can load Master information from sequence");
	SetSpecialOperand(NULL					,0		,117	,"Indicates Operator ID number."					,_ReadOnly);
	SetSpecialOperand(NULL					,0		,118	,"Indicates system cameras(quantity)."				,_ReadOnly);
	SetSpecialOperand(NULL					,0		,119	,"Indicates Dot counts per 1 camera image."			,_ReadOnly);
	SetSpecialOperand(NULL					,0		,120	,"Indicates Line counts per 1 camera image."		,_ReadOnly);
	SetSpecialOperand(NULL					,0		,121	,"Indicates Page count."							,_ReadOnly);
	SetSpecialOperand(NULL					,0		,122	,"Indicates Layer count."							,_ReadOnly);
	SetSpecialOperand(NULL					,0		,123	,"Indicates strategy counts."						,_ReadOnly);
	SetSpecialOperand(NULL					,0		,124	,"Indicates Resolution X direction(nano meter)."	,_ReadOnly);
	SetSpecialOperand(NULL					,0		,125	,"Indicates Resolution Y direction(nano meter)."	,_ReadOnly);
	SetSpecialOperand(NULL					,0		,126	,"Indicates Phase count."							,_ReadOnly);

	SetSpecialOperand(NULL					,0		,130	,"Indicates an inspected total count."	,_ReadWrite);
	SetSpecialOperand(NULL					,0		,131	,"Indicates an inspected OK count."		,_ReadOnly);
	SetSpecialOperand(NULL					,0		,132	,"Indicates an inspected NG count."		,_ReadOnly);
	SetSpecialOperand(&ResultIndex			,0		,133	,"Index for S134."						,_ReadWrite);
	SetSpecialOperand(NULL					,0		,134	,"Indicates an inspected result count."	,_ReadOnly);
	SetSpecialOperand(NULL					,0		,135	,"Indicates calculated time(mili seconds).",_ReadOnly);

	SetSpecialOperand(&InspectStartTime		,0		,136	,"Time(seconds) when inspection process starts");
	SetSpecialOperand(&DoneInspectTime		,0		,137	,"Time(seconds) when inspection process finishes");
	SetSpecialOperand(NULL					,0		,138	,"Current strategic number for capturing",_ReadWrite);
	SetSpecialOperand(NULL					,0		,139	,"Inspection Number",_ReadWrite);

	SetSpecialOperand(NULL					,4		,140	,"Result buffer depth");
	SetSpecialOperand(NULL					,false	,10		,"If sequence controls result to be saved ,this must be true(1)");
	SetSpecialOperand(NULL					,0		,141	,"ID mask-bit/mod-number when sequence controls result to be saved.");
	SetSpecialOperand(NULL					,false	,11		,"In true(1) if sequence controls result to be saved and ID cycles on decimal.");
	SetSpecialOperand(NULL					,0		,142	,"ID code when sequence controls result to be saved. Buffered Result in this ID is saved.");
	SetSpecialOperand(NULL					,0		,143	,"Finish mode. 1:All PC reboot, 2: Only this PC reboots");
	SetSpecialOperand(&PermitCapture		,false	,20		,"If true(1) , capture(including inspect) proceeds");
	SetSpecialOperand(NULL					,false	,23		,"If true(1) , found Form indexed Q17");
	SetSpecialOperand(NULL					,false	,24		,"If true(1) , Clear unsaved inspection data");

	SetSpecialOperand(NULL					,0		,150	,"Error count"									,_ReadWrite);
	SetSpecialOperand(&ErrorIndex			,0		,151	,"Index for Error"								,_ReadWrite);
	SetSpecialOperand(NULL					,0		,152	,"Error Level of indexed error"					,_ReadOnly);
	SetSpecialOperand(NULL					,0		,153	,"Error Code of indexed error"					,_ReadOnly);
	SetSpecialOperand(NULL					,0		,154	,"Written Result-ID"							,_ReadWrite);
	SetSpecialOperand(NULL					,0		,155	,"Minimum InspectionID not to be written yet"	,_ReadOnly);
	SetSpecialOperand(&CapturedFlag			,0		,156	,"Captured flag, Bit0:Page0, Bit1:Page1,,,,"	,_ReadWrite);
	SetSpecialOperand(NULL					,0		,157	,"Current Phase number"						,_ReadWrite);
	SetSpecialOperand(&CaptureStartCounter	,0		,158	,"CaptureStart counter"							,_ReadWrite);
	SetSpecialOperand(NULL					,0		,160	,"Max ScanPhase Count in system"				,_ReadOnly);
	SetSpecialOperand(NULL					,0		,161	,"Current ScanPhase Number in system"			,_ReadWrite);
	SetSpecialOperand(NULL					,0		,165	,"Force to change current strategic number"		,_WriteOnly);
	SetSpecialOperand(&LoadedMasterData		,false	,25		,"MasterData Loaded Flag"						,_ReadWrite);
	SetSpecialOperand(NULL					,false	,26		,"Flag of Capture started"						,_ReadWrite);
	SetSpecialOperand(NULL					,false	,27		,"Write out buffered oldest data"				,_ReadWrite);
	SetSpecialOperand(NULL					,0		,162	,"Remove buffered result from oldest"			,_ReadWrite);
	SetSpecialOperand(NULL					,0		,164	,"Result NG from Algorithm directly"			,_ReadWrite);
	SetSpecialOperand(&NowProcessing		,false	,28		,"True while processing after capture image"	,_ReadWrite);
	SetSpecialOperand(&AllFinishInProcess	,false	,29		,"Clear in all finish"							,_ReadWrite);
	SetSpecialOperand(&DoneCapture			,false	,30		,"Capture one time image"						,_ReadWrite);
	SetSpecialOperand(&NotOutputResult		,false	,32		,"1: Not output result and keep"				,_ReadWrite);

	SetSpecialOperand(&InspactionStatus		,0		,100	,"Indicate Inspection unit status"			,_ReadWrite	);
	SetSpecialOperand(&CancelCapturing		,0		,191	,"1:Cancel capturing"						,_ReadWrite	);

	SetSpecialOperand(&TactTimeMilisec		,4000	,501	,"TactTime (milisecond)"					,_ReadWrite	);
	SetSpecialOperand(&RailWidth			,1000	,502	,"RailWidth (mm)"							,_ReadWrite	);
	SetSpecialOperand(&ZHeight				,1000	,503	,"Z Height (um)"							,_ReadWrite	);

	SetSpecialOperand(&GeneralInfo0			,0		,300	,"General Information 0"					,_ReadWrite	);
	SetSpecialOperand(&GeneralInfo1			,0		,301	,"General Information 1"					,_ReadWrite	);
	SetSpecialOperand(&GeneralInfo2			,0		,302	,"General Information 2"					,_ReadWrite	);
	SetSpecialOperand(&GeneralInfo3			,0		,303	,"General Information 3"					,_ReadWrite	);
	SetSpecialOperand(&GeneralInfo4			,0		,304	,"General Information 4"					,_ReadWrite	);
	SetSpecialOperand(&GeneralInfo5			,0		,305	,"General Information 5"					,_ReadWrite	);
	SetSpecialOperand(&GeneralInfo6			,0		,306	,"General Information 6"					,_ReadWrite	);
	SetSpecialOperand(&GeneralInfo7			,0		,307	,"General Information 7"					,_ReadWrite	);
	SetSpecialOperand(&GeneralInfo8			,0		,308	,"General Information 8"					,_ReadWrite	);
	SetSpecialOperand(&GeneralInfo9			,0		,309	,"General Information 9"					,_ReadWrite	);

	// 移動位置設定レジスタ設定
	// モーター移動要求
	SetSpecialOperand(&VRSReqMoterMove	,0		,200	,"Moter Requirest"			,_ReadWrite	);

	// アフィン変換等などにより得られた結果を送信する
	SetSpecialOperand(&VRSPosX	,0		,201	,"X Absolute distance"		,_ReadWrite	);
	SetSpecialOperand(&VRSPosY	,0		,202	,"Y Absolute distance"		,_ReadWrite	);
	SetSpecialOperand(&VRSPosZ	,0		,203	,"Z Absolute distance"		,_ReadWrite	);

	// 読み込み専用のミリあたりのパルス数
	// 微動に関して使用する
	SetSpecialOperand(&VRSMoterPalusX	,0		,204	,"X Palus per millimeter"	,_ReadWrite	);
	SetSpecialOperand(&VRSMoterPalusY	,0		,205	,"Y Palus per millimeter"	,_ReadWrite	);
	SetSpecialOperand(&VRSMoterPalusZ	,0		,206	,"Z Palus per millimeter"	,_ReadWrite	);

	// モーターステータス設定
	// trueの時設定可能と判断
	SetSpecialOperand(&VRSMoterEnableX	,false	,100	,"Get X status"				,_ReadWrite	);
	SetSpecialOperand(&VRSMoterEnableX	,false	,101	,"Get Y status"				,_ReadWrite	);
	SetSpecialOperand(&VRSMoterEnableX	,false	,102	,"Get Z status"				,_ReadWrite	);

	SetSpecialOperand(&DoneControlGUI		,true		,22		,"Done to control GUI(Q10-)");
	SetSpecialOperand((volatile QString *)NULL	,"Master"	,1		,"Master Name"							,_ReadOnly	);
	SetSpecialOperand((volatile QString *)NULL	,"Lot"		,2		,"Lot Name"								,_ReadOnly	);
	SetSpecialOperand((volatile QString *)NULL	,"Worker"	,3		,"Worker Name"							,_ReadOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,4		,"Error Message of indexed error"		,_ReadOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,10		,"Click button"							,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,11		,"Select TableWidget "					,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,12		,"Input data in lineEdit"				,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,13		,"Input value in spinEdit"				,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,14		,"Check down"							,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,15		,"Check up"								,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,16		,"Check toggle"							,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,17		,"Form name for search"					,_ReadWrite	);
	SetSpecialOperand((volatile QString *)NULL	,""			,18		,"Visible widget"						,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,19		,"Invisible widget"						,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,20		,"Enable widget"						,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,21		,"Disable widget"						,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,22		,"ToolButton Down"						,_WriteOnly	);
	SetSpecialOperand((volatile QString *)NULL	,""			,50		,"Delivered information for result"		,_ReadWrite	);

	QWidget	*W=GetLayersBase()->GetMainWidget();
	W->connect(this,SIGNAL(SignalButtonClick(QString ,QString))				,this,SLOT(SlotButtonClick(QString,QString))				,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalTableWidgetSelect(QString,QString,int,int)),this,SLOT(SlotTableWidgetSelect(QString,QString,int,int))	,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalInputEdit(QString,QString,QString))		,this,SLOT(SlotInputEdit(QString,QString,QString))			,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalInputValue(QString,QString,int))			,this,SLOT(SlotInputValue(QString,QString,int))				,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalCheckDown(QString ,QString))				,this,SLOT(SlotCheckDown(QString,QString))					,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalCheckUp(QString ,QString))					,this,SLOT(SlotCheckUp(QString,QString))					,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalCheckToggle(QString ,QString))				,this,SLOT(SlotCheckToggle(QString,QString))				,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalSearchForm(QString))						,this,SLOT(SlotSearchForm(QString))							,Qt::QueuedConnection);

	W->connect(this,SIGNAL(SignalVisilize(QString ,QString))				,this,SLOT(SlotVisilize(QString,QString))					,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalInvisilize(QString ,QString))				,this,SLOT(SlotInvisilize(QString,QString))					,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalEnable(QString ,QString))					,this,SLOT(SlotEnable(QString,QString))						,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalDisable(QString ,QString))					,this,SLOT(SlotDisable(QString,QString))					,Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalButtonDown(QString ,QString))				,this,SLOT(SlotButtonDown(QString,QString))					,Qt::QueuedConnection);

	W->connect(this,SIGNAL(SignalFinishMode(int))							,this,SLOT(SlotFinishMode(int)),Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalInspectionNumber(int))						,this,SLOT(SlotInspectionNumber(int)),Qt::QueuedConnection);

	W->connect(this,SIGNAL(SignalSetCurrentPhaseScanNumber(int))			,this,SLOT(SlotSetCurrentPhaseScanNumber(int)),Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalForceStrategicNumber(int))					,this,SLOT(SlotForceStrategicNumber(int)),Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalForceToChangeCurrentStrategicNumber(int))	,this,SLOT(SlotForceToChangeCurrentStrategicNumber(int)),Qt::QueuedConnection);

	W->connect(this,SIGNAL(SignalLightOn())									,this,SLOT(SlotLightOn()),Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalLightOff())								,this,SLOT(SlotLightOff()),Qt::QueuedConnection);
	DoneControlGUI=true;
}
SeqControlParam::~SeqControlParam(void)
{
	delete	[]CaptureBeginFlag;
	CaptureBeginFlag=NULL;
}
void	SeqControlParam::SetDataSpecialOperand(int ID, int d)
{
	switch(ID){
		case 108:	if(GetLayersBase()->GetLightBase()!=NULL){
						GetLayersBase()->GetLightBase()->SetPattern(d);
					}
					break;
		case 114:	//GetLayersBase()->GetLot()->SetLotID(QString::number(d));
					break;
		case 115:	//GetLayersBase()->GetLot()->SetLotAutoCount(d);
					break;
		case 116:	GetLayersBase()->SetMasterCode(d);
					break;
		case 117:	GetLayersBase()->SetWorkerID(d);
					break;
		case 118:	break;
		case 130:	GetLayersBase()->GetResultHistryData()->SetMaxCount(d);
					break;
		case 138:	//GetLayersBase()->SetCurrentStrategicNumberForSeq(d);
					//GetLayersBase()->ForceStrategicNumber(d);
					emit	SignalForceStrategicNumber(d);
					break;
		case 139:	GetLayersBase()->SetInspectionNumber(d);
					emit SignalInspectionNumber(d);
					break;
		case 141:	GetLayersBase()->GetResultThread()->SetIDMaskBit(d);
					break;
		case 142:	GetLayersBase()->GetResultThread()->SetIDtoWriteOut(d);
					break;
		case 143:	emit	SignalFinishMode(d);
					break;
		case 150:	if(d==0){
						GetLayersBase()->ClearErrorCount();
					}
					break;
		case 154:	GetLayersBase()->SetResultWrittenID(d);
					break;
		case 157:	GetLayersBase()->SetCurrentPhase(d);
					break;
		case 161:	emit	SignalSetCurrentPhaseScanNumber(d);
					break;
		case 162:	GetLayersBase()->RemoveResultFromOldest(d);
					break;
		case 164:	GetLayersBase()->SetResultFromAlgorithm(d);
					break;
		case 165:	emit	SignalForceToChangeCurrentStrategicNumber(d);
					break;
		default:
					SeqLocalParam::SetDataSpecialOperand(ID, d);
	}
}
int		SeqControlParam::GetDataSpecialOperand(int ID)	const
{
	ErrorCodeList	ErrorData;
	switch(ID){
		//case 102:	return GetLayersBase()->GetCurrentInspectIDForExecute();
		case 106:	if(GetLayersBase()->GetEntryPoint()==NULL || GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL){
						return 0;
					}
					return (int)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetState();
		case 108:	if(GetLayersBase()->GetLightBase()!=NULL){
						return GetLayersBase()->GetLightBase()->GetPatternNo();
					}
					return 0;
		case 114:	return GetLayersBase()->GetLotBase()->GetLotID().toInt();
		case 115:	if(GetLayersBase()->GetLot(0)!=NULL)
						return GetLayersBase()->GetLot(0)->GetLotAutoCount();
					return -1;
		case 116:	return GetLayersBase()->GetMasterCode();
		case 117:	return GetLayersBase()->GetWorkerID();
		case 118:	return GetLayersBase()->GetParamGlobal()->TotalCameraNumb;
		case 119:	return GetLayersBase()->GetParamGlobal()->DotPerLine;
		case 120:	return GetLayersBase()->GetParamGlobal()->MaxLines;
		case 121:	return GetLayersBase()->GetParamGlobal()->PageNumb;
		case 122:	return GetLayersBase()->GetParamGlobal()->LayerNumb;
		case 123:	return GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy();
		case 124:	return GetLayersBase()->GetParamGlobal()->ResolutionXNano;
		case 125:	return GetLayersBase()->GetParamGlobal()->ResolutionYNano;
		case 126:	return GetLayersBase()->GetParamGlobal()->GetPhaseNumb();

		case 130:	return GetLayersBase()->GetResultHistryData()->GetAllCount();
		case 131:	return GetLayersBase()->GetResultHistryData()->GetCount(1);
		case 132:	return GetLayersBase()->GetResultHistryData()->GetCount(2);
		case 134:	return GetLayersBase()->GetResultHistryData()->GetCount(ResultIndex);
		case 135:	return GetLayersBase()->GetInspectionTimeMilisec();
		case 136:	return GetLayersBase()->GetStartInspectTime().to64();
		case 137:	return GetLayersBase()->GetEndInspectionTime().to64();
		case 138:	return GetLayersBase()->GetCurrentStrategicNumberForSeq();
		case 139:	return GetLayersBase()->GetInspectionNumber();
		case 140:	return GetLayersBase()->GetResultThread()->GetStockedCount();
		case 141:	return GetLayersBase()->GetResultThread()->GetIDMaskBit();
		case 142:	return GetLayersBase()->GetResultThread()->GetIDtoWriteOut();
		case 150:	return GetLayersBase()->GetErrorCount();
		case 152:	if(GetLayersBase()->GetError(ErrorIndex,ErrorData)==true){
						return (int)ErrorData.GetLevel();
					}
					return -1;
		case 153:	if(GetLayersBase()->GetError(ErrorIndex,ErrorData)==true){
						return (int)ErrorData.GetErrorCode();
					}
					return -1;
		case 154:	return GetLayersBase()->GetResultWrittenID();
		case 155:	return GetLayersBase()->GetUnsavedMinimumID();
		case 157:	return GetLayersBase()->GetCurrentPhase();

		case 160:	return GetLayersBase()->GetParamGlobal()->GetScanPhaseCount();
		case 161:	return GetLayersBase()->GetCurrentScanPhaseNumber();
		case 164:	return GetLayersBase()->GetResultFromAlgorithm();
		case 165:	return GetLayersBase()->GetCurrentStrategicNumberForSeq();
		default:
					return SeqLocalParam::GetDataSpecialOperand(ID);
	}
}
void	SeqControlParam::SetDataSpecialBitOperand(int ID, bool d)
{
	switch(ID){
		//case 2:		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->StartInspection=d;
		//			break;
		//case 3:		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->StartScanOnly=d;
		//			break;
		case 5:		if(d==false){
						GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->ClearHaltMode();
					}
					else{
						GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoHalt();
					}
					break;
		case 8:		if(d==true){
						GetLayersBase()->SetForceChangedInspectID();
					}
					else{
						GetLayersBase()->ResetForceChangedInspectID();
					}
					break;
					
		case 10:	GetLayersBase()->GetResultThread()->SetEnabledStockedWrite(d);
					break;
		case 11:	GetLayersBase()->GetResultThread()->SetIDMaskMode10Base(d);
					break;
		case 21:	if(GetLayersBase()->GetLightBase()!=NULL){
						if(d==true){
							emit	SignalLightOn();
						}
						else{
							emit	SignalLightOff();
						}
					}
					break;
		case 24:	if(d==true){
						GetLayersBase()->GetResultThread()->SetCastAll();
					}
					break;
		case 26:
					if(d==false){
						ClearCaptureBeginFlag();
					}
					break;
		case 27:	if(d==true){
						GetLayersBase()->GetResultThread()->SetWriteOldestOne();
					}
					break;
		default:
					SeqLocalParam::SetDataSpecialBitOperand(ID, d);
	}
}
	
void	SeqControlParam::SlotLightOn()
{
	GetLayersBase()->GetLightBase()->LightOn();
}

void	SeqControlParam::SlotLightOff()
{
	GetLayersBase()->GetLightBase()->LightOff();
}

bool	SeqControlParam::GetDataSpecialBitOperand(int ID)	const
{
	ResultInspection	*DRes;
	bool	b;

	switch(ID){
		//case 2:	return GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->StartInspection;
		//case 3:	return GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->StartScanOnly;

		case 5:
				if(GetLayersBase()==NULL
				|| GetLayersBase()->GetEntryPoint()==NULL
				|| GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL){
					return false;
				}
				b=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetHaltMode();
				if(b==true){
					GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->ClearHaltMode();
				}
				return b;
		case 6:	DRes=GetLayersBase()->GetCurrentResultForDraw();
				if(DRes!=NULL){
					if(DRes->GetTimeOutBreak()==true
					|| DRes->GetMaxErrorBreak()==true){
						return true;
					}
					else{
						return false;
					}
				}
				return false;
				
		case 7:	if(GetLayersBase()==NULL
				|| GetLayersBase()->GetEntryPoint()==NULL
				|| GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL){
					return false;
				}
				if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat()==ExecuteInspectBase::_AutoCaptureInspect){
					return true;
				}
				else{
					return false;
				}
		case 8:
				return GetLayersBase()->GetForceChangedInspectID();
		case 10:	return GetLayersBase()->GetResultThread()->GetEnabledStockedWrite();
		case 11:	return GetLayersBase()->GetResultThread()->GetIDMaskMode10Base();
		case 21:	if(GetLayersBase()->GetLightBase()!=NULL){
						return GetLayersBase()->GetLightBase()->IsTurnOn();
					}
					return false;
		case 23:return FoundForm;
		case 26:
				return DoesCaptureBegin();
		case 27:
				return GetLayersBase()->GetResultThread()->IsWrittenOldestOne();
		default:
					return SeqLocalParam::GetDataSpecialBitOperand(ID);
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
		DoneControlGUI=false;
		emit	SignalButtonDown(formname ,controlname);
	}
	else if(ID==50){
		GetLayersBase()->GetResultThread()->SetDeliveredInfo(d);
	}

	else{
		SeqLocalParam::SetDataSpecialStringOperand(ID, d);
	}
}
QString SeqControlParam::GetDataSpecialStringOperand(int ID)	const
{
	ErrorCodeList	ErrorData;
	switch(ID){
		case 1:	return GetLayersBase()->GetMasterName();
		case 2:	return GetLayersBase()->GetLotBase()->GetLotName();
		case 3:	return GetLayersBase()->GetWorkerName();
		case 4:	if(GetLayersBase()->GetError(ErrorIndex,ErrorData)==true){
					return ErrorData.GetMessageStr();
				}
				return QString("");
		case 5:	if(GetLayersBase()->GetError(ErrorIndex,ErrorData)==true){
					return ErrorData.GetErrorTime().toString("yyyy/MM/dd hh:mm:ss");
				}
				return QString("");
		case 50:
				return GetLayersBase()->GetResultThread()->GetDeliveredInfo();

		default:
				return SeqLocalParam::GetDataSpecialStringOperand(ID);
	}
}

void	SeqControlParam::SlotButtonClick(QString formname ,QString controlname)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.ButtonPush(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotTableWidgetSelect(QString formname ,QString controlname,int row ,int col)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.TableSelect(formname ,controlname,row ,col);
	DoneControlGUI=true;
}
void	SeqControlParam::SlotInputEdit(QString formname ,QString controlname,QString data)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.InputEdit(formname ,controlname,data);
	DoneControlGUI=true;
}
void	SeqControlParam::SlotInputValue(QString formname ,QString controlname,int data)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.InputValue(formname ,controlname,data);
	DoneControlGUI=true;
}
void	SeqControlParam::SlotCheckDown(QString formname ,QString controlname)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.CheckboxChecked(formname ,controlname);
	DoneControlGUI=true;
}
void	SeqControlParam::SlotCheckUp(QString formname ,QString controlname)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.CheckboxUnchecked(formname ,controlname);
	DoneControlGUI=true;
}
void	SeqControlParam::SlotCheckToggle(QString formname ,QString controlname)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.CheckboxToggle(formname ,controlname);
	DoneControlGUI=true;
}
void	SeqControlParam::SlotVisilize(QString formname ,QString controlname)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.SetVisible(formname ,controlname);
	DoneControlGUI=true;
}
void	SeqControlParam::SlotInvisilize(QString formname ,QString controlname)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.SetInvisible(formname ,controlname);
	DoneControlGUI=true;
}
void	SeqControlParam::SlotEnable(QString formname ,QString controlname)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.SetEnabled(formname ,controlname);
	DoneControlGUI=true;
}
void	SeqControlParam::SlotDisable(QString formname ,QString controlname)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.SetDisabled(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotButtonDown(QString formname ,QString controlname)
{
	FormOperator	F(GetLayersBase()->GetMainWidget());
	F.ButtonDown(formname ,controlname);
	DoneControlGUI=true;
}

void	SeqControlParam::SlotInspectionNumber(int Number)
{
	GetLayersBase()->BroadcastInspectionNumber();
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
	FormOperator	F(GetLayersBase()->GetMainWidget());
	if(F.ExistForm(formname)==true){
		FoundForm=true;
	}
	else{
		FoundForm=false;
	}
}

void	SeqControlParam::SlotSetCurrentPhaseScanNumber(int d)
{
	GetLayersBase()->TF_SetCurrentScanPhaseNumber(d);
}

void	SeqControlParam::SlotForceStrategicNumber(int d)
{
	//GetLayersBase()->ForceStrategicNumber(d);
	GetLayersBase()->SetCurrentStrategicNumberForSeq(d);
}

void	SeqControlParam::SlotForceToChangeCurrentStrategicNumber(int d)
{
	GetLayersBase()->ForceStrategicNumber(d);
	GetLayersBase()->SetCurrentStrategicNumberInExe(d);
}

void	SeqControlParam::SetCaptureBegins(int page)
{
	CaptureBeginFlag[page]=true;
}

bool	SeqControlParam::DoesCaptureBegin(void)	const
{
	//戦略番号を考慮するべき

	for(int page=0;page<GetPageNumb();page++){
		if(CaptureBeginFlag[page]==true){
			return true;
		}
	}
	return false;
}

void	SeqControlParam::ClearCaptureBeginFlag(void)
{
	for(int page=0;page<GetPageNumb();page++){
		CaptureBeginFlag[page]=false;
	}
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

void	SeqControlParam::Captured(int Page)
{
	CapturedFlag |= 0x01<<Page;
}
