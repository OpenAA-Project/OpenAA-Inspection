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

#include "RWShowObjectPropertyForm.h"
#include "ui_RWShowObjectPropertyForm.h"

RWShowObjectPropertyForm::RWShowObjectPropertyForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent)
    ,ui(new Ui::RWShowObjectPropertyForm)
{
    ui->setupUi(this);
}

RWShowObjectPropertyForm::~RWShowObjectPropertyForm()
{
    delete ui;
}

void RWShowObjectPropertyForm::resizeEvent(QResizeEvent *event)
{
    ui->treeWidgetObject->resize(width(),ui->treeWidgetObject->height());
    ui->tableWidgetProperty->resize(width(),height()-ui->tableWidgetProperty->geometry().top());
}