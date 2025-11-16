/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImageBank\ImageBank.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ImageBank.h"
#include "XGeneralDialog.h"
#include "ImageBankListForm.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XCriticalFunc.h"
#include "XResult.h"
#include "SaveImageTargetButton.h"
#include "XDataInLayer.h"
#include "StartProcessAgainButton.h"
#include "XLotInformation.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ImageBank";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show and store images");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqResult		(Base,sRoot,sName);
	(*Base)=new GUICmdSendResult	(Base,sRoot,sName);

	(*Base)=new GUICmdPushed		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIAckPushed		(Base,QString(sRoot),QString(sName));
	(*Base)=new CmdInspectionAgainReplied(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ImageBank(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ImageBank *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ImageBank *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ImageBank *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ImageBank *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"ListCount";
	Data[4].Pointer				 =&((ImageBank *)Instance)->ListCount;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"BootON";
	Data[5].Pointer				 =&((ImageBank *)Instance)->BootON;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"StoreOnlyOK";
	Data[6].Pointer				 =&((ImageBank *)Instance)->StoreOnlyOK;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"StoreOnlyNG";
	Data[7].Pointer				 =&((ImageBank *)Instance)->StoreOnlyNG;

	return(8);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ImageBank.png")));
}

//==================================================================================================

QString	ImageInInspection::MakeFileName(void)
{
	if(ResultOK==true){
		return Time.toString(/**/"yyMMdd-hhmmss")
					+ QString(/**/"-OK.pix");
	}
	else{
		return Time.toString(/**/"yyMMdd-hhmmss")
					+ QString(/**/"-NG.pix");
	}
}


ImageBank::ImageBank(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button=new QToolButton();
	Button->setParent(this);
	Button->move(0,0);
	Button->setObjectName(/**/"ImageBank");
	RButton=new ButtonRightClickEnabler(Button);

	Msg=/**/"Image Bank";
	ListCount	=10;
	Form		=NULL;
	WPoint		=0;
	LastInspectionID	=-1;
	BootON		=true;
	StoreOnlyOK	=true;
	StoreOnlyNG	=true;
	LoadedID	=0;
	CountOfStartProcessAgain	=0;

	Button->setCheckable(true);

	GetParamGUI()->SetParam(&BootON, /**/"ImageBank",/**/"BootON"	
										,"True if stocking image starts after booting");

	resize(60,25);
	if(!connect(RButton,SIGNAL(RightClicked(QAbstractButton *)), this ,SLOT(SlotRClicked(QAbstractButton *)))){
		BootON=false;
	}
	if(!connect(Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()))){
		BootON=false;
	}
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(this,SIGNAL(SignalUpdateList()), this ,SLOT(SlotUpdateList()),Qt::QueuedConnection);
}

ImageBank::~ImageBank(void)
{
}

void	ImageBank::Prepare(void)
{
	Button->setText(Msg);
	Button->setFont (CFont);
	ResizeAction();

	AllocateImages();
	if(BootON==true){
		Button->setChecked(true);
	}
}

void	ImageBank::ReadyParam(void)
{
	CountOfStartProcessAgain=GetLayersBase()->EnumGUIInst(/**/"Action"
														,/**/"StartProcessAgainButton"
														,StartProcessAgainDim ,100);
	RegisterExecutePostProcessing();
	Pushed=Button->isChecked();
}

void	ImageBank::ResizeAction()
{
	Button->resize(width(),height());
}

void	ImageBank::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSetStateImageBank	*CmdSetStateImageBankVar=dynamic_cast<CmdSetStateImageBank *>(packet);
	if(CmdSetStateImageBankVar!=NULL){
		Button->setChecked(CmdSetStateImageBankVar->ONMode);
		StoreOnlyOK	=CmdSetStateImageBankVar->StoreOnlyOK	;
		StoreOnlyNG	=CmdSetStateImageBankVar->StoreOnlyNG	;
		ListCount	=CmdSetStateImageBankVar->ListCount		;
		return;
	}
	CmdSetClearImageBank	*CmdSetClearImageBankVar=dynamic_cast<CmdSetClearImageBank *>(packet);
	if(CmdSetClearImageBankVar!=NULL){
		ClearBank();
		if(Form!=NULL){
			Form->UpdateList();
		}
		return;
	}
	CmdSwitchImageBank	*CmdSwitchImageBankVar=dynamic_cast<CmdSwitchImageBank *>(packet);
	if(CmdSwitchImageBankVar!=NULL){
		int		ListCount=0;
		for(ImageInInspection *a=Bank.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->InspectionID>=0){
				ListCount++;
			}
		}
		for(int i=0;i<ListCount;i++){
			int	RPoint=WPoint-i-1;
			if(RPoint<0)
				RPoint=RPoint+ListCount;
			ImageInInspection *a=Bank[RPoint];
			if(a->LoadedID==CmdSwitchImageBankVar->LoadedID){
				RestoreToTarget(a);
				break;
			}
		}
		return;
	}
	CmdRetryImageBank	*CmdRetryImageBankVar=dynamic_cast<CmdRetryImageBank *>(packet);
	if(CmdRetryImageBankVar!=NULL){
		RetryBank();
	}
}
void	ImageBank::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	LoadMasterSpecifiedBroadcaster	*LoadMasterSpecifiedBroadcasterVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(LoadMasterSpecifiedBroadcasterVar!=NULL){
		AllocateImages();
		return;
	}
}

void	ImageBank::AllocateImages(void)
{
	Bank.RemoveAll();
	if(GetEditMode()==false){
		int	PhaseNumb=GetPhaseNumb();
		if(GetParamGlobal()->CommonTargetBetweenPhases==true)
			PhaseNumb=1;
		for(int i=0;i<ListCount;i++){
			ImageInInspection	*a=new ImageInInspection();
			for(int phase=0;phase<PhaseNumb;phase++){
				ImageBankInPhase	*eh=new ImageBankInPhase();
				for(int page=0;page<GetPageNumb();page++){
					ImageBankInPage	*ep=new ImageBankInPage();
					for(int layer=0;layer<GetLayerNumb(page);layer++){
						ImageBufferList	*L=new ImageBufferList();
						int	DotPerLine	=GetDotPerLine(page);
						int	MaxLines	=GetMaxLines(page);
						L->Set(page,0,DotPerLine,MaxLines);
						ep->ImageInLayers.AppendList(L);
					}
					eh->ImageInPages.AppendList(ep);
				}
				a->ImageInPhases.AppendList(eh);
			}
			Bank.AppendList(a);
		}
	}
	WPoint=0;
}

void ImageBank::SlotClicked ()
{
	Pushed=Button->isChecked();
}

void ImageBank::SlotRClicked (QAbstractButton *obj)
{
	//if(Button->isChecked()==true){
		if(Form==NULL){
			Form=new ImageBankListForm(this);
		}
		Form->show();
		Form->UpdateList();
	//}
	//else{
	//	Form->hide();
	//}
}
bool	ImageBank::IsProcessAgain(void)
{
	for(int i=0;i<CountOfStartProcessAgain;i++){
		StartProcessAgainButton	*f=(StartProcessAgainButton *)StartProcessAgainDim[i];
		if(f->NowOnRunning==true){
			return true;
		}
	}
	return false;
}
void	ImageBank::ShowInPlayer(int64 shownInspectionID)
{
}
ExeResult	ImageBank::ExecutePostProcessing(void)
{
	if(Pushed==true && IsProcessAgain()==false){
		LayersBase	*LBase	=GetLayersBase();

		int64	shownInspectionID=LBase->GetCurrentInspectIDForExecute();
		ImageInInspection	*a=Bank[WPoint];
		if(a!=NULL && LastInspectionID!=shownInspectionID){
			bool	ResultOK=true;
			if(LBase->IsLocalCamera()==false){
				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=LBase->GetGlobalPageFromLocal(page);
					GUICmdReqResult		CmdReq(LBase,sRoot,sName,GlobalPage);
					CmdReq.ShownInspectionID=shownInspectionID;
					GUICmdSendResult	CmdAck(LBase,sRoot,sName,GlobalPage);
					if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
						if(CmdAck.ResultOK==false){
							ResultOK=false;
						}
					}
				}
			}
			else{
				ResultInspection	*R=GetLayersBase()->GetBufferedResultAbsolutely(shownInspectionID);
				if(R!=NULL){
					bool3	OK;
					bool	MaxError , TimeOver;
					R->GatherResult(OK ,MaxError , TimeOver,true,false);
					ResultOK=(OK==true3)?true:false;
				}
			}

			if((ResultOK==true && StoreOnlyOK==true)
			|| (ResultOK==false && StoreOnlyNG==true)){
				ResultHistry *H=LBase->GetResultHistryData()->GetLast();
				int	PhaseNumb=GetPhaseNumb();
				if(GetParamGlobal()->CommonTargetBetweenPhases==true)
					PhaseNumb=1;
				for(int phase=0;phase<PhaseNumb;phase++){
					PageDataInOnePhase	*Dh=LBase->GetPageDataPhase(phase);
					ImageBankInPhase	*eh=a->ImageInPhases[phase];
					for(int page=0;page<GetPageNumb();page++){
						DataInPage		*Dp=Dh->GetPageData(page);
						ImageBankInPage	*ep=eh->ImageInPages[page];
						for(int layer=0;layer<GetLayerNumb(page);layer++){
							DataInLayer	*Dl=Dp->GetLayerData(layer);
							ImageBufferList	*L=ep->ImageInLayers[layer];
							//*L=Dl->GetDelayedViewBuff();
							*L=Dl->GetTargetBuff();
						}
					}
				}
				a->Time			=XDateTime::currentDateTime();
				a->InspectionID	=shownInspectionID;
				a->ResultOK		=ResultOK;
				a->LoadedID		=LoadedID;
				a->LotAutoCount	=LBase->GetLot(0)->GetLotAutoCount();
				a->ProcessMSec	=(H!=NULL)?H->ProcessMilisec:0;
				LoadedID++;

				WPoint++;
				if(WPoint>=Bank.GetCount()){
					WPoint=0;
				}
				if(Form!=NULL){
					emit	SignalUpdateList();
					
				}
			}
		}
		LastInspectionID=shownInspectionID;
	}
	return _ER_true;
}

void	ImageBank::SlotUpdateList()
{
	Form->UpdateList();
}

int	ImageBank::GetIndexFromRow(int Row)
{
	int	RPoint=WPoint-Row-1;
	if(RPoint<0)
		RPoint=RPoint+Bank.GetCount();
	return RPoint;
}
bool	ImageBank::RestoreToTarget(int row)
{
	int	RPoint=GetIndexFromRow(row);
	ImageInInspection	*a=Bank[RPoint];
	if(a!=NULL && a->InspectionID>=0){
		return RestoreToTarget(a);
	}
	return false;
}
bool	ImageBank::RestoreToTarget(ImageInInspection *a)
{
	if(a!=NULL && a->InspectionID>=0){
		int	PhaseNumb=GetPhaseNumb();
		if(GetParamGlobal()->CommonTargetBetweenPhases==true)
			PhaseNumb=1;
		for(int phase=0;phase<PhaseNumb;phase++){
			PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(phase);
			ImageBankInPhase	*eh=a->ImageInPhases[phase];
			for(int page=0;page<GetPageNumb();page++){
				DataInPage		*Dp=Dh->GetPageData(page);
				ImageBankInPage	*ep=eh->ImageInPages[page];
				for(int layer=0;layer<GetLayerNumb(page);layer++){
					DataInLayer	*Dl=Dp->GetLayerData(layer);
					ImageBufferList	*L=ep->ImageInLayers[layer];
					Dl->GetTargetBuff()=*L;
				}
			}
		}
		BroadcastRepaintAll();
		return true;
	}
	return false;
}
bool	ImageBank::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	AllocateImages();
	return true;
}
bool	ImageBank::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	AllocateImages();
	return true;
}
void	ImageBank::CloseFowm(void)
{
	//Button->setChecked(false);
}
void	ImageBank::ClearBank(void)
{
	for(ImageInInspection *a=Bank.GetFirst();a!=NULL;a=a->GetNext()){
		a->InspectionID=-1;
	}
	WPoint=0;
}

bool	ImageBank::ExecuteOne(void)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);

	//Canceled=false;
	int	CurrentPhase=0;
	if(PhaseCodes.GetCount()>0)
		CurrentPhase=PhaseCodes[0];
	else
		CurrentPhase=GetLayersBase()->GetCurrentPhase();

	GetLayersBase()->ClearAllAckFlag();

	bool	Ok=true;

	if(GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdPushed	PushRequester(GetLayersBase(),sRoot,sName);
			GUIAckPushed	PushAnswer	 (GetLayersBase(),sRoot,sName);
			PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
			PushRequester.MaxInspectMilisec		=99999999;
			if(PushRequester.Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,PushAnswer)==true){
				if(PushAnswer.Ok==false)
					Ok=false;
			}
		}
		GetLayersBase()->WaitAllAcknowledged(60*20);
	}
	else{
		GUICmdPushed	PushRequester(GetLayersBase(),sRoot,sName);
		GUIAckPushed	PushAnswer	 (GetLayersBase(),sRoot,sName);
		PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
		PushRequester.MaxInspectMilisec		=99999999;
		if(PushRequester.Send(GetLayersBase()->GetGlobalPageFromLocal(0),0,PushAnswer)==true){
			if(PushAnswer.Ok==false)
				Ok=false;
		}

		GetLayersBase()->SetShouldWriteResult(false);

		GetLayersBase()->SetShouldWriteResult(true);
	}
	GetLayersBase()->SetCurrentInspectID(GetLayersBase()->GetCurrentInspectIDForExecute());

	GetLayersBase()->SetCurrentPhase(CurrentPhase);
	return Ok;
}

void	ImageBank::RetryBank(void)
{
	GUIFormBase	*RetryPointer=GetLayersBase()->FindByName(/**/"Action",/**/"StartProcessAgainButton",/**/"");
	if(RetryPointer!=NULL){
		int	N=Bank.GetCount();
		for(int row=0;row<N;row++){
			if(RestoreToTarget(row)==false){
				break;
			}
			int	RPoint=GetIndexFromRow(row);
			ImageInInspection	*a=Bank[RPoint];
			if(a!=NULL && a->InspectionID>=0){
				bool	Ok=ExecuteOne();
				a->ResultOK=Ok;
			}
		}
	}
}

void	ImageBank::SaveAll(const QString &Path)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"SaveImageTargetButton",/**/"");
	if(f!=NULL){
		int		N=0;
		for(ImageInInspection *a=Bank.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->InspectionID>=0){
				N++;
			}
		}
		for(int i=0;i<ListCount && i<N;i++){
			int	RPoint=WPoint-i-1;
			if(RPoint<0)
				RPoint=RPoint+ListCount;
			ImageInInspection *a=Bank[RPoint];

			RestoreToTarget(i);

			CmdReqSaveImage	RCmd(GetLayersBase());
			RCmd.FileName=Path+QDir::separator()+a->MakeFileName();
			RCmd.UsageImageMode=CmdReqSaveImage::_SaveTargetImage;
			RCmd.UseLayer=-1;
			f->TransmitDirectly(&RCmd);
		}
	}
}

//=======================================================================

GUICmdReqResult::GUICmdReqResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqResult::Save(QIODevice *f)
{
	::Save(f,ShownInspectionID);
	return(true);
}
bool	GUICmdReqResult::Load(QIODevice *f)
{
	::Load(f,ShownInspectionID);
	return(true);
}

void	GUICmdReqResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendResult	*SendBack=GetSendBack(GUICmdSendResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		bool3	OK;
		bool	MaxError;
		bool	TimeOver;
		R->GatherResult(OK ,MaxError , TimeOver,true,false);
		if(OK==true3)
			SendBack->ResultOK=true;
		else
			SendBack->ResultOK=false;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendResult::GUICmdSendResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ResultOK=true;
}


bool	GUICmdSendResult::Load(QIODevice *f)
{
	if(::Load(f,ResultOK)==false){
		return false;
	}

	return true;
}
bool	GUICmdSendResult::Save(QIODevice *f)
{
	if(::Save(f,ResultOK)==false){
		return false;
	}

	return true;
}

//===========================================================================================

GUICmdPushed::GUICmdPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	InspectionID=0;
}

bool	GUICmdPushed::Load(QIODevice *f)
{
	if(::Load(f,InspectionID)==false)
		return false;
	if(::Load(f,MaxInspectMilisec)==false)
		return false;
	return true;
}
bool	GUICmdPushed::Save(QIODevice *f)
{
	if(::Save(f,InspectionID)==false)
		return false;
	if(::Save(f,MaxInspectMilisec)==false)
		return false;
	return true;
}

void	GUICmdPushed::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckPushed	*SendBack=GetSendBack(GUIAckPushed,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	if(localPage==0){
		if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
			for(int page=0;page<GetPageNumb();page++){
				for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
					GetLayersBase()->GetPageData(page)->GetLayerData(Layer)->RestoreTargetImageFromRaw();
				}
			}
		}

		GetLayersBase()->SetCurrentInspectID(InspectionID);
		int32	TmpMaxInspectMilisec	=GetParamGlobal()->MaxInspectMilisec;
		GetParamGlobal()->MaxInspectMilisec	=MaxInspectMilisec;

		GetLayersBase()->AddMaxProcessing(localPage,7);
		int	TempStrategy=GetParamGlobal()->GetMaxScanStrategy();
		GetParamGlobal()->SetMaxScanStrategy(1);

		int	CPoint[6];
		GetLayersBase()->GetCalcPoint(CPoint);
		CPoint[1]=CPoint[0];
		int	CurrentCalcPoint=CPoint[0];
		CurrentCalcPoint--;
		if(CurrentCalcPoint<0)
			CurrentCalcPoint=GetParamGlobal()->NGCacheNumb-1;
		if(GetLayersBase()->GetExecuter(CurrentCalcPoint)->GetState()==DataInExecuter::FinExecuteStartByInspection
		|| GetLayersBase()->GetExecuter(CurrentCalcPoint)->GetState()==DataInExecuter::FinExecuteStartByScanOnly){
			GetLayersBase()->DecPoint();
			CPoint[1]--;
			if(CPoint[1]<0)
				CPoint[1]=GetParamGlobal()->NGCacheNumb-1;
		}

		GetLayersBase()->PushExecuterState();
		GetLayersBase()->StepProcessing(localPage);

		XDateTime	SaveTm=GetLayersBase()->GetStartInspectTime();
		DWORD		SaveRm=GetLayersBase()->GetStartInspectionTimeMilisec();

		GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
		GetLayersBase()->SetStartInspectionTimeMilisec(GetComputerMiliSec());

//		GetLayersBase()->SetForceChangedInspectID();
//		XDateTime	NowD=GetLayersBase()->GetStartInspectionTime();
//		GetLayersBase()->GetLogicDLLBase()->SetStartTimeForInspection(NowD);


		GetLayersBase()->StepProcessing(localPage);
		GetLayersBase()->ExecuteStartByInspection	(false);
		ResultInspection	*CurrentResult=GetLayersBase()->GetCurrentResultForCalc();
		if(CurrentResult!=NULL){
			CurrentResult->SetStartTimeForInspect(GetLayersBase()->GetStartInspectTime());

			DWORD	C=GetComputerMiliSec();
			DWORD	Cn;

			ListPhasePageLayerPack	CapturedList;
			GetLayersBase()->MakeCapturedAllList(CapturedList);

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecuteCaptured(CapturedList,false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteCaptured=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecutePreAlignment(false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePreAlignment=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecuteAlignment			(false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteAlignment=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecutePreProcessing		(false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePreProcessing=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecuteProcessing			(false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteProcessing=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecuteProcessingRevived	(false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteProcessingRevived=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->SetShouldWriteResult(false);
			GetLayersBase()->ExecutePostProcessing		(false);		
			GetLayersBase()->SetShouldWriteResult(true);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePostProcessing=Cn-C;
			C=Cn;

			GetParamGlobal()->SetMaxScanStrategy(TempStrategy);

			int	NGCount=CurrentResult->GetNGCount();
			SendBack->Ok		=(NGCount==0)?true:false;
			SendBack->NGCount	=CurrentResult->GetNGCount();

			GetLayersBase()->SendAckToMaster(localPage);

			CmdInspectionAgainReplied	PacketReplied(GetLayersBase(),QString(sRoot),QString(sName));
			PacketReplied.Result		=CmdInspectionAgainReplied::_OK;
			PacketReplied.NGCounts		=CurrentResult->GetNGCount();
			PacketReplied.TimeOutBreak	=CurrentResult->GetTimeOutBreak()	;
			PacketReplied.MaxErrorBreak	=CurrentResult->GetMaxErrorBreak()	;
			DataInExecuter	*Re			=GetLayersBase()->GetExecuter(CurrentResult);
			PacketReplied.ExecuterID	=Re->GetID();
			if(GetParamComm()->Mastered==true){
				for(int page=0;page<GetPageNumb();page++){
					Re->SetResultReceivedFlag(page,PacketReplied.NGCounts,PacketReplied.TimeOutBreak,PacketReplied.MaxErrorBreak);
				}
			}
			else{
				Re->SetResultReceivedFlag(localPage,PacketReplied.NGCounts,PacketReplied.TimeOutBreak,PacketReplied.MaxErrorBreak);
			}
		}


		GetLayersBase()->PopExecuterState();
		GetLayersBase()->SetCalcPoint(CPoint);
		GetLayersBase()->SetStartInspectTime(SaveTm);
		GetLayersBase()->SetStartInspectionTimeMilisec(SaveRm);
		GetParamGlobal()->MaxInspectMilisec=TmpMaxInspectMilisec;
	}
	else{
		ResultInspection	*CurrentResult=GetLayersBase()->GetCurrentResultForCalc();
		if(CurrentResult!=NULL){
			DataInExecuter	*Re	=GetLayersBase()->GetExecuter(CurrentResult);
			Re->SetResultReceivedFlag(localPage,0,false,false);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

CmdInspectionAgainReplied::CmdInspectionAgainReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	CmdInspectionAgainReplied::Load(QIODevice *f)
{
	BYTE	ResultData;
	if(::Load(f,ResultData)==false)
		return false;
	Result=(__Result)ResultData;
	if(::Load(f,NGCounts)==false)
		return false;
	if(::Load(f,TimeOutBreak)==false)
		return false;
	if(::Load(f,MaxErrorBreak)==false)
		return false;
	if(::Load(f,ExecuterID)==false)
		return false;
	return true;
}
bool	CmdInspectionAgainReplied::Save(QIODevice *f)
{
	BYTE	ResultData=(BYTE)Result;
	if(::Save(f,ResultData)==false)
		return false;
	if(::Save(f,NGCounts)==false)
		return false;
	if(::Save(f,TimeOutBreak)==false)
		return false;
	if(::Save(f,MaxErrorBreak)==false)
		return false;
	if(::Save(f,ExecuterID)==false)
		return false;
	return true;
}

void	CmdInspectionAgainReplied::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LayersBase	*L=GetLayersBase();
	DataInExecuter	*Re=L->GetExecuter(ExecuterID);
	Re->SetResultReceivedFlag(localPage,NGCounts,TimeOutBreak,MaxErrorBreak);

	SendAck(localPage);
}

GUIAckPushed::GUIAckPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Ok		=false;
	NGCount	=0;
}
bool	GUIAckPushed::Load(QIODevice *f)
{
	if(::Load(f,Ok)==false)
		return false;
	if(::Load(f,NGCount)==false)
		return false;
	return true;
}
bool	GUIAckPushed::Save(QIODevice *f)
{
	if(::Save(f,Ok)==false)
		return false;
	if(::Save(f,NGCount)==false)
		return false;
	return true;
}
