/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExit\ButtonExit.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonExitResource.h"
#include "ButtonExit.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "XGeneralFunc.h"
#include "CloseMessageForm.h"
#include "XGUI.h"
#include "XSyncGUI.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ButtonExit";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button Exit");
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
	return(new ButtonExit(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonExit *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonExit *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonExit *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonExit *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ConfirmAfterEdit";
	Data[4].Pointer				 =&((ButtonExit *)Instance)->ConfirmAfterEdit;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonExit.png")));
}

//=========================================================================================================

ButtonExit::ButtonExit(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonExitBtn");
	ConfirmAfterEdit=true;
	Button.move(0,0);
	Msg=/**/"Exit";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

}


void	ButtonExit::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
	QWidget	*p=parentWidget();
	while(p!=NULL){
		MainGUIFormBase *m=dynamic_cast<MainGUIFormBase *>(p);
		if(m!=NULL){
			m->CloseCompletely=false;
			connect(m, SIGNAL(QuitFromMenu()), this, SLOT(QuitProcess()));
			connect(m, SIGNAL(QuitUnconditionally()), this, SLOT(SlotQuitUnconditionally()));
			break;
		}
		p=p->parentWidget();
	}
}
void	ButtonExit::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonExit::QuitProcess()
{
	SlotClicked (true);
}

void ButtonExit::SlotQuitUnconditionally()
{
	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		int	Cmd=1;
		::Save(&Buff,Cmd);
		TxSync(Buff.buffer());
	}
	GetLayersBase()->CloseAll();
	QCoreApplication::quit();	
}

void ButtonExit::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetShadowLevel()>0){
		GetLayersBase()->GetMainWidget()->hide();
		return;
	}
	if(GetLayersBase()->GetEntryPoint()->GUIIsEditMode()==true){
		GetLayersBase()->SetOnTerminating(true);
		QCoreApplication::quit();
	}
	else{
		if(GetLayersBase()->GetParamComm()->Mastered==true){

			if(ConfirmAfterEdit==true){
				if(GetLayersBase()->IsEdited()==true){
					if(QMessageBox::question ( NULL	
											, LangSolver.GetString(ButtonExit_LS,LID_10)/*"Caution"*/
											, LangSolver.GetString(ButtonExit_LS,LID_11)/*"Unsaved data is on memory. Do you finish?"*/
											, QMessageBox::Yes | QMessageBox::No)==QMessageBox::No){
						return;
					}
				}
			}
			BroadcastReadyTerminate();

			GetLayersBase()->TmpHideProcessingForm();
			CloseMessageForm	*Qx=new CloseMessageForm(GetLayersBase(),this,GetLayersBase()->GetMainWidget());
			Qx->exec();
			GetLayersBase()->TmpRercoverProcessingForm();
			//if(QMessageBox::question ( NULL, "Warning", "Close OK?", QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
			//	QCoreApplication::quit();
		}
		else{
			GetLayersBase()->SetOnTerminating(true);
			QCoreApplication::quit();
		}
	}
}
void	ButtonExit::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p1=new MenuInfoList(1,LangSolver.GetString(ButtonExit_LS,LID_0)/*"FILE"*/,/**/"Separator",this);
	MenuInfoList	*p2=new MenuInfoList(2,LangSolver.GetString(ButtonExit_LS,LID_1)/*"FILE"*/,LangSolver.GetString(ButtonExit_LS,LID_2)/*"Exit"*/,this);
	p1->SetMenuNumber(2000000000);
	p2->SetMenuNumber(2000000001);
	Info.AppendList(p1);
	Info.AppendList(p2);
}
void	ButtonExit::ExecuteMenu(int ID)
{
	if(ID==2){
		SlotClicked(true);
	}
}

void	ButtonExit::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);

	int Cmd;
	::Load(&Buff,Cmd);

	if(Cmd==1){
		GetLayersBase()->CloseAll();
		QCoreApplication::quit();	
	}
	else if(Cmd==2){
		GetLayersBase()->CloseOne();
		QCoreApplication::quit();	
	}
}