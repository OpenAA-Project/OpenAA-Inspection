/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationButtonCreateRepeatControl\IntegrationButtonCreateRepeatControl.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationButtonCreateRepeatControl.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>
#include "CreateRepeatCountDialog.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ButtonCreateRepeatControl";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to create RepeatControl");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdReqRepeatCount(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdAckRepeatCount(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdSetRepeatCount(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationButtonCreateRepeatControl(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((IntegrationButtonCreateRepeatControl *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationButtonCreateRepeatControl *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationButtonCreateRepeatControl *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationButtonCreateRepeatControl *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationButtonCreateRepeatControl.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"RepeatControl"));
}

//==================================================================================================
IntegrationButtonCreateRepeatControl::IntegrationButtonCreateRepeatControl(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationButtonCreateRepeatControlBtn");
	Button.move(0,0);
	Msg=/**/"Create RepeatControl";

	resize(200,25);
	Button.setStyleSheet(/**/"QToolButton {"
						 /**/"	border-style: outset;"
						 /**/"	border-width: 1px;"
						 /**/"	border-radius: 25px;"
						 /**/"	border-color: gray;"
						 /**/"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));"
						 /**/"}"
						 /**/"QToolButton:pressed { 	"
						 /**/"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));"
						 /**/"}"
						);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationButtonCreateRepeatControl::~IntegrationButtonCreateRepeatControl()
{

}

void	IntegrationButtonCreateRepeatControl::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationButtonCreateRepeatControl::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationButtonCreateRepeatControl::SlotClicked ()
{
	CreateRepeatCountDialog	D(GetLayersBase());
	D.exec();
}

