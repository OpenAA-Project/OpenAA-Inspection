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

#include "RWRobotRunForm.h"
#include "ui_RWRobotRunForm.h"

RWRobotRunForm::RWRobotRunForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::RWRobotRunForm)
{
    ui->setupUi(this);
}

RWRobotRunForm::~RWRobotRunForm()
{
    delete ui;
}

void RWRobotRunForm::on_toolButtonExecute_clicked()
{

}


void RWRobotRunForm::on_toolButtonOrigin_clicked()
{

}
