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

#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "InputPasswordForm.h"
#include "ui_InputPasswordForm.h"
#include "XGeneralFunc.h"

InputPasswordForm::InputPasswordForm(LayersBase *pbase ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(pbase)
    ,ui(new Ui::InputPasswordForm)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);

    SetWidgetCenter(this);
    ui->lineEditPassword->setFocus();
    InstallOperationLog(this);
}

InputPasswordForm::~InputPasswordForm()
{
    delete ui;
}

void InputPasswordForm::on_pushButtonOK_clicked()
{
    Password=ui->lineEditPassword->text();
    done(true);
}

void InputPasswordForm::on_pushButtonCancel_clicked()
{
    done(false);
}