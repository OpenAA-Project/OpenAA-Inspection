/*
 * Copyright (C) 2021
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

#include "SettingBarcodeFormDialog.h"
#include "ui_SettingBarcodeFormDialog.h"
#include "swap.h"
#include "XCrossObj.h"
#include "XColorSpace.h"
#include "ButtonSettingBarcodeForm.h"
#include "XGeneralFunc.h"


extern	char *sRoot;
extern	char *sName;


SettingBarcodeFormDialog::SettingBarcodeFormDialog(LayersBase *base, ButtonSettingBarcodeForm *p, QWidget *parent) :
    QDialog(parent),ServiceForLayers(base), Parent(p),
    ui(new Ui::SettingBarcodeFormDialog)
{
    ui->setupUi(this);
}

SettingBarcodeFormDialog::~SettingBarcodeFormDialog()
{
    delete ui;
}

void SettingBarcodeFormDialog::on_tableWidgetItemList_clicked(const QModelIndex &index)
{

}

void SettingBarcodeFormDialog::on_pushButtonAdd_clicked()
{

}

void SettingBarcodeFormDialog::on_pushButtonSub_clicked()
{

}

void SettingBarcodeFormDialog::on_ButtonRelrectOnlyBlock_clicked()
{

}

void SettingBarcodeFormDialog::on_ButtonReflectAllBlocks_clicked()
{

}

void SettingBarcodeFormDialog::on_ButtonClose_clicked()
{

}