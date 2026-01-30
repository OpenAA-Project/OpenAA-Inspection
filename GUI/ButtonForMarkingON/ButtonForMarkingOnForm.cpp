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

#include "ButtonForMarkingONResource.h"
#include "ButtonForMarkingOnForm.h"
#include "ui_ButtonForMarkingOnForm.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"

ButtonForMarkingOnForm::ButtonForMarkingOnForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base ,parent),
    ui(new Ui::ButtonForMarkingOnForm)
{
	Msg=/**/"MarkingON";
    ui->setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	ioMarkingON=NULL;

}

ButtonForMarkingOnForm::~ButtonForMarkingOnForm()
{
    delete ui;
}
void	ButtonForMarkingOnForm::Prepare(void)
{
	ui->toolButton->setText(Msg);
	ui->toolButton->setFont (CFont);

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMarkingON	=new SignalOperandInt(this,520,/**/"ButtonForMarkingOnForm:ioMarkingON");
			connect(ioMarkingON	,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMarkingON,&Error)==false){
				ioMarkingON->ShowErrorMessage(Error);
			}
		}
	}

	ResizeAction();
}
void	ButtonForMarkingOnForm::ResizeAction()
{
	ui->toolButton->resize(width(),height());
}
void	ButtonForMarkingOnForm::OperandChanged()
{
}
void ButtonForMarkingOnForm::on_toolButton_clicked()
{
	if(ioMarkingON!=NULL){
		if(ui->toolButton->isChecked()==true)
			ioMarkingON->Set(1);
		else
			ioMarkingON->Set(0);
	}
}