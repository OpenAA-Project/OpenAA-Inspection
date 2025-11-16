/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SetAlignmentLargeHeadLine\SetAlignmentLargeHeadLine.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "SetAlignmentLargeHeadLine.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XAlgorithmBase.h"
#include "XAlignmentLarge.h"
#include "XWriteResultThread.h"
#include "XAlignmentLarge.h"
#include "SetAlignmentLargeHeadLineDialog.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SetAlignmentLargeHeadLine";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to set AlignmentLarge HeadLine parameter");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSetAlignmentLargeHeadLine(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new SetAlignmentLargeHeadLine(Base,parent));
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
	Data[0].Pointer				 =&((SetAlignmentLargeHeadLine *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((SetAlignmentLargeHeadLine *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((SetAlignmentLargeHeadLine *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((SetAlignmentLargeHeadLine *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SetAlignmentLargeHeadLine.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
SetAlignmentLargeHeadLine::SetAlignmentLargeHeadLine(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"HeadLine";
	resize(60,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

SetAlignmentLargeHeadLine::~SetAlignmentLargeHeadLine(void)
{
}

void	SetAlignmentLargeHeadLine::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setObjectName(QString(/**/"HeadLine"));
	ResizeAction();
}

void	SetAlignmentLargeHeadLine::ResizeAction()
{
	Button.resize(width(),height());
}

AlignmentLargeBase	*SetAlignmentLargeHeadLine::GetAlignmentLargeBase(void)
{
	AlignmentLargeBase	*A=(AlignmentLargeBase	*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	return A;
}

void	SetAlignmentLargeHeadLine::SlotClicked()
{
	AlignmentLargeBase	*ABase=GetAlignmentLargeBase();
	SetAlignmentLargeHeadLineDialog	D(GetLayersBase());
	D.UseHeadAlignment		=ABase->UseHeadAlignment		;
	D.MaxHeadAlignmentX		=ABase->MaxHeadAlignmentX		;
	D.MaxHeadAlignmentY		=ABase->MaxHeadAlignmentY		;
	D.SkipHeadAlignmentX	=ABase->SkipHeadAlignmentX		;
	D.SkipHeadAlignmentY	=ABase->SkipHeadAlignmentY		;
	D.HeadAlignmentDifColor	=ABase->HeadAlignmentDifColor	;
	D.HeadAlignmentMinSize	=ABase->HeadAlignmentMinSize	;
	D.HeadAlignmentStep		=ABase->HeadAlignmentStep		;

	D.SetInitial();
	if(D.exec()==true){
		ABase->UseHeadAlignment		=D.UseHeadAlignment		;
		ABase->MaxHeadAlignmentX	=D.MaxHeadAlignmentX	;	
		ABase->MaxHeadAlignmentY	=D.MaxHeadAlignmentY	;	
		ABase->SkipHeadAlignmentX	=D.SkipHeadAlignmentX	;	
		ABase->SkipHeadAlignmentY	=D.SkipHeadAlignmentY	;	
		ABase->HeadAlignmentDifColor=D.HeadAlignmentDifColor;	
		ABase->HeadAlignmentMinSize	=D.HeadAlignmentMinSize	;
		ABase->HeadAlignmentStep	=D.HeadAlignmentStep	;	

		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetAlignmentLargeHeadLine	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
			RCmd.UseHeadAlignment		=D.UseHeadAlignment		;
			RCmd.MaxHeadAlignmentX		=D.MaxHeadAlignmentX	;	
			RCmd.MaxHeadAlignmentY		=D.MaxHeadAlignmentY	;	
			RCmd.SkipHeadAlignmentX		=D.SkipHeadAlignmentX	;	
			RCmd.SkipHeadAlignmentY		=D.SkipHeadAlignmentY	;	
			RCmd.HeadAlignmentDifColor	=D.HeadAlignmentDifColor;	
			RCmd.HeadAlignmentMinSize	=D.HeadAlignmentMinSize	;
			RCmd.HeadAlignmentStep		=D.HeadAlignmentStep	;	
	
			RCmd.SendOnly(GlobalPage ,0);
		}
	}
}

//========================================================================================================

GUICmdSetAlignmentLargeHeadLine::GUICmdSetAlignmentLargeHeadLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetAlignmentLargeHeadLine::Load(QIODevice *f)
{
	if(::Load(f,UseHeadAlignment		)==false)	return false;
	if(::Load(f,MaxHeadAlignmentX		)==false)	return false;
	if(::Load(f,MaxHeadAlignmentY		)==false)	return false;
	if(::Load(f,SkipHeadAlignmentX		)==false)	return false;
	if(::Load(f,SkipHeadAlignmentY		)==false)	return false;
	if(::Load(f,HeadAlignmentDifColor	)==false)	return false;
	if(::Load(f,HeadAlignmentMinSize	)==false)	return false;
	if(::Load(f,HeadAlignmentStep		)==false)	return false;

	return true;
}

bool	GUICmdSetAlignmentLargeHeadLine::Save(QIODevice *f)
{
	if(::Save(f,UseHeadAlignment		)==false)	return false;
	if(::Save(f,MaxHeadAlignmentX		)==false)	return false;
	if(::Save(f,MaxHeadAlignmentY		)==false)	return false;
	if(::Save(f,SkipHeadAlignmentX		)==false)	return false;
	if(::Save(f,SkipHeadAlignmentY		)==false)	return false;
	if(::Save(f,HeadAlignmentDifColor	)==false)	return false;
	if(::Save(f,HeadAlignmentMinSize	)==false)	return false;
	if(::Save(f,HeadAlignmentStep		)==false)	return false;

	return true;
}

void	GUICmdSetAlignmentLargeHeadLine::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlignmentLargeBase	*ABase=(AlignmentLargeBase	*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");

	ABase->UseHeadAlignment		=UseHeadAlignment		;
	ABase->MaxHeadAlignmentX	=MaxHeadAlignmentX		;
	ABase->MaxHeadAlignmentY	=MaxHeadAlignmentY		;
	ABase->SkipHeadAlignmentX	=SkipHeadAlignmentX		;
	ABase->SkipHeadAlignmentY	=SkipHeadAlignmentY		;
	ABase->HeadAlignmentDifColor=HeadAlignmentDifColor	;
	ABase->HeadAlignmentMinSize	=HeadAlignmentMinSize	;
	ABase->HeadAlignmentStep	=HeadAlignmentStep		;

	SendAck(localPage);
}
