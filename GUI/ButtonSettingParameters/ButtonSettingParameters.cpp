/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSettingParameters\ButtonSettingParameters.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QFileDialog>
#include "ButtonSettingParameters.h"
#include "SettingParamDialog.h"
#include "SettingParamDialogResource.h"
//#include "ServiceLibResource.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SettingParameters";

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
	return(/**/"Show setting-parameters window");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
	LangLibSolver.SetLanguage(Pkg,LanguageCode);
	LangSolverGUILib.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSettingParamImageTable(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSettingParameters(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSettingParameters *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSettingParameters *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSettingParameters *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSettingParameters *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSettingParameters.png")));
}

//==================================================================================================

ButtonSettingParameters::ButtonSettingParameters(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonSettingParametersBtn");
	Button.move(0,0);
	Msg=/**/"Parameters";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSettingParameters::~ButtonSettingParameters(void)
{
}

void	ButtonSettingParameters::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSettingParameters::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSettingParameters::SlotClicked (bool checked)
{
	SettingParamDialog	D(GetLayersBase(),NULL);
	GetLayersBase()->TmpHideProcessingForm();
	D.exec();
	GetLayersBase()->TmpRercoverProcessingForm();
}

void	ButtonSettingParameters::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,/**/"Setting","Setting Parameters",this);
	p->SetMenuNumber(1000);
	Info.AppendList(p);
}
void	ButtonSettingParameters::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
