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

#include "WindowMismatchForm.h"
#include "ui_WindowMismatchForm.h"
#include "XGeneralFunc.h"

WindowMismatchForm::WindowMismatchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowMismatchForm)
{
    ui->setupUi(this);
    ::SetWidgetCenter(this);
}

WindowMismatchForm::~WindowMismatchForm()
{
    delete ui;
}

void WindowMismatchForm::on_pushButtonOK_clicked()
{
    close();
}
