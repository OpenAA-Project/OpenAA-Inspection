/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonAlignmentOffset\ButtonAlignmentOffset.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonAlignmentOffset.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XAlgorithmBase.h"
#include "XAlignmentLarge.h"
#include "SetAlignmentOffsetForm.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"AlignmentOffset";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to set AlignmentOffset");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqAlignmentOffset(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckAlignmentOffset(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetAlignmentOffset(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonAlignmentOffset(Base,parent));
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
	Data[0].Pointer				 =&((ButtonAlignmentOffset *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonAlignmentOffset *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonAlignmentOffset *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonAlignmentOffset *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"MaxOffsetXDot";
	Data[4].Pointer				 =&((ButtonAlignmentOffset *)Instance)->MaxOffsetXDot;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"MaxOffsetYDot";
	Data[5].Pointer				 =&((ButtonAlignmentOffset *)Instance)->MaxOffsetYDot;
	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonAlignmentOffset.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonAlignmentOffset::ButtonAlignmentOffset(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	MaxOffsetXDot=5000;
	MaxOffsetYDot=5000;
	Window		=NULL;

	Button.setParent(this);
	Button.setObjectName(QString(/**/"AlignmentOffset"));
	Button.move(0,0);
	Msg=/**/"AlignmentOffset";
	resize(60,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonAlignmentOffset::~ButtonAlignmentOffset(void)
{
}

void	ButtonAlignmentOffset::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonAlignmentOffset::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonAlignmentOffset::SlotClicked()
{
	if(Window==NULL){
		Window=new SetAlignmentOffsetForm(GetLayersBase(),this);
	}
	Window->show();
}

//========================================================================================================

GUICmdReqAlignmentOffset::GUICmdReqAlignmentOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAlignmentOffset::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentOffset	*SendBack=GetSendBack(GUICmdAckAlignmentOffset,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase!=NULL){
		AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)AlignBase->GetPageData(localPage);
		if(Ap!=NULL){
			SendBack->OffsetX	=Ap->OffsetX;
			SendBack->OffsetY	=Ap->OffsetY;
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
//========================================================================================================

GUICmdAckAlignmentOffset::GUICmdAckAlignmentOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckAlignmentOffset::Load(QIODevice *f)
{
	if(::Load(f,OffsetX)==false)
		return false;
	if(::Load(f,OffsetY)==false)
		return false;
	return true;
}

bool	GUICmdAckAlignmentOffset::Save(QIODevice *f)
{
	if(::Save(f,OffsetX)==false)
		return false;
	if(::Save(f,OffsetY)==false)
		return false;
	return true;
}
//========================================================================================================

GUICmdSetAlignmentOffset::GUICmdSetAlignmentOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetAlignmentOffset::Load(QIODevice *f)
{
	if(::Load(f,OffsetX)==false)
		return false;
	if(::Load(f,OffsetY)==false)
		return false;
	return true;
}

bool	GUICmdSetAlignmentOffset::Save(QIODevice *f)
{
	if(::Save(f,OffsetX)==false)
		return false;
	if(::Save(f,OffsetY)==false)
		return false;
	return true;
}

void	GUICmdSetAlignmentOffset::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase!=NULL){
		AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)AlignBase->GetPageData(localPage);
		if(Ap!=NULL){
			Ap->OffsetX=OffsetX;
			Ap->OffsetY=OffsetY;
		}
	}
}