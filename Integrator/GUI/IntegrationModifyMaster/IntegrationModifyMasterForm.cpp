/*
 * Copyright (C) 2025
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

#include "IntegrationModifyMasterResource.h"
#include "IntegrationModifyMasterForm.h"
#include "ui_IntegrationModifyMasterForm.h"
#include "PopupMenuForm.h"

IntegrationModifyMasterForm::IntegrationModifyMasterForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationModifyMasterForm)
{
    ui->setupUi(this);
	Msg=/**/"Modify";

    W=NULL;
    connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	IntegrationModifyMasterForm::Prepare(void)
{
	ui->PushButton->setText(Msg);
	ui->PushButton->setFont (CFont);
	ResizeAction();
}

void	IntegrationModifyMasterForm::ResizeAction()
{
	ui->PushButton->setGeometry(0,0,width(),height());
}

IntegrationModifyMasterForm::~IntegrationModifyMasterForm()
{
    delete ui;
    if(W!=NULL){
        W->deleteLater();
    }
}

void IntegrationModifyMasterForm::on_PushButton_clicked()
{
    if(W==NULL){
        W=new PopupMenuForm(GetLayersBase());
    }
    W->show();
}
