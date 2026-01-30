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
#include "ShrinkItemDialog.h"
#include "ui_ShrinkItemDialog.h"
#include "XDataInLayer.h"
#include "XRememberer.h"

ShrinkItemDialog::ShrinkItemDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::ShrinkItemDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);

    ui->spinBoxExpandRate		->setValue(ControlRememberer::GetInt(ui->spinBoxExpandRate));
	ui->checkBoxMaskForSameLib	->setChecked(ControlRememberer::GetBool(ui->checkBoxMaskForSameLib));
	MaskForSameLib=true;
	ExpandPixels=0;

	Base->InstallOperationLog(this);
}

ShrinkItemDialog::~ShrinkItemDialog()
{
    delete ui;
}

void ShrinkItemDialog::on_pushButtonOK_clicked()
{
	ExpandPixels	=ControlRememberer::SetValue(ui->spinBoxExpandRate);
	MaskForSameLib	=ControlRememberer::SetValue(ui->checkBoxMaskForSameLib);
	done(true);
}

void ShrinkItemDialog::on_pushButtonCancel_clicked()
{
	done(false);
}