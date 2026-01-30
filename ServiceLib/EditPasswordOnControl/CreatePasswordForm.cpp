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
#include "CreatePasswordForm.h"
#include "ui_CreatePasswordForm.h"

CreatePasswordForm::CreatePasswordForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatePasswordForm)
{
    ui->setupUi(this);
}

CreatePasswordForm::~CreatePasswordForm()
{
    delete ui;
}
void	CreatePasswordForm::Initial(const QString &Name)
{
    ui->lineEditPassword->setText(Name);
}
void	CreatePasswordForm::ShowData(void)
{
    ui->lineEditPassword->setText(Password);
}

void CreatePasswordForm::on_pushButtonOK_clicked()
{
    Password=ui->lineEditPassword->text();
    done(true);
}

void CreatePasswordForm::on_pushButtonCancel_clicked()
{
    done(false);
}