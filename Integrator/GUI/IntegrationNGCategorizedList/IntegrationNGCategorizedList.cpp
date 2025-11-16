#include "IntegrationNGCategorizedListResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationNGCategorizedList\IntegrationNGCategorizedList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationNGCategorizedList.h"
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
#include "IntegrationNGCategorizedListForm.h"

static	const	char	*sRoot=/**/"Integration";
static	const	char	*sName=/**/"NGCategorizedList";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to show NG categorized list");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)	=new IntegrationCmdChangeCameraSetting(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationNGCategorizedList(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((IntegrationNGCategorizedList *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationNGCategorizedList *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationNGCategorizedList *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationNGCategorizedList *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SlaveNo";
	Data[4].Pointer				 =&((IntegrationNGCategorizedList *)Instance)->SlaveNo;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationNGCategorizedList.png")));
}


//==================================================================================================
IntegrationNGCategorizedList::IntegrationNGCategorizedList(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Form	=NULL;
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationNGCategorizedListBtn");
	Button.move(0,0);
	Msg=/**/"NG Categorized list";
	SlaveNo	=0;

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

IntegrationNGCategorizedList::~IntegrationNGCategorizedList()
{

}

void	IntegrationNGCategorizedList::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationNGCategorizedList::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationNGCategorizedList::SlotClicked ()
{
	if(Form!=NULL){
		delete	Form;
	}
	Form=new IntegrationNGCategorizedListForm(GetLayersBase());
	Form->show();
}
void	IntegrationNGCategorizedList::TransmitDirectly(GUIDirectMessage *packet)
{
}
