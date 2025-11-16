#include "ButtonToShowOtherGUIResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonToShowOtherGUI\ButtonToShowOtherGUI.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonToShowOtherGUI.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XGeneralFunc.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ButtonToShowOtherGUI";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to show other GUI");
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
	return(new ButtonToShowOtherGUI(Base,parent));
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
	Data[0].Pointer				 =&((ButtonToShowOtherGUI *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonToShowOtherGUI *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonToShowOtherGUI *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonToShowOtherGUI *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"GUIFileName";
	Data[4].Pointer				 =&((ButtonToShowOtherGUI *)Instance)->GUIFileName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonToShowOtherGUI.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonToShowOtherGUI::ButtonToShowOtherGUI(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Show other GUI";
	GUIFileName	=/**/"";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	CurrentGUI=NULL;
}

ButtonToShowOtherGUI::~ButtonToShowOtherGUI(void)
{
}

void	ButtonToShowOtherGUI::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonToShowOtherGUI::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonToShowOtherGUI::SlotClicked( bool checked )
{
	if(QFile::exists(GUIFileName)==true){
		CurrentGUI=GetLayersBase()->GetEntryPoint()->ShowOtherGUI(this,GUIFileName,GetLayersBase());
	}
}
bool	ButtonToShowOtherGUI::SaveContent(QIODevice *f)
{
	if(::Save(f,ChainedContent)==false){
		return false;
	}
	return true;
}
bool	ButtonToShowOtherGUI::LoadContent(QIODevice *f)
{
	if(::Load(f,ChainedContent)==false){
		return false;
	}
	QIODevice	*Dev=GetChainedDevice();
	if(LoadAll(Dev)==false){
		delete	Dev;
		return false;
	}
	delete	Dev;
	return true;
}

