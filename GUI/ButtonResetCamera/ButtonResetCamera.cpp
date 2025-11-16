/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonResetCamera\ButtonResetCamera.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonResetCamera.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XExecuteInspectBase.h"
#include "XCameraCommon.h"
#include "XForWindows.h"
#include "XEntryPoint.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ResetCamera";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to reset camera");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdResetCamera(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonResetCamera(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonResetCamera *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonResetCamera *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonResetCamera *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonResetCamera *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"RestartPC";
	Data[4].Pointer				 =&((ButtonResetCamera *)Instance)->RestartPC;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonResetCamera.png")));
}

//==================================================================================================
ButtonResetCamera::ButtonResetCamera(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonResetCamera");
	Msg=/**/"Reset camera";
	RestartPC	=true;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonResetCamera::~ButtonResetCamera(void)
{
}

void	ButtonResetCamera::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonResetCamera::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonResetCamera::SlotClicked (bool checked)
{
	if(GetLayersBase()->IsLocalCamera()==true){
		for(int page=0;page<GetPageNumb();page++){
			SpecifiedBroadcasterSendResetCamera	RCmd;
			RCmd.Page	=page;
			RCmd.Cmd	=0;
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				BroadcastSpecifiedDirectly(&RCmd);
			}
			if(RestartPC==true){
				MtShutdownSelfPC(true,true);
			}
		}
	}
	else{
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdResetCamera	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
			RCmd.Cmd	=0;
			RCmd.RestartPC=RestartPC;
			RCmd.Send(NULL,page,0);
		}
	}
}

//===============================================================

GUICmdResetCamera::GUICmdResetCamera(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdResetCamera::Load(QIODevice *f)
{
	if(::Load(f,Cmd)==false)
		return false;
	if(::Load(f,RestartPC)==false)
		return false;
	return true;
}

bool	GUICmdResetCamera::Save(QIODevice *f)
{
	if(::Save(f,Cmd)==false)
		return false;
	if(::Save(f,RestartPC)==false)
		return false;
	return true;
}


void	GUICmdResetCamera::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SpecifiedBroadcasterSendResetCamera	RCmd;
	RCmd.Page	=localPage;
	RCmd.Cmd	=Cmd;
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetLayersBase()->GetMainWidget()->BroadcastSpecifiedDirectly(&RCmd);
		if(RestartPC==true){
			MtShutdownSelfPC(true,true);
		}
	}
}