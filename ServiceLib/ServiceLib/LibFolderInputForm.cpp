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

#include "XTypeDef.h"
#include "LibFolderInputForm.h"
#include "ui_LibFolderInputForm.h"
#include "XDataInLayer.h"

LibFolderInputForm::LibFolderInputForm(LayersBase *lbase ,const QString &folderName ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LibFolderInputForm)
{
    ui->setupUi(this);

    //LangDISolver.SetLanguage(lbase->GetLanguagePackageData(),lbase->GetLanguageCode());
    //LangDISolver.SetUI(this);
    lbase->InstallOperationLog(this);

    FolderName	=folderName;

    ui->EditFolderName	->setText(FolderName);}

LibFolderInputForm::~LibFolderInputForm()
{
    delete ui;
}

void LibFolderInputForm::on_ButtonOK_clicked()
{
    FolderName	=ui->EditFolderName->text();
    done((int)true);
}

void LibFolderInputForm::on_ButtonCancel_clicked()
{
    done((int)false);
}