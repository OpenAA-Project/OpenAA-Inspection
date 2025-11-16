/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyShowAlignment\EasyShowAlignment.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "EasyShowAlignment.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "EasyShowAlignmentForm.h"
#include "EasyPropertyAlignmentForm.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyShowAlignment";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to show alignment");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)	=new IntegrationCmdReqAlignmentMark	(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdAckAlignmentMark	(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdReqAlignmentImage(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationCmdAckAlignmentImage(Base,sRoot,sName,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new EasyShowAlignment(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				  =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SlaveNo";
	Data[0].Pointer			  =&((EasyShowAlignment *)Instance)->SlaveNo;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"Msg";
	Data[1].Pointer				 =&((EasyShowAlignment *)Instance)->Msg;
	Data[1].Translatable		=true;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"CharColor";
	Data[2].Pointer				 =&((EasyShowAlignment *)Instance)->CharColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"BackColor";
	Data[3].Pointer				 =&((EasyShowAlignment *)Instance)->BackColor;
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((EasyShowAlignment *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyShowAlignment.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic"	,/**/"AlignmentLarge"));
}

//=======================================================================

EasyShowAlignment::EasyShowAlignment(LayersBase *Base ,QWidget *parent) :
	GUIFormBase(Base,parent)
{
	SlaveNo=0;
	Window					=NULL;

	Button.setParent(this);
	Button.setObjectName(/**/"EasyShowAlignmentBtn");
	Button.move(0,0);
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

	Msg=/**/"Alignment";
	resize(80,25);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
}

EasyShowAlignment::~EasyShowAlignment()
{
	Window->deleteLater();
}

void	EasyShowAlignment::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	EasyShowAlignment::ResizeAction()
{
	Button.resize(width(),height());
}

void	EasyShowAlignment::SlotClicked (bool checked)
{
	if(Window==NULL){
		Window=new EasyShowAlignmentForm(GetLayersBase(),this);
	}
	Window->ShowStart();
	Window->show();
	Window->raise();
}

void	EasyShowAlignment::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	EasyShowAlignment::ShowInPlayer		(int64 shownInspectionID)
{
	if(Window!=NULL){
		Window->ShowInPlayer(shownInspectionID);
	}
}
