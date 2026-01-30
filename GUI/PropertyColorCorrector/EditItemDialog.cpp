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

#include "EditItemDialog.h"
#include "ui_EditItemDialog.h"
#include "XColorCorrector.h"

EditItemDialog::EditItemDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::EditItemDialog)
{
    ui->setupUi(this);
}

EditItemDialog::~EditItemDialog()
{
    delete ui;
}

    
void    EditItemDialog::SetCurrentItem(const ColorShiftVThreshold *RThr)
{
    ui->spinBoxSearchXDot->setValue(RThr->SearchXDot);
    ui->spinBoxSearchYDot->setValue(RThr->SearchYDot);

    ui->checkBoxLayer0  ->setChecked((RThr->RegularLayer==0)?true:false);
    ui->checkBoxLayer1  ->setChecked((RThr->RegularLayer==1)?true:false);
    ui->checkBoxLayer2  ->setChecked((RThr->RegularLayer==2)?true:false);
}

void    EditItemDialog::GetCurrentItem(ColorShiftVThreshold *WThr)
{
    WThr->SearchXDot    =ui->spinBoxSearchXDot->value();
    WThr->SearchYDot    =ui->spinBoxSearchYDot->value();

    if(ui->checkBoxLayer0->isChecked()==true)
        WThr->RegularLayer=0;
    else
    if(ui->checkBoxLayer1->isChecked()==true)
        WThr->RegularLayer=1;
    else
    if(ui->checkBoxLayer2->isChecked()==true)
        WThr->RegularLayer=2;
}

