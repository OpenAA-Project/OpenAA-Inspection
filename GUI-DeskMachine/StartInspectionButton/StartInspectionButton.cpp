/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartInspectionButton\StartInspectionButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "StartInspectionButtonResource.h"
#include "StartInspectionButton.h"

#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "swap.h"
#include "XLotInformation.h"
#include <QMessageBox>

char	*sRoot=/**/"Inspection";
char	*sName=/**/"StartInspectionButton";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to start Inspection");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdStartInspect(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReplyInspect(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new StartInspectionButton(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1){
		return(-1);
	}
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"PushedColor";
	Data[0].Pointer				 =&((StartInspectionButton *)Instance)->PushedColor;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StartInspectionButton.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"PixelInspection"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoMaskingPI"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoAlignment"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"StatisticImager"));
}

//==================================================================================================

StartInspectionButton::StartInspectionButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
,Button(QImage(/**/":Resources/StartInspectionImage.bmp"),parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"StartInspectionButtonColored");
	//Button.setAutoExclusive(true);
//	Button.setCheckable(true);	//D-20090910
	//Button.setCheckable(false);	//A-20090910
	PushedColor=Qt::red;
	resize(176,74);
//	connect(&Button,SIGNAL(SignalClicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(&Button,SIGNAL(SignalClicked()),	this,SLOT(SlotClicked()));
	connect(this,	SIGNAL(SignalResize()),		this,SLOT(ResizeAction()));
	SetKeyGrab(true);
	Started=false;
	IsNecessaryLot=true;
	GetParamGUI()->SetParam(&IsNecessaryLot, /**/"StartInspectionButton",/**/"IsNecessaryLot"	
											,LangSolver.GetString(StartInspectionButton_LS,LID_0)/*"True if lot-id is necessary"*/		);
}

StartInspectionButton::~StartInspectionButton(void)
{
}

void	StartInspectionButton::Prepare(void)
{
	//Button.setPressedColor(PushedColor);
	ResizeAction();
}

void	StartInspectionButton::ResizeAction()
{
	Button.resize(width(),height());
}

IntList	DbgSlotList;

//void StartInspectionButton::SlotClicked (bool checked)
void StartInspectionButton::SlotClicked ()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
//	if(checked==true){	//D-20090910
		if(Started==true){
			ReEntrant=false;
			return;
		}
		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==true){
			if(GetLayersBase()->GetLot(0)->GetLotID()==/**/"-1" || GetLayersBase()->GetLot(0)->GetLotID().isEmpty()==true){
				if(IsNecessaryLot==true){
					QMessageBox::warning ( NULL, LangSolver.GetString(StartInspectionButton_LS,LID_1)/*"Warning"*/
												, LangSolver.GetString(StartInspectionButton_LS,LID_2)/*"ƒƒbƒg‚ðÝ’è‚µ‚Ä‚­‚¾‚³‚¢"*/);
//					Button.setChecked(false);
					//Button.Cancel();
					ReEntrant=false;
					return;
				}
			}

			GetLayersBase()->ShowProcessingForm ("Start inspection");
			GetLayersBase()->AddMaxProcessing(0,0);
///			Button.setColor(PushedColor);
			//GetLayersBase()->ExecuteStartByInspection(GetLayersBase()->GetEntryPoint());
			//GetLayersBase()->GetInspectionData()->GetExecuteInspect()->StartAllCamera();
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				Param->CaptureMode=3;
				Param->StartInspection=true;
			}

			if(GetParamGlobal()->GetMaxScanStrategy()<=1 || (GetLayersBase()->GetCurrentStrategicNumberForSeq()==0)){
				GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
				GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());
			}

			while(Param->PermitCapture==false){
				if(GetLayersBase()->GetOnTerminating()==true){
					ReEntrant=false;
					return;
				}
				//SeqControlParamData->CaptureMode=3;
				GSleep(10);
				QCoreApplication::processEvents();
//				if(Button.isChecked()==false){		//D-20090910
///					Button.setColor(NormalColor);
//					ReEntrant=false;				//D-20090910
//					return;							//D-20090910
//				}									//D-20090910
			}

			GUICmdStartInspect	*Cmd[1000];
			GUICmdReplyInspect	*Reply[1000];
			Started=true;
			StrategicListContainer SList;
			int	CStrategic=max(GetLayersBase()->GetCurrentStrategicNumber(),GetLayersBase()->GetCurrentStrategicNumberForSeq());
			GetParamGlobal()->GetStrategy(CStrategic,SList);

			int	N=0;
			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				int page=s->Page;
				Cmd[N]	=new GUICmdStartInspect(GetLayersBase(),sRoot,sName,page);
				Cmd[N]->StartInspectionTime	=GetLayersBase()->GetStartInspectTime();
				Cmd[N]->CurrentInspectID	=GetLayersBase()->GetCurrentInspectIDForExecute();
				Cmd[N]->Layer				=s->Layer;
				Cmd[N]->StrategicNumber		=GetLayersBase()->GetCurrentStrategicNumberForSeq();
				Reply[N]	=new GUICmdReplyInspect(GetLayersBase(),sRoot,sName,page);
			}
			for(int i=0;i<N;i++){
				Cmd[i]->Send(Cmd[i]->GetGlobalPage() ,0,*Reply[i]);
			}
			bool	ReadyAll;
			do{
				ReadyAll=true;
				for(int i=0;i<N;i++){
					if(Reply[i]->IsReceived()==false){
						ReadyAll=false;
					}
				}
			}while(ReadyAll==false);

			if(Param!=NULL){
				Param->ReadyForScan=true;
			}

			if((GetParamGlobal()->DebugLevel & 0x04)!=0){
				DbgSlotList.AppendList(new IntClass(CStrategic));
			}

			for(int i=0;i<N;i++){
				delete	Cmd[i]	;
				delete	Reply[i];
			}
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()!=ExecuteInspectBase::_CaptureInspect){
				GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoInspect();
			}
		}
//	}	//D-20090910
	ReEntrant=false;
}

void StartInspectionButton::keyPressEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_F9){
		//SlotClicked(true);
//		Button.setChecked(true);
		//Button.Exec();
	}
}
bool StartInspectionButton::OnIdle(void)
{
	GUIFormBase::OnIdle();
	
	if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
		ExecuteInspectBase	*EBase=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(EBase!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)EBase->GetSeqParam();
			if(Started==true){
				if(Param->StartInspection==false){
					//Button.setChecked(true);
					//Param->StartInspection=false;
///					Button.setColor(NormalColor);
					//Button.setChecked(false);
					Started=false;
				}
				if(EBase->GetHaltMode()==true){
					//Button.setChecked(true);
					//Param->StartInspection=false;
///					Button.setColor(NormalColor);
					//Button.setChecked(false);
					Started=false;
					GetLayersBase()->CloseProcessingForm();
					GSleep(500);
					EBase->ClearHaltMode();
				}
			}
			else if(EBase->GetMode()==ExecuteInspectBase::_CaptureNone
			&& Param->ExecuteInspection==true && Param->PermitCapture==true){
			//&& Param->ExecuteInspection==true){
				Param->ExecuteInspection=false;
				//Button.setChecked(true);
//				SlotClicked(true);
				SlotClicked();
			}
		}
	}
	return true;
}

//==================================================================================================

GUICmdStartInspect::GUICmdStartInspect(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdStartInspect::~GUICmdStartInspect(void)
{
}

bool	GUICmdStartInspect::Load(QIODevice *f)
{
	if(::Load(f,StartInspectionTime)==false)
		return false;
	if(::Load(f,CurrentInspectID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,StrategicNumber)==false)
		return false;
	return true;
}
bool	GUICmdStartInspect::Save(QIODevice *f)
{
	if(::Save(f,StartInspectionTime)==false)
		return false;
	if(::Save(f,CurrentInspectID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,StrategicNumber)==false)
		return false;
	return true;
}

void	GUICmdStartInspect::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1 || StrategicNumber==0){
		GetLayersBase()->SetStartInspectTime(StartInspectionTime);
		GetLayersBase()->SetCurrentInspectID(CurrentInspectID);
		GetLayersBase()->SetCurrentStrategicNumber		(StrategicNumber);
		GetLayersBase()->SetCurrentStrategicNumberForSeq(StrategicNumber);
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoInspect();
		}
	}
	
	GUICmdReplyInspect	*SendBack=GetSendBack(GUICmdReplyInspect,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdReplyInspect::GUICmdReplyInspect(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdReplyInspect::~GUICmdReplyInspect(void)
{
}

bool	GUICmdReplyInspect::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReplyInspect::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReplyInspect::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
