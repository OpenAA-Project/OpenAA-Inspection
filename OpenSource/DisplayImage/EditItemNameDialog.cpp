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
#include "EditItemNameDialog.h"
#include "ui_EditItemNameDialog.h"
#include "XDataInLayer.h"

EditItemNameDialog::EditItemNameDialog(LayersBase *base ,const QString &itemname ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditItemNameDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);

	InstallOperationLog(this);

	ItemName	=itemname;
	ui->lineEditItemName	->setText(ItemName);
}

EditItemNameDialog::~EditItemNameDialog()
{
    delete ui;
}

void EditItemNameDialog::on_pushButtonChange_clicked()
{
	ItemName	=ui->lineEditItemName	->text();
	done(true);
}

void EditItemNameDialog::on_pushButtonClose_clicked()
{
	done(false);
}