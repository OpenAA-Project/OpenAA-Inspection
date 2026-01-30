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

#include "ObjectListForm.h"
#include "ui_ObjectListForm.h"
#include "EditRegulusWorld.h"

ObjectListForm::ObjectListForm(EditRegulusWorld *p,QWidget *parent) :
    QWidget(parent)
    ,Parent(p)
    ,ui(new Ui::ObjectListForm)
{
    ui->setupUi(this);

    Splitter= new QSplitter(this);
    Splitter->setOrientation(Qt::Vertical);
    Splitter->addWidget(ui->treeWidget);
    Splitter->addWidget(ui->tableWidgetProperty);
}

ObjectListForm::~ObjectListForm()
{
    delete ui;
}

void ObjectListForm::resizeEvent(QResizeEvent *event)
{
    Splitter->setGeometry(0,0,width(),height());
}