/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonOutlineOffsetWindow\ButtonOutlineOffsetWindow.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonOutlineOffsetWindow.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XLanguageClass.h"
#include "OutlineOffsetForm.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"OutlineOffsetWindow";
extern	LangSolverNew	LangLibSolver;
extern	LangSolverNew	LangSolverGUILib;


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to open OutlineOffset window");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
	LangLibSolver.SetLanguage(Pkg,LanguageCode);
	LangSolverGUILib.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonOutlineOffsetWindow(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonOutlineOffsetWindow *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonOutlineOffsetWindow *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonOutlineOffsetWindow *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonOutlineOffsetWindow *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonOutlineOffsetWindow.png")));
}

//==================================================================================================


ButtonOutlineOffsetWindow::ButtonOutlineOffsetWindow(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"OutlineOffset";
	resize(60,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	Window=NULL;
}

ButtonOutlineOffsetWindow::~ButtonOutlineOffsetWindow(void)
{
	if(Window!=NULL){
		Window->deleteLater();
		Window=NULL;
	}
}

void	ButtonOutlineOffsetWindow::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setObjectName(QString(/**/"OutlineOffset"));
	ResizeAction();
}

void	ButtonOutlineOffsetWindow::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonOutlineOffsetWindow::SlotClicked()
{
	if(Window==NULL){
		Window	=new OutlineOffsetForm(GetLayersBase());
	}
	Window->show();
}
