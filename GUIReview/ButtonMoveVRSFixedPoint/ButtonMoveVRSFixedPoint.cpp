#include "ButtonMoveVRSFixedPointResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUIReview\ButtonMoveVRSFixedPoint\ButtonMoveVRSFixedPoint.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonMoveVRSFixedPoint.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XAlgorithmBase.h"
#include "XMacroFunction.h"
#include "XSequenceRepairLocal.h"

#include "XDataInLayer.h"
#include "XRememberer.h"
#include <QString>
#include "swap.h"
#include "XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"

static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"ButtonMoveVRSFixedPoint";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to move VRS into fixed point");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonMoveVRSFixedPoint(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<13)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"XPos";
	Data[4].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->XPos;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"YPos";
	Data[5].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->YPos;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"AbsoluteMode";
	Data[6].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->AbsoluteMode;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"ToggleMode";
	Data[7].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->ToggleMode;
	Data[8].Type				 =/**/"int32";
	Data[8].VariableNameWithRoute=/**/"SysBitNumber";
	Data[8].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->SysBitNumber;
	Data[9].Type				 =/**/"int32";
	Data[9].VariableNameWithRoute=/**/"SysRegisterXPos";
	Data[9].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->SysRegisterXPos;
	Data[10].Type				 =/**/"int32";
	Data[10].VariableNameWithRoute=/**/"SysRegisterYPos";
	Data[10].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->SysRegisterYPos;
	Data[11].Type				 =/**/"bool";
	Data[11].VariableNameWithRoute=/**/"ReleaseButtonOnOtherOperation";
	Data[11].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->ReleaseButtonOnOtherOperation;
	Data[12].Type				 =/**/"int32";
	Data[12].VariableNameWithRoute=/**/"ShortcutKey";
	Data[12].Pointer				 =&((ButtonMoveVRSFixedPoint *)Instance)->ShortcutKey;

	return(13);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonMoveVRSFixedPoint.png")));
}


//==================================================================================================
	
KeyedColorButton::KeyedColorButton(bool ColorDialogOnLClick ,QWidget *parent)
	:mtToolButtonColored(ColorDialogOnLClick ,parent)
{
}

KeyedColorButton::KeyedColorButton(bool ColorDialogOnLClick ,const QColor &col ,QWidget *parent)
	:mtToolButtonColored(ColorDialogOnLClick ,col ,parent)
{
}

void KeyedColorButton::leaveEvent ( QEvent * e )
{
	//if(isChecked()==true){
	//	setChecked(false);
	//	emit	clicked(false);
	//}
}


ButtonMoveVRSFixedPoint::ButtonMoveVRSFixedPoint(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonMoveVRSFixedPoint");
	Msg=/**/"Move VRS";
	XPos=0;
	YPos=0;
	AbsoluteMode=true;
	ToggleMode	=false;
	BackColor	=Qt::gray;
	SysBitNumber	=-1;
	SysRegisterXPos	=-1;
	SysRegisterYPos	=-1;
	oPushedOperand	=NULL;
	iFixedXPos		=NULL;
	iFixedYPos		=NULL;
	ReleaseButtonOnOtherOperation	=false;
	ShortcutKey		=-1;
	LastKeyTime		=0;

	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonMoveVRSFixedPoint::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setCheckable(ToggleMode);
	Button.setColor(BackColor);
	Button.setPressedColor(Qt::red);
	ResizeAction();

	if(GetEditMode()==false){
		if(GetLayersBase()->GetInsideLearningEditor()==false 
		&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				if(SysBitNumber>0){
					oPushedOperand		=new SignalOperandBit(this,SysBitNumber,/**/"ButtonMoveVRSFixedPoint:oPushedOperand");
					Param->SetSpecialOperand(oPushedOperand);
					if(Button.isChecked()==true)
						oPushedOperand->Set(true);
					else
						oPushedOperand->Set(false);
				}
				if(SysRegisterXPos>0){
					iFixedXPos		=new SignalOperandInt(this,SysRegisterXPos,/**/"ButtonMoveVRSFixedPoint:iFixedXPos");
					Param->SetSpecialOperand(iFixedXPos);
					iFixedXPos	->Set(XPos);
				}
				if(SysRegisterYPos>0){
					iFixedYPos		=new SignalOperandInt(this,SysRegisterYPos,/**/"ButtonMoveVRSFixedPoint:iFixedYPos");
					Param->SetSpecialOperand(iFixedYPos);
					iFixedYPos	->Set(YPos);
				}
			}
		}
	}
	if(ShortcutKey>0){
		SetKeyGrab(true);
	}
}

void	ButtonMoveVRSFixedPoint::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonMoveVRSFixedPoint::SlotClicked (bool checked)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	if(AbsoluteMode==true){
		CmdSetVRSMotorState setMotor(GetLayersBase());
		setMotor.setX(XPos);
		setMotor.setY(YPos);
		RBase->TransmitDirectly( &setMotor );
	}
	else{
		CmdReqVRSMotorState reqMotor(GetLayersBase());
		RBase->TransmitDirectly( &reqMotor );

		if(ToggleMode==false){
			CmdSetVRSMotorState setMotor(GetLayersBase());
			setMotor.setX(XPos+reqMotor.x);
			setMotor.setY(YPos+reqMotor.y);
			RBase->TransmitDirectly( &setMotor );
		}
		else{
			if(Button.isChecked()==true){
				CmdSetVRSMotorState setMotor(GetLayersBase());
				LastX=XPos+reqMotor.x;
				LastY=YPos+reqMotor.y;
				setMotor.setX(XPos+reqMotor.x);
				setMotor.setY(YPos+reqMotor.y);
				RBase->TransmitDirectly( &setMotor );
			}
			else{
				CmdSetVRSMotorState setMotor(GetLayersBase());
				int	dx=reqMotor.x-LastX;
				int	dy=reqMotor.y-LastY;
				if(dx==0 && dy==0){
					setMotor.setX(-XPos+reqMotor.x);
					setMotor.setY(-YPos+reqMotor.y);
					RBase->TransmitDirectly( &setMotor );
				}
			}
		}
	}
	if(oPushedOperand!=NULL){
		if(ToggleMode==true){
			if(Button.isChecked()==true)
				oPushedOperand->Set(true);
			else
				oPushedOperand->Set(false);
		}
		else{
			oPushedOperand->Set(true);
		}
	}
}

void	ButtonMoveVRSFixedPoint::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	WorkedSpecifiedBroadcaster	*WorkedSpecifiedBroadcasterVar=dynamic_cast<WorkedSpecifiedBroadcaster *>(v);
	if(WorkedSpecifiedBroadcasterVar!=NULL){
		if(ReleaseButtonOnOtherOperation==true && Button.isChecked()==true){
			Button.setChecked(false);
			SlotClicked(false);
		}
		return;
	}
}

void	ButtonMoveVRSFixedPoint::keyPressEvent ( QKeyEvent * event )
{
	int	Key=event->key();
	//GUIFormBase::keyPressEvent (event);
	if(Key==ShortcutKey){
		DWORD	CurrentKeyTime=::GetComputerMiliSec();
		DWORD	t=CurrentKeyTime-LastKeyTime;
		LastKeyTime=CurrentKeyTime;
		if(t<50)
			return;
		if(ToggleMode==false){
			SlotClicked(true);
		}
		else{
			if(Button.isChecked()==true){
				Button.setChecked(false);
				SlotClicked(false);
			}
			else{
				Button.setChecked(true);
				SlotClicked(true);
			}
		}
	}
}

