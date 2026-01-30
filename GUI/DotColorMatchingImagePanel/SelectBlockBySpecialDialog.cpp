/*
 * Copyright (C) 2026
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

#include "DotColorMatchingImagePanelResource.h"
#include "SelectBlockBySpecialDialog.h"
#include "ui_SelectBlockBySpecialDialog.h"
#include "XTypeDef.h"
#include "XDataInLayer.h"
#include "XRememberer.h"
#include "DotColorMatchingImagePanel.h"

SelectBlockBySpecialDialog::SelectBlockBySpecialDialog(DotColorMatchingImagePanel *p,int libType ,LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,Parent(p)
    ,Libs(libType ,Base)
    ,ui(new Ui::SelectBlockBySpecialDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    LangSolver.SetUI(this);

    Libs.setParent(ui->frameLibrary);
    Libs.move(0,0);
    Libs.resize(ui->frameLibrary->width(),ui->frameLibrary->height());

    Parent->RestoreForm(this);

    Base->InstallOperationLog(this);
}

SelectBlockBySpecialDialog::~SelectBlockBySpecialDialog()
{
    delete ui;
}

void SelectBlockBySpecialDialog::on_ButtonSelect_clicked()
{
    Parent->SaveForm(this);
    OutlineMode=ui->checkBoxOutline->isChecked();
    done(true);
}


void SelectBlockBySpecialDialog::on_ButtonCancel_clicked()
{
    done(false);
}