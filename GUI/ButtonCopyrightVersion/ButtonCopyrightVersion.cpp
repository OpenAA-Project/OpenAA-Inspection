#include "ButtonCopyrightVersionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonCopyrightVersion\ButtonCopyrightVersion.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonCopyrightVersion.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "XGeneralFunc.h"
#include "VeisionInfoForm.h"
#include "XGeneralDialog.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"CopyrightVersion";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for Copyright & Version");
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
	return(new ButtonCopyrightVersion(Base,parent));
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
	Data[0].VariableNameWithRoute=/**/"CopyrightMessage";
	Data[0].Pointer				 =&((ButtonCopyrightVersion *)Instance)->CopyrightMessage;
	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonCopyrightVersion.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=========================================================================================================

ButtonCopyrightVersion::ButtonCopyrightVersion(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	CopyrightMessage=/**/"Copyright(C) MEGATRADE";
	Button.setParent(this);
	Button.move(0,0);
	resize(200,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}


void	ButtonCopyrightVersion::Prepare(void)
{
	Button.setText(CopyrightMessage);
	ResizeAction();
}
void	ButtonCopyrightVersion::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonCopyrightVersion::SlotClicked (bool checked)
{
	VeisionInfoForm	*MD=new VeisionInfoForm(GetLayersBase());
	GeneralDialog	D(GetLayersBase(),MD,this);
	D.exec();
}
