#include "ButtonShutdownResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonShutdown\ButtonShutdown.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <time.h>
#include "ButtonShutdown.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "XGeneralFunc.h"
#include "XForWindows.h"
#include "XEntryPoint.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"Shutdown";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button Shutdown");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdShutDown(Base ,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonShutdown(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonShutdown *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"RebootMode";
	Data[1].Pointer				 =&((ButtonShutdown *)Instance)->RebootMode;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonShutdown.png")));
}

//=========================================================================================================

ButtonShutdown::ButtonShutdown(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Shutdown";
	setObjectName(/**/"ButtonShutdown");
	RebootMode=false;
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}


void	ButtonShutdown::Prepare(void)
{
	Button.setText(Msg);
	ResizeAction();
}
void	ButtonShutdown::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonShutdown::SlotClicked (bool checked)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;

	for(int page=0;page<GetPageNumb();page++){
		GUICmdShutDown	RCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.Send(NULL,page,0);
	}
	if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==true){
		for(DWORD t=time(NULL);time(NULL)-t<3;){
			QCoreApplication::processEvents ();
		}
		MtShutdownSelfPC( true, RebootMode);
	}
	ReEntrant=false;
}

GUICmdShutDown::GUICmdShutDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdShutDown::Load(QIODevice *f)
{
	if(::Load(f,RebootMode)==false){
		return false;
	}
	return true;
}
bool	GUICmdShutDown::Save(QIODevice *f)
{
	if(::Save(f,RebootMode)==false){
		return false;
	}
	return true;
}

void	GUICmdShutDown::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MtShutdownSelfPC( true, RebootMode);
}

