/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonCopyAnyPhasePageLayer\ButtonCopyAnyPhasePageLayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonCopyAnyPhasePageLayer.h"
#include "XGeneralDialog.h"
#include "CopyAnyPhasePageLayerDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"CopyAnyPhasePageLayer";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Copy any Phase/Page/Layer - image/algorithm data");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqAnyData	(Base,sRoot,sName);
	(*Base)=new GUICmdAckAnyData	(Base,sRoot,sName);
	(*Base)=new GUICmdSendAnyData	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonCopyAnyPhasePageLayer(Base,parent));
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
	Data[0].Pointer				 =&((ButtonCopyAnyPhasePageLayer *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonCopyAnyPhasePageLayer *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonCopyAnyPhasePageLayer *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonCopyAnyPhasePageLayer *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonCopyAnyPhasePageLayer.png")));
}

//==================================================================================================
ButtonCopyAnyPhasePageLayer::ButtonCopyAnyPhasePageLayer(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonCopyAnyPhasePageLayer");
	Msg=/**/"Copy any Phase/Page/Layer";


	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonCopyAnyPhasePageLayer::~ButtonCopyAnyPhasePageLayer(void)
{
}

void	ButtonCopyAnyPhasePageLayer::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonCopyAnyPhasePageLayer::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonCopyAnyPhasePageLayer::SlotClicked (bool checked)
{
	CopyAnyPhasePageLayerDialog	D(GetLayersBase());
	D.exec();
}
