/*
 * Copyright (C) 2022
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

#include "IntegrationShowNGMapResource.h"
#include "IntegrationShowNGMapButtonForm.h"
#include "ui_IntegrationShowNGMapButtonForm.h"
#include "ShowNGMapDialog.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

IntegrationShowNGMapButtonForm::IntegrationShowNGMapButtonForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationShowNGMapButtonForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SlaveNo=0;
	
	Msg=/**/"NG Map";
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationShowNGMapButtonForm::~IntegrationShowNGMapButtonForm()
{
    delete ui;
}
void	IntegrationShowNGMapButtonForm::Prepare(void)
{
	ui->PushButtonNGMap->setText(Msg);
	ui->PushButtonNGMap->setFont (CFont);
	ResizeAction();
}
void	IntegrationShowNGMapButtonForm::ResizeAction()
{
	ui->PushButtonNGMap->move(0,0);
	ui->PushButtonNGMap->resize(width(),height());
}

void IntegrationShowNGMapButtonForm::on_PushButtonNGMap_clicked()
{
	//if(GetLayersBase()->GetIntegrationBasePointer()->NowOnUsing()==false){
		ShowNGMapDialog	D(GetLayersBase(),this);
		D.exec();
	//}
}