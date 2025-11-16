/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonModeAutoIncScanNumber\ButtonModeAutoIncScanNumber.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonModeAutoIncScanNumber.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"

//extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ModeAutoIncScanNumber";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to set mode Auto Inc ScanNumber");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSetModeAutoIncScanNumber(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonModeAutoIncScanNumber(Base,parent));
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
	Data[0].Pointer				 =&((ButtonModeAutoIncScanNumber *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonModeAutoIncScanNumber *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonModeAutoIncScanNumber *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonModeAutoIncScanNumber *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonModeAutoIncScanNumber.png")));
}

//==================================================================================================


ButtonModeAutoIncScanNumber::ButtonModeAutoIncScanNumber(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setAutoExclusive (false);
	Button.setCheckable(true);

	Button.setObjectName(/**/"ButtonModeAutoIncScanNumber");
	Msg=/**/"AutoIncScanNumber";
	resize(60,25);

	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonModeAutoIncScanNumber::~ButtonModeAutoIncScanNumber(void)
{
}

void	ButtonModeAutoIncScanNumber::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();

	Button.setChecked(GetParamGlobal()->AutoIncrementScanPhaseNumber);
}

void	ButtonModeAutoIncScanNumber::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonModeAutoIncScanNumber::SlotClicked (bool checked)
{
	GetParamGlobal()->AutoIncrementScanPhaseNumber	=Button.isChecked();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetModeAutoIncScanNumber	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.ModeAutoIncScanNumber	=GetParamGlobal()->AutoIncrementScanPhaseNumber;
		RCmd.Send(NULL,page,0);
	}
}

void	ButtonModeAutoIncScanNumber::TransmitDirectly(GUIDirectMessage *packet)
{
}


//==================================================================================================

GUICmdSetModeAutoIncScanNumber::GUICmdSetModeAutoIncScanNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ModeAutoIncScanNumber=true;
}

bool	GUICmdSetModeAutoIncScanNumber::Load(QIODevice *f)
{
	if(::Load(f,ModeAutoIncScanNumber)==false)
		return false;
	return true;
}

bool	GUICmdSetModeAutoIncScanNumber::Save(QIODevice *f)
{
	if(::Save(f,ModeAutoIncScanNumber)==false)
		return false;
	return true;
}

void	GUICmdSetModeAutoIncScanNumber::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	GetParamGlobal()->AutoIncrementScanPhaseNumber	=ModeAutoIncScanNumber;
}