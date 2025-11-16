/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationStopUpdateThumbnail\IntegrationStopUpdateThumbnail.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationStopUpdateThumbnail.h"
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
#include "XCriticalFunc.h"
#include "XExecuteInspectBase.h"
#include "IntegrationStackNGThumbnail.h"
#include "IntegrationStackNGThumbnailForm.h"
#include "XIntegrationStackNGThumbnailPacket.h"

static	const	char	*sRoot=/**/"Integration";
static	const	char	*sName=/**/"StopUpdateThumbnail";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to stop update thumbnail");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	
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
	return(new IntegrationStopUpdateThumbnail(Base,parent));
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
	Data[0].Pointer				 =&((IntegrationStopUpdateThumbnail *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationStopUpdateThumbnail *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationStopUpdateThumbnail *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationStopUpdateThumbnail *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationStopUpdateThumbnail.png")));
}


//==================================================================================================
IntegrationStopUpdateThumbnail::IntegrationStopUpdateThumbnail(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationStopUpdateThumbnailBtn");
	Button.move(0,0);
	Button.setCheckable(true);
	Msg=/**/"Stop update";

	resize(200,25);
	Button.setStyleSheet(/**/"QToolButton {"
						 /**/"	border-style: outset;"
						 /**/"	border-width: 1px;"
						 /**/"	border-radius: 25px;"
						 /**/"	border-color: gray;"
						 /**/"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));"
						 /**/"}"
						 /**/"QToolButton:checked { 	"
						 /**/"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 0, 0, 255), stop:1 rgba(141, 0, 0, 255));"
						 /**/"}"
						);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationStopUpdateThumbnail::~IntegrationStopUpdateThumbnail()
{

}

void	IntegrationStopUpdateThumbnail::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationStopUpdateThumbnail::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationStopUpdateThumbnail::SlotClicked ()
{
	bool	BMode=Button.isChecked();
	GUIFormBase	*Form[100];
	int	N=GetLayersBase()->EnumGUIInst(/**/"Integration",/**/"StackNGThumbnail",Form,100);
	for(int SlaveNo=0;SlaveNo<GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();SlaveNo++){
		IntegrationStackNGThumbnailForm	*f=(IntegrationStackNGThumbnailForm *)Form[SlaveNo];
		CmdSetUpdateMode	RCmd(GetLayersBase());
		RCmd.StartUpdate=!BMode;
		f->TransmitDirectly(&RCmd);
	}
}
