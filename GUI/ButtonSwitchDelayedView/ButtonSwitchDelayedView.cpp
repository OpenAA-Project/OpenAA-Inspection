#include "ButtonSwitchDelayedViewResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSwitchDelayedView\ButtonSwitchDelayedView.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSwitchDelayedView.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SwitchDelayedView";




DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to switch delayed view");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendSwitchDelayedView(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSwitchDelayedView(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSwitchDelayedView *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSwitchDelayedView *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"NormalColor";
	Data[2].Pointer				 =&((ButtonSwitchDelayedView *)Instance)->NormalColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"PushedColor";
	Data[3].Pointer				 =&((ButtonSwitchDelayedView *)Instance)->PushedColor;	
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((ButtonSwitchDelayedView *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSwitchDelayedView.png")));
}

static	bool	MacroSwitchDelayedView(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSwitchDelayedView	*V=dynamic_cast<ButtonSwitchDelayedView *>(Instance);
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
		Functions[ret].FuncName	=/**/"SwitchDelayedView";
		Functions[ret].Explain.append(/**/"Switch delayed view");
		Functions[ret].DLL_ExcuteMacro	=MacroSwitchDelayedView;
		ret++;
	}
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonSwitchDelayedView::ButtonSwitchDelayedView(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Switch Delayed View";

	CharColor	=Qt::white;
	NormalColor	=Qt::gray;
	PushedColor	=Qt::yellow;

	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonSwitchDelayedView::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSwitchDelayedView::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	ButtonSwitchDelayedView::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonSwitchDelayedView::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSendSwitchDelayedView	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
		RCmd.SendOnly(GlobalPage ,0);
	}
	BroadcastShowInEdit();
}

//==========================================================================================
GUICmdSendSwitchDelayedView::GUICmdSendSwitchDelayedView(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendSwitchDelayedView::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetPageData(localPage)->CopyToDelayedView();
	GetLayersBase()->SetCurrentInspectID(GetLayersBase()->GetCurrentInspectIDForExecute());
	SendAck(localPage);
}