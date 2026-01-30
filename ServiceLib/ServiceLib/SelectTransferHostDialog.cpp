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
#include "SelectTransferHostDialog.h"
#include "ui_SelectTransferHostDialog.h"

#include "XGeneralFunc.h"
#include "XTransfer.h"
#include "XDataInLayer.h"

SelectTransferHostDialog::SelectTransferHostDialog(LayersBase *Base, QWidget *parent) :
    QDialog(parent), ServiceForLayers(Base),
    ui(new Ui::SelectTransferHostDialog)
{
    ui->setupUi(this);
	LangLibSolver.SetUI(this);

	int	W=ui->tableWidget->width();
	ui->tableWidget->setColumnWidth(0, W*0.4);
	ui->tableWidget->setColumnWidth(1, W*0.4);
	ui->tableWidget->setColumnWidth(2, W*0.2);

	MixTransferComm *Trans=GetLayersBase()->GetMTransfer();
	RemoteTransferListDimNumb	=Trans->GetRemoteTransferList(List);

	ui->tableWidget->setRowCount(RemoteTransferListDimNumb);
	for(int Row=0;Row<RemoteTransferListDimNumb;Row++){
		::SetDataToTable(ui->tableWidget, 0, Row, List[Row].Name);
		::SetDataToTable(ui->tableWidget, 1, Row, List[Row].IPAddress);
		::SetDataToTable(ui->tableWidget, 2, Row, QString::number(List[Row].Port));
	}
	InstallOperationLog(this);
}

SelectTransferHostDialog::~SelectTransferHostDialog()
{
    delete ui;
}

void SelectTransferHostDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void SelectTransferHostDialog::on_pushButtonSelect_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	Selected	=List[Row];
	done(true);
}

void SelectTransferHostDialog::on_pushButtonCancel_clicked()
{
	done(false);
}