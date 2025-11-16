/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectCountedLot\ButtonSelectCountedLot.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "ButtonSelectLotResource.h"
#include "ButtonSelectCountedLot.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "SelectLotForm.h"
#include "XGeneralDialog.h"
#include "XResultDLLManager.h"
#include "XSequenceLocal.h"
#include "SelectLotDialog.h"
#include "XLotInformation.h"

char	*sRoot=/**/"Button";
char	*sName=/**/"SelectCountedLot";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for select-lot dialog with counter");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonSelectCountedLot(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSelectCountedLot *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSelectCountedLot *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSelectCountedLot *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSelectCountedLot *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSelectCountedLot.png")));
}

//==================================================================================================


ButtonSelectCountedLot::ButtonSelectCountedLot(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonSelectLot");
	Msg=/**/"Select lot";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	LoadLastID=true;
	GetParamGUI()->SetParam(&LoadLastID, /**/"ButtonSelectCountedLot",/**/"LoadLastID"		
							,/**/"True if loading last ID"	);
	StartCount	=0;
	NGCount		=0;
}

ButtonSelectCountedLot::~ButtonSelectCountedLot(void)
{
}

void	ButtonSelectCountedLot::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();

	GetLayersBase()->ReplaceLotInstance(new LotInformationWithCounted(GetLayersBase()));
}

void	ButtonSelectCountedLot::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSelectCountedLot::SlotClicked (bool checked)
{
	/*
	SelectLotForm	*SelectLot=new SelectLotForm(GetLayersBase(),this);
	LogoInQWidget(GetLayersBase(),SelectLot,sRoot ,sName);
	GeneralDialog	D(GetLayersBase(),SelectLot,this);
	D.exec();
	if(SelectLot->RetMode==true){
		SetLotToSystem(SelectLot->SelectedLotAutoCount
					  ,SelectLot->SelectedLotID
					  ,SelectLot->SelectedLotName);
	}
	*/
	static	bool	Connected=true;

	SelectLotDialog	*SelectLot=new SelectLotDialog(GetLayersBase(),this);
	SelectLot->exec();
	if(SelectLot->RetMode==true){
		SelectedLotID=SelectLot->SelectedLotID;
		LotCountNumber	=SelectLot->LotCountNumber;

		StartCount=GetMaxLotID(SelectedLotID);
		QString	xLotID=CalcLotID(SelectedLotID,StartCount);
		StartCount++;

		SetLotToSystem(SelectLot->SelectedLotAutoCount
					  ,xLotID
					  ,SelectLot->SelectedLotName
					  ,SelectLot->LotCountNumber);
		if(!disconnect(GetLayersBase()->GetResultThread(),SIGNAL(SignalWroteCommon(XDateTime))	
					,this,SLOT(SlotWroteCommon(XDateTime)))){
			Connected=false;
		}
		else{
			Connected=true;
		}
		if(!connect(GetLayersBase()->GetResultThread(),SIGNAL(SignalWroteCommon(XDateTime))	
					,this,SLOT(SlotWroteCommon(XDateTime)),Qt::QueuedConnection)){
			Connected=true;
		}
		else{
			Connected=true;
		}
	}
	delete	SelectLot;
}

int	ButtonSelectCountedLot::GetMaxLotID(const QString &iLotID)
{
	int	k=iLotID.indexOf("[*]");
	if(k>=0){
		for(int i=1;;i++){
			QString	xLotID=iLotID.left(k)+QString::number(i)+iLotID.mid(k+3);
			if(GetLayersBase()->GetResultDLLBase()->SearchLotID(xLotID)==false){
				return i;
			}
			GSleep(100);
		}
	}
	return 0;
}

void	ButtonSelectCountedLot::SlotWroteCommon(XDateTime tm)
{
	ResultInspectionForStock	*r=GetLayersBase()->GetResultThread()->Pickup(tm);
	if(r!=NULL){
		if(r->IsResultOK()==false){
			NGCount++;
		}
		if(NGCount>=LotCountNumber){
			QString	xLotID=CalcLotID(SelectedLotID,StartCount);
			StartCount++;
		
			SetLotToSystem(GetLayersBase()->GetLot()->GetLotAutoCount()
						  ,xLotID
						  ,GetLayersBase()->GetLot()->GetLotName()
						  ,LotCountNumber);
		}
	}
}


QString	ButtonSelectCountedLot::CalcLotID(const QString &iLotID ,int iStartCount)
{
	int	k=iLotID.indexOf("[*]");
	if(k>=0){
		QString	xLotID=iLotID.left(k)+QString::number(iStartCount)+iLotID.mid(k+3);
		return xLotID;
	}
	return iLotID;
}

void ButtonSelectCountedLot::SetLotToSystem(int iLotAutoCount
									,const QString &iLotID
									,const QString &iLotName
									,int LotCountNumber)
{
	GetLayersBase()->RemoveStockedResult();

	GetLayersBase()->GetLot()->SetLotAutoCount	(iLotAutoCount);
	GetLayersBase()->GetLot()->SetLotID			(iLotID);
	GetLayersBase()->GetLot()->SetLotName		(iLotName);
	GetLayersBase()->ClearInspectID();
	int64 InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();

	if(LoadLastID==true){
		if(GetLayersBase()->GetResultDLLBase()->GetLastInspectionID(GetLayersBase()->GetMasterCode(),iLotID,InspectionID)==true)
			InspectionID++;
	}
	GetLayersBase()->SetCurrentInspectID(InspectionID);

	GetLayersBase()->SetForceChangedInspectID();
	GetLayersBase()->GetResultHistryData()->Reset();

	BroadcastDirectly(_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());

	//?・・・・・?・D?・S102?・?宿・鐃・・・D?・・・?・?・?・・・・
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			Param->InspectionID=InspectionID;
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		GUICmdSelectLot	RCmd(GetLayersBase(),sRoot,sName ,page);
		RCmd.LotAutoCount	=iLotAutoCount;
		RCmd.LotID			=iLotID;
		RCmd.LotName		=iLotName;
		RCmd.LotCountNumber	=LotCountNumber;
		RCmd.Send(NULL,page,0);
	}
	//GetLayersBase()->ShowProcessingForm();
	GetLayersBase()->GetResultDLLBase()->OutputInLotChangedCommon();
	GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	//GetLayersBase()->CloseProcessingForm();
	NGCount=0;
}

void	ButtonSelectCountedLot::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSelectLot	*CmdSelectLotVar=dynamic_cast<CmdSelectLot *>(packet);
	if(CmdSelectLotVar!=NULL){
		SlotClicked (true);
	}
}

void	ButtonSelectCountedLot::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,/**/"Execute",/**/"Select Lot",this);
	p->SetMenuNumber(100);
	Info.AppendList(p);
}
void	ButtonSelectCountedLot::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	ButtonSelectCountedLot::RxSync(QByteArray &f)
{
	SelectLotDialog	*SelectLot=new SelectLotDialog(GetLayersBase(),this);
	if(SelectLot->RxSync(f)==true){
		SelectedLotID=SelectLot->SelectedLotID;
		LotCountNumber	=SelectLot->LotCountNumber;

		StartCount=GetMaxLotID(SelectedLotID);
		QString	xLotID=CalcLotID(SelectedLotID,StartCount);
		StartCount++;

		SetLotToSystem(SelectLot->SelectedLotAutoCount
					  ,xLotID
					  ,SelectLot->SelectedLotName
					  ,LotCountNumber);
		static	bool	Connected=true;
		if(!disconnect(GetLayersBase()->GetResultThread(),SIGNAL(SignalWroteCommon(XDateTime))	
					,this,SLOT(SlotWroteCommon(XDateTime)))){
			Connected=false;
		}
		else{
			Connected=true;
		}
		if(!connect(GetLayersBase()->GetResultThread(),SIGNAL(SignalWroteCommon(XDateTime))	
					,this,SLOT(SlotWroteCommon(XDateTime)),Qt::QueuedConnection)){
			Connected=true;
		}
		else{
			Connected=true;
		}
	}
	delete	SelectLot;
}

GUICmdSelectLot::GUICmdSelectLot(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSelectLot::Load(QIODevice *f)
{
	if(::Load(f,LotAutoCount)==false)
		return false;
	if(::Load(f,LotID)==false)
		return false;
	if(::Load(f,LotName)==false)
		return false;
	if(::Load(f,LotCountNumber)==false)
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
	if(::Save(f,LotCountNumber)==false)
		return false;
	return true;
}
void	GUICmdSelectLot::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==false){
			GetLayersBase()->GetLot()->SetLotAutoCount	(LotAutoCount);
			GetLayersBase()->GetLot()->SetLotID			(LotID);
			GetLayersBase()->GetLot()->SetLotName		(LotName);

			int64	InspectionID;
			GetLayersBase()->GetResultDLLBase()->GetLastInspectionID(GetLayersBase()->GetMasterCode()
																	,LotID
																	,InspectionID);
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
	}
}

