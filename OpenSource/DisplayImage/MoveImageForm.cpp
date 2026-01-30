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
#include "MoveImageForm.h"
#include "ui_MoveImageForm.h"
#include "XGeneralDialog.h"
#include "XDataInLayer.h"
#include "XRememberer.h"

MoveImageForm::MoveImageForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::MoveImageForm)
    
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);
    InstallOperationLog(this);

    RetMode=false;

	ui->checkBoxMaster		->setEnabled(GetParamGlobal()->AllocateMasterBuff);
	ui->checkBoxTarget		->setEnabled(GetParamGlobal()->AllocateTargetBuff);

    ui->checkBoxMaster	->setChecked(ControlRememberer::GetBool(ui->checkBoxMaster));
    ui->checkBoxTarget	->setChecked(ControlRememberer::GetBool(ui->checkBoxTarget));
    ui->spinBoxXDir		->setValue(ControlRememberer::GetInt(ui->spinBoxXDir));
    ui->spinBoxYDir		->setValue(ControlRememberer::GetInt(ui->spinBoxYDir));
}

MoveImageForm::~MoveImageForm()
{
    delete ui;
}

void MoveImageForm::on_pushButtonGo_clicked()
{
    XDir=ControlRememberer::SetValue(ui->spinBoxXDir);
    YDir=ControlRememberer::SetValue(ui->spinBoxYDir);
    FlagMaster=ControlRememberer::SetValue(ui->checkBoxMaster);
    FlagTarget=ControlRememberer::SetValue(ui->checkBoxTarget);

    RetMode=true;
    emit	SignalClose();
}

void MoveImageForm::on_pushButtonCancel_clicked()
{
    RetMode=false;
    emit	SignalClose();
}