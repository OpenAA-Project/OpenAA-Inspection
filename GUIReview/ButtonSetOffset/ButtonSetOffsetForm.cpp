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

#include "ButtonSetOffsetResource.h"
#include "ButtonSetOffsetForm.h"
#include "ui_ButtonSetOffsetForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"
#include <QString>
#include "swap.h"
#include "ThreadSequence.h"
#include "XSequenceRepairLocal.h"
#include "XExecuteInspectBase.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "XReviewCommonPacket.h"
#include "XGUIReviewGlobal.h"

ButtonSetOffsetForm::ButtonSetOffsetForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ButtonSetOffsetForm)
{
    ui->setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSetOffsetForm::~ButtonSetOffsetForm()
{
    delete ui;
}


void	ButtonSetOffsetForm::Prepare(void)
{
	ResizeAction();

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iButton	=new SignalOperandBit(this,266,/**/"ButtonSetOffset:iButton");
			connect(iButton	,SIGNAL(changed())	,this	,SLOT(OperandChanged())	,Qt::QueuedConnection);
			Param->SetSpecialOperand(iButton);
		}
	}
}
void ButtonSetOffsetForm::on_pushButtonSetOffset_clicked()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase!=NULL){
		CmdSetOffsetVRS Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
	}
}
void	ButtonSetOffsetForm::ResizeAction(void)
{
	ui->pushButtonSetOffset->resize(width(),height());
}

void	ButtonSetOffsetForm::OperandChanged()
{

}