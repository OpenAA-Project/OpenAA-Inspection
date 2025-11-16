#include "ButtonTransferPushGUIResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonTransferPushGUI\ButtonTransferPushGUI.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonTransferPushGUI.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XTransfer.h"
#include <QMessageBox>
#include <QMenu>
#include <QCursor>
#include "EditTransferHostDialog.h"

static	const	char	*sRoot=/**/"Transfer";
static	const	char	*sName=/**/"PushGUI";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Transfer Push GUI");
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
	return(new ButtonTransferPushGUI(Base,parent));
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
	Data[0].Pointer				 =&((ButtonTransferPushGUI *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"GUIRoot";
	Data[1].Pointer				 =&((ButtonTransferPushGUI *)Instance)->GUIRoot;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"GUIName";
	Data[2].Pointer				 =&((ButtonTransferPushGUI *)Instance)->GUIName;
	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"GUIInst";
	Data[3].Pointer				 =&((ButtonTransferPushGUI *)Instance)->GUIInst;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonTransferPushGUI.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=========================================================================================================

ButtonTransferPushGUI::ButtonTransferPushGUI(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Transfer Push GUI";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&Button,SIGNAL(RightClicked()), this ,SLOT(SlotRightClicked()));
}

void	ButtonTransferPushGUI::Prepare(void)
{
	Button.setText(Msg);
	ResizeAction();
}
void	ButtonTransferPushGUI::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonTransferPushGUI::SlotClicked (bool checked)
{
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ButtonTransferPushGUI_LS,LID_0)/*"Transfering data"*/);
	if(GetLayersBase()->GetMTransfer()->OperationGUIPush(GUIRoot ,GUIName ,GUIInst)==false){
		QMessageBox::warning(NULL
							,LangSolver.GetString(ButtonTransferPushGUI_LS,LID_1)/*"Error"*/
							,LangSolver.GetString(ButtonTransferPushGUI_LS,LID_2)/*"Can not push GUI"*/);
	}

	GetLayersBase()->CloseProcessingForm ();
}
void	ButtonTransferPushGUI::SlotRightClicked()
{
	QMenu	Menu(this);
	Menu.addAction (QString(tr("Reset fixed host"))	, this, SLOT(SlotResetFixedHost()));
	Menu.addAction (QString(tr("Edit host"))		, this, SLOT(SlotEditHost()));

	QPoint Q=QCursor::pos();
	Menu.exec(Q);
}

void	ButtonTransferPushGUI::SlotResetFixedHost()
{
	GetLayersBase()->GetMTransfer()->ResetFixedHost();
}
void	ButtonTransferPushGUI::SlotEditHost()
{
	EditTransferHostDialog	D(GetLayersBase());
	D.exec();
}