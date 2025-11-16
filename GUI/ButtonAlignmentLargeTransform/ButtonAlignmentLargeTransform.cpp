/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonAlignmentLargeTransform\ButtonAlignmentLargeTransform.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonAlignmentLargeTransform.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XAlgorithmBase.h"
#include "XAlignmentLarge.h"
#include "XWriteResultThread.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"AlignmentLargeTransform";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to transform by AlignmentLarge");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqAlignmentLargeTransform(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonAlignmentLargeTransform(Base,parent));
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
	Data[0].Pointer				 =&((ButtonAlignmentLargeTransform *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonAlignmentLargeTransform *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonAlignmentLargeTransform *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonAlignmentLargeTransform *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"MasterImage";
	Data[4].Pointer				 =&((ButtonAlignmentLargeTransform *)Instance)->MasterImage;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonAlignmentLargeTransform.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonAlignmentLargeTransform::ButtonAlignmentLargeTransform(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	MasterImage=true;

	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Transform";
	resize(60,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonAlignmentLargeTransform::~ButtonAlignmentLargeTransform(void)
{
}

void	ButtonAlignmentLargeTransform::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setObjectName(QString(/**/"Transform"));
	ResizeAction();
}

void	ButtonAlignmentLargeTransform::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonAlignmentLargeTransform::SlotClicked()
{
	GetLayersBase()->GetResultThread()->SetCastAll();
	GetLayersBase()->GetResultThread()->WaitForFinishingCast();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentLargeTransform	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
		RCmd.MasterImage	=MasterImage;
		RCmd.SendOnly(GlobalPage ,0);
	}
	BroadcastDirectly(_BC_BuildForShow	,0);
}

//========================================================================================================

GUICmdReqAlignmentLargeTransform::GUICmdReqAlignmentLargeTransform(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MasterImage=true;
}

bool	GUICmdReqAlignmentLargeTransform::Load(QIODevice *f)
{
	if(::Load(f,MasterImage)==false)
		return false;
	return true;
}

bool	GUICmdReqAlignmentLargeTransform::Save(QIODevice *f)
{
	if(::Save(f,MasterImage)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentLargeTransform::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;

	CmdReqAlignmentLargeTransform	RCmd(GetLayersBase());
	RCmd.MasterImage=MasterImage;
	AlignBase->GetPageData(localPage)->TransmitDirectly(&RCmd);

	SendAck(localPage);
}
