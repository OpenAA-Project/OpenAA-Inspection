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

#include "ButtonSwapInForm.h"
#include "ui_ButtonSwapInForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XCriticalFunc.h"

ButtonSwapInForm::ButtonSwapInForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ButtonSwapInForm)
{
    ui->setupUi(this);
    Msg			=/**/"Swap in";
	ButtonColor	=Qt::green;
	MasterImage=true;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSwapInForm::~ButtonSwapInForm()
{
    delete ui;
}
	
void	ButtonSwapInForm::Prepare(void)
{
	ui->pushButton->setText(Msg);
	ui->pushButton->setFont (CFont);
	//ui->pushButton->setColor(ButtonColor,ButtonColor);
	ResizeAction();
}
void	ButtonSwapInForm::ResizeAction()
{
	ui->pushButton->resize(width(),height());
}
void	ButtonSwapInForm::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	ButtonSwapInForm::CommandSwapIn(void)
{
	on_pushButton_clicked();
}
void ButtonSwapInForm::on_pushButton_clicked()
{
	if(MasterImage==true)
		GetLayersBase()->SwapImageInToBuffer(ImageBufferMaster);
	else
		GetLayersBase()->SwapImageInToBuffer(ImageBufferTarget);
}