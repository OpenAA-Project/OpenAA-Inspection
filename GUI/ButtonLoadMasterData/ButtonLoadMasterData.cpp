/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadMasterData\ButtonLoadMasterData.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonLoadMasterData.h"
#include "XGeneralDialog.h"
#include "LoadMasterDataWindow.h"
#include "ButtonLoadMasterDataResource.h"
#include "XGeneralFunc.h"
#include "ButtonSelectLot.h"
#include "ButtonSelectMachine.h"
#include "ShowLoadedInfoForm.h"
#include "XMacroFunction.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include <QMessageBox>
#include "XParamDatabase.h"
#include "XEntryPoint.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"LoadMasterData";


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
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonLoadMasterData(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<10)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonLoadMasterData *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadMasterData *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadMasterData *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadMasterData *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowLoadedInfo";
	Data[4].Pointer				 =&((ButtonLoadMasterData *)Instance)->ShowLoadedInfo;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"EnableManyTimes";
	Data[5].Pointer				 =&((ButtonLoadMasterData *)Instance)->EnableManyTimes;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"SelectLotSRoot";
	Data[6].Pointer				 =&((ButtonLoadMasterData *)Instance)->SelectLotSRoot;
	Data[7].Type				 =/**/"QString";
	Data[7].VariableNameWithRoute=/**/"SelectLotSName";
	Data[7].Pointer				 =&((ButtonLoadMasterData *)Instance)->SelectLotSName;
	Data[8].Type				 =/**/"QString";
	Data[8].VariableNameWithRoute=/**/"SelectMachineSRoot";
	Data[8].Pointer				 =&((ButtonLoadMasterData *)Instance)->SelectMachineSRoot;
	Data[9].Type				 =/**/"QString";
	Data[9].VariableNameWithRoute=/**/"SelectMachineSName";
	Data[9].Pointer				 =&((ButtonLoadMasterData *)Instance)->SelectMachineSName;
	Data[10].Type				 =/**/"bool";
	Data[10].VariableNameWithRoute=/**/"InitializeAfterEdit";
	Data[10].Pointer				=&((ButtonLoadMasterData *)Instance)->InitializeAfterEdit;
	Data[11].Type				 =/**/"bool";
	Data[11].VariableNameWithRoute=/**/"ShowSelectToLoadImage";
	Data[11].Pointer				=&((ButtonLoadMasterData *)Instance)->ShowSelectToLoadImage;	
	Data[12].Type				 =/**/"bool";
	Data[12].VariableNameWithRoute=/**/"ReleaseAutoMode";
	Data[12].Pointer				=&((ButtonLoadMasterData *)Instance)->ReleaseAutoMode;	

	return(13);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadMasterData.png")));
}

static	bool	MacroLoadMaster(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonLoadMasterData	*V=dynamic_cast<ButtonLoadMasterData *>(Instance);
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

	bool	SilentMode=false;
	if(Args.count()>=3){
		if(Args[2].toUpper()==QString("TRUE")){
			SilentMode=true;
		}
	}

	V->CommandLoadMaster(MasterID,ModeLoadMasterImage,SilentMode);

	return true;
}

static	bool	MacroOpenLoadDialog(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonLoadMasterData	*V=dynamic_cast<ButtonLoadMasterData *>(Instance);
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
		Functions[ret].ArgName.append(/**/"Silent mode TRUE/false (Optional)");
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
ButtonLoadMasterData::ButtonLoadMasterData(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonLoadMasterData");
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
												,LangSolver.GetString(ButtonLoadMasterData_LS,LID_29)/*"True if algorithm list shows to be loaded"*/);
}

ButtonLoadMasterData::~ButtonLoadMasterData(void)
{
}

void	ButtonLoadMasterData::Prepare(void)
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
			iExeLoadMasterData	=new SignalOperandInt(this,496	,/**/"LoadMasterData:iExeLoadMasterData");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iExeLoadMasterData,&Error)==false){
				iExeLoadMasterData->ShowErrorMessage(Error);
			}
			iOnLoading			=new SignalOperandBit(this,496	,/**/"LoadMasterData:iOnLoading");
			if(Param->SetSpecialOperand(iOnLoading	,&Error)==false){
				iOnLoading->ShowErrorMessage(Error);
			}

			connect(iExeLoadMasterData	,SIGNAL(changed())	,this	,SLOT(OperandExeLoadMAsterData())	,Qt::QueuedConnection);
		}
	}

}

void	ButtonLoadMasterData::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonLoadMasterData::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetShadowLevel()>0){
		return;
	}
	LoadMasterDataWindow	*w=new LoadMasterDataWindow(GetLayersBase(),QString(sRoot),QString(sName),this);
	GeneralDialog	D(GetLayersBase(),w,GetLayersBase()->GetMainWidget());
	D.exec();
	if(w->RetMode==true && EnableManyTimes==false){
		Button.setEnabled(false);
	}
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void	ButtonLoadMasterData::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonLoadMasterData_LS,LID_24)/*"FILE"*/
										 ,LangSolver.GetString(ButtonLoadMasterData_LS,LID_25)/*"Load MasterData"*/
										 ,this);
	p->SetMenuNumber(1000);
	Info.AppendList(p);
}
void	ButtonLoadMasterData::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	ButtonLoadMasterData::RxSync(QByteArray &f)
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
	GetLayersBase()->ClearAllAckFlag(1);
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ButtonLoadMasterData_LS,LID_9)/*"Loading master data in recieved Sync"*/);
	bool CriticalErrorOccured=false;
	bool	ret;
	//GetLayersBase()->LockWChangingDataStructure();

	QString ErrorMessageOfFalse;
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
		QMessageBox::critical(NULL,"Error",ErrorMessageOfFalse);
		ret=false;
	}
	if(ret==true){
		LoadMasterBeforeFinilizeSpecifiedBroadcaster	SData;
		BroadcastSpecifiedDirectly(&SData);

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
				QMessageBox::critical ( NULL, LangSolver.GetString(LoadMasterDataWindow_LS,LID_7)/*"Reboot"*/
											, LangSolver.GetString(LoadMasterDataWindow_LS,LID_8)/*"Reboot software to change critical items"*/
											, QMessageBox::Ok);
				GetLayersBase()->CloseAll();
				QCoreApplication::quit();

				if(iOnLoading!=NULL){
					iOnLoading->Set(false);
				}
				//GetLayersBase()->UnlockChangingDataStructure();
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
			//GetLayersBase()->UnlockChangingDataStructure();
			return;
		}
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
	//GetLayersBase()->UnlockChangingDataStructure();
}
void	ButtonLoadMasterData::OperandExeLoadMAsterData()
{
	if(iExeLoadMasterData!=NULL){
		int	iMasterID=iExeLoadMasterData->Get();
		CommandLoadMaster(iMasterID,true,true);
		iExeLoadMasterData->Set(0);
	}
}
void	ButtonLoadMasterData::CommandLoadMaster(int MasterCode,bool	ModeLoadMasterImage ,bool SilentMode)
{
	if(iOnLoading!=NULL){
		iOnLoading->Set(false);
	}	
	int	DotPerLine	=GetLayersBase()->GetDotPerLine(-1);
	int	MaxLines	=GetLayersBase()->GetMaxLines(-1);
	int	PageNumb	=GetLayersBase()->GetPageNumb();
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ButtonLoadMasterData_LS,LID_10)/*"Loading master data"*/);
	bool CriticalErrorOccured=false;
	bool	ret=false;

	//GetLayersBase()->LockWChangingDataStructure();
	QString ErrorMessageOfFalse;
	if(MasterCode>0){
		ret=GetLayersBase()->SQLLoadMasterData(MasterCode,GetLayersBase()->GetMachineID()
											   ,ModeLoadMasterImage,CriticalErrorOccured
												,ErrorMessageOfFalse);
	}

	if(ret==true){
		LoadMasterBeforeFinilizeSpecifiedBroadcaster	SData;
		BroadcastSpecifiedDirectly(&SData);

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
				if(SilentMode==false){
					QMessageBox::critical ( NULL, LangSolver.GetString(LoadMasterDataWindow_LS,LID_7)/*"Reboot"*/
												, LangSolver.GetString(LoadMasterDataWindow_LS,LID_8)/*"Reboot software to change critical items"*/
												, QMessageBox::Ok);
				}
				GetLayersBase()->CloseAll();
				QCoreApplication::quit();	
				if(iOnLoading!=NULL){
					iOnLoading->Set(false);
				}	
				//GetLayersBase()->UnlockChangingDataStructure();
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
			if(SilentMode==false){
				QMessageBox::critical ( NULL, LangSolver.GetString(LoadMasterDataWindow_LS,LID_7)/*"Reboot"*/
											, LangSolver.GetString(LoadMasterDataWindow_LS,LID_8)/*"Reboot software to change critical items"*/
											, QMessageBox::Ok);
			}
			GetLayersBase()->CloseAll();
			QCoreApplication::quit();	

			if(iOnLoading!=NULL){
				iOnLoading->Set(false);
			}
			//GetLayersBase()->UnlockChangingDataStructure();
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
	//GetLayersBase()->UnlockChangingDataStructure();
}

void	ButtonLoadMasterData::SlotShowInfo(void)
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
	GetLayersBase()->LockWChangingDataStructure();
	GetLayersBase()->ReallocXYPixels(DotPerLine,MaxLines);
	GetLayersBase()->UnlockChangingDataStructure();
}