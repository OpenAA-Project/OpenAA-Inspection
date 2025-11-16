/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationCameraAdjustment\IntegrationCameraAdjustment.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationCameraAdjustment.h"
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
#include "CameraChangeQuickPropertyForm.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"CameraAdjustment";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Adjust Camera");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdSetAdjustCamera(Base,sRoot,sName);
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
	return(new IntegrationCameraAdjustment(Base,parent));
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
	Data[0].Pointer				 =&((IntegrationCameraAdjustment *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationCameraAdjustment *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationCameraAdjustment *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationCameraAdjustment *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationCameraAdjustment.png")));
}


//==================================================================================================
IntegrationCameraAdjustment::IntegrationCameraAdjustment(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationCameraAdjustmentBtn");
	Button.move(0,0);
	Msg=/**/"Adjust camera";

	resize(200,25);
	Button.setStyleSheet(/**/"QToolButton {"
						 /**/"	border-style: outset;"
						 /**/"	border-width: 1px;"
						 /**/"	border-radius: 25px;"
						 /**/"	border-color: gray;"
						 /**/"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));"
						 /**/"}"
						 /**/"QToolButton:checked { 	"
						 /**/"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));"
						 /**/"}"
						);
	Button.setCheckable(true);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationCameraAdjustment::~IntegrationCameraAdjustment()
{

}

void	IntegrationCameraAdjustment::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationCameraAdjustment::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationCameraAdjustment::SlotClicked ()
{
	int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	if(Button.isChecked()==true){
		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			if(m!=NULL){
				for(int page=0;page<m->GetPageNumb();page++){
					IntegrationCmdSetAdjustCamera	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					RCmd.ONAdjustMode=true;
					RCmd.Send(NULL,SlaveNo,m->GetLocalPageFromGlobal(page));
				}
			}
		}
	}
	else{
		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			if(m!=NULL){
				for(int page=0;page<m->GetPageNumb();page++){
					IntegrationCmdSetAdjustCamera	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					RCmd.ONAdjustMode=false;
					RCmd.Send(NULL,SlaveNo,m->GetLocalPageFromGlobal(page));
				}
			}
		}
	}
}


//==================================================================================================

IntegrationCmdSetAdjustCamera::IntegrationCmdSetAdjustCamera(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdSetAdjustCamera::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Camera",/**/"ChangeQuickProperty",/**/"");
	if(f!=NULL){
		CmdCameraAdjustment	Cmd(GetLayersBase());
		Cmd.ON=ONAdjustMode;
		f->TransmitDirectly(&Cmd);
	}

}