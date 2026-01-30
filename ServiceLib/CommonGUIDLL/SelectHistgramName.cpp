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
#include "SelectHistgramName.h"
#include "ui_SelectHistgramName.h"
#include <QStringList>

SelectHistgramName::SelectHistgramName(AlgorithmBase *abase ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectHistgramName)
{
    ui->setupUi(this);

	ABase=abase ;

	QStringList HistNames;
	ABase->EnumHistgram(HistNames);
	ui->listWidgetHistName->addItems(HistNames);
	HistgramID=-1;

	abase->GetLayersBase()->InstallOperationLog(this);
}

SelectHistgramName::~SelectHistgramName()
{
    delete ui;
}

void SelectHistgramName::on_pushButtonSelect_clicked()
{
	int	Row=ui->listWidgetHistName->currentRow();
	if(Row<0)
		return;
	HistgramID=ABase->GetHistgramID(Row);
}

void SelectHistgramName::on_listWidgetHistName_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}