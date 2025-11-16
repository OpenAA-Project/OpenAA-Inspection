/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartStatisticScanButton\StartStatisticScanButtonForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StartStatisticScanButtonForm.h"
#include "StartStatisticScanButtonResource.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


StartStatisticScanButtonForm::StartStatisticScanButtonForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
	,StartStatisticScanBase(Base)
	,Button(false)
{
	ui.setupUi(this);

	Counter	=0;
	Button.setParent(this);
	Button.move(0,0);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	NormalColor=Qt::lightGray;
	PushedColor=Qt::red;
	Msg=/**/"Inspect";
	resize(60,25);
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	SetKeyGrab(true);
}

StartStatisticScanButtonForm::~StartStatisticScanButtonForm()
{

}

void	StartStatisticScanButtonForm::Prepare(void)
{
	Button.setText(Msg);
	Button.setColor(NormalColor);
	Button.setFont (CFont);
	ResizeAction();
}

void	StartStatisticScanButtonForm::ResizeAction()
{
	Button.resize(96,height());
}

void	StartStatisticScanButtonForm::SlotToggled (bool checked)
{
	SlotToggledInside(checked);
}


void StartStatisticScanButtonForm::keyPressEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_F2){
		//SlotClicked(true);
		Button.setChecked(true);
		event->accept();
	}
}
bool StartStatisticScanButtonForm::OnIdle(void)
{
	GUIFormBase::OnIdle();
	StartStatisticScanBase::OnIdleFunc();
	return true;
}

void StartStatisticScanButtonForm::OnIdleEnd(void)
{
	Button.setColor(NormalColor);
	Button.setChecked(false);
	Counter++;
	ui.labelNowCount->setText(QString::number(Counter));
	if(Counter<ui.spinBoxMaxCount->value()){
		SlotToggledInside(true);
	}
}
void StartStatisticScanButtonForm::OnToggled(void)
{
	Button.setColor(PushedColor);
}

//==================================================================================================
