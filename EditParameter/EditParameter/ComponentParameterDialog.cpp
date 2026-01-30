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

#include "ComponentParameterDialog.h"
#include "ui_ComponentParameterDialog.h"
#include "WEditParameterTab.h"
#include "XParamBase.h"

ComponentParameterDialog::ComponentParameterDialog(ParamBase *P,LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,Param(P)
    ,ui(new Ui::ComponentParameterDialog)
{
    ui->setupUi(this);

    int EnableCondition=ParamEnableInTransfer;
    WTabAlgorithm=new WEditParameterTab(Param ,EnableCondition,NULL);

    WTabAlgorithm->setParent(this);
    WTabAlgorithm->setGeometry(0,0,width(),height()-ui->frameBottom->height());
}

ComponentParameterDialog::~ComponentParameterDialog()
{
    delete ui;
}

void ComponentParameterDialog::on_ButtonOK_clicked()
{
    WTabAlgorithm->LoadFromWindow();
    done(true);
}


void ComponentParameterDialog::on_ButtonCancel_clicked()
{
    done(false);
}
