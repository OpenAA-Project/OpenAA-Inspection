/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonEnableFilter\ButtonEnableFilter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonEnableFilter.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmBase.h"
#include <QIcon>
#include <QPixmap>
#include <QStringList>

const	char	*sRoot=/**/"Filter";
const	char	*sName=/**/"EnableFilter";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to enable/disable filter");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdEnableFilter		(Base,sRoot,sName);
	//(*Base)=new GUICmdReqButtonClearMasterInfoPhase(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonEnableFilter(Base,parent));
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
	Data[0].Pointer				 =&((ButtonEnableFilter *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonEnableFilter *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonEnableFilter *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonEnableFilter *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonEnableFilter.png")));
}

//==================================================================================================
ButtonEnableFilter::ButtonEnableFilter(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setCheckable(true);
	Button.setObjectName(/**/"ButtonEnableFilter");
	Msg=/**/"Enable filter";

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonEnableFilter::~ButtonEnableFilter(void)
{
}

void	ButtonEnableFilter::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setChecked(GetLayersBase()->IsEnableFilter());
	ResizeAction();
}

void	ButtonEnableFilter::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonEnableFilter::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdEnableFilter	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.EnableFilter=Button.isChecked();
		RCmd.Send(NULL,globalPage,0);
	}
}

//============================================================================================

GUICmdEnableFilter::GUICmdEnableFilter(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdEnableFilter::Load(QIODevice *f)
{
	if(::Load(f,EnableFilter)==false)	return false;
	return true;
}
bool	GUICmdEnableFilter::Save(QIODevice *f)
{
	if(::Save(f,EnableFilter)==false)	return false;
	return true;
}

void	GUICmdEnableFilter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->SetEnableFilter(EnableFilter);
	}
}
