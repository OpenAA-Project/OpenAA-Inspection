/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectMultiDelivery\ButtonSelectMultiDelivery.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSelectMultiDeliveryResource.h"
#include "ButtonSelectMultiDelivery.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XResultDLLManager.h"
#include "XSequenceLocal.h"
#include "XLotInformation.h"
#include "XResult.h"
#include "XCriticalFunc.h"
#include "XWriteResultThread.h"
#include "ButtonAutoMode.h"
#include "ButtonSelectMultiDeliveryDialog.h"
#include "ResultXMLMultiDelivery.h"
#include "ShowResultMultiDeliveryForm.h"
#include <QMessageBox>

//extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SelectMultiDelivery";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for selectMultiDelivery dialog");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonSelectMultiDelivery(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSelectMultiDelivery *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSelectMultiDelivery *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSelectMultiDelivery *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSelectMultiDelivery *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"MaxLines";
	Data[4].Pointer				 =&((ButtonSelectMultiDelivery *)Instance)->MaxLines;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSelectMultiDelivery.png")));
}

//==================================================================================================


ButtonSelectMultiDelivery::ButtonSelectMultiDelivery(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonSelectMultiDelivery");
	Msg=/**/"Select MultiDelivery";
	resize(60,25);
	MaxLines	=100;
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	LoadLastID=true;
	GetParamGUI()->SetParam(&LoadLastID, /**/"ButtonSelectMultiDelivery", /**/"LoadLastID"		
							, LangSolver.GetString(ButtonSelectMultiDelivery_LS, LID_0)/*"True if loading last ID"*/		);
}

ButtonSelectMultiDelivery::~ButtonSelectMultiDelivery(void)
{
}

void	ButtonSelectMultiDelivery::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSelectMultiDelivery::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSelectMultiDelivery::SlotClicked (bool checked)
{
	ButtonSelectMultiDeliveryDialog	*SelectLot=new ButtonSelectMultiDeliveryDialog(GetLayersBase(),this);
	LogoInQWidget(GetLayersBase(),SelectLot,sRoot ,sName);
	SelectLot->exec();

	if(SelectLot->RetMode==true){
		IntList 	iAutoCount	=SelectLot->SelectedLotAutoCount;
		iLotID		=SelectLot->SelectedLotID;
		iLotName	=SelectLot->SelectedLotName;
		iRemark		=SelectLot->SelectedRemark;

		CmdGetStateOnAutoMode	GCmd(GetLayersBase());
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"AutoMode",/**/"");
		if(f!=NULL){
			f->TransmitDirectly(&GCmd);
			if(GCmd.AutoModeOn==true){
				CmdSetStateOnAutoMode	RCmd(GetLayersBase());
				RCmd.AutoModeOn=false;
				f->TransmitDirectly(&RCmd);
				QApplication::processEvents();
				GSleep(700);
				QApplication::processEvents();
				RCmd.AutoModeOn=true;
				f->TransmitDirectly(&RCmd);
				QApplication::processEvents();
				GSleep(700);
				QApplication::processEvents();
			}
		}

		SetLotToSystem(iAutoCount
					  ,iLotID
					  ,iLotName);
	}
	delete	SelectLot;

	//GetLayersBase()->ShowProcessingForm("Show lot information",false);
	//GetLayersBase()->DelayedCloseProcessingForm(7);

	CmdReqShowLot	sCmd(GetLayersBase());
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Result",/**/"ShowResultMultiDelivery",/**/"");
	if(f!=NULL){
		//sCmd.IDNumber=iIDNumber;
		f->TransmitDirectly(&sCmd);
	}
}


bool ButtonSelectMultiDelivery::SetLotToSystem(IntList &iFirstLotAutoCount
									,QString iLotID
									,QString iLotName)
{
//	GetLayersBase()->RemoveStockedResult();

	if(GetLayersBase()->GetResultDLLBase()->CheckConnection()==false){
		QMessageBox::warning(NULL
						,LangSolver.GetString(ButtonSelectMultiDelivery_LS,LID_1)/*"Error"*/
						,LangSolver.GetString(ButtonSelectMultiDelivery_LS,LID_2)/*"Server has stopped. Don't start"*/);
		return false;
	}

	GetLayersBase()->ClearInspectID();
	GetLayersBase()->GetLotBase()->SetLotID(iLotID);
	GetLayersBase()->GetLotBase()->SetLotName(iLotName);

	ResultXMLMultiDelivery	*RL=NULL;
	ResultDLLBaseClass		*RDLL=GetLayersBase()->GetResultDLLBase();
	if(RDLL!=NULL){
		ResultDLL	*R=RDLL->GetResultDLL(/**/"Result",/**/"ResultXMLMultiDelivery");
		if(R!=NULL){
			RL=dynamic_cast<ResultXMLMultiDelivery *>(R->GetDLLPoint());
		}
	}
	if(RL==NULL){
		QMessageBox::warning(NULL
						,LangSolver.GetString(ButtonSelectMultiDelivery_LS,LID_3)/*"Error"*/
						,LangSolver.GetString(ButtonSelectMultiDelivery_LS,LID_4)/*"ResultXMLMultiDelivery.dll is not loaded"*/);
		return false;
	}
	GetLayersBase()->RemoveStockedResult();

	QStringList	tmpLotNameList;
	QStringList	tmpLotIDList;
	int		MaxInspectionID=0;
	for(int DeliveryNo=0;DeliveryNo<GetParamGlobal()->MaxLotDeliveryCount;DeliveryNo++){
		QString	DeliveryStr=RL->GetDeliveryInfoList(DeliveryNo);
		if(DeliveryStr.isEmpty()==true)
			break;
		int		LotSubNumber=1;
		QString	tmpLotName	=iLotName+QString(/**/"-")+DeliveryStr+QString(/**/"-")+QString::number(LotSubNumber);
		QString	tmpLotID	=iLotID	 +QString(/**/"-")+DeliveryStr+QString(/**/"-")+QString::number(LotSubNumber);

		tmpLotNameList.append(tmpLotName);
		tmpLotIDList.append(tmpLotID);

		GetLayersBase()->GetLot(DeliveryNo)->SetLotAutoCount(iFirstLotAutoCount[DeliveryNo]);
		GetLayersBase()->GetLot(DeliveryNo)->SetLotID		(tmpLotID);
		GetLayersBase()->GetLot(DeliveryNo)->SetLotName		(tmpLotName);
		
		int64	InspectionID;
		GetLayersBase()->GetResultDLLBase()->GetLastInspectionID(GetLayersBase()->GetMasterCode()
																,tmpLotID
																,InspectionID);
		if(InspectionID>MaxInspectionID){
			MaxInspectionID=InspectionID;
		}
	}
	
	int64 InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
	GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
	GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());

	GetLayersBase()->SetCurrentInspectID(InspectionID);

	GetLayersBase()->SetForceChangedInspectID();
	GetLayersBase()->GetResultHistryData()->Reset();

	BroadcastDirectly(_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());

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

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->ClearCameraBuffer();
	}

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectLot	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		RCmd.LotAutoCount	=iFirstLotAutoCount;
		RCmd.LotID			=tmpLotIDList;
		RCmd.LotName		=tmpLotNameList;
		RCmd.CurrentInspectTime=NowR;
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			RCmd.AMode			=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat();
		}
		RCmd.Send(NULL,page,0);
	}
	//GetLayersBase()->ShowProcessingForm("Output lot information");
	GetLayersBase()->GetResultDLLBase()->OutputInLotChangedCommon();
	GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	//GetLayersBase()->CloseProcessingForm();

	if(RL!=NULL){
		CmdChangeResultMultiDeliveryLotInfo	ResCmd(GetLayersBase());
		ResCmd.LotID	=tmpLotIDList;
		ResCmd.LotName	=tmpLotNameList;
		ResCmd.Remark	=iRemark;
		RL->TransmitDirectly(&ResCmd);
	}
	return true;
}

void	ButtonSelectMultiDelivery::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSelectLot	*CmdSelectLotVar=dynamic_cast<CmdSelectLot *>(packet);
	if(CmdSelectLotVar!=NULL){
		SlotClicked (true);
		return;
	}
	CmdReqLotInfo	*CmdReqLotInfoVar=dynamic_cast<CmdReqLotInfo *>(packet);
	if(CmdReqLotInfoVar!=NULL){
		CmdReqLotInfoVar->LotID		=iLotID;
		CmdReqLotInfoVar->LotName	=iLotName;
		CmdReqLotInfoVar->Remark	=iRemark;
		return;
	}
}

void	ButtonSelectMultiDelivery::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1
										,LangSolver.GetString(ButtonSelectMultiDelivery_LS,LID_5)/*"Execute"*/
										,LangSolver.GetString(ButtonSelectMultiDelivery_LS,LID_6)/*"Select Multi-Delivery Lot"*/,this);
	p->SetMenuNumber(100);
	Info.AppendList(p);
}
void	ButtonSelectMultiDelivery::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	ButtonSelectMultiDelivery::RxSync(QByteArray &f)
{
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ButtonSelectMultiDelivery_LS,LID_7)/*"Changing lot in received Sync"*/,false);
	ButtonSelectMultiDeliveryDialog	*SelectLot=new ButtonSelectMultiDeliveryDialog(GetLayersBase(),this);
	if(SelectLot->RxSync(f)==true){
		iLotID		=SelectLot->SelectedLotID;
		iLotName	=SelectLot->SelectedLotName;
		iRemark		=SelectLot->SelectedRemark;
		SetLotToSystem(SelectLot->SelectedLotAutoCount
					  ,SelectLot->SelectedLotID
					  ,SelectLot->SelectedLotName);

		CmdReqShowLot	sCmd(GetLayersBase());
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Result",/**/"ShowResultMultiDelivery",/**/"");
		if(f!=NULL){
			//sCmd.IDNumber=iIDNumber;
			f->TransmitDirectly(&sCmd);
		}
	}
	delete	SelectLot;
	GetLayersBase()->CloseProcessingForm();
}

//==============================================================================================

GUICmdSelectLot::GUICmdSelectLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AMode=ExecuteInspectBase::_NoAutoRepeat;
}

bool	GUICmdSelectLot::Load(QIODevice *f)
{
	if(LotAutoCount.Load(f)==false)
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
	if(LotAutoCount.Save(f)==false)
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
		ResultXMLMultiDelivery	*RL=NULL;
		ResultDLLBaseClass		*RDLL=GetLayersBase()->GetResultDLLBase();
		if(RDLL!=NULL){
			ResultDLL	*R=RDLL->GetResultDLL(/**/"Result",/**/"ResultXMLMultiDelivery");
			if(R!=NULL){
				RL=dynamic_cast<ResultXMLMultiDelivery *>(R->GetDLLPoint());
			}
		}
		if(RL!=NULL && GetLayersBase()->GetEntryPoint()->IsMasterPC()==false){
			int	MaxInspectionID=0;
			for(int DeliveryNo=0;DeliveryNo<GetParamGlobal()->MaxLotDeliveryCount;DeliveryNo++){
				QString	DeliveryStr=RL->GetDeliveryInfoList(DeliveryNo);
				if(DeliveryStr.isEmpty()==true)
					break;
				GetLayersBase()->GetLot(DeliveryNo)->SetLotAutoCount(LotAutoCount[DeliveryNo]);
				GetLayersBase()->GetLot(DeliveryNo)->SetLotID		(LotID[DeliveryNo]);
				GetLayersBase()->GetLot(DeliveryNo)->SetLotName		(LotName[DeliveryNo]);

				int64	InspectionID;
				GetLayersBase()->GetResultDLLBase()->GetLastInspectionID(GetLayersBase()->GetMasterCode()
																		,LotID[DeliveryNo]
																		,InspectionID);
				if(InspectionID>MaxInspectionID){
					MaxInspectionID=InspectionID;
				}
			
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
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->ClearCameraBuffer();
		}
	}
}

