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
#include "SelectImageFormatForm.h"
#include "ui_SelectImageFormatForm.h"
#include "XDisplayImage.h"

SelectImageFormatForm::SelectImageFormatForm(DisplayImage *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base->GetLayersBase())
    ,ui(new Ui::SelectImageFormatForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);
    InstallOperationLog(this);

    ImageBase=Base;
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

SelectImageFormatForm::~SelectImageFormatForm()
{
    delete ui;
}

void SelectImageFormatForm::on_pushButtonOK_clicked()
{
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

void SelectImageFormatForm::on_pushButtonCancel_clicked()
{
    done(false);
}