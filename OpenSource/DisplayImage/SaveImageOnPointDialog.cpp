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
#include "SaveImageOnPointDialog.h"
#include "ui_SaveImageOnPointDialog.h"
#include "XDisplayImage.h"

SaveImageOnPointDialog::SaveImageOnPointDialog(DisplayImage *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base->GetLayersBase())
    ,ui(new Ui::SaveImageOnPointDialog)
    
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);
    InstallOperationLog(this);

    ImageBase=Base;

    ui->spinBoxXDot->setValue(ImageBase->SaveImageSizeXDot);
    ui->spinBoxYDot->setValue(ImageBase->SaveImageSizeYDot);
    ui->comboBoxXCount	->setCurrentIndex(ui->comboBoxXCount->findText(QString::number(ImageBase->SaveImageXCount)));
    ui->comboBoxYCount	->setCurrentIndex(ui->comboBoxYCount->findText(QString::number(ImageBase->SaveImageYCount)));
    if(ImageBase->ImgFormat==/**/"BMP"){
        ui->comboBoxFormat->setCurrentIndex(0);
    }
    else if(ImageBase->ImgFormat==/**/"JPG"){
        ui->comboBoxFormat->setCurrentIndex(1);
    }
    else if(ImageBase->ImgFormat==/**/"PNG"){
        ui->comboBoxFormat->setCurrentIndex(2);
    }
}

SaveImageOnPointDialog::~SaveImageOnPointDialog()
{
    delete ui;
}

void SaveImageOnPointDialog::on_pushButtonOK_clicked()
{
    ImageBase->SaveImageSizeXDot	=ui->spinBoxXDot->value();
    ImageBase->SaveImageSizeYDot	=ui->spinBoxYDot->value();
    ImageBase->SaveImageXCount		=ui->comboBoxXCount	->currentText ().toInt();
    ImageBase->SaveImageYCount		=ui->comboBoxYCount	->currentText ().toInt();
    switch(ui->comboBoxFormat->currentIndex()){
        case 0:	ImageBase->ImgFormat=/**/"BMP";
                break;
        case 1:	ImageBase->ImgFormat=/**/"JPG";
                break;
        case 2:	ImageBase->ImgFormat=/**/"PNG";
                break;
    }
    done(true);
}

void SaveImageOnPointDialog::on_pushButton_2_clicked()
{
    done(false);
}