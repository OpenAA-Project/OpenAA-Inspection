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

#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "InputSavingFileNameForm.h"
#include "ui_InputSavingFileNameForm.h"
#include "XDisplayImage.h"

InputSavingFileNameForm::InputSavingFileNameForm(LayersBase *Base,const QString &filename,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputSavingFileNameForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);
    Base->InstallOperationLog(this);

    PathFileName=filename;
    ui->lineEditFileName->setText(PathFileName);
}

InputSavingFileNameForm::~InputSavingFileNameForm()
{
    delete ui;
}

void InputSavingFileNameForm::on_pushButtonOK_clicked()
{
    PathFileName=ui->lineEditFileName->text();
    done(true);
}

void InputSavingFileNameForm::on_pushButtonCancel_clicked()
{
    done(false);
}