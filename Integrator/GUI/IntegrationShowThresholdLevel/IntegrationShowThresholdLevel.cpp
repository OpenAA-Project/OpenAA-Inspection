/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationShowThresholdLevel\IntegrationShowThresholdLevel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationShowThresholdLevel.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include <QIcon>
#include <QPixmap>
#include "SetThresholdLevelForm.h"
#include "XIntegrationBase.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ShowThresholdLevel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Integration threshold level");
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
	return(new IntegrationShowThresholdLevel(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationShowThresholdLevel.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=======================================================================================

IntegrationShowThresholdLevel::IntegrationShowThresholdLevel(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	SForm=NULL;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()),Qt::QueuedConnection);
}

IntegrationShowThresholdLevel::~IntegrationShowThresholdLevel(void)
{
	if(SForm!=NULL){
		SForm->deleteLater();
		SForm=NULL;
	}
}
void	IntegrationShowThresholdLevel::ReadyParam(void)
{
	if(SForm==NULL){
		SForm=new SetThresholdLevelForm(GetLayersBase());
		SForm->setParent(this);
		connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalChangeThresholdLevel(int,int))
				,this,SLOT(SlotChangeThresholdLevel(int,int)));
		connect(SForm,SIGNAL(SignalChangeThresholdLevelID(int))
				,this,SLOT(SlotChangeThresholdLevelID(int)));
		SForm->show();
	}
}

void	IntegrationShowThresholdLevel::ResizeAction()
{
	if(SForm!=NULL){
		SForm->setGeometry(0,0,width(),height());
	}
}

void	IntegrationShowThresholdLevel::SlotChangeThresholdLevel(int oldLevel ,int newLevel)
{
	SForm->SetCurrentThresholdLevelID(newLevel);
	GetLayersBase()->GetIntegrationBasePointer()->DeliverThresholdLevel(newLevel);
}

void    IntegrationShowThresholdLevel::SlotChangeThresholdLevelID(int ThresholdLevelID)
{
	SForm->SetCurrentThresholdLevelID(ThresholdLevelID);
	GetLayersBase()->GetIntegrationBasePointer()->DeliverThresholdLevel(ThresholdLevelID);
}
