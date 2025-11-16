#include "ButtonExecuteFilterImageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExecuteFilterImage\ButtonExecuteFilterImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonExecuteFilterImage.h"
#include "XGeneralFunc.h"
#include "XGeneralDialog.h"
#include "XFilterInstance.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ButtonExecuteFilterImage";

const	int		MAXBUFFERCOUNTS=10000;

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to execute Filter in Target image");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqExecuteFilterImage(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonExecuteFilterImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonExecuteFilterImage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonExecuteFilterImage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonExecuteFilterImage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonExecuteFilterImage *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"Mastered";
	Data[4].Pointer				 =&((ButtonExecuteFilterImage *)Instance)->Mastered;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonExecuteFilterImage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonExecuteFilterImage::ButtonExecuteFilterImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Execute Filter";
	resize(150,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	Mastered=true;
}

void	ButtonExecuteFilterImage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonExecuteFilterImage::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonExecuteFilterImage::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqExecuteFilterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
		RCmd.Mastered=Mastered;
		RCmd.Send(NULL,page ,0);
	}
}


//======================================================================================

GUICmdReqExecuteFilterImage::GUICmdReqExecuteFilterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqExecuteFilterImage::Load(QIODevice *f)
{
	if(::Load(f,Mastered)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqExecuteFilterImage::Save(QIODevice *f)
{
	if(::Save(f,Mastered)==false){
		return false;
	}
	return true;
}

void	GUICmdReqExecuteFilterImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		int	SavedMaxScanStrategy=GetParamGlobal()->GetMaxScanStrategy();
		GetParamGlobal()->SetMaxScanStrategy(1);
		if(Mastered==true){
			GetLayersBase()->ExecuteFilteringMaster();
		}
		else{
			GetLayersBase()->ExecuteFilteringTarget();
		}
		GetParamGlobal()->SetMaxScanStrategy(SavedMaxScanStrategy);
	}
}

