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

#include "EditMarkMoveDialog.h"
#include "ui_EditMarkMoveDialog.h"
#include "XRobotAction.h"

EditMarkMoveDialog::EditMarkMoveDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditMarkMoveDialog)
{
    ui->setupUi(this);

    Speed=20;
    ui->doubleSpinBox->setValue(Speed);
}

EditMarkMoveDialog::~EditMarkMoveDialog()
{
    delete ui;
}

void    EditMarkMoveDialog::Initial(ActionMarkBase *src)
{
    ActionMarkMove  *a=dynamic_cast<ActionMarkMove *>(src);
    if(a!=NULL){
        Speed=a->Speed;
        ui->doubleSpinBox->setValue(Speed);
    }
}

void EditMarkMoveDialog::on_pushButtonOK_clicked()
{
    Speed=ui->doubleSpinBox->value();
    done(true);
}


void EditMarkMoveDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
