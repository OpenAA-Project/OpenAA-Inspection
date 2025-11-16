#include "ButtonPasswordOpenerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonPasswordOpener\ButtonPasswordOpener.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonPasswordOpener.h"
#include "XGeneralFunc.h"
#include <QIcon>
#include <QPixmap>
#include "XDataInLayer.h"
#include "XPassword.h"

//extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PasswordOpener";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to expire Password");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
	//LangCGSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonPasswordOpener(Base,parent));
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
	Data[0].Pointer				 =&((ButtonPasswordOpener *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonPasswordOpener *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonPasswordOpener *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonPasswordOpener *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"ExpiredTimeSec";
	Data[4].Pointer				 =&((ButtonPasswordOpener *)Instance)->ExpiredTimeSec;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonPasswordOpener.png")));
}

//==================================================================================================


ButtonPasswordOpener::ButtonPasswordOpener(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false)
{
	Button.setParent(this);
	Button.move(0,0);
	ExpiredTimeSec	=3600;
	Button.setObjectName(/**/"ButtonPasswordOpener");
	Msg=/**/"Expire Password";
	LockedColor	=Qt::green;
	UnlockedColor=Qt::red;

	resize(60,25);
	Button.setCheckable(true);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonPasswordOpener::~ButtonPasswordOpener(void)
{
}

void	ButtonPasswordOpener::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();

	Button.setColor(LockedColor);
	Button.setPressedColor(UnlockedColor);
}

void	ButtonPasswordOpener::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonPasswordOpener::SlotClicked (bool checked)
{
	if(Button.isChecked()==true)
		GetLayersBase()->GetPasswordHolder()->EnablePasswordAgain();
}


void	ButtonPasswordOpener::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonPasswordOpener_LS,LID_0)/*"Setting"*/,LangSolver.GetString(ButtonPasswordOpener_LS,LID_1)/*"Enable password"*/,this);
	p->SetMenuNumber(181);
	Info.AppendList(p);
}
void	ButtonPasswordOpener::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
bool ButtonPasswordOpener::OnIdle(void)
{
	if(GetLayersBase()->GetPasswordHolder()->IsPassed()==true){
		GetLayersBase()->GetPasswordHolder()->IsExpired();
		if(Button.isChecked()==false){
			Button.setChecked(true);
		}
	}
	else{
		if(Button.isChecked()==true){
			Button.setChecked(false);
		}
	}
	return true;
}