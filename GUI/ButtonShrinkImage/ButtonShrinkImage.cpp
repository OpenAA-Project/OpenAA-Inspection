#include "ButtonShrinkImageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonShrinkImage\ButtonShrinkImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonShrinkImage.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "ShrinkImageDialog.h"
#include "XImageBufferFunctions.h"

static	const	char	*sRoot=/**/"ImageProcess";
static	const	char	*sName=/**/"ButtonShrinkImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Shrink Image");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqShrinkImage (Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonShrinkImage(Base,parent));
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
	Data[0].Pointer				 =&((ButtonShrinkImage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonShrinkImage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonShrinkImage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonShrinkImage *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonShrinkImage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonShrinkImage::ButtonShrinkImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Shrink Image";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonShrinkImage::~ButtonShrinkImage(void)
{
}

void	ButtonShrinkImage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonShrinkImage::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonShrinkImage::SlotClicked (bool checked)
{
	ShrinkImageDialog	Q(GetLayersBase(),this);

	if(Q.exec()==(int)true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqShrinkImage	RCmd(GetLayersBase(),sRoot,sName,page);
			RCmd.Rate		=Q.Rate;
			RCmd.ExeMaster	=Q.ExeMaster;
			RCmd.ExeTarget	=Q.ExeTarget;
			RCmd.Send(NULL,page,0);
		}
	}
}

GUICmdReqShrinkImage::GUICmdReqShrinkImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqShrinkImage::Load(QIODevice *f)
{
	if(::Load(f,Rate)==false){
		return false;
	}
	if(::Load(f,ExeMaster)==false){
		return false;
	}
	if(::Load(f,ExeTarget)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqShrinkImage::Save(QIODevice *f)
{
	if(::Save(f,Rate)==false){
		return false;
	}
	if(::Save(f,ExeMaster)==false){
		return false;
	}
	if(::Save(f,ExeTarget)==false){
		return false;
	}
	return true;
}

void	GUICmdReqShrinkImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
		if(ExeMaster==true){
			ShrinkImage(GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer)->GetMasterBuff(),Rate);
		}
		if(ExeTarget==true){
			ShrinkImage(GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer)->GetTargetBuff(),Rate);
		}
	}
}
