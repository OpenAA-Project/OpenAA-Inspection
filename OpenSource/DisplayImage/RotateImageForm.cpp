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
#include "RotateImageForm.h"
#include "ui_RotateImageForm.h"
#include "XGeneralDialog.h"
#include "XDataInLayer.h"
#include "XRememberer.h"

RotateImageForm::RotateImageForm(LayersBase *Base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::RotateImageForm)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
	LangDISolver.SetUI(this);
	Base->InstallOperationLog(this);

	RetMode=false;

	ui->checkBoxMaster		->setEnabled(GetParamGlobal()->AllocateMasterBuff);
	ui->checkBoxTarget		->setEnabled(GetParamGlobal()->AllocateTargetBuff);

	ui->checkBoxMaster		->setChecked(ControlRememberer::GetBool(ui->checkBoxMaster));
	ui->checkBoxTarget		->setChecked(ControlRememberer::GetBool(ui->checkBoxTarget));
	ui->doubleSpinBoxAngle	->setValue	(ControlRememberer::GetDouble(ui->doubleSpinBoxAngle));
}

RotateImageForm::~RotateImageForm()
{
    delete ui;
}

void RotateImageForm::on_pushButtonGo_clicked()
{
	Angle		=ControlRememberer::SetValue(ui->doubleSpinBoxAngle);
	FlagMaster	=ControlRememberer::SetValue(ui->checkBoxMaster);
	FlagTarget	=ControlRememberer::SetValue(ui->checkBoxTarget);

	RetMode=true;
	done(true);
}

void RotateImageForm::on_pushButtonCancel_clicked()
{
	RetMode=false;
	done(false);
}