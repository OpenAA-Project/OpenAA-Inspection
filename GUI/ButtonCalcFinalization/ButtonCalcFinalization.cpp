/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonCalcFinalization\ButtonCalcFinalization.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonCalcFinalizationResource.h"
#include "ButtonCalcFinalization.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XSyncGUI.h"
#include "XWriteResultThread.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"CalcFinalization";


static	bool	MacroExecute(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroExecuteByOnlyImage(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to calculate finalization (ExecuteInitialAfterEdit)");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqCalcFinalization			(Base,sRoot,sName);
	(*Base)=new GUICmdReqCalcFinalizationOnlyByImage(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonCalcFinalization(Base,parent));
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
	Data[0].Pointer				 =&((ButtonCalcFinalization *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonCalcFinalization *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonCalcFinalization *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonCalcFinalization *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonCalcFinalization.png")));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Execute";
		Functions[ret].Explain.append(/**/"Execute calc-finalization");
		Functions[ret].DLL_ExcuteMacro	=MacroExecute;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ExecuteOnlyByImage";
		Functions[ret].Explain.append(/**/"Execute calc-finalization only by image");
		Functions[ret].DLL_ExcuteMacro	=MacroExecuteByOnlyImage;
		ret++;
	}
	return ret;
}

static	bool	MacroExecute(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonCalcFinalization	*V=dynamic_cast<ButtonCalcFinalization *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotClicked(true);

	return true;
}

static	bool	MacroExecuteByOnlyImage(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonCalcFinalization	*V=dynamic_cast<ButtonCalcFinalization *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ExecuteByOnlyImage();

	return true;
}


//==================================================================================================
ButtonCalcFinalization::ButtonCalcFinalization(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SyncMode		=false;
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonCalcFinalization");
	Msg=/**/"Calc finalization";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonCalcFinalization::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonCalcFinalization::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonCalcFinalization::SlotClicked (bool checked)
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ButtonCalcFinalization_LS,LID_2)/*"Calculating finalization"*/);

	if(SyncMode==false){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			TxSync(Buff.buffer());
		}
	}
	GetLayersBase()->ScanChangedInSlave();
	if(GetParamComm()->GetConnectedPCNumb()!=0){
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

		ExecuteInitialAfterEditInfo EInfo;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqCalcFinalization	RCmd(GetLayersBase() ,sRoot,sName,page);
			RCmd.Send(NULL,page ,0);
		}
		GetLayersBase()->WaitAllAcknowledged(10*60*100);
	}
	else{
		ExecuteInitialAfterEditInfo EInfo;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
	}
	GetLayersBase()->CloseProcessingForm ();
	BroadcastDirectly(_BC_BuildForShow	,0);
}

void	ButtonCalcFinalization::ExecuteByOnlyImage(void)
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ButtonCalcFinalization_LS,LID_2)/*"Calculating finalization"*/);

	GetLayersBase()->ScanChangedInSlave();
	if(GetParamComm()->GetConnectedPCNumb()!=0){
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

		ExecuteInitialAfterEditInfo EInfo;
		EInfo.HasChangedOnlyImage=true;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqCalcFinalizationOnlyByImage	RCmd(GetLayersBase() ,sRoot,sName,page);
			RCmd.Send(NULL,page ,0);
		}
		GetLayersBase()->WaitAllAcknowledged(10*60*100);
	}
	else{
		ExecuteInitialAfterEditInfo EInfo;
		EInfo.HasChangedOnlyImage=true;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
	}
	GetLayersBase()->CloseProcessingForm ();
	BroadcastDirectly(_BC_BuildForShow	,0);
}

void	ButtonCalcFinalization::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonCalcFinalization_LS,LID_0)/*"Execute"*/,LangSolver.GetString(ButtonCalcFinalization_LS,LID_1)/*"Finish editing"*/,this);
	p->SetMenuNumber(1050);
	Info.AppendList(p);
}
void	ButtonCalcFinalization::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
void	ButtonCalcFinalization::RxSync(QByteArray &f)
{
	SyncMode=true;
	SlotClicked(true);
	SyncMode=false;
}


//======================================================================================
GUICmdReqCalcFinalization::GUICmdReqCalcFinalization(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqCalcFinalization::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
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

		GetLayersBase()->PushExecuterState();
		ExecuteInitialAfterEditInfo EInfo;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
		GetLayersBase()->PopExecuterState();
	}
	SendAck(localPage);
}

//======================================================================================
GUICmdReqCalcFinalizationOnlyByImage::GUICmdReqCalcFinalizationOnlyByImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqCalcFinalizationOnlyByImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
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

		GetLayersBase()->PushExecuterState();
		ExecuteInitialAfterEditInfo EInfo;
		EInfo.HasChangedOnlyImage=true;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
		GetLayersBase()->PopExecuterState();
	}
	SendAck(localPage);
}