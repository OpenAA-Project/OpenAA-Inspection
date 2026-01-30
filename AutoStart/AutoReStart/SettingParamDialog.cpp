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

#include "SettingParamDialog.h"
#include "ui_SettingParamDialog.h"
#include "AutoReStart.h"
#include <QFileDialog>

SettingParamDialog::SettingParamDialog(AutoReStart *p ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingParamDialog)
{
    ui->setupUi(this);
    Parent=p;

    ui->lineEditExecuteFileName ->setText(Parent->ParamData.ExeFileName);
    ui->lineEditWorkingPath     ->setText(Parent->ParamData.WorkingPath);
    ui->lineEditParameter       ->setText(Parent->ParamData.Parameter);
    ui->spinBoxWaitingSecond    ->setValue(Parent->ParamData.WaitingSecond);
}

SettingParamDialog::~SettingParamDialog()
{
    delete ui;
}

void SettingParamDialog::on_pushButtonOK_clicked()
{
    Parent->ParamData.ExeFileName   =ui->lineEditExecuteFileName ->text();
    Parent->ParamData.WorkingPath   =ui->lineEditWorkingPath     ->text();
    Parent->ParamData.Parameter     =ui->lineEditParameter       ->text();
    Parent->ParamData.WaitingSecond =ui->spinBoxWaitingSecond    ->value();
    done(true);
}


void SettingParamDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


void SettingParamDialog::on_pushButtonSelectFileName_clicked()
{
    QString ExeFileName=QFileDialog::getOpenFileName(nullptr
                                                    ,"Execute file name with parh"
                                                    , QString()
                                                    , "Exe file(*.exe);;All files(*.*)");
    if(ExeFileName.isEmpty()==false){
        ui->lineEditExecuteFileName->setText(ExeFileName);
    }
}


void SettingParamDialog::on_pushButtonSelectPath_clicked()
{
    QString Path=QFileDialog::getExistingDirectory(nullptr
                                                , "Working pah"
                                                , QString());
    if(Path.isEmpty()==false){
        ui->lineEditWorkingPath->setText(Path);
    }
}
