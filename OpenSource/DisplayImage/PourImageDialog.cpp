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
#include "PourImageDialog.h"
#include "ui_PourImageDialog.h"
#include "XRememberer.h"
#include "XDataInLayer.h"

PourImageDialog::PourImageDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::PourImageDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);

    ui->spinBoxPickup	->setValue(ControlRememberer::GetInt(ui->spinBoxPickup));
    ui->spinBoxExpand	->setValue(ControlRememberer::GetInt(ui->spinBoxExpand));
}

PourImageDialog::~PourImageDialog()
{
    delete ui;
}

void PourImageDialog::on_pushButtonGo_clicked()
{
    PickupBrightness    =ControlRememberer::SetValue(ui->spinBoxPickup);
    ExpandedDot         =ControlRememberer::SetValue(ui->spinBoxExpand);
    done(true);
}


void PourImageDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
