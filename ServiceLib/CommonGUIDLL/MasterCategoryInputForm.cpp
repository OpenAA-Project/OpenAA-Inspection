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

#include "CommonGUIDLLResource.h"

#include "MasterCategoryInputForm.h"
#include "ui_MasterCategoryInputForm.h"
#include "XDataInLayer.h"


MasterCategoryInputForm::MasterCategoryInputForm(LayersBase *lbase ,const QString &folderName ,const QString &remark ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(lbase)
    ,ui(new Ui::MasterCategoryInputForm)
    
{
    ui->setupUi(this);
    //LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    //LangLibSolver.SetUI(this);
    FolderName	=folderName;
    Remark		=remark;

    ui->EditFolderName	->setText(FolderName);
    ui->EditRemark		->setText(Remark);
}

MasterCategoryInputForm::~MasterCategoryInputForm()
{
    delete ui;
}

void MasterCategoryInputForm::closeEvent ( QCloseEvent * event )
{
    QDialog::closeEvent (event);
    deleteLater ();
}

void MasterCategoryInputForm::on_ButtonOK_clicked()
{
    FolderName	=ui->EditFolderName->text();
    Remark		=ui->EditRemark->text();
    done((int)true);
}

void MasterCategoryInputForm::on_ButtonCancel_clicked()
{
    done((int)false);
}