#include "ButtonEditFilterBankResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonEditFilterBank\ButtonEditFilterBank.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonEditFilterBank.h"
#include "XGeneralFunc.h"
#include "XGeneralDialog.h"
#include "EditFilterBank.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ButtonEditFilterBank";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to show/edit FilterBank");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//new GUICmdReqCalcFinalization(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonEditFilterBank(Base,parent));
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
	Data[0].Pointer				 =&((ButtonEditFilterBank *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonEditFilterBank *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonEditFilterBank *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonEditFilterBank *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonEditFilterBank.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonEditFilterBank::ButtonEditFilterBank(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Edit FilterBank";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonEditFilterBank::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonEditFilterBank::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonEditFilterBank::SlotClicked (bool checked)
{
	EditFilterBank	*Q=new EditFilterBank(GetLayersBase(),NULL);
	GeneralDialog	Dlg(GetLayersBase(),Q,this);
	Dlg.exec();
	/*
	if(GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqCalcFinalization	RCmd(GetLayersBase() ,sRoot,sName,page);
			RCmd.Send(NULL,page ,0);
		}
	}
	*/
}


//======================================================================================
/*
GUICmdReqEditFilterBank::GUICmdReqEditFilterBank(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqEditFilterBank::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqEditFilterBank::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqEditFilterBank::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0)
		GetLayersBase()->ExecuteInitialAfterEdit(GetLayersBase()->GetEntryPoint());
}
*/
