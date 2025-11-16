/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationButtonCopyAlgorithm\IntegrationButtonCopyAlgorithm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationButtonCopyAlgorithm.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>
#include "XIntegrationSimpleImagePanel.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ButtonCopyAlgorithm";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to copy algorithm between Slaves");
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
	return(new IntegrationButtonCopyAlgorithm(Base,parent));
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
	Data[0].Pointer				 =&((IntegrationButtonCopyAlgorithm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationButtonCopyAlgorithm *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationButtonCopyAlgorithm *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationButtonCopyAlgorithm *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SlaveNo";
	Data[4].Pointer				 =&((IntegrationButtonCopyAlgorithm *)Instance)->SlaveNo;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"IntegrationAlgoSimpleImagePanelInst";
	Data[5].Pointer				 =&((IntegrationButtonCopyAlgorithm *)Instance)->IntegrationAlgoSimpleImagePanelInst;
	Data[6].Type				 =/**/"IntList";
	Data[6].VariableNameWithRoute=/**/"DestSlaveNo";
	Data[6].Pointer				 =&((IntegrationButtonCopyAlgorithm *)Instance)->DestSlaveNo;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"ClearBeforeCopy";
	Data[7].Pointer				 =&((IntegrationButtonCopyAlgorithm *)Instance)->ClearBeforeCopy;
	return(8);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationButtonCopyAlgorithm.png")));
}

//==================================================================================================
IntegrationButtonCopyAlgorithm::IntegrationButtonCopyAlgorithm(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationButtonCopyAlgorithmBtn");
	Button.move(0,0);
	Msg=/**/"Copy";
	SlaveNo=0;
	ClearBeforeCopy=true;

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

void	IntegrationButtonCopyAlgorithm::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationButtonCopyAlgorithm::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationButtonCopyAlgorithm::SlotClicked ()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(IntegrationAlgoSimpleImagePanelInst);
	if(f!=NULL){
		IntegrationAlgoSimpleImagePanel	*P=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(f);
		if(P!=NULL){
			P->CopyToSlave(DestSlaveNo,ClearBeforeCopy);
			QMessageBox::information(NULL,"完了"
									,"コピーされました");
		}
	}
}

