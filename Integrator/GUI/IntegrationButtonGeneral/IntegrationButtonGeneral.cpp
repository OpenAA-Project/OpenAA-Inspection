/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integration\GUI\IntegrationButtonGeneral\IntegrationButtonGeneral.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationButtonGeneral.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XCriticalFunc.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Integration";
static	const	char	*sName=/**/"ButtonGeneral";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Any Button for Integration");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)	=new IntegrationCmdButtonGeneral(Base,sRoot,sName,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationButtonGeneral(Base,parent));
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
	Data[0].Pointer				 =&((IntegrationButtonGeneral *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationButtonGeneral *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationButtonGeneral *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationButtonGeneral *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"DefaultPushed";
	Data[4].Pointer				 =&((IntegrationButtonGeneral *)Instance)->DefaultPushed;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"Checkable";
	Data[5].Pointer				 =&((IntegrationButtonGeneral *)Instance)->Checkable;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"SystemRegisterNo";
	Data[6].Pointer				 =&((IntegrationButtonGeneral *)Instance)->SystemRegisterNo;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationButtonGeneral.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
IntegrationButtonGeneral::IntegrationButtonGeneral(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SystemRegisterNo=-1;
	ioMode			=NULL;
	DefaultPushed	=false;
	Checkable		=true;

	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	Msg=/**/"General";
	resize(60,25);
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationButtonGeneral::~IntegrationButtonGeneral(void)
{
}

void	IntegrationButtonGeneral::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setCheckable(Checkable);
	Button.setChecked(DefaultPushed);
	QPalette	Pal=Button.palette();
	Pal.setColor(QPalette::Button,BackColor);
	Button.setPalette(Pal);
	Button.setObjectName(QString(/**/"IntegrationButtonGeneral")+QString::number(SystemRegisterNo));
	ResizeAction();

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0
	&& SystemRegisterNo>0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMode		=new SignalOperandBit(this,SystemRegisterNo,/**/"IntegrationButtonGeneral:ioMode");
			connect(ioMode			,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMode,&Error)==false){
				ioMode->ShowErrorMessage(Error);
			}
		}
	}

	SlotToggled(true);
}

void	IntegrationButtonGeneral::ResizeAction()
{
	Button.resize(width(),height());
}

void	IntegrationButtonGeneral::SlotToggled( bool checked )
{
	bool	b=Button.isChecked();
	SetToggled(b);

	if(GetLayersBase()->GetIntegrationBasePointer()->IsMastered()==true){
		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			IntegrationCmdButtonGeneral	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.ButtonState=b;
			RCmd.Send(NULL,SlaveNo,0);
		}
	}
}

void	IntegrationButtonGeneral::SetToggled( bool ButtonState )
{
	if(ioMode!=NULL){
		if(ButtonState==true)
			ioMode->Set(true);
		else
			ioMode->Set(false);
	}
}

void	IntegrationButtonGeneral::SetButtonChecked( bool ButtonState )
{
	Button.setChecked(ButtonState);
}

//--------------------------------------------------------------------------------------

IntegrationCmdButtonGeneral::IntegrationCmdButtonGeneral(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdButtonGeneral::Load(QIODevice *f)
{
	if(::Load(f,ButtonState)==false)
		return false;

	return true;
}
bool	IntegrationCmdButtonGeneral::Save(QIODevice *f)
{
	if(::Save(f,ButtonState)==false)
		return false;

	return true;
}

void	IntegrationCmdButtonGeneral::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationButtonGeneral	*f=(IntegrationButtonGeneral *)GetLayersBase()->FindByName(sRoot ,sName ,/**/"");
	if(f!=NULL){
		f->SetToggled(ButtonState);
		f->SetButtonChecked(ButtonState);
	}
}

