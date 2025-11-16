#include "ShowResultAlarmResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowResultAlarm\ShowResultAlarm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowResultAlarm.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XLotInformation.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"ResultAlarm";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for alarm");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqResult	(Base,sRoot,sName);
	(*Base)=new GUICmdSendResult	(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowResultAlarm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QFont";
	Data[0].VariableNameWithRoute=/**/"MessageSize";
	Data[0].Pointer				 =&((ShowResultAlarm *)Instance)->MessageSize;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"ColorOK";
	Data[1].Pointer				 =&((ShowResultAlarm *)Instance)->ColorNormal;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"ColorNG";
	Data[2].Pointer				 =&((ShowResultAlarm *)Instance)->ColorAlarm;
	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"MsgOK";
	Data[3].Pointer				 =&((ShowResultAlarm *)Instance)->MsgNormal;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"MsgNG";
	Data[4].Pointer				 =&((ShowResultAlarm *)Instance)->MsgAlarm;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"AlarmNGCountInOneResult";
	Data[5].Pointer				 =&((ShowResultAlarm *)Instance)->AlarmNGCountInOneResult;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"AlarmNGContinuous";
	Data[6].Pointer				 =&((ShowResultAlarm *)Instance)->AlarmNGContinuous;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"SystemRegisterNo";
	Data[7].Pointer				 =&((ShowResultAlarm *)Instance)->SystemRegisterNo;

	return(8);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowResultAlarm.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ShowResultAlarm::ShowResultAlarm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SystemRegisterNo=51;
	ioMode			=NULL;

	ColorNormal	=Qt::green;
	ColorAlarm	=Qt::red;
	MsgNormal	=/**/"OK";
	MsgAlarm	=/**/"Alarm";
	resize(250,250);

	AlarmNGCountInOneResult	=10;
	AlarmNGContinuous		=3;

	ContinuousNG		=0;
	CurrentNGCount		=0;
}

void	ShowResultAlarm::Prepare(void)
{
	ShowInPlayer(-1);

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMode		=new SignalOperandBit(this,SystemRegisterNo,/**/"ShowResultAlarm:ioMode");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMode,&Error)==false){
				ioMode->ShowErrorMessage(Error);
			}
		}
	}
}

void	ShowResultAlarm::ShowInPlayer(int64 shownInspectionID)
{
	bool	ResultOk=true;
	CurrentNGCount=0;

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqResult		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.ShownInspectionID=shownInspectionID;
		GUICmdSendResult		CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
			if(CmdAck.ResultOk==false){
				ResultOk=false;
			}
			CurrentNGCount+=CmdAck.NGCount;
		}
	}
	if(ResultOk==false){
		if(LastLotAutoCountList==GetLayersBase()->GetLotBase()->GetLotAutoCount()){
			ContinuousNG++;
		}
		else{
			ContinuousNG=1;
		}
	}
	else{
		ContinuousNG=0;
	}
	LastLotAutoCountList=GetLayersBase()->GetLotBase()->GetLotAutoCount();

	repaint();
}
void	ShowResultAlarm::paintEvent ( QPaintEvent * event )
{
	QPainter	pnt(this);

	pnt.setFont(MessageSize);
	QString	Msg;
	if(CurrentNGCount>=AlarmNGCountInOneResult
	|| ContinuousNG>=AlarmNGContinuous){
		QBrush	B(ColorAlarm);
		Msg=MsgAlarm;
		pnt.fillRect(0,0,width(),height(),B);
		if(ioMode!=NULL){
			ioMode->Set(true);
		}
	}
	else{
		QBrush	B(ColorNormal);
		Msg=MsgNormal;
		pnt.fillRect(0,0,width(),height(),B);
		if(ioMode!=NULL){
			ioMode->Set(false);
		}
	}

	QBrush	B(Qt::black);
	pnt.setBrush(B);
	pnt.drawText(0,0,width(),height(),Qt::AlignHCenter | Qt::AlignVCenter ,Msg);
}

//=====================================================================================
GUICmdReqResult::GUICmdReqResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqResult::Load(QIODevice *f)
{
	if(::Load(f,ShownInspectionID)==false)
		return false;
	return true;
}
bool	GUICmdReqResult::Save(QIODevice *f)
{
	if(::Save(f,ShownInspectionID)==false)
		return false;
	return true;
}

void	GUICmdReqResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendResult	*SendBack=GetSendBack(GUICmdSendResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		SendBack->ResultOk		=R->IsResultOK();
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendResult::GUICmdSendResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ResultOk		=true;
	NGCount			=0;
}

bool	GUICmdSendResult::Load(QIODevice *f)
{
	if(::Load(f,ResultOk)==false)
		return false;
	if(::Load(f,NGCount)==false)
		return false;
	return true;
}
bool	GUICmdSendResult::Save(QIODevice *f)
{
	if(::Save(f,ResultOk)==false)
		return false;
	if(::Save(f,NGCount)==false)
		return false;
	return true;
}