/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectLot\ButtonSelectLot.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSelectLotResource.h"
#include "ButtonSelectLot.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "SelectLotForm.h"
#include "XGeneralDialog.h"
#include "XResultDLLManager.h"
#include "XSequenceLocal.h"
#include "XLotInformation.h"
#include "XResult.h"
#include "XCriticalFunc.h"
#include "XWriteResultThread.h"
#include "ButtonAutoMode.h"
#include "XEntryPoint.h"

extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SelectLot";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for select-lot dialog");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
	LangCGSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSelectLot(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSelectLot(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonSelectLot *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSelectLot *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSelectLot *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSelectLot *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"MaxLines";
	Data[4].Pointer				 =&((ButtonSelectLot *)Instance)->MaxLines;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSelectLot.png")));
}

static	bool	MacroCreateLot(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCreateLot2(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateLot";
		Functions[ret].Explain.append(/**/"Create new lot");
		Functions[ret].ArgName.append(/**/"Lot Name");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateLot;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateLot2";
		Functions[ret].Explain.append(/**/"Create new lot with ID/Name");
		Functions[ret].ArgName.append(/**/"Lot Name");
		Functions[ret].ArgName.append(/**/"Lot ID");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateLot2;
		ret++;
	}

	return ret;
}

static	bool	MacroCreateLot(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSelectLot	*V=dynamic_cast<ButtonSelectLot *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString	LotName=Args[0];
	V->CreateNewLot(LotName,true);

	return true;
}

static	bool	MacroCreateLot2(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSelectLot	*V=dynamic_cast<ButtonSelectLot *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	QString	LotName=Args[0];
	QString	LotID=Args[1];
	V->CreateNewLot(LotName,LotID,true);

	return true;
}

//==================================================================================================


ButtonSelectLot::ButtonSelectLot(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonSelectLot");
	Msg=/**/"Select lot";
	resize(60,25);
	MaxLines	=100;
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	LoadLastID=true;
	GetParamGUI()->SetParam(&LoadLastID, /**/"ButtonSelectLot",/**/"LoadLastID"		
							,LangSolver.GetString(ButtonSelectLot_LS,LID_0)/*"True if loading last ID"*/		);
}

ButtonSelectLot::~ButtonSelectLot(void)
{
}

void	ButtonSelectLot::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSelectLot::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSelectLot::SlotClicked (bool checked)
{
	SelectLotForm	*SelectLot=new SelectLotForm(GetLayersBase(),this,this,MaxLines);
	LogoInQWidget(GetLayersBase(),SelectLot,sRoot ,sName);
	GeneralDialog	D(GetLayersBase(),SelectLot,this);
	D.exec();

	CmdGetStateOnAutoMode	GCmd(GetLayersBase());
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"AutoMode",/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&GCmd);
		if(GCmd.AutoModeOn==true){
			CmdSetStateOnAutoMode	RCmd(GetLayersBase());
			RCmd.AutoModeOn=false;
			f->TransmitDirectly(&RCmd);
			GSleep(500);
		}
	}

	if(SelectLot->RetMode==true){
		SetLotToSystem(SelectLot->SelectedLotAutoCount
					  ,SelectLot->SelectedLotID
					  ,SelectLot->SelectedLotName);
	}

	if(f!=NULL){
		if(GCmd.AutoModeOn==true){
			GSleep(500);
			CmdSetStateOnAutoMode	RCmd(GetLayersBase());
			RCmd.AutoModeOn=true;
			f->TransmitDirectly(&RCmd);
		}
	}
}

void	ButtonSelectLot::CreateNewLot(const QString &LotName,bool Synchronized)
{
	SelectLotForm	*SelectLot=new SelectLotForm(GetLayersBase(),this,this,MaxLines);
	SelectLot->CreateNewLot(/**/"",LotName ,Synchronized);

	CmdGetStateOnAutoMode	GCmd(GetLayersBase());
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"AutoMode",/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&GCmd);
		if(GCmd.AutoModeOn==true){
			CmdSetStateOnAutoMode	RCmd(GetLayersBase());
			RCmd.AutoModeOn=false;
			f->TransmitDirectly(&RCmd);
			GSleep(500);
		}
	}

	SetLotToSystem(SelectLot->SelectedLotAutoCount
				  ,SelectLot->SelectedLotID
				  ,SelectLot->SelectedLotName);

	if(f!=NULL){
		if(GCmd.AutoModeOn==true){
			GSleep(500);
			CmdSetStateOnAutoMode	RCmd(GetLayersBase());
			RCmd.AutoModeOn=true;
			f->TransmitDirectly(&RCmd);
		}
	}
	delete	SelectLot;
}

void	ButtonSelectLot::CreateNewLot(const QString &LotName,const QString &LotID,bool Synchronized)
{
	SelectLotForm	*SelectLot=new SelectLotForm(GetLayersBase(),this,this,MaxLines);
	SelectLot->CreateNewLot(LotID,LotName ,Synchronized);

	CmdGetStateOnAutoMode	GCmd(GetLayersBase());
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"AutoMode",/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&GCmd);
		if(GCmd.AutoModeOn==true){
			CmdSetStateOnAutoMode	RCmd(GetLayersBase());
			RCmd.AutoModeOn=false;
			f->TransmitDirectly(&RCmd);
			GSleep(500);
		}
	}

	SetLotToSystem(SelectLot->SelectedLotAutoCount
				  ,SelectLot->SelectedLotID
				  ,SelectLot->SelectedLotName);

	if(f!=NULL){
		if(GCmd.AutoModeOn==true){
			GSleep(500);
			CmdSetStateOnAutoMode	RCmd(GetLayersBase());
			RCmd.AutoModeOn=true;
			f->TransmitDirectly(&RCmd);
		}
	}
	delete	SelectLot;
}


void ButtonSelectLot::SetLotToSystem(int iLotAutoCount
									,QString iLotID
									,QString iLotName)
{
//	GetLayersBase()->RemoveStockedResult();

	GetLayersBase()->ClearInspectID();

	GetLayersBase()->GetLot(0)->SetLotAutoCount	(iLotAutoCount);
	GetLayersBase()->GetLot(0)->SetLotID			(iLotID);
	GetLayersBase()->GetLot(0)->SetLotName		(iLotName);

	GetLayersBase()->GetLotBase()->SetLotID(iLotID);
	GetLayersBase()->GetLotBase()->SetLotName(iLotName);
	
	GetLayersBase()->RemoveStockedResult();

	int64 InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
 	GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
	GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());

	if(LoadLastID==true){
		if(GetLayersBase()->GetResultDLLBase()->GetLastInspectionID(GetLayersBase()->GetMasterCode(),iLotID,InspectionID)==true)
			InspectionID++;
	}
	GetLayersBase()->SetCurrentInspectID(InspectionID);

	GetLayersBase()->SetForceChangedInspectID();
	GetLayersBase()->GetResultHistryData()->Reset();

	BroadcastDirectly(_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());

	//?!?n????CID?iS102?j?E?a????CID?d?Z?b?g??E?e
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			Param->InspectionID=InspectionID;
		}
	}
	int		RPoint[3];
	RPoint[0]=0;
	RPoint[1]=0;
	RPoint[2]=0;
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat()==ExecuteInspectBase::_AutoCaptureInspect){
			RPoint[0]=1;
		}
	}
	GetLayersBase()->SetCalcPoint(RPoint);

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->ChangeLot();
	}
	XDateTime	NowR=GetLayersBase()->GetStartInspectTime();
	ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
	if(Res!=NULL){
		Res->SetStartTimeForInspect(NowR);
	}
					
	ResultInspection	*NRes=GetLayersBase()->GetNextResultForCalc();
	if(NRes!=NULL){
		NRes->SetStartTimeForInspect(GetLayersBase()->GetStartInspectTime());
	}
	for(int page=0;page<GetPageNumb();page++){
		GUICmdSelectLot	RCmd(GetLayersBase(),sRoot,sName ,page);
		RCmd.LotAutoCount	=iLotAutoCount;
		RCmd.LotID			=iLotID;
		RCmd.LotName		=iLotName;
		RCmd.CurrentInspectTime=NowR;
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			RCmd.AMode			=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat();
		}
		RCmd.Send(NULL,page,0);
	}
	//GetLayersBase()->ShowProcessingForm("Output lot to change");
	GetLayersBase()->GetResultDLLBase()->OutputInLotChangedCommon();
	GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	//GetLayersBase()->CloseProcessingForm();
}

void	ButtonSelectLot::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSelectLot	*CmdSelectLotVar=dynamic_cast<CmdSelectLot *>(packet);
	if(CmdSelectLotVar!=NULL){
		SlotClicked (true);
	}
}

void	ButtonSelectLot::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonSelectLot_LS,LID_1)/*"Execute"*/,LangSolver.GetString(ButtonSelectLot_LS,LID_2)/*"Select Lot"*/,this);
	p->SetMenuNumber(100);
	Info.AppendList(p);
}
void	ButtonSelectLot::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	ButtonSelectLot::RxSync(QByteArray &f)
{
	SelectLotForm	*SelectLot=new SelectLotForm(GetLayersBase(),this,NULL,1000);
	if(SelectLot->RxSync(f)==true){
		SetLotToSystem(SelectLot->SelectedLotAutoCount
					  ,SelectLot->SelectedLotID
					  ,SelectLot->SelectedLotName);
	}
	delete	SelectLot;
}

GUICmdSelectLot::GUICmdSelectLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AMode=ExecuteInspectBase::_NoAutoRepeat;
}

bool	GUICmdSelectLot::Load(QIODevice *f)
{
	if(::Load(f,LotAutoCount)==false)
		return false;
	if(::Load(f,LotID)==false)
		return false;
	if(::Load(f,LotName)==false)
		return false;
	if(::Load(f,CurrentInspectTime)==false)
		return false;
	if(f->read((char *)&AMode,sizeof(AMode))!=sizeof(AMode))
		return false;
	return true;
}
bool	GUICmdSelectLot::Save(QIODevice *f)
{
	if(::Save(f,LotAutoCount)==false)
		return false;
	if(::Save(f,LotID)==false)
		return false;
	if(::Save(f,LotName)==false)
		return false;
	if(::Save(f,CurrentInspectTime)==false)
		return false;
	if(f->write((const char *)&AMode,sizeof(AMode))!=sizeof(AMode))
		return false;
	return true;
}
void	GUICmdSelectLot::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==false){
			GetLayersBase()->GetLot(0)->SetLotAutoCount	(LotAutoCount);
			GetLayersBase()->GetLot(0)->SetLotID			(LotID);
			GetLayersBase()->GetLot(0)->SetLotName		(LotName);

			int64	InspectionID;
			GetLayersBase()->GetResultDLLBase()->GetLastInspectionID(GetLayersBase()->GetMasterCode()
																	,LotID
																	,InspectionID);
			int		RPoint[3];
			RPoint[0]=0;
			RPoint[1]=0;
			RPoint[2]=0;
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				if(AMode==ExecuteInspectBase::_AutoCaptureInspect){
					RPoint[0]=1;
				}
			}
			GetLayersBase()->SetCalcPoint(RPoint);
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->ChangeLot();
			}
			GetLayersBase()->SetStartInspectTime(CurrentInspectTime);
			ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
			if(Res!=NULL){
				Res->SetStartTimeForInspect(CurrentInspectTime);
			}
			
			ResultInspection	*NRes=GetLayersBase()->GetNextResultForCalc();
			if(NRes!=NULL){
				NRes->SetStartTimeForInspect(CurrentInspectTime);
			}
		}
		for(int i=0;i<3;i++){
			int	N=GetLayersBase()->GetResultThread()->GetStockedCount();
			if(N==0){
				break;
			}
			GSleep(2000);
			int	M=GetLayersBase()->GetResultThread()->GetStockedCount();
			if(N==M){
				break;
			}
		}
		GetLayersBase()->GetResultThread()->SetCastAll();
		GetLayersBase()->GetResultThread()->WaitForFinishingCast();
		GetLayersBase()->GetResultThread()->ClearAllErrorGroup();
		GetLayersBase()->ClearExecuterState();
	}
}

