/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonArrangePage\ButtonArrangePage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonArrangePage.h"
#include "ThreadSequence.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XAlgorithmBase.h"

static	char	*sRoot=/**/"Button";
static	char	*sName=/**/"ArrangePage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Initialize");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqArrangePage(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonArrangePage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonArrangePage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonArrangePage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonArrangePage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonArrangePage *)Instance)->CFont;
	Data[4].Type				 =/**/"ArrangeVertical,ArrangeHorizontal,ArrangeTile";
	Data[4].VariableNameWithRoute=/**/"ArrangeMethod";
	Data[4].Pointer				 =&((ButtonArrangePage *)Instance)->ArrangeMethod;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonArrangePage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonArrangePage::ButtonArrangePage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ArrangeMethod	=/**/"ArrangeVertical";

	Button.setObjectName(/**/"ButtonArrangePage");
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Vertical";
	resize(60,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonArrangePage::~ButtonArrangePage(void)
{
}

void	ButtonArrangePage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setCheckable(true);
	Button.setObjectName(QString(/**/"ButtonArrangePage"));
	ResizeAction();
}

void	ButtonArrangePage::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonArrangePage::SlotClicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqArrangePage	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
		RCmd.ArrangeMethod	=ArrangeMethod;
		RCmd.SendOnly(GlobalPage ,0);
	}

}

//=======================================================================================================

GUICmdReqArrangePage::GUICmdReqArrangePage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqArrangePage::Load(QIODevice *f)
{
	if(::Load(f,ArrangeMethod)==false)
		return false;
	return true;
}
bool	GUICmdReqArrangePage::Save(QIODevice *f)
{
	if(::Save(f,ArrangeMethod)==false)
		return false;
	return true;
}

void	GUICmdReqArrangePage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{

}
