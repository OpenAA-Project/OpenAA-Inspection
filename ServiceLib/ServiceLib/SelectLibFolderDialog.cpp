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

#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "SelectLibFolderDialog.h"
#include "ui_SelectLibFolderDialog.h"
#include "XDataInLayer.h"
#include "LibFolderForm.h"

SelectLibFolderDialog::SelectLibFolderDialog(int LibType ,LayersBase * base,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectLibFolderDialog)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);
    pLibFolderForm=new LibFolderForm(LibType,base,ui->frameLibFolder);
    connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
    base->InstallOperationLog(this);
}

SelectLibFolderDialog::~SelectLibFolderDialog()
{
    delete ui;
}

void SelectLibFolderDialog::closeEvent ( QCloseEvent * event )
{
    QDialog::closeEvent (event);
    deleteLater ();
}

void SelectLibFolderDialog::on_pushButtonSelect_clicked()
{
    done((int)true);
}

void SelectLibFolderDialog::on_pushButtonCancel_clicked()
{
    done((int)false);
}

void	SelectLibFolderDialog::SlotSelectLibFolder(int LibFolderID ,QString FolderName)
{
    SelectedLibFolderID	=LibFolderID;
    SelectedFolderName	=FolderName;
}