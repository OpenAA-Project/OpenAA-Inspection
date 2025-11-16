/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSequence\ButtonSequence.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSequenceResource.h"
#include "ButtonSequence.h"
#include "ThreadSequence.h"
#include <QMessageBox>
#include <QApplication>
#include "XEntryPoint.h"

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"SequenceButton";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show sequence window");
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
	return(new ButtonSequence(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSequence *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSequence *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSequence *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSequence *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSequence.png")));
}

//==================================================================================================
ButtonSequence::ButtonSequence(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Sequence";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSequence::~ButtonSequence(void)
{
}

void	ButtonSequence::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSequence::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonSequence::Terminated(void)
{
	emit	SignalButtonClosed();
	QApplication::processEvents();
}
void ButtonSequence::SlotClicked (bool checked)
{
	QWidget	*SequencePanel=NULL;
	if(GetLayersBase()!=NULL){
		if(GetLayersBase()->GetEntryPoint()!=NULL){
			if(GetLayersBase()->GetEntryPoint()->GetThreadSequence()!=NULL){
				SequencePanel=GetLayersBase()->GetEntryPoint()->GetThreadSequence()->ShowSimulateSequence(NULL);
			}else if(GetLayersBase()->GetSequenceInstance()!=NULL){
				SequencePanel=GetLayersBase()->GetSequenceInstance()->ShowSimulateSequence(NULL);
			}
			else{
				QMessageBox::warning(this
									, LangSolver.GetString(ButtonSequence_LS,LID_2)/*"ButtonSequence"*/
									, LangSolver.GetString(ButtonSequence_LS,LID_3)/*"GetLayersBase()->GetEntryPoint()->GetThreadSequence() is NULL."*/);
			}
		}else{
			QMessageBox::warning(this
									, LangSolver.GetString(ButtonSequence_LS,LID_4)/*"ButtonSequence"*/
									, LangSolver.GetString(ButtonSequence_LS,LID_5)/*"GetLayersBase()->GetEntryPoint() is NULL."*/);
		}
	}else{
		QMessageBox::warning(this
							, LangSolver.GetString(ButtonSequence_LS,LID_6)/*"ButtonSequence"*/
							, LangSolver.GetString(ButtonSequence_LS,LID_7)/*"GetLayersBase() is NULL."*/);
	}
	if(SequencePanel!=NULL){
		connect(this,SIGNAL(SignalButtonClosed()),SequencePanel,SLOT(close()),Qt::QueuedConnection);
	}
}
void	ButtonSequence::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1
							,LangSolver.GetString(ButtonSequence_LS,LID_0)/*"Execute"*/
							,LangSolver.GetString(ButtonSequence_LS,LID_1)/*"Show Sequence"*/
							,this);
	p->SetMenuNumber(1000000000);
	Info.AppendList(p);
}
void	ButtonSequence::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}