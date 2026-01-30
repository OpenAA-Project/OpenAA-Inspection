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

#include "SelectResultAnalizerDialog.h"
#include "ui_SelectResultAnalizerDialog.h"
#include "XGeneralFunc.h"
#include "XResultAnalizer.h"
#include "XDataInLayer.h"

SelectResultAnalizerDialog::SelectResultAnalizerDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::SelectResultAnalizerDialog)
{
    ui->setupUi(this);
	Selected=NULL;
	ui->tableWidgetResultAnalizerItemBase->setColumnWidth(0,48);
	ui->tableWidgetResultAnalizerItemBase->setColumnWidth(1,120);
	ui->tableWidgetResultAnalizerItemBase->setColumnWidth(2,120);

	ShowList();
	InstallOperationLog(this);
}

SelectResultAnalizerDialog::~SelectResultAnalizerDialog()
{
    delete ui;
}

void	SelectResultAnalizerDialog::ShowList(void)
{
	ui->tableWidgetResultAnalizerItemBase->setRowCount(GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetCount());
	int	Row=0;
	for(ResultAnalizerItemBase *a=GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetResultAnalizerItemBase ,0 ,Row ,QString::number(a->GetID()));
		QString	DLLRoot,DLLName;
		a->GetDLL()->GetRootName(DLLRoot,DLLName);
		::SetDataToTable(ui->tableWidgetResultAnalizerItemBase ,1 ,Row ,QString(DLLRoot)+QString(':')+QString(DLLName));
		::SetDataToTable(ui->tableWidgetResultAnalizerItemBase ,2 ,Row ,a->GetName(),Qt::ItemIsEditable);
	}
}
void SelectResultAnalizerDialog::on_tableWidgetResultAnalizerItemBase_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void SelectResultAnalizerDialog::on_pushButtonSelect_clicked()
{
	int	Row=ui->tableWidgetResultAnalizerItemBase->currentRow();
	if(Row<0)
		return;
	Selected=GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetItem(Row);
	done(true);
}

void SelectResultAnalizerDialog::on_pushButtonCancel_clicked()
{
	done(false);
}