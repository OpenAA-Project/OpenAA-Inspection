#include "ButtonTransferMasterDataResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonTransferMasterData\ButtonTransferMasterData.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonTransferMasterData.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XTransfer.h"

static	char	*sRoot=/**/"Button";
static	char	*sName=/**/"ButtonTransferMasterData";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Transfer Button");
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
	return(new ButtonTransferMasterData(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonTransferMasterData *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"IPAddress";
	Data[1].Pointer				 =&((ButtonTransferMasterData *)Instance)->IPAddress;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"SenderPort";
	Data[2].Pointer				 =&((ButtonTransferMasterData *)Instance)->SenderPort;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonTransferMasterData.png")));
}

//=========================================================================================================

ButtonTransferMasterData::ButtonTransferMasterData(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	IPAddress=/**/"localhost";
	SenderPort	=18666;

	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Transfer";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}


void	ButtonTransferMasterData::Prepare(void)
{
	Button.setText(Msg);
	ResizeAction();
}
void	ButtonTransferMasterData::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonTransferMasterData::SlotClicked (bool checked)
{
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ButtonTransferMasterData_LS,LID_0)/*"Transfering data"*/);
	//GetLayersBase()->Transfer(IPAddress,SenderPort,CmdMixTransfer_TxAll);
	//GetLayersBase()->CloseProcessingForm ();
}
