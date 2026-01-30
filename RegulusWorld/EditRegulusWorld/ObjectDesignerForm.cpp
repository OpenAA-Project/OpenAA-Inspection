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

#include "ObjectDesignerForm.h"
#include "ui_ObjectDesignerForm.h"
#include "EditRegulusWorld.h"

ObjectDesignerForm::ObjectDesignerForm(EditRegulusWorld *p,QWidget *parent) :
    QWidget(parent)
    ,Parent(p)
    ,ui(new Ui::ObjectDesignerForm)
{
    ui->setupUi(this);
}

ObjectDesignerForm::~ObjectDesignerForm()
{
    delete ui;
}

void ObjectDesignerForm::resizeEvent(QResizeEvent *event)
{
}