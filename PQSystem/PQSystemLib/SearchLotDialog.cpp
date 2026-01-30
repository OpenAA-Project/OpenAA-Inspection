/*
 * Copyright (C) 2022
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

#include "SearchLotDialog.h"
#include "ui_SearchLotDialog.h"
#include "PQSystemService.h"

SearchLotDialog::SearchLotDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::SearchLotDialog)
{
    ui->setupUi(this);

	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	ui->pushButtonTitleLotID	->setText(LBase->GetParamPQSystem()->TitleLotID);
	ui->pushButtonTitleLotNumber->setText(LBase->GetParamPQSystem()->TitleLotNumber);
	ui->pushButtonTitleSubCode	->setText(LBase->GetParamPQSystem()->TitleSubCode);
}

SearchLotDialog::~SearchLotDialog()
{
    delete ui;
}

void SearchLotDialog::on_pushButtonSelect_clicked()
{
	SelectedLotID		=ui->lineEditLotID		->text();
	SelectedLotNumber	=ui->lineEditLotNumber	->text();
	SelectedSubCode	    =ui->lineEditSubCode	->text();

	done(true);
}