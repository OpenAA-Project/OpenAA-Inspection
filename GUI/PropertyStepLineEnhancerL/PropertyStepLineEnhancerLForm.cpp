/*
 * Copyright (C) 2016
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

#include "PropertyStepLineEnhancerLForm.h"
#include "ui_PropertyStepLineEnhancerLForm.h"

PropertyStepLineEnhancerLForm::PropertyStepLineEnhancerLForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropertyStepLineEnhancerLForm)
{
    ui->setupUi(this);
}

PropertyStepLineEnhancerLForm::~PropertyStepLineEnhancerLForm()
{
    delete ui;
}

void PropertyStepLineEnhancerLForm::on_pushButtonEditLibFolder_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_tableWidgetLibList_clicked(const QModelIndex &index)
{

}

void PropertyStepLineEnhancerLForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{

}

void PropertyStepLineEnhancerLForm::on_ButtonPickupTest_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_ButtonPickupClearTest_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index)
{

}

void PropertyStepLineEnhancerLForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{

}

void PropertyStepLineEnhancerLForm::on_pushButtonSetFrom_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_pushButtonGetBack_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_pushButtonSetFromAll_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_pushButtonGetBackAll_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_pushButtonEditLibrary_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_ButtonGenerateLibs_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_radioButtonPickupArea_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_radioButtonBlock_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_radioButtonCalc_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_radioButtonMatching_clicked()
{

}

void PropertyStepLineEnhancerLForm::on_ButtonLibSave_clicked()
{

}