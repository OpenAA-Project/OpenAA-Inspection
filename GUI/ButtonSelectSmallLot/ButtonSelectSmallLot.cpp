/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectSmallLot\ButtonSelectSmallLot.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSelectSmallLotResource.h"
#include "ButtonSelectSmallLot.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "SelectSmallLotForm.h"
#include "XResultDLLManager.h"
#include "XSequenceLocal.h"
#include "XLotInformation.h"
#include "XResult.h"
#include "XCriticalFunc.h"
#include "XSyncGUI.h"
#include "ButtonAutoMode.h"
#include "ShowResultSmallLotForm.h"
#include "XResultXMLSmallLotCommon.h"
#include "XWriteResultThread.h"
#include <QElapsedTimer>
#include <QMessageBox>
#include "XEntryPoint.h"

//extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SelectSmallLot";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for select-smalllot dialog");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
	//LangCGSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonSelectSmallLot(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSelectSmallLot *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSelectSmallLot *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSelectSmallLot *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSelectSmallLot *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"MaxLines";
	Data[4].Pointer				 =&((ButtonSelectSmallLot *)Instance)->MaxLines;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSelectSmallLot.png")));
}

//==================================================================================================


ButtonSelectSmallLot::ButtonSelectSmallLot(LayersBase *Base ,QWidget *parent)
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
							,LangSolver.GetString(ButtonSelectSmallLot_LS,LID_0)/*"True if loading last ID"*/		);
}

ButtonSelectSmallLot::~ButtonSelectSmallLot(void)
{
}

void	ButtonSelectSmallLot::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSelectSmallLot::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSelectSmallLot::SlotClicked (bool checked)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	SelectSmallLotForm	*SelectLot=new SelectSmallLotForm(true,GetLayersBase(),this,this);
	LogoInQWidget(GetLayersBase(),SelectLot,sRoot ,sName);
	SelectLot->exec();

	int		tRetCmd			=SelectLot->RetCmd;
	QString	tSelectedLotID	=SelectLot->SelectedLotID;
	QString	tSelectedLotName=SelectLot->SelectedLotName;
	QString	tSelectedRemark	=SelectLot->SelectedRemark;
	int		tSelectedIDNumber=SelectLot->SelectedIDNumber;
	bool	tRetMode		=SelectLot->RetMode;
	int		iAutoCount		=SelectLot->SelectedLotAutoCount;
	delete	SelectLot;

	if(tRetMode==true){
		iLotID		=tSelectedLotID;
		iLotName	=tSelectedLotName;
		iRemark		=tSelectedRemark;
		iIDNumber	=tSelectedIDNumber;

		bool	SyncLater=false;
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			if(QMessageBox::question(NULL
										,LangSolver.GetString(ButtonSelectSmallLot_LS,LID_14)/*"Synchronized"*/
										,LangSolver.GetString(ButtonSelectSmallLot_LS,LID_15)/*"Synchronize other ?"*/
										,QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
				SyncLater=true;
			}
		}
		CmdGetStateOnAutoMode	GCmd(GetLayersBase());
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"AutoMode",/**/"");
		if(f!=NULL){
			f->TransmitDirectly(&GCmd);
			if(GCmd.AutoModeOn==true){
				CmdSetStateOnAutoMode	RCmd(GetLayersBase());
				RCmd.AutoModeOn=false;
				f->TransmitDirectly(&RCmd);
				if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
					QApplication::processEvents();
					QElapsedTimer	TMM1;
					TMM1.start();
					while(TMM1.hasExpired(2000)==false){
						QApplication::processEvents();
						if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()!=ExecuteInspectBase::_CaptureInspect
						&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()!=ExecuteInspectBase::_CaptureInspectWithoutCapture)
							break;
					}
				}
				//GSleep(700);	//Longer than waiting time in XExecuteInspect/Halt-Mode
				QCoreApplication::processEvents ();
				GSleep(700);	//Longer than waiting time in XExecuteInspect/Halt-Mode
				QCoreApplication::processEvents ();

				RCmd.AutoModeOn=true;
				f->TransmitDirectly(&RCmd);
				if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
					QApplication::processEvents();
					QElapsedTimer	TMM1;
					TMM1.start();
					while(TMM1.hasExpired(10000)==false){
						QApplication::processEvents();
						if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()==ExecuteInspectBase::_CaptureInspect
						|| GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()==ExecuteInspectBase::_CaptureInspectWithoutCapture)
							break;
					}
				}
				//GSleep(100);
				QCoreApplication::processEvents ();
				GSleep(100);
			}
		}
		if(SyncLater==true){
			if(tRetCmd==1){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				int	Cmd=1;
				::Save(&Buff,Cmd);
				::Save(&Buff,tSelectedLotID);
				::Save(&Buff,tSelectedLotName);
				::Save(&Buff,tSelectedRemark);
				TxSync(Buff.buffer());
			}
			else if(tRetCmd==2){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				int	Cmd=2;
				::Save(&Buff,Cmd);
				::Save(&Buff,tSelectedLotID);
				::Save(&Buff,tSelectedLotName);
				::Save(&Buff,tSelectedRemark);
				TxSync(Buff.buffer());
			}
		}

		SetLotToSystem(iAutoCount
					  ,iLotID
					  ,iLotName);
	}

//	if(f!=NULL){
//		if(GCmd.AutoModeOn==true){
//			GSleep(500);
//			CmdSetStateOnAutoMode	RCmd(GetLayersBase());
//			RCmd.AutoModeOn=true;
//			f->TransmitDirectly(&RCmd);
//		}
//	}

	//GetLayersBase()->ShowProcessingForm("Show lot",false);
	//GetLayersBase()->DelayedCloseProcessingForm(7);

	CmdReqShowLot	sCmd(GetLayersBase());
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Result",/**/"ShowResultSmallLot",/**/"");
	if(f!=NULL){
		sCmd.IDNumber=iIDNumber;
		f->TransmitDirectly(&sCmd);
	}
	ReEntrant=false;
}


void ButtonSelectSmallLot::SetLotToSystem(int iLotAutoCount
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
	GetLayersBase()->ClearAllReceivedResultCounts();

	int64 InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
 	GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
	GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());

	if(GetLayersBase()->GetResultDLLBase()->CheckConnection()==false){
		QMessageBox::warning(NULL
						,LangSolver.GetString(ButtonSelectSmallLot_LS,LID_1)/*"Error"*/
						,LangSolver.GetString(ButtonSelectSmallLot_LS,LID_2)/*"Server has stopped. Don't start"*/);
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
		GUICmdSelectLot	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		RCmd.LotAutoCount	=iLotAutoCount;
		RCmd.LotID			=tmpLotID;
		RCmd.LotName		=tmpLotName;
		RCmd.CurrentInspectTime=NowR;
		GetLayersBase()->GetCalcPoint(RCmd.CPoints);

		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			RCmd.AMode			=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat();
		}
		RCmd.Send(NULL,page,0);
	}
	//GetLayersBase()->ShowProcessingForm("Change lot");
	GetLayersBase()->GetResultDLLBase()->OutputInLotChangedCommon();
	GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	//GetLayersBase()->CloseProcessingForm();

	ResultDLLBaseClass		*RDLL=GetLayersBase()->GetResultDLLBase();
	if(RDLL!=NULL){
		ResultDLL	*R=RDLL->GetResultDLL(/**/"Result",/**/"XMLSmallLot");
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

void	ButtonSelectSmallLot::TransmitDirectly(GUIDirectMessage *packet)
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
		CmdReqLotInfoVar->IDNumber	=iIDNumber;
		return;
	}
}

void	ButtonSelectSmallLot::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1
										,LangSolver.GetString(ButtonSelectSmallLot_LS,LID_3)/*"Execute"*/
										,LangSolver.GetString(ButtonSelectSmallLot_LS,LID_4)/*"Select Small-Lot"*/,this);
	p->SetMenuNumber(100);
	Info.AppendList(p);
}
void	ButtonSelectSmallLot::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	ButtonSelectSmallLot::RxSync(QByteArray &f)
{
	/*
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		QApplication::processEvents();
		QElapsedTimer	TMM1;
		TMM1.start();
		while(TMM1.hasExpired(10000)==false){
			QApplication::processEvents();
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()==ExecuteInspectBase::_CaptureInspect
			|| GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()==ExecuteInspectBase::_CaptureInspectWithoutCapture)
				break;
		}
		GSleep(100);
	}
	*/
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ButtonSelectSmallLot_LS,LID_10)/*"Changing lot in received Sync"*/,false);
	SelectSmallLotForm	*SelectLot=new SelectSmallLotForm(false,GetLayersBase(),this);
	if(SelectLot->RxSync(f)==true){
		iLotID		=SelectLot->SelectedLotID;
		iLotName	=SelectLot->SelectedLotName;
		iRemark		=SelectLot->SelectedRemark;
		iIDNumber	=SelectLot->SelectedIDNumber;
		SetLotToSystem(SelectLot->SelectedLotAutoCount
					  ,SelectLot->SelectedLotID
					  ,SelectLot->SelectedLotName);

		CmdReqShowLot	sCmd(GetLayersBase());
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Result",/**/"ShowResultSmallLot",/**/"");
		if(f!=NULL){
			sCmd.IDNumber=iIDNumber;
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
	if(f->read((char *)CPoints,sizeof(CPoints))!=sizeof(CPoints))
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
	if(f->write((const char *)CPoints,sizeof(CPoints))!=sizeof(CPoints))
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
			
			//GetLayersBase()->SetCalcPoint(CPoints);

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

