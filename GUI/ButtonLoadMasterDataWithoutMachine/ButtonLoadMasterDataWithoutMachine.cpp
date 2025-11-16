#include "ButtonLoadMasterDataWithoutMachineResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadMasterDataWithoutMachine\ButtonLoadMasterDataWithoutMachine.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonLoadMasterDataWithoutMachine.h"
#include "XGeneralDialog.h"
#include "LoadMasterDataWindow.h"
//#include "ButtonLoadMasterDataResource.h"
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
const	char	*sName=/**/"LoadMasterDataWithoutMachine";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show the window to load master data without selecting machine");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLoadMasterDataWithoutMachine(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<11)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonLoadMasterDataWithoutMachine *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadMasterDataWithoutMachine *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadMasterDataWithoutMachine *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadMasterDataWithoutMachine *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowLoadedInfo";
	Data[4].Pointer				 =&((ButtonLoadMasterDataWithoutMachine *)Instance)->ShowLoadedInfo;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"EnableManyTimes";
	Data[5].Pointer				 =&((ButtonLoadMasterDataWithoutMachine *)Instance)->EnableManyTimes;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"SelectLotSRoot";
	Data[6].Pointer				 =&((ButtonLoadMasterDataWithoutMachine *)Instance)->SelectLotSRoot;
	Data[7].Type				 =/**/"QString";
	Data[7].VariableNameWithRoute=/**/"SelectLotSName";
	Data[7].Pointer				 =&((ButtonLoadMasterDataWithoutMachine *)Instance)->SelectLotSName;
	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"InitializeAfterEdit";
	Data[8].Pointer				=&((ButtonLoadMasterDataWithoutMachine *)Instance)->InitializeAfterEdit;
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"ShowSelectToLoadImage";
	Data[9].Pointer				=&((ButtonLoadMasterDataWithoutMachine *)Instance)->ShowSelectToLoadImage;	
	Data[10].Type				 =/**/"QStringList";
	Data[10].VariableNameWithRoute=/**/"IncludedMachines";
	Data[10].Pointer				=&((ButtonLoadMasterDataWithoutMachine *)Instance)->IncludedMachines;	
	Data[11].Type				 =/**/"bool";
	Data[11].VariableNameWithRoute=/**/"ReleaseAutoMode";
	Data[11].Pointer				=&((ButtonLoadMasterDataWithoutMachine *)Instance)->ReleaseAutoMode;	

	return(12);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadMasterDataWithoutMachine.png")));
}

static	bool	MacroLoadMaster(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonLoadMasterDataWithoutMachine	*V=dynamic_cast<ButtonLoadMasterDataWithoutMachine *>(Instance);
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
	ButtonLoadMasterDataWithoutMachine	*V=dynamic_cast<ButtonLoadMasterDataWithoutMachine *>(Instance);
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
ButtonLoadMasterDataWithoutMachine::ButtonLoadMasterDataWithoutMachine(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonLoadMasterDataWithoutMachine");
	Msg=/**/"Load MasterData";
	ShowLoadedInfo		=true;
	EnableManyTimes		=true;
	SelectLotSRoot		=/**/"Button";
	SelectLotSName		=/**/"SelectLot";
	InitializeAfterEdit	=true;
	ShowSelectToLoadImage	=false;
	ReleaseAutoMode			=true;
	iExeLoadMasterData	=NULL;
	iOnLoading			=NULL;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(this,SIGNAL(SignalShowInfo()),this,SLOT(SlotShowInfo()),Qt::QueuedConnection);

	GetParamGUI()->SetParam(&ShowLoadedInfo	, /**/"ButtonLoadMasterDataWithoutMachine"
											, /**/"ShowLoadedInfo"	
											,LangSolver.GetString(ButtonLoadMasterDataWithoutMachine_LS,LID_0)/*"True if algorithm list shows to be loaded"*/);
}

ButtonLoadMasterDataWithoutMachine::~ButtonLoadMasterDataWithoutMachine(void)
{
}

void	ButtonLoadMasterDataWithoutMachine::Prepare(void)
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
			iExeLoadMasterData	=new SignalOperandInt(this,496,/**/"ButtonLoadMasterDataWithoutMachine:iExeLoadMasterData");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iExeLoadMasterData,&Error)==false){
				iExeLoadMasterData->ShowErrorMessage(Error);
			}
			iOnLoading			=new SignalOperandBit(this,496,/**/"ButtonLoadMasterDataWithoutMachine:iOnLoading");
			if(Param->SetSpecialOperand(iOnLoading,&Error)==false){
				iOnLoading->ShowErrorMessage(Error);
			}

			connect(iExeLoadMasterData	,SIGNAL(changed())	,this	,SLOT(OperandExeLoadMAsterData())	,Qt::QueuedConnection);
		}
	}
}

void	ButtonLoadMasterDataWithoutMachine::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonLoadMasterDataWithoutMachine::SlotClicked (bool checked)
{
	LoadMasterDataWindow	*w=new LoadMasterDataWindow(GetLayersBase(),QString(sRoot),QString(sName),this);
	GeneralDialog	D(GetLayersBase(),w,GetLayersBase()->GetMainWidget());
	D.exec();
	if(w->RetMode==true && EnableManyTimes==false){
		Button.setEnabled(false);
	}
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void	ButtonLoadMasterDataWithoutMachine::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonLoadMasterDataWithoutMachine_LS,LID_1)/*"FILE"*/
										 ,LangSolver.GetString(ButtonLoadMasterDataWithoutMachine_LS,LID_2)/*"Load MasterData"*/
										 ,this);
	p->SetMenuNumber(1000);
	Info.AppendList(p);
}
void	ButtonLoadMasterDataWithoutMachine::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	ButtonLoadMasterDataWithoutMachine::RxSync(QByteArray &f)
{
	if(iOnLoading!=NULL){
		iOnLoading->Set(true);
	}

	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);
	int	Count;
	RelationMasterList MasterListDim[100];
	bool	ModeLoadMasterImage=true;
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
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ButtonLoadMasterDataWithoutMachine_LS,LID_3)/*"Loading master data in recieved Sync"*/);
	GetLayersBase()->ClearAllAckFlag(1);
	bool CriticalErrorOccured=false;
	QString ErrorMessageOfFalse;
	bool	ret;
	if(iMasterCode>0){
		ret=GetLayersBase()->SQLLoadMasterData(iMasterCode,GetLayersBase()->GetMachineID()
											   ,ModeLoadMasterImage,CriticalErrorOccured
												,ErrorMessageOfFalse);
	}
	else if(Count>0){
		ret=GetLayersBase()->SQLLoadMasterData(MasterListDim[0].MasterCode,MasterListDim[0].MachineID
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
				QMessageBox::critical ( NULL, LangSolver.GetString(ButtonLoadMasterDataWithoutMachine_LS,LID_4)/*"Reboot"*/
											, LangSolver.GetString(ButtonLoadMasterDataWithoutMachine_LS,LID_5)/*"Reboot software to change critical items"*/
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
			QMessageBox::critical ( NULL, LangSolver.GetString(ButtonLoadMasterDataWithoutMachine_LS,LID_6)/*"Reboot"*/
										, LangSolver.GetString(ButtonLoadMasterDataWithoutMachine_LS,LID_7)/*"Reboot software to change critical items"*/
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

void	ButtonLoadMasterDataWithoutMachine::SlotShowInfo(void)
{
	if(ShowLoadedInfo==true){
		ShowLoadedInfoForm	*ShowLoadedInfo=new ShowLoadedInfoForm(GetLayersBase());
		ShowLoadedInfo->show();
		ShowLoadedInfo->update();
	}
	BroadcastBuildForShow();
}
void	ButtonLoadMasterDataWithoutMachine::OperandExeLoadMAsterData()
{
	if(iExeLoadMasterData!=NULL){
		int	iMasterID=iExeLoadMasterData->Get();
		CommandLoadMaster(iMasterID,true);
		iExeLoadMasterData->Set(0);
	}
}

void	ButtonLoadMasterDataWithoutMachine::CommandLoadMaster(int MasterCode,bool	ModeLoadMasterImage)
{
	if(iOnLoading!=NULL){
		iOnLoading->Set(false);
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
				QMessageBox::critical ( NULL, LangSolver.GetString(LoadMasterDataWindow_LS,LID_7)/*"Reboot"*/
											, LangSolver.GetString(LoadMasterDataWindow_LS,LID_8)/*"Reboot software to change critical items"*/
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
			QMessageBox::critical ( NULL, LangSolver.GetString(LoadMasterDataWindow_LS,LID_7)/*"Reboot"*/
										, LangSolver.GetString(LoadMasterDataWindow_LS,LID_8)/*"Reboot software to change critical items"*/
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