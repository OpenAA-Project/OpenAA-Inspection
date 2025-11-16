/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadFilterConfig\ButtonLoadFilterConfig.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonLoadFilterConfig.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmBase.h"
#include <QIcon>
#include <QPixmap>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>

const	char	*sRoot=/**/"Filter";
const	char	*sName=/**/"LoadFilterConfig";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load filter configuration file");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	//(*Base)=new GUICmdReqButtonClearMasterInfo		(Base,sRoot,sName);
	//(*Base)=new GUICmdReqButtonClearMasterInfoPhase(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLoadFilterConfig(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonLoadFilterConfig *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadFilterConfig *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadFilterConfig *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadFilterConfig *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadFilterConfig.png")));
}


//==================================================================================================
ButtonLoadFilterConfig::ButtonLoadFilterConfig(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonLoadFilterConfig");
	Msg=/**/"Load filter file";

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonLoadFilterConfig::~ButtonLoadFilterConfig(void)
{
}

void	ButtonLoadFilterConfig::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLoadFilterConfig::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonLoadFilterConfig::SlotClicked (bool checked)
{
	QString	FileName=QFileDialog::getOpenFileName(nullptr
												  , "Load filter config file"
												  , QString()
												  , /**/"Config file(ConfigFilter*.dat);;dat file(*.dat);;All file(*.*)"
												  );
	if(FileName.isEmpty()==true){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			if(GetLayersBase()->LoadFilterDef(&File)==false){
				QMessageBox::warning(NULL,"Loading filter error"
										, "Mistake Filter Config file or broken");
			}
		}
	}
}
