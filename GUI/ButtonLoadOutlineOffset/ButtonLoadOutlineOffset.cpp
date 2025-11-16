#include "ButtonLoadOutlineOffsetResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadOutlineOffset\ButtonLoadOutlineOffset.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonLoadOutlineOffset.h"
#include "LoadOutlineOffsetForm.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"LoadOutlineOffset";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for loading OutlineOffset");
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
	return(new ButtonLoadOutlineOffset(Base,parent));
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
	Data[0].Pointer				 =&((ButtonLoadOutlineOffset *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadOutlineOffset *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadOutlineOffset *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadOutlineOffset *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadOutlineOffset.png")));
}

//==================================================================================================

ButtonLoadOutlineOffset::ButtonLoadOutlineOffset(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load outline offset";
	resize(100,25);
	bool Ret1=(connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked())))?true:false;
	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;
}

ButtonLoadOutlineOffset::~ButtonLoadOutlineOffset(void)
{
}

void	ButtonLoadOutlineOffset::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLoadOutlineOffset::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonLoadOutlineOffset::SlotClicked()
{
	GetLayersBase()->TmpHideProcessingForm();
	LoadOutlineOffsetForm	D(GetLayersBase(),NULL);
	D.exec();
	GetLayersBase()->TmpRercoverProcessingForm();
}

void	ButtonLoadOutlineOffset::TransmitDirectly(GUIDirectMessage *packet)
{

}
void	ButtonLoadOutlineOffset::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonLoadOutlineOffset_LS,LID_0)/*"Setting"*/,LangSolver.GetString(ButtonLoadOutlineOffset_LS,LID_1)/*"Select Machine"*/,this);
	p->SetMenuNumber(120);
	Info.AppendList(p);
}
void	ButtonLoadOutlineOffset::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked();
	}
}
