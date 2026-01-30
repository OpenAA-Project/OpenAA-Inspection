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
#include "MessageBoxStringList.h"
#include "ui_MessageBoxStringList.h"
#include "XDataInLayer.h"


MessageBoxStringList::MessageBoxStringList(LayersBase *lbase ,QStringList &Msg ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(lbase)
    ,ui(new Ui::MessageBoxStringList)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);

    LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangLibSolver.SetUI(this);
    ui->listWidgetMsg->addItems(Msg);
    InstallOperationLog(this);
}

MessageBoxStringList::~MessageBoxStringList()
{
    delete ui;
}

void MessageBoxStringList::closeEvent ( QCloseEvent * event )
{
    QDialog::closeEvent (event);
    deleteLater ();
}

void MessageBoxStringList::on_pushButtonOK_clicked()
{
    close();
}