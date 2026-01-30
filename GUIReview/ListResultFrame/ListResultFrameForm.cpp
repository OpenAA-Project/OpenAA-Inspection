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

#include "ListResultFrameForm.h"
#include "ui_ListResultFrameForm.h"

ListResultFrameForm::ListResultFrameForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ListResultFrameForm)
{
    ui->setupUi(this);
}

ListResultFrameForm::~ListResultFrameForm()
{
    delete ui;
}


void	ListResultFrameForm::Prepare(void)
{
	ResizeAction();
}

void	ListResultFrameForm::ResizeAction()
{
	ui->tableWidget->resize(width(),height());
}