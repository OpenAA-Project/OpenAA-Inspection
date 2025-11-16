/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadRelease\ButtonLoadRelease.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonLoadRelease.h"
#include "XGUI.h"
#include "SettingLoadReleaseDialog.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"LoadRelease";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Load / Release partial data");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqRelease	(Base ,sRoot,sName ,-1);
	(*Base)=new GUICmdReqLoad		(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLoadRelease(Base,parent));
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
	Data[0].Pointer				 =&((ButtonLoadRelease *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadRelease *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadRelease *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadRelease *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadRelease.png")));
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	QByteArray	Array;
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"SAVEOUTLINEOFFSET",Array);
	//A->TableName=/**/"MASTERDATA";
	//A->FieldName=/**/"SAVEOUTLINEOFFSET";
	//QByteArray	Array;
	//A->DefaultData.setValue(Array);
	Data.AppendList(A);
}
//==================================================================================================

ButtonLoadRelease::ButtonLoadRelease(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SwapInOut	=true;
	SwapPath	=/**/"d:\\data";
	AllocateMasterBuff	=true;
	AllocateTargetBuff	=true;

	Button.setParent(this);
	Button.move(0,0);
	Button.setCheckable(true);
	Msg=/**/"Load/Release";
	resize(100,25);
	bool Ret1=(connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool))))?true:false;
	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;

	GetParamGUI()->SetParam(&SettingDataArray, /**/"ButtonLoadRelease", /**/"Setting"		
											 , "True if loading last ID"		);
	GetParamGUI()->SetParam(&SwapInOut		, /**/"ButtonLoadRelease", /**/"SwapInOut"		
											 , "Swap In/Out when master data is not saved"		);
	GetParamGUI()->SetParam(&SwapPath		, /**/"ButtonLoadRelease", /**/"SwapPath"		
											 , "Path for swap in/out"		);
	bool	Ret=(connect(GetParamGUI(),SIGNAL(SignalExecuteForByteArray(const QString & ,const QString & ,QByteArray &)),this,SLOT(SlotExecuteForByteArray(const QString & ,const QString & ,QByteArray &))))?true:false;
}

ButtonLoadRelease::~ButtonLoadRelease(void)
{
}

void	ButtonLoadRelease::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLoadRelease::ReadyParam(void)
{
	if(SettingDataArray.count()>0){
		QBuffer	Buff(&SettingDataArray);
		Buff.open(QIODevice::ReadWrite);
		SettingData.Load(&Buff);
	}
}

void	ButtonLoadRelease::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonLoadRelease::SlotClicked(bool checked)
{
	GetLayersBase()->TmpHideProcessingForm();
	if(Button.isChecked()==true){
		GetLayersBase()->ClearAllAckFlag();
		GetLayersBase()->ShowProcessingForm("Save and release memory...");
		GetLayersBase()->SetMaxProcessing(0);

		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqRelease	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
			RCmd.SettingData	=SettingData;
			RCmd.SwapInOut		=SwapInOut;
			RCmd.SwapPath		=SwapPath;
			RCmd.Send(NULL,page,0);
		}

		GetLayersBase()->WaitAllAcknowledged(60*GetPageNumb());
		GetLayersBase()->CloseProcessingForm ();
	}
	else{
		GetLayersBase()->ClearAllAckFlag();
		GetLayersBase()->ShowProcessingForm("Restore and realloc memory...");
		GetLayersBase()->SetMaxProcessing(0);

		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqLoad		RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
			RCmd.SettingData	=SettingData;
			RCmd.SwapInOut		=SwapInOut;
			RCmd.SwapPath		=SwapPath;
			RCmd.Send(NULL,page,0);
		}

		GetLayersBase()->WaitAllAcknowledged(60*GetPageNumb());
		GetLayersBase()->CloseProcessingForm ();
	}
	GetLayersBase()->TmpRercoverProcessingForm();
}

void	ButtonLoadRelease::TransmitDirectly(GUIDirectMessage *packet)
{

}
void	ButtonLoadRelease::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,/**/"File"
										,"Load/Release data"
										,this);
	p->SetMenuNumber(255);
	Info.AppendList(p);
}
void	ButtonLoadRelease::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	ButtonLoadRelease::SlotExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)
{
	SettingLoadReleaseDialog	D(GetLayersBase());
	D.Merge(SettingData);
	D.ReflectToWindow();
	if(D.exec()==(int)true){
		SettingData=D.SettingData;
	}
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	SettingData.Save(&Buff);
	data=Buff.buffer();
	SettingDataArray=Buff.buffer();
}

void	ButtonLoadRelease::RxSync(QByteArray &f)
{
}

static	QString	GetFileNameOFMasterImage(QString &SwapPath,int GlobalPage ,int phase)
{
	return SwapPath
			+QString(/**/"\\MasterImage-")
			+QString::number(phase)
			+QString(/**/"-")
			+QString::number(GlobalPage)
			+QString(/**/".swp");
}

static	QString	GetFileNameOFAlgorithmData(QString &SwapPath,int GlobalPage ,int phase,AlgorithmInPageRoot *Pg)
{
	AlgorithmBase	*ABase=Pg->GetParentBase();
	QString	DLLRoot,DLLName;
	ABase->GetDLLName(DLLRoot,DLLName);
	return SwapPath
			+QString(/**/"\\Algorithm-")
			+DLLRoot
			+QString(/**/"-")
			+DLLName
			+QString::number(phase)
			+QString(/**/"-")
			+QString::number(GlobalPage)
			+QString(/**/".swp");
}
//==========================================================================================================

GUICmdReqRelease::GUICmdReqRelease(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	SwapInOut=true;
}
	
bool	GUICmdReqRelease::Load(QIODevice *f)
{
	if(::Load(f,SwapInOut)==false)
		return false;
	if(::Load(f,SwapPath)==false)
		return false;
	if(SettingData.Load(f)==false)
		return false;
	return true;
}
	
bool	GUICmdReqRelease::Save(QIODevice *f)
{
	if(::Save(f,SwapInOut)==false)
		return false;
	if(::Save(f,SwapPath)==false)
		return false;
	if(SettingData.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqRelease::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ButtonLoadRelease	*Form=(ButtonLoadRelease *)GetLayersBase()->FindByName(sRoot,sName,/**/"");
	if(Form!=NULL){
		if(SettingData.ReleaseableMasterBuff==true){
			if(localPage==0){
				Form->AllocateMasterBuff=GetParamGlobal()->AllocateMasterBuff;
				GetParamGlobal()->AllocateMasterBuff=false;
			}
			if(Form->AllocateMasterBuff==true){
				if(GetLayersBase()->GetMasterCode()>0){
					for(int phase=0;phase!=GetPhaseNumb();phase++){
						PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
						DataInPage	*Pg=Ph->GetPageData(localPage);

						bool	ShouldSave=false;
						for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
							DataInLayer	*Ly=Pg->GetLayerData(Layer);
							if(Ly->GetMasterBuff().IsChanged()==true){
								ShouldSave=true;
								break;
							}
						}
						if(ShouldSave==true){
							QString	ErrorMsg;
							GetLayersBase()->SaveMasterImageInMasterData(GetLayersBase()->GetMasterCode(),GetLayersBase()->GetMachineID()
																		,localPage
																		,false
																		,ErrorMsg);
						}
						for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
							DataInLayer	*Ly=Pg->GetLayerData(Layer);
							Ly->GetMasterBuff().Free();
						}
					}
				}
				else{
					if(SwapInOut==true){
						for(int phase=0;phase!=GetPhaseNumb();phase++){
							SwapOutMasterData(localPage,phase);
						}
					}
					for(int phase=0;phase!=GetPhaseNumb();phase++){
						PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
						DataInPage	*Pg=Ph->GetPageData(localPage);

						for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
							DataInLayer	*Ly=Pg->GetLayerData(Layer);
							Ly->GetMasterBuff().Free();
						}
					}
				}
			}
		}	
		if(SettingData.ReleaseableTargetBuff==true){
			if(localPage==0){
				Form->AllocateTargetBuff=GetParamGlobal()->AllocateTargetBuff;
				GetParamGlobal()->AllocateTargetBuff=false;
			}
			for(int phase=0;phase!=GetPhaseNumb();phase++){
				PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
				for(int page=0;page!=GetPageNumb();page++){
					DataInPage	*Pg=Ph->GetPageData(page);
					for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
						DataInLayer	*Ly=Pg->GetLayerData(Layer);
						Ly->GetTargetBuff().Free();
					}
				}
			}
		}
		for(LogicDLL *d=GetLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
			LoadReleaseAlgoList *Found=NULL;
			for(LoadReleaseAlgoList *a=SettingData.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->DLLRoot==d->GetDLLRoot() && a->DLLName==d->GetDLLName()){
					Found=a;
					break;
				}
			}
			if(Found!=NULL && Found->Releaseable==true){
				AlgorithmBase	*Ab=d->GetInstance();
				for(int phase=0;phase!=GetPhaseNumb();phase++){
					AlgorithmInPageInOnePhase	*Ph=Ab->GetPageDataPhase(phase);
					for(int page=0;page!=GetPageNumb();page++){
						AlgorithmInPageRoot	*Pg=Ph->GetPageData(page);

						if(GetLayersBase()->GetMasterCode()>0){
							if(Pg->IsChanged()==true){
								QString	ErrorMsg;
								GetLayersBase()->SaveAlgorithmDataInMasterData(GetLayersBase()->GetMasterCode(),GetLayersBase()->GetMachineID()
																				,Pg,ErrorMsg);
							}
						}
						else{
							if(SwapInOut==true){
								SwapOutAlgorithmData(localPage,phase,Pg);
							}
						}

						IntList	LayerList;
						for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
							LayerList.Add(Layer);
						}
						Pg->UnlockAll(LayerList);
						Pg->SelectAll(LayerList);
						Pg->DeleteSelectedItems(LayerList);
					}
				}
				Ab->SetEnableToSave(false);
			}
		}
	}
	SendAck(localPage);
}
bool	GUICmdReqRelease::SwapOutMasterData(int localPage,int phase)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
	QString	FileName=GetFileNameOFMasterImage(SwapPath,GetLayersBase()->GetGlobalPageFromLocal(localPage),phase);
	DataInPage	*Pg=Ph->GetPageData(localPage);
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		if(::Save(&File,GetLayerNumb(localPage))==false)
			return false;
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			DataInLayer	*Ly=Pg->GetLayerData(Layer);
			if(Ly->GetMasterBuff().Save(&File)==false)
				return false;
		}
	}
	return true;
}

bool	GUICmdReqRelease::SwapOutAlgorithmData(int localPage,int phase,AlgorithmInPageRoot *Pg)
{
	QString	FileName=GetFileNameOFAlgorithmData(SwapPath,GetLayersBase()->GetGlobalPageFromLocal(localPage),phase,Pg);
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		if(Pg->Save(&File)==false){
			return false;
		}
	}
	return true;
}

//==========================================================================================================

GUICmdReqLoad::GUICmdReqLoad(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	SwapInOut=true;
}
	
bool	GUICmdReqLoad::Load(QIODevice *f)
{
	if(::Load(f,SwapInOut)==false)
		return false;
	if(::Load(f,SwapPath)==false)
		return false;
	if(SettingData.Load(f)==false)
		return false;
	return true;
}
	
bool	GUICmdReqLoad::Save(QIODevice *f)
{
	if(::Save(f,SwapInOut)==false)
		return false;
	if(::Save(f,SwapPath)==false)
		return false;
	if(SettingData.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqLoad::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ButtonLoadRelease	*Form=(ButtonLoadRelease *)GetLayersBase()->FindByName(sRoot,sName,/**/"");
	if(Form!=NULL){
		if(SettingData.ReleaseableMasterBuff==true){
			if(Form->AllocateMasterBuff==true){
				if(localPage==0){
					GetParamGlobal()->AllocateMasterBuff=true;
				}
				for(int phase=0;phase!=GetPhaseNumb();phase++){
					PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
					DataInPage	*Pg=Ph->GetPageData(localPage);
					Pg->ReallocMemoryMaster();
				}
				if(GetLayersBase()->GetMasterCode()>0){
					QString	ErrorMsg;
					GetLayersBase()->LoadMasterImageInMasterData(GetLayersBase()->GetMasterCode(),GetLayersBase()->GetMachineID()
																		,localPage,ErrorMsg);
				}
				else{
					if(SwapInOut==true){
						for(int phase=0;phase!=GetPhaseNumb();phase++){
							SwapInMasterData(localPage,phase);
						}
					}
				}
			}
		}	
		if(SettingData.ReleaseableTargetBuff==true){
			if(Form->AllocateTargetBuff==true){
				if(localPage==0){
					GetParamGlobal()->AllocateTargetBuff=true;
				}
				for(int phase=0;phase!=GetPhaseNumb();phase++){
					PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
					DataInPage	*Pg=Ph->GetPageData(localPage);
					Pg->ReallocMemoryTarget();
				}
			}
		}
		for(LogicDLL *d=GetLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
			LoadReleaseAlgoList *Found=NULL;
			for(LoadReleaseAlgoList *a=SettingData.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->DLLRoot==d->GetDLLRoot() && a->DLLName==d->GetDLLName()){
					Found=a;
					break;
				}
			}
			if(Found!=NULL && Found->Releaseable==true){
				AlgorithmBase	*Ab=d->GetInstance();
				for(int phase=0;phase!=GetPhaseNumb();phase++){
					AlgorithmInPageInOnePhase	*Ph=Ab->GetPageDataPhase(phase);
					AlgorithmInPageRoot	*Ap=Ph->GetPageData(localPage);

					if(GetLayersBase()->GetMasterCode()>0){	
						QString	ErrorMsg;
						GetLayersBase()->LoadAlgorithmDataInMasterData(GetLayersBase()->GetMasterCode(),GetLayersBase()->GetMachineID()
																			,Ap,ErrorMsg);
					}
					else{
						if(SwapInOut==true){
							SwapInAlgorithmData(localPage,phase,Ap);
						}
					}
				}
				Ab->SetEnableToSave(true);
			}
		}
	}
	SendAck(localPage);
}

bool	GUICmdReqLoad::SwapInMasterData(int localPage,int phase)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
	QString	FileName=GetFileNameOFMasterImage(SwapPath,GetLayersBase()->GetGlobalPageFromLocal(localPage),phase);
	DataInPage	*Pg=Ph->GetPageData(localPage);
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		int32	iLayerNumb;
		if(::Load(&File,iLayerNumb)==false)
			return false;
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			DataInLayer	*Ly=Pg->GetLayerData(Layer);
			if(Ly->GetMasterBuff().Load(&File)==false)
				return false;
		}
	}
	return true;
}

bool	GUICmdReqLoad::SwapInAlgorithmData(int localPage,int phase,AlgorithmInPageRoot *Pg)
{
	QString	FileName=GetFileNameOFAlgorithmData(SwapPath,GetLayersBase()->GetGlobalPageFromLocal(localPage),phase,Pg);
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(Pg->Load(&File)==false){
			return false;
		}
	}
	return true;
}