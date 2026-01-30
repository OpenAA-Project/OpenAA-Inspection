/*
 * Copyright (C) 2024
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

#include "MakeOutlineItemDialog.h"
#include "ui_MakeOutlineItemDialog.h"
#include "XRememberer.h"

MakeOutlineItemDialog::MakeOutlineItemDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::MakeOutlineItemDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    ui->spinBoxOutlineWidth	->setValue(ControlRememberer::GetInt(ui->spinBoxOutlineWidth));
}

MakeOutlineItemDialog::~MakeOutlineItemDialog()
{
    delete ui;
}

void MakeOutlineItemDialog::on_pushButtonGenerate_clicked()
{
     OutlineWidth=ControlRememberer::SetValue(ui->spinBoxOutlineWidth);
     done(true);
}


void MakeOutlineItemDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
