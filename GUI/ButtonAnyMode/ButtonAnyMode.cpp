#include "ButtonAnyModeResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonAnyMode\ButtonAnyMode.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonAnyMode.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XCriticalFunc.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"AnyMode";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Any Mode Button");
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
	return(new ButtonAnyMode(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonAnyMode *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonAnyMode *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonAnyMode *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonAnyMode *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"DefaultPushed";
	Data[4].Pointer				 =&((ButtonAnyMode *)Instance)->DefaultPushed;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"SystemRegisterNo";
	Data[5].Pointer				 =&((ButtonAnyMode *)Instance)->SystemRegisterNo;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"ShortcutKey";
	Data[6].Pointer				 =&((ButtonAnyMode *)Instance)->ShortcutKey;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonAnyMode.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonAnyMode::ButtonAnyMode(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SystemRegisterNo=50;
	ioMode			=NULL;
	ShortcutKey		=-1;
	LastKeyTime		=0;

	DefaultPushed	=false;
	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	Msg=/**/"AnyMode";
	resize(60,25);
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonAnyMode::~ButtonAnyMode(void)
{
}

void	ButtonAnyMode::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setChecked(DefaultPushed);
	QPalette	Pal=Button.palette();
	Pal.setColor(QPalette::Button,BackColor);
	Button.setPalette(Pal);
	Button.setObjectName(QString(/**/"ButtonAnyMode")+QString::number(SystemRegisterNo));
	ResizeAction();

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMode		=new SignalOperandBit(this,SystemRegisterNo,/**/"ButtonAnyMode:ioMode");
			connect(ioMode			,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMode,&Error)==false){
				ioMode->ShowErrorMessage(Error);
			}
		}
	}
	if(ShortcutKey>0){
		SetKeyGrab(true);
	}
	SlotToggled(true);
}

void	ButtonAnyMode::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonAnyMode::SlotToggled( bool checked )
{
	if(ioMode!=NULL){
		if(Button.isChecked()==true)
			ioMode->Set(true);
		else
			ioMode->Set(false);
	}
}
void	ButtonAnyMode::keyPressEvent ( QKeyEvent * event )
{
	int	Key=event->key();
	//GUIFormBase::keyPressEvent (event);
	if(Key==ShortcutKey){
		DWORD	CurrentKeyTime=::GetComputerMiliSec();
		DWORD	t=CurrentKeyTime-LastKeyTime;
		LastKeyTime=CurrentKeyTime;
		if(t<50)
			return;	
		if(Button.isChecked()==true){
			Button.setChecked(false);
			SlotToggled(false);
		}
		else{
			Button.setChecked(true);
			SlotToggled(true);
		}
	}
}
