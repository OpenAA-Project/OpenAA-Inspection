/*
 * Copyright (C) 2017
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

#include "ButtonSwapOutForm.h"
#include "ui_ButtonSwapOutForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XCriticalFunc.h"

ButtonSwapOutForm::ButtonSwapOutForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ButtonSwapOutForm)
{
    ui->setupUi(this);
	Msg			=/**/"Swap out";
	ButtonColor	=Qt::green;
	MasterImage=true;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSwapOutForm::~ButtonSwapOutForm()
{
    delete ui;
}
	
void	ButtonSwapOutForm::Prepare(void)
{
	ui->pushButton->setText(Msg);
	ui->pushButton->setFont (CFont);
	//ui->pushButton->setColor(ButtonColor,ButtonColor);
	ResizeAction();
}
void	ButtonSwapOutForm::ResizeAction()
{
	ui->pushButton->resize(width(),height());
}
void	ButtonSwapOutForm::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	ButtonSwapOutForm::CommandSwapOut(void)
{
	on_pushButton_clicked();
}
void ButtonSwapOutForm::on_pushButton_clicked()
{
	if(MasterImage==true)
		GetLayersBase()->SwapImageOutOfBuffer(ImageBufferMaster);
	else
		GetLayersBase()->SwapImageOutOfBuffer(ImageBufferTarget);
}