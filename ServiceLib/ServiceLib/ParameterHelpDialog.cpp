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

#include "XTypeDef.h"
#include "ParameterHelpDialog.h"
#include "ui_ParameterHelpDialog.h"
#include "XParameterHelp.h"

ParameterHelpDialog::ParameterHelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParameterHelpDialog)
{
    ui->setupUi(this);
}

ParameterHelpDialog::~ParameterHelpDialog()
{
    delete ui;
}