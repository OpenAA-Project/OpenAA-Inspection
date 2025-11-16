/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonFilterSwitch\ButtonFilterSwitch.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonFilterSwitch.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmBase.h"
#include <QIcon>
#include <QPixmap>
#include <QStringList>

const	char	*sRoot=/**/"Filter";
const	char	*sName=/**/"SwitchFilter";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to switch to registered filter");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSwitchFilter		(Base,sRoot,sName);
	//(*Base)=new GUICmdReqButtonClearMasterInfoPhase(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonFilterSwitch(Base,parent));
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
	Data[0].Pointer				 =&((ButtonFilterSwitch *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonFilterSwitch *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonFilterSwitch *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonFilterSwitch *)Instance)->CFont;
	Data[4].Type				 =/**/"QStringList";
	Data[4].VariableNameWithRoute=/**/"FileNames";
	Data[4].Pointer				 =&((ButtonFilterSwitch *)Instance)->FileNames;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonFilterSwitch.png")));
}

//==================================================================================================
ButtonFilterSwitch::ButtonFilterSwitch(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonFilterSwitch");
	Msg=/**/"Switch filter";

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonFilterSwitch::~ButtonFilterSwitch(void)
{
}

void	ButtonFilterSwitch::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonFilterSwitch::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonFilterSwitch::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSwitchFilter	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.FilterFileName=FileNames;
		RCmd.Send(NULL,globalPage,0);
	}
}

//============================================================================================

GUICmdSwitchFilter::GUICmdSwitchFilter(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSwitchFilter::Load(QIODevice *f)
{
	if(::Load(f,FilterFileName)==false)	return false;
	return true;
}
bool	GUICmdSwitchFilter::Save(QIODevice *f)
{
	if(::Save(f,FilterFileName)==false)	return false;
	return true;
}

void	GUICmdSwitchFilter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		for(int i=0;i<FilterFileName.count();i++){
			QString	FileName=FilterFileName[i];
			QFile	File(FileName);
			if(File.open(QIODevice::ReadOnly)==true){
				if(GetLayersBase()->LoadFilterDef(&File)==true){
					break;
				}
			}
		}
	}
}
