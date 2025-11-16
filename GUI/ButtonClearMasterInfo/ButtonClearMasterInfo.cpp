/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonClearMasterInfo\ButtonClearMasterInfo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonClearMasterInfo.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmBase.h"
#include "XWriteResultThread.h"
#include <QIcon>
#include <QPixmap>
#include <QStringList>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ClearMasterInfo";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to clear Master information");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqButtonClearMasterInfo		(Base,sRoot,sName);
	(*Base)=new GUICmdReqButtonClearMasterInfoPhase(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonClearMasterInfo(Base,parent));
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
	Data[0].Pointer				 =&((ButtonClearMasterInfo *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonClearMasterInfo *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonClearMasterInfo *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonClearMasterInfo *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonClearMasterInfo.png")));
}

static	bool	MacroClearMasterInfo(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonClearMasterInfo	*V=dynamic_cast<ButtonClearMasterInfo *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotClicked(true);

	return true;
}
static	bool	MacroClearMasterInfoPhase(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonClearMasterInfo	*V=dynamic_cast<ButtonClearMasterInfo *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotClickedPhase(true);

	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Clear";
		Functions[ret].Explain.append(/**/"Clear master info");
		Functions[ret].DLL_ExcuteMacro	=MacroClearMasterInfo;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearPhase";
		Functions[ret].Explain.append(/**/"Clear master info and phase");
		Functions[ret].DLL_ExcuteMacro	=MacroClearMasterInfoPhase;
		ret++;
	}

	return ret;
}

//==================================================================================================
ButtonClearMasterInfo::ButtonClearMasterInfo(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonClearMasterInfo");
	Msg=/**/"Clear master info";


	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonClearMasterInfo::~ButtonClearMasterInfo(void)
{
}

void	ButtonClearMasterInfo::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonClearMasterInfo::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonClearMasterInfo::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqButtonClearMasterInfo	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Send(NULL,globalPage,0);
	}
}

void ButtonClearMasterInfo::SlotClickedPhase (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqButtonClearMasterInfoPhase	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Send(NULL,globalPage,0);
	}
}

//===============================================================================

GUICmdReqButtonClearMasterInfo::GUICmdReqButtonClearMasterInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqButtonClearMasterInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage	*Dp=Ph->GetPageData(localPage);
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			DataInLayer	*DL=Dp->GetLayerData(Layer);
			DL->GetMasterBuff().Memset(0);
			DL->GetTargetBuff().Memset(0);
			DL->GetBitBuff().Memset(0);
		}
	}
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*Ab=L->GetInstance();
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			Ap->ClearHistgram();
			Ap->ClearStartItemID();
			IntList	LayerList;
			for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
				LayerList.Add(Layer);
			}
			//Ap->SelectAll(LayerList);
			Ap->RemoveAllDatas();	//DeleteSelectedItems(LayerList);
		}
	}
	GetLayersBase()->GetResultThread()->SetCastAll();

	GetLayersBase()->PushExecuterState();
	ExecuteInitialAfterEditInfo EInfo;
	GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
	GetLayersBase()->PopExecuterState();

}

//===============================================================================

GUICmdReqButtonClearMasterInfoPhase::GUICmdReqButtonClearMasterInfoPhase(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqButtonClearMasterInfoPhase::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->Reallocate(1);
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage	*Dp=Ph->GetPageData(localPage);
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			DataInLayer	*DL=Dp->GetLayerData(Layer);
			DL->GetMasterBuff().Memset(0);
			DL->GetTargetBuff().Memset(0);
			DL->GetBitBuff().Memset(0);
		}
	}
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*Ab=L->GetInstance();
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			Ap->ClearHistgram();
			Ap->ClearStartItemID();
			IntList	LayerList;
			for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
				LayerList.Add(Layer);
			}
			Ap->SelectAll(LayerList);
			Ap->DeleteSelectedItems(LayerList);
		}
	}
	GetLayersBase()->GetResultThread()->SetCastAll();

	GetLayersBase()->PushExecuterState();
	ExecuteInitialAfterEditInfo EInfo;
	GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
	GetLayersBase()->PopExecuterState();

}
