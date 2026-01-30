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

#include "CommDialogForm.h"
#include "ui_CommDialogForm.h"

CommDialogForm::CommDialogForm(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),FormComm(Base)
    ,ui(new Ui::CommDialogForm)
{
    ui->setupUi(this);
    FormComm.setParent(ui->frameFormComm);
    FormComm.move(0,0);
    ui->lineEditFileName->setText(GetLayersBase()->GetParamComm()->GetDefaultFileName());
}

CommDialogForm::~CommDialogForm()
{
    delete ui;
}

void CommDialogForm::on_pushButtonFileName_clicked()
{
    QString	FileName=QFileDialog::getOpenFileName(0
                                   ,/**/"File name for COMM file"
                                   ,QString()
                                   ,"*.dat(*.dat)");
    if(FileName.isEmpty()==false){
        ui->lineEditFileName->setText(FileName);
    }
}

void CommDialogForm::on_pushButtonLoad_clicked()
{
    QString	FileName=ui->lineEditFileName->text();
    if(QFile::exists(FileName)==true){
        GetParamComm()->LoadFromFile(FileName);
        FormComm.Show();
    }
}

void CommDialogForm::on_pushButtonUpdate_clicked()
{
    FormComm.LoadFromWindow();
    QString	FileName=ui->lineEditFileName->text();
    GetParamComm()->SaveToFile(FileName);
}

void CommDialogForm::on_pushButtonSaveNew_clicked()
{
    QString	FileName=QFileDialog::getSaveFileName(0
                                   ,/**/"File name for COMM file"
                                   ,QString()
                                   ,"*.dat(*.dat)");
    if(FileName.isEmpty()==false){
        ui->lineEditFileName->setText(FileName);
        FormComm.LoadFromWindow();
        GetParamComm()->SaveToFile(FileName);
    }
}

void CommDialogForm::on_pushButtonClose_clicked()
{
    close();
}