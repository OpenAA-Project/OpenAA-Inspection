#include "ButtonRewindInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonRewindInspection\ButtonRewindInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonRewindInspection.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"RewindInspection";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Rewind Inspection");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdRewindInspection(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonRewindInspection(Base,parent));
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
	Data[0].Pointer				 =&((ButtonRewindInspection *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonRewindInspection *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"NormalColor";
	Data[2].Pointer				 =&((ButtonRewindInspection *)Instance)->NormalColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"PushedColor";
	Data[3].Pointer				 =&((ButtonRewindInspection *)Instance)->PushedColor;	
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((ButtonRewindInspection *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonRewindInspection.png")));
}

static	bool	MacroRewindInspection(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonRewindInspection	*V=dynamic_cast<ButtonRewindInspection *>(Instance);
	if(V==NULL){
		return false;
	}

	V->SlotClicked(true);
	return false;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"RewindInspection";
		Functions[ret].Explain.append(/**/"Rewind Inspection");
		Functions[ret].DLL_ExcuteMacro	=MacroRewindInspection;
		ret++;
	}
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonRewindInspection::ButtonRewindInspection(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Rewind Inspection";

	CharColor	=Qt::white;
	NormalColor	=Qt::gray;
	PushedColor	=Qt::yellow;

	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonRewindInspection::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonRewindInspection::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	ButtonRewindInspection::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonRewindInspection::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRewindInspection	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
		RCmd.SendOnly(GlobalPage ,0);
	}
	BroadcastShowInEdit();
}

//==========================================================================================
GUICmdRewindInspection::GUICmdRewindInspection(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdRewindInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetPageData(localPage)->CopyToDelayedView();
	//GetLayersBase()->SetCurrentInspectID(GetLayersBase()->GetCurrentInspectIDForExecute());
	SendAck(localPage);
}