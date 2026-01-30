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

#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectByLibraryDialog.h"
#include "ui_SelectByLibraryDialog.h"
#include "XDataInLayer.h"
#include "XRememberer.h"

SelectByLibraryDialog::SelectByLibraryDialog(int libType ,LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,Libs(libType ,Base)
    ,ui(new Ui::SelectByLibraryDialog)
    
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);
    Libs.setParent(ui->frameLibrary);
    Libs.move(0,0);
    Libs.resize(ui->frameLibrary->width(),ui->frameLibrary->height());

    RestoreForm(this);

    Base->InstallOperationLog(this);
}

SelectByLibraryDialog::~SelectByLibraryDialog()
{
    delete ui;
}

void SelectByLibraryDialog::on_ButtonSelect_clicked()
{
    SaveForm(this);
    done(true);
}

void SelectByLibraryDialog::on_ButtonCancel_clicked()
{
    done(false);
}