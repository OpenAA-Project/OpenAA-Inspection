/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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