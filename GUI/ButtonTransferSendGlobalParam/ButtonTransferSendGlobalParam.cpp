#include "ButtonTransferSendGlobalParamResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonTransferSendGlobalParam\ButtonTransferSendGlobalParam.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonTransferSendGlobalParam.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XTransfer.h"
#include <QMessageBox>
#include <QMenu>
#include <QCursor>
#include "EditTransferHostDialog.h"

static	const	char	*sRoot=/**/"Transfer";
static	const	char	*sName=/**/"SendGlobalParam";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"TransferSending GlobalParam");
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
	return(new ButtonTransferSendGlobalParam(Base,parent));
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
	Data[0].Pointer				 =&((ButtonTransferSendGlobalParam *)Instance)->Msg;
	Data[0].Translatable		 =true;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonTransferSendGlobalParam.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=========================================================================================================

ButtonTransferSendGlobalParam::ButtonTransferSendGlobalParam(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Transfer sending GrobalParam";
	resize(100,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&Button,SIGNAL(RightClicked()), this ,SLOT(SlotRightClicked()));
}

void	ButtonTransferSendGlobalParam::Prepare(void)
{
	Button.setText(Msg);
	ResizeAction();
}
void	ButtonTransferSendGlobalParam::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonTransferSendGlobalParam::SlotClicked (bool checked)
{
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ButtonTransferSendGlobalParam_LS,LID_0)/*"Transfering data"*/);
	if(GetLayersBase()->GetMTransfer()->SndGlobalParam()==false){
		QMessageBox::warning(NULL
							,LangSolver.GetString(ButtonTransferSendGlobalParam_LS,LID_1)/*"Error"*/
							,LangSolver.GetString(ButtonTransferSendGlobalParam_LS,LID_2)/*"Can not send GlobalParam"*/);
	}
	GetLayersBase()->CloseProcessingForm ();
}
void	ButtonTransferSendGlobalParam::SlotRightClicked()
{
	QMenu	Menu(this);
	Menu.addAction (QString(tr("Reset fixed host"))	, this, SLOT(SlotResetFixedHost()));
	Menu.addAction (QString(tr("Edit host"))		, this, SLOT(SlotEditHost()));

	QPoint Q=QCursor::pos();
	Menu.exec(Q);
}

void	ButtonTransferSendGlobalParam::SlotResetFixedHost()
{
	GetLayersBase()->GetMTransfer()->ResetFixedHost();
}
void	ButtonTransferSendGlobalParam::SlotEditHost()
{
	EditTransferHostDialog	D(GetLayersBase());
	D.exec();
}
