/*
 * Copyright (C) 2024
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

#include "SettingShiftDialog.h"
#include "ui_SettingShiftDialog.h"
#include <QString>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"

SettingShiftDialog::SettingShiftDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::SettingShiftDialog)
{
    ui->setupUi(this);

    ui->tableWidgetPhase->setRowCount(GetPhaseNumb());
    for(int phase=0;phase<GetPhaseNumb();phase++){
        ::SetDataToTable(ui->tableWidgetPhase, 0, phase, QString::number(phase));
        ::SetDataToTable(ui->tableWidgetPhase, 1, phase, GetParamGlobal()->GetPhaseString(phase));
    }
    ui->listWidgetPage->clear();
    for(int page=0;page<GetPageNumb();page++){
        ui->listWidgetPage->addItem(QString::number(page));
    }
    int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
    ui->tableWidgetLayer->setRowCount(LayerNumb);
    for(int layer=0;layer<LayerNumb;layer++){
        ::SetDataToTable(ui->tableWidgetLayer, 0, layer, QString::number(layer));
        ::SetDataToTable(ui->tableWidgetLayer, 1, layer, GetParamGlobal()->GetLayerName(layer));
    }
    setResult(false);
}

SettingShiftDialog::~SettingShiftDialog()
{
    delete ui;
}

void SettingShiftDialog::on_pushButtonExecuteShift_clicked()
{
    ::GetSelectedRows(ui->tableWidgetPhase, SelectedPhase);
    ::GetSelectedRows(ui->listWidgetPage  , SelectedPage);
    ::GetSelectedRows(ui->tableWidgetLayer, SelectedLayers);
    ShiftMaster =ui->checkBoxMasterImage    ->isChecked();
    ShiftTarget =ui->checkBoxTargetImage    ->isChecked();
    ShiftDx     =ui->spinBoxDx  ->value();
    ShiftDy     =ui->spinBoxDy  ->value();
    done(true);
}

void SettingShiftDialog::on_pushButtonCancel_clicked()
{
    done(false);
}