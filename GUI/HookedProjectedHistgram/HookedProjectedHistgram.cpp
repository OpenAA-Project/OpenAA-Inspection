#include "HookedProjectedHistgramResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\HookedProjectedHistgram\HookedProjectedHistgram.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "HookedProjectedHistgram.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

static	char	*sRoot=/**/"Button";
static	char	*sName=/**/"HookedProjectedHistgram";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Hooked unction : Projected Histgram");
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
	return(new HookedProjectedHistgram(Base,parent));
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
	Data[0].Pointer				 =&((HookedProjectedHistgram *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"IPAddress";
	Data[1].Pointer				 =&((HookedProjectedHistgram *)Instance)->IPAddress;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"SenderPort";
	Data[2].Pointer				 =&((HookedProjectedHistgram *)Instance)->SenderPort;
	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"ImagePanelNameToHook";
	Data[3].Pointer				 =&((HookedProjectedHistgram *)Instance)->ImagePanelNameToHook;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/HookedProjectedHistgram.png")));
}

//=========================================================================================================

HookedProjectedHistgram::HookedProjectedHistgram(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	IPAddress=/**/"localhost";
	SenderPort	=18666;

	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Projected Histgram";
	resize(100,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}


void	HookedProjectedHistgram::Prepare(void)
{
	Button.setText(Msg);
	ResizeAction();
}
void	HookedProjectedHistgram::ResizeAction()
{
	Button.resize(width(),height());
}

void HookedProjectedHistgram::SlotClicked (bool checked)
{
}
