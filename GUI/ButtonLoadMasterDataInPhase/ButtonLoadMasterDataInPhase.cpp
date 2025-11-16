/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadMasterDataInPhase\ButtonLoadMasterDataInPhase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonLoadMasterDataInPhase.h"
#include "XGeneralDialog.h"
#include "LoadMasterDataWindow.h"
#include "XGeneralFunc.h"
#include "ButtonSelectLot.h"
#include "ButtonSelectMachine.h"
#include "ShowLoadedInfoForm.h"
#include "XMacroFunction.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XParamDatabase.h"
#include <QMessageBox>
#include "XEntryPoint.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"LoadMasterDataInPhas";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show the window to load master data");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendInitialXYPixelsData	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLoadMasterDataInPhase(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<14)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonLoadMasterDataInPhase *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadMasterDataInPhase *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadMasterDataInPhase *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadMasterDataInPhase *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowLoadedInfo";
	Data[4].Pointer				 =&((ButtonLoadMasterDataInPhase *)Instance)->ShowLoadedInfo;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"EnableManyTimes";
	Data[5].Pointer				 =&((ButtonLoadMasterDataInPhase *)Instance)->EnableManyTimes;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"SelectLotSRoot";
	Data[6].Pointer				 =&((ButtonLoadMasterDataInPhase *)Instance)->SelectLotSRoot;
	Data[7].Type				 =/**/"QString";
	Data[7].VariableNameWithRoute=/**/"SelectLotSName";
	Data[7].Pointer				 =&((ButtonLoadMasterDataInPhase *)Instance)->SelectLotSName;
	Data[8].Type				 =/**/"QString";
	Data[8].VariableNameWithRoute=/**/"SelectMachineSRoot";
	Data[8].Pointer				 =&((ButtonLoadMasterDataInPhase *)Instance)->SelectMachineSRoot;
	Data[9].Type				 =/**/"QString";
	Data[9].VariableNameWithRoute=/**/"SelectMachineSName";
	Data[9].Pointer				 =&((ButtonLoadMasterDataInPhase *)Instance)->SelectMachineSName;
	Data[10].Type				 =/**/"bool";
	Data[10].VariableNameWithRoute=/**/"InitializeAfterEdit";
	Data[10].Pointer				=&((ButtonLoadMasterDataInPhase *)Instance)->InitializeAfterEdit;
	Data[11].Type				 =/**/"bool";
	Data[11].VariableNameWithRoute=/**/"ShowSelectToLoadImage";
	Data[11].Pointer				=&((ButtonLoadMasterDataInPhase *)Instance)->ShowSelectToLoadImage;	
	Data[12].Type				 =/**/"bool";
	Data[12].VariableNameWithRoute=/**/"ReleaseAutoMode";
	Data[12].Pointer				=&((ButtonLoadMasterDataInPhase *)Instance)->ReleaseAutoMode;	
	Data[13].Type				 =/**/"int32";
	Data[13].VariableNameWithRoute=/**/"DestinationPhase";
	Data[13].Pointer				=&((ButtonLoadMasterDataInPhase *)Instance)->DestinationPhase;	

	return(14);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadMasterDataInPhase.png")));
}

static	bool	MacroLoadMaster(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonLoadMasterDataInPhase	*V=dynamic_cast<ButtonLoadMasterDataInPhase *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	MasterID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	bool	ModeLoadMasterImage=false;
	if(Args[1].toLower()==/**/"true")
		ModeLoadMasterImage=true;
	V->CommandLoadMaster(MasterID,ModeLoadMasterImage);

	return true;
}

static	bool	MacroOpenLoadDialog(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonLoadMasterDataInPhase	*V=dynamic_cast<ButtonLoadMasterDataInPhase *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotClicked(true);

	return true;
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Load master";
		Functions[ret].Explain.append(/**/"Load master data");
		Functions[ret].ArgName.append(/**/"MasterCode");
		Functions[ret].ArgName.append(/**/"LoadMasterImage?(true/false)");
		Functions[ret].DLL_ExcuteMacro	=MacroLoadMaster;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenLoadDialog";
		Functions[ret].Explain.append(/**/"Open dialog to load master data");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenLoadDialog;
		ret++;
	}

	return ret;
}
//==================================================================================================
ButtonLoadMasterDataInPhase::ButtonLoadMasterDataInPhase(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonLoadMasterDataInPhase");
	Msg=/**/"Load MasterData";
	ShowLoadedInfo		=true;
	EnableManyTimes		=true;
	SelectLotSRoot		=/**/"Button";
	SelectLotSName		=/**/"SelectLot";
	SelectMachineSRoot	=/**/"Button";
	SelectMachineSName	=/**/"SelectMachine";
	InitializeAfterEdit	=true;
	ShowSelectToLoadImage	=false;
	ReleaseAutoMode		=true;
	iExeLoadMasterData	=NULL;
	iOnLoading			=NULL;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(this,SIGNAL(SignalShowInfo()),this,SLOT(SlotShowInfo()),Qt::QueuedConnection);

	GetParamGUI()->SetParam(&ShowLoadedInfo, /**/"ButtonLoadMaster",/**/"ShowLoadedInfo"	
												,"True if algorithm list shows to be loaded");
}

ButtonLoadMasterDataInPhase::~ButtonLoadMasterDataInPhase(void)
{
}

void	ButtonLoadMasterDataInPhase::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
	if(GetLayersBase()->GetInsideLearningEditor()==true){
		Button.setEnabled(false);
	}
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iExeLoadMasterData	=new SignalOperandInt(this,496,/**/"ButtonLoadMasterDataInPhase:iExeLoadMasterData");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iExeLoadMasterData,&Error)==false){
				iExeLoadMasterData->ShowErrorMessage(Error);
			}
			iOnLoading			=new SignalOperandBit(this,496,/**/"ButtonLoadMasterDataInPhase:iOnLoading");
			if(Param->SetSpecialOperand(iOnLoading,&Error)==false){
				iOnLoading->ShowErrorMessage(Error);
			}

			connect(iExeLoadMasterData	,SIGNAL(changed())	,this	,SLOT(OperandExeLoadMAsterData())	,Qt::QueuedConnection);
		}
	}

}

void	ButtonLoadMasterDataInPhase::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonLoadMasterDataInPhase::SlotClicked (bool checked)
{
	LoadMasterDataWindow	*w=new LoadMasterDataWindow(GetLayersBase(),QString(sRoot),QString(sName),this);
	w->DestinationPhase	=DestinationPhase;
	GeneralDialog	D(GetLayersBase(),w,GetLayersBase()->GetMainWidget());
	D.exec();
	if(w->RetMode==true && EnableManyTimes==false){
		Button.setEnabled(false);
	}
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void	ButtonLoadMasterDataInPhase::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,"FILE"
										 ,"Load MasterData"
										 ,this);
	p->SetMenuNumber(1000);
	Info.AppendList(p);
}
void	ButtonLoadMasterDataInPhase::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	ButtonLoadMasterDataInPhase::RxSync(QByteArray &f)
{
	if(iOnLoading!=NULL){
		iOnLoading->Set(true);
	}

	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);
	int	Count;
	RelationMasterList MasterListDim[100];
	bool	ModeLoadMasterImage=true;
	int32	iDestinationPhase;
	::Load(&Buff,iDestinationPhase);
	::Load(&Buff,Count);
	for(int i=0;i<Count;i++){
		::Load(&Buff,MasterListDim[i].MasterCode);
		::Load(&Buff,MasterListDim[i].MachineID);
	}
	::Load(&Buff,ModeLoadMasterImage);
	int	iMasterCode=-1;
	for(int i=0;i<Count;i++){
		if(MasterListDim[i].MachineID==GetLayersBase()->GetMachineID()){
			iMasterCode=MasterListDim[i].MasterCode;
			break;
		}
	}
	int	DotPerLine	=GetLayersBase()->GetDotPerLine(-1);
	int	MaxLines	=GetLayersBase()->GetMaxLines(-1);
	int	PageNumb	=GetLayersBase()->GetPageNumb();
	GetLayersBase()->ClearAllAckFlag(1);
	GetLayersBase()->ShowProcessingForm ("Loading master data in recieved Sync");
	bool CriticalErrorOccured=false;
	bool	ret;
	QString ErrorMessageOfFalse;
	if(iMasterCode>0){
		ret=GetLayersBase()->SQLLoadMasterDataIn1Phase(iMasterCode,GetLayersBase()->GetMachineID()
														,iDestinationPhase
														,ModeLoadMasterImage,CriticalErrorOccured
														,ErrorMessageOfFalse);
	}
	else if(Count>0){
		ret=GetLayersBase()->SQLLoadMasterDataIn1Phase(MasterListDim[0].MasterCode,MasterListDim[0].MachineID
														,iDestinationPhase
														,ModeLoadMasterImage,CriticalErrorOccured
														,ErrorMessageOfFalse);
	}
	else{
		ret=false;
	}
	if(ret==true){
		ExecuteInitialAfterEditInfo EInfo;
		EInfo.CalledInLoadMaster=true;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
		GetLayersBase()->WaitAllAcknowledged(60*100);
		GetLayersBase()->CloseProcessingForm ();
	
		if(GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
			if(DotPerLine	!=GetLayersBase()->GetDotPerLine(-1)
			|| MaxLines		!=GetLayersBase()->GetMaxLines(-1)
			|| PageNumb		!=GetLayersBase()->GetPageNumb()){
				GetLayersBase()->WriteAllSettingFiles();
				GetLayersBase()->SendSettingsToSlave();
				QMessageBox::critical ( NULL, "Reboot"
											, "Reboot software to change critical items"
											, QMessageBox::Ok);
				GetLayersBase()->CloseAll();
				QCoreApplication::quit();	
				if(iOnLoading!=NULL){
					iOnLoading->Set(false);
				}	
				return;
			}
		}
		emit	SignalShowInfo();
	}
	else{
		GetLayersBase()->CloseProcessingForm ();
		if(CriticalErrorOccured==true){
			GetLayersBase()->WriteAllSettingFiles();
			GetLayersBase()->SendSettingsToSlave();
			QMessageBox::critical ( NULL, "Reboot"
										, "Reboot software to change critical items"
										, QMessageBox::Ok);
			GetLayersBase()->CloseAll();
			QCoreApplication::quit();	
			if(iOnLoading!=NULL){
				iOnLoading->Set(false);
			}	
			return;
		}
		QMessageBox::critical(NULL,"Load Error",ErrorMessageOfFalse);
	}

	LoadMasterSpecifiedBroadcaster	SData;
	BroadcastSpecifiedDirectly(&SData);

	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());

	if(EnableManyTimes==false){
		Button.setEnabled(false);
	}
	if(iOnLoading!=NULL){
		iOnLoading->Set(false);
	}	
}
void	ButtonLoadMasterDataInPhase::OperandExeLoadMAsterData()
{
	if(iExeLoadMasterData!=NULL){
		int	iMasterID=iExeLoadMasterData->Get();
		CommandLoadMaster(iMasterID,true);
	}
}
void	ButtonLoadMasterDataInPhase::CommandLoadMaster(int MasterCode,bool	ModeLoadMasterImage)
{
	if(iOnLoading!=NULL){
		iOnLoading->Set(true);
	}
	int	DotPerLine	=GetLayersBase()->GetDotPerLine(-1);
	int	MaxLines	=GetLayersBase()->GetMaxLines(-1);
	int	PageNumb	=GetLayersBase()->GetPageNumb();
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm ("Loading master data");
	bool CriticalErrorOccured=false;
	bool	ret=false;
	QString ErrorMessageOfFalse;
	if(MasterCode>0){
		ret=GetLayersBase()->SQLLoadMasterData(MasterCode,GetLayersBase()->GetMachineID()
											   ,ModeLoadMasterImage,CriticalErrorOccured
												,ErrorMessageOfFalse);
	}

	if(ret==true){
		ExecuteInitialAfterEditInfo EInfo;
		EInfo.CalledInLoadMaster=true;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
		GetLayersBase()->WaitAllAcknowledged(60*100,true);
		GetLayersBase()->CloseProcessingForm ();
	
		if(GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
			if(DotPerLine	!=GetLayersBase()->GetDotPerLine(-1)
			|| MaxLines		!=GetLayersBase()->GetMaxLines(-1)
			|| PageNumb		==GetLayersBase()->GetPageNumb()){
				for(int page=0;page<GetParamGlobal()->PageNumb;page++){
					int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
					GUICmdSendInitialXYPixelsData	RCmd(GetLayersBase(),sRoot,sName,globalPage);
					RCmd.DotPerLine	=DotPerLine;
					RCmd.MaxLines	=MaxLines;
					RCmd.Send(NULL,globalPage,0);
				}
					
				GetLayersBase()->ReallocXYPixels(DotPerLine,MaxLines);
			}
			else 
			if(DotPerLine	!=GetLayersBase()->GetDotPerLine(-1)
			|| MaxLines		!=GetLayersBase()->GetMaxLines(-1)
			|| PageNumb		!=GetLayersBase()->GetPageNumb()){
				GetLayersBase()->WriteAllSettingFiles();
				GetLayersBase()->SendSettingsToSlave();
				QMessageBox::critical ( NULL, "Reboot"
											, "Reboot software to change critical items"
											, QMessageBox::Ok);
				GetLayersBase()->CloseAll();
				QCoreApplication::quit();	
				if(iOnLoading!=NULL){
					iOnLoading->Set(false);
				}
				return;
			}
		}
		emit	SignalShowInfo();
	}
	else{
		GetLayersBase()->CloseProcessingForm ();
		if(CriticalErrorOccured==true){
			GetLayersBase()->WriteAllSettingFiles();
			GetLayersBase()->SendSettingsToSlave();
			QMessageBox::critical ( NULL, "Reboot"
										, "Reboot software to change critical items"
										, QMessageBox::Ok);
			GetLayersBase()->CloseAll();
			QCoreApplication::quit();	
			if(iOnLoading!=NULL){
				iOnLoading->Set(false);
			}
			return;
		}
		QMessageBox::critical(NULL,"Load Error",ErrorMessageOfFalse);
	}
	GetLayersBase()->CloseInformed();
	LoadMasterSpecifiedBroadcaster	SData;
	BroadcastSpecifiedDirectly(&SData);

	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());


	if(EnableManyTimes==false){
		Button.setEnabled(false);
	}
	
	if(iOnLoading!=NULL){
		iOnLoading->Set(false);
	}
}

void	ButtonLoadMasterDataInPhase::SlotShowInfo(void)
{
	if(ShowLoadedInfo==true){
		ShowLoadedInfoForm	*ShowLoadedInfo=new ShowLoadedInfoForm(GetLayersBase());
		ShowLoadedInfo->show();
		ShowLoadedInfo->update();
	}
	BroadcastBuildForShow();
}

//----------------------------------------------------------------------------------

GUICmdSendInitialXYPixelsData::GUICmdSendInitialXYPixelsData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendInitialXYPixelsData::Load(QIODevice *f)
{
	if(::Load(f,DotPerLine)==false)
		return false;
	if(::Load(f,MaxLines)==false)
		return false;
	return true;
}
bool	GUICmdSendInitialXYPixelsData::Save(QIODevice *f)
{
	if(::Save(f,DotPerLine)==false)
		return false;
	if(::Save(f,MaxLines)==false)
		return false;
	return true;
}

void	GUICmdSendInitialXYPixelsData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->ReallocXYPixels(DotPerLine,MaxLines);
}