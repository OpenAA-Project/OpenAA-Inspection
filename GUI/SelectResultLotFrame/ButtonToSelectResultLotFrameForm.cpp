#include "ButtonToSelectResultLotFrameForm.h"
#include "ui_ButtonToSelectResultLotFrameForm.h"
#include "SelectResultLotFrameDialog.h"
#include "XFrameDef.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XResultDLLManager.h"
#include "XSequenceLocal.h"
#include "XLotInformation.h"
#include "XResult.h"
#include "XCriticalFunc.h"
#include "ButtonAutoMode.h"
#include "XFrameDefCommon.h"
#include "XWriteResultThread.h"
#include <QMessageBox>
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ButtonToSelectResultLotFrameForm::ButtonToSelectResultLotFrameForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ButtonToSelectResultLotFrameForm)
{
    ui->setupUi(this);

	Msg=/**/"Select lot";
	resize(60,25);
	MaxLines=100;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	//LoadLastID=true;
	//GetParamGUI()->SetParam(&LoadLastID, /**/"ButtonSelectLot",/**/"LoadLastID"		
	//						,LangSolver.GetString(ButtonSelectSmallLot_LS,LID_0)/*"True if loading last ID"*/		);
}

ButtonToSelectResultLotFrameForm::~ButtonToSelectResultLotFrameForm()
{
    delete ui;
}
void	ButtonToSelectResultLotFrameForm::Prepare(void)
{
	ui->pushButton->setText(Msg);
	ui->pushButton->setFont (CFont);
	ResizeAction();
}

void	ButtonToSelectResultLotFrameForm::ResizeAction()
{
	ui->pushButton->resize(width(),height());
}

void	ButtonToSelectResultLotFrameForm::BuildForShow(void)
{
	GroupList.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqGroupList	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdAckGroupList	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==false){
			GroupList.Merge(ACmd.GroupList);
		}
	}
}
void ButtonToSelectResultLotFrameForm::on_pushButton_clicked()
{
	SelectResultLotFrameDialog	*SelectLot=new SelectResultLotFrameDialog(true,GetLayersBase(),this,this);
	LogoInQWidget(GetLayersBase(),SelectLot,sRoot ,sName);
	SelectLot->exec();

	if(SelectLot->RetMode==true){
		int	iAutoCount	=SelectLot->SelectedLotAutoCount;
		iLotID		=SelectLot->SelectedLotID;
		iLotName	=SelectLot->SelectedLotName;
		iRemark		=SelectLot->SelectedRemark;
		iIDNumber	=SelectLot->SelectedIDNumber;

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

	CmdReqShowInitial	sCmd(GetLayersBase());
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Result",/**/"ShowResultSmallLot",/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&sCmd);
	}
}

void ButtonToSelectResultLotFrameForm::SetLotToSystem(int iLotAutoCount
									,QString iLotID
									,QString iLotName)
{
//	GetLayersBase()->RemoveStockedResult();

	GetLayersBase()->ClearInspectID();
	int		LotSubNumber=1;
	QString	tmpLotName	=iLotName+QString(/**/"-")+QString::number(LotSubNumber);
	QString	tmpLotID	=iLotID	 +QString(/**/"-")+QString::number(LotSubNumber);

	GetLayersBase()->GetLot(0)->SetLotAutoCount	(iLotAutoCount);
	GetLayersBase()->GetLot(0)->SetLotID			(tmpLotID);
	GetLayersBase()->GetLot(0)->SetLotName		(tmpLotName);

	GetLayersBase()->GetLotBase()->SetLotID(iLotID);
	GetLayersBase()->GetLotBase()->SetLotName(iLotName);
	
	GetLayersBase()->RemoveStockedResult();

	int64 InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
 	GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
	GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());

	if(GetLayersBase()->GetResultDLLBase()->CheckConnection()==false){
		QMessageBox::warning(NULL
						,"Error"
						,"Server has stopped. Don't start");
		return;
	}

	if(LoadLastID==true){
		if(GetLayersBase()->GetResultDLLBase()->GetLastInspectionID(GetLayersBase()->GetMasterCode(),tmpLotID,InspectionID)==true)
			InspectionID++;
	}
	GetLayersBase()->SetCurrentInspectID(InspectionID);

	GetLayersBase()->SetForceChangedInspectID();
	GetLayersBase()->GetResultHistryData()->Reset();

	BroadcastDirectly(_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());

	//?!?n???CID?iS102?j?E?a???CID?d?Z?b?g?E?e
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
		GUICmdSelectFrameLot	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		RCmd.LotAutoCount		=iLotAutoCount;
		RCmd.LotID				=tmpLotID;
		RCmd.LotName			=tmpLotName;
		RCmd.CurrentInspectTime=NowR;
		RCmd.Send(NULL,page,0);
	}
	//GetLayersBase()->ShowProcessingForm("Change lot");
	GetLayersBase()->GetResultDLLBase()->OutputInLotChangedCommon();
	GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	//GetLayersBase()->CloseProcessingForm();

	ResultDLLBaseClass		*RDLL=GetLayersBase()->GetResultDLLBase();
	if(RDLL!=NULL){
		ResultDLL	*R=RDLL->GetResultDLL(/**/"Result",/**/"ResultFrameDLL");
		if(R!=NULL){
			ResultDLLBaseRoot	*RL=R->GetDLLPoint();
			CmdChangeResultLotInfo	ResCmd(GetLayersBase());
			ResCmd.LotID	=tmpLotID;
			ResCmd.LotName	=tmpLotName;
			ResCmd.Remark	=iRemark;
			RL->TransmitDirectly(&ResCmd);
		}
	}
}

void	ButtonToSelectResultLotFrameForm::TransmitDirectly(GUIDirectMessage *packet)
{
	/*
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
		CmdReqLotInfoVar->IDNumber	=iIDNumber;
		return;
	}
	*/
}

void	ButtonToSelectResultLotFrameForm::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1
										,"Execute"
										,"Select Frame-Lot",this);
	p->SetMenuNumber(100);
	Info.AppendList(p);
}
void	ButtonToSelectResultLotFrameForm::ExecuteMenu(int ID)
{
	if(ID==1){
		on_pushButton_clicked();
	}
}

void	ButtonToSelectResultLotFrameForm::RxSync(QByteArray &f)
{
	GetLayersBase()->ShowProcessingForm("Changing lot in received Sync",false);
	SelectResultLotFrameDialog	*SelectLot=new SelectResultLotFrameDialog(false,GetLayersBase(),this);
	if(SelectLot->RxSync(f)==true){
		iLotID		=SelectLot->SelectedLotID;
		iLotName	=SelectLot->SelectedLotName;
		iRemark		=SelectLot->SelectedRemark;
		iIDNumber	=SelectLot->SelectedIDNumber;
		SetLotToSystem(SelectLot->SelectedLotAutoCount
					  ,SelectLot->SelectedLotID
					  ,SelectLot->SelectedLotName);

			
		CmdReqShowInitial	sCmd(GetLayersBase());
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Result",/**/"ShowResultSmallLot",/**/"");
		if(f!=NULL){
			f->TransmitDirectly(&sCmd);
		}
	}
	delete	SelectLot;
	GetLayersBase()->CloseProcessingForm();
}

//==========================================================================================
GUICmdReqGroupList::GUICmdReqGroupList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqGroupList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckGroupList	*SendBack=GetSendBack(GUICmdAckGroupList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"FrameDef");
	if(PBase==NULL)
		return;
	FrameDefInPage	*PPage=dynamic_cast<FrameDefInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqGroupList	Da(GetLayersBase());
		PPage->TransmitDirectly(&Da);
		SendBack->GroupList	=Da.GroupList;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckGroupList::GUICmdAckGroupList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckGroupList::Load(QIODevice *f)
{
	if(GroupList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckGroupList::Save(QIODevice *f)
{
	if(GroupList.Save(f)==false)
		return false;
	return true;
}

//==============================================================================================

GUICmdSelectFrameLot::GUICmdSelectFrameLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSelectFrameLot::Load(QIODevice *f)
{
	if(::Load(f,LotAutoCount)==false)
		return false;
	if(::Load(f,LotID)==false)
		return false;
	if(::Load(f,LotName)==false)
		return false;
	if(::Load(f,CurrentInspectTime)==false)
		return false;
	return true;
}
bool	GUICmdSelectFrameLot::Save(QIODevice *f)
{
	if(::Save(f,LotAutoCount)==false)
		return false;
	if(::Save(f,LotID)==false)
		return false;
	if(::Save(f,LotName)==false)
		return false;
	if(::Save(f,CurrentInspectTime)==false)
		return false;
	return true;
}
void	GUICmdSelectFrameLot::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
				if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat()==ExecuteInspectBase::_AutoCaptureInspect){
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
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->ClearCameraBuffer();
		}
	}
}