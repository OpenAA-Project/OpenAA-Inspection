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
#include "EditTransferHostDialog.h"
#include "ui_EditTransferHostDialog.h"
#include "XGeneralFunc.h"
#include "XParamGlobal.h"


EditTransferHostDialog::EditTransferHostDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::EditTransferHostDialog)
{
    ui->setupUi(this);

    ui->tableWidgetTransfer->setColumnWidth(0,240);
    ui->tableWidgetTransfer->setColumnWidth(1,240);
	ui->tableWidgetTransfer->setColumnWidth(2,70);

	ShowTransfer();
}

EditTransferHostDialog::~EditTransferHostDialog()
{
    delete ui;
}
void EditTransferHostDialog::ShowTransfer(void)
{
	int	N=GetParamGlobal()->GetRemoteTransferCount();
	ui->tableWidgetTransfer->setRowCount(N);
	for(int Row=0;Row<N;Row++){
		RemoteTransferList	*L=GetParamGlobal()->GetRemoteTransfer(Row);
		::SetDataToTable(ui->tableWidgetTransfer, 0, Row, L->Name					,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetTransfer, 1, Row, L->IPAddress				,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetTransfer, 2, Row, QString::number(L->Port)	,Qt::ItemIsEditable);
	}
}

void	EditTransferHostDialog::GetTransferFromWindow(void)
{
	int	N=ui->tableWidgetTransfer->rowCount();
	for(int Row=0;Row<N;Row++){
		RemoteTransferList	*L=GetParamGlobal()->GetRemoteTransfer(Row);
		if(L!=NULL){
			L->Name		=::GetDataToTable(ui->tableWidgetTransfer, 0, Row);
			L->IPAddress=::GetDataToTable(ui->tableWidgetTransfer, 1, Row);
			L->Port		=::GetDataToTable(ui->tableWidgetTransfer, 2, Row).toInt();
		}
	}
}

void EditTransferHostDialog::on_pushButtonTransferPlus_clicked()
{
	RemoteTransferList n;
	GetParamGlobal()->AddRemoteTransfer(n);
	ShowTransfer();
}

void EditTransferHostDialog::on_pushButtonTransferMinus_clicked()
{
	int	Row=ui->tableWidgetTransfer->currentRow();
	if(Row<0)
		return;
	GetParamGlobal()->RemoveRemoteTransfer(Row);
	ShowTransfer();
}

void EditTransferHostDialog::on_pushButtonOverWriteFileTransfer_clicked()
{
	GetTransferFromWindow();
	done(true);
}