/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExit\ButtonExit.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonExit.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "XGeneralFunc.h"
#include "CloseMessageForm.h"
#include "ButtonExitResource.h"
#include "XFileRegistry.h"



char	*sRoot="Button";
char	*sName="ButtonExit";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Button Exit");
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
	if(maxDataDim<0){
		return(-1);
	}

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/ButtonExit.png")));
}

//=========================================================================================================

ButtonExit::ButtonExit(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent,false)
{
	//Œ¾Œê‘Î‰ž
	FileRegistry	*FRegistry=new FileRegistry("./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt("Language",0);

	QString ImageBmpFile[5]={
		":Resources/ExitImage.bmp",		//“ú–{Œê
		":Resources/ExitImage-en.bmp",	//English
		":Resources/ExitImage-en.bmp",	//ŠÈ‘Ì’†•¶
		":Resources/ExitImage-en.bmp",	//”É‘Ì’†•¶
		":Resources/ExitImage-en.bmp"	//Korean
	};
	Button.setImageBmp(QImage(ImageBmpFile[LanguageCode]));

	Button.setParent(this);
	Button.move(0,0);
	resize(121,39);
	connect(&Button,SIGNAL(SignalClicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(this,	SIGNAL(SignalResize()),		this,SLOT(ResizeAction()));
}


void	ButtonExit::Prepare(void)
{
	ResizeAction();
}
void	ButtonExit::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonExit::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetParamComm()->Mastered==true){
		GetLayersBase()->TmpHideProcessingForm();
//		CloseMessageForm	*Qx=new CloseMessageForm(GetLayersBase(),GetLayersBase()->GetMainWidget());
		CloseMessageForm	*Qx=new CloseMessageForm(GetLayersBase(),NULL);
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
