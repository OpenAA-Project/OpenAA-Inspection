#include "ButtonLightONResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLightON\ButtonLightON.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QColor>
#include "ButtonLightON.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XLightClass.h"
#include "XSyncGUI.h"
#include "XCriticalFunc.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"LightON";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Light Button ON/OFF");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLightON(Base,parent));
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
	Data[0].Pointer				 =&((ButtonLightON *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLightON *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLightON *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLightON *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"DefaultPushed";
	Data[4].Pointer				 =&((ButtonLightON *)Instance)->DefaultPushed;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLightON.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonLightON::ButtonLightON(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false)
{
	SyncMode		=false;
	DefaultPushed	=false;
	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	//Button.setObjectName(QString(/**/"ButtonLightON"));
	Msg=/**/"Light ON/OFF";
	resize(60,25);
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonLightON::~ButtonLightON(void)
{
}

void	ButtonLightON::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setColor(Qt::gray);
	Button.setPressedColor(Qt::green);
	Button.setChecked(DefaultPushed);
	Button.setObjectName(QString(/**/"ButtonLightON"));
	ResizeAction();

	SlotToggled(DefaultPushed);
}

void	ButtonLightON::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonLightON::SlotToggled( bool checked )
{
	ExecuteToggled(checked);

	if(SyncMode==false){
		if(GetLayersBase()->GetSyncGUIData()!=NULL
		&& GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			::Save(&Buff,checked);
			TxSync(Buff.buffer());
		}
	}
}
void	ButtonLightON::ExecuteToggled( bool checked )
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		if(checked==true){
			//GetLayersBase()->GetLightBase()->LightOff();
			//GSleep(1000);
			GetLayersBase()->GetLightBase()->LightOn();
		}
		else{
			GetLayersBase()->GetLightBase()->LightOff();
		}
	}
}
void	ButtonLightON::ReadyTerminate(void)
{
	SlotToggled(false);

	for(DWORD t=::GetComputerMiliSec();::GetComputerMiliSec()-t<2000;){
		QCoreApplication::processEvents();
	}
}

void	ButtonLightON::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);

	bool checked;
	::Load(&Buff,checked);

	SyncMode=true;
	Button.setChecked(checked);
	SyncMode=true;
}
