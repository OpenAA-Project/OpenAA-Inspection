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

#include "SetAlignmentLargeHeadLineDialog.h"
#include "ui_SetAlignmentLargeHeadLineDialog.h"

SetAlignmentLargeHeadLineDialog::SetAlignmentLargeHeadLineDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SetAlignmentLargeHeadLineDialog)
{
    ui->setupUi(this);
}

SetAlignmentLargeHeadLineDialog::~SetAlignmentLargeHeadLineDialog()
{
    delete ui;
}

void	SetAlignmentLargeHeadLineDialog::SetInitial(void)
{
    ui->checkBoxUseHeadAlignment    ->setChecked(UseHeadAlignment   );
    ui->spinBoxSkipHeadAlignmentX   ->setValue(SkipHeadAlignmentX   );
    ui->spinBoxMaxHeadAlignmentX    ->setValue(MaxHeadAlignmentX    );
    ui->spinBoxSkipHeadAlignmentY   ->setValue(SkipHeadAlignmentY   );
    ui->spinBoxMaxHeadAlignmentY    ->setValue(MaxHeadAlignmentY    );
    ui->spinBoxHeadAlignmentDifColor->setValue(HeadAlignmentDifColor);
    ui->spinBoxHeadAlignmentMinSize ->setValue(HeadAlignmentMinSize );
    ui->spinBoxHeadAlignmentStep    ->setValue(HeadAlignmentStep    );
}
void SetAlignmentLargeHeadLineDialog::on_pushButtonOK_clicked()
{
    UseHeadAlignment        =ui->checkBoxUseHeadAlignment    ->isChecked();
    SkipHeadAlignmentX      =ui->spinBoxSkipHeadAlignmentX   ->value();
    MaxHeadAlignmentX       =ui->spinBoxMaxHeadAlignmentX    ->value();
    SkipHeadAlignmentY      =ui->spinBoxSkipHeadAlignmentY   ->value();
    MaxHeadAlignmentY       =ui->spinBoxMaxHeadAlignmentY    ->value();
    HeadAlignmentDifColor   =ui->spinBoxHeadAlignmentDifColor->value();
    HeadAlignmentMinSize    =ui->spinBoxHeadAlignmentMinSize ->value();
    HeadAlignmentStep       =ui->spinBoxHeadAlignmentStep    ->value();
    done(true);
}


void SetAlignmentLargeHeadLineDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
