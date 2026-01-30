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


#include "VeisionInfoForm.h"
#include "ui_VeisionInfoForm.h"
#include "XDataInLayer.h"
#include "Regulus64Version.h"


VeisionInfoForm::VeisionInfoForm(LayersBase *lbase ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(lbase)
    ,ui(new Ui::VeisionInfoForm)   
{
    ui->setupUi(this);
    //LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    //LangLibSolver.SetUI(this);
    //ui->labelDate->setText(VersionDate);
    ui->labelRevision->setText(RegulusVersionRevision);
}

VeisionInfoForm::~VeisionInfoForm()
{
    delete ui;
}

void VeisionInfoForm::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

void VeisionInfoForm::on_pushButton_clicked()
{
    emit	SignalClose();
}