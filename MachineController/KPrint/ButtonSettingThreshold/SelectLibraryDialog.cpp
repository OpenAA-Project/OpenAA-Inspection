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

#include "ButtonSettingThresholdResource.h"
#include "SelectLibraryDialog.h"
#include "ui_SelectLibraryDialog.h"
#include <QString>

SelectLibraryDialog::SelectLibraryDialog(LayersBase *base, ButtonSettingThresholdForm *p, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,Parent(p),
    ui(new Ui::SelectLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	Selected=NULL;

	::SetColumnWidthInTable(ui->tableWidget,0, 15);
	::SetColumnWidthInTable(ui->tableWidget,1, 75);
}

SelectLibraryDialog::~SelectLibraryDialog()
{
    delete ui;
}
void	SelectLibraryDialog::Initial(AlgorithmLibraryListContainer &src)
{
	List=src;
	ui->tableWidget->setRowCount(List.GetCount());
	int	row=0;
	for(AlgorithmLibraryList *a=List.GetFirst();a!=NULL;a=a->GetNext(),row++){
		//QString	LibTypeName=GetLayersBase()->GetLibTypeName(a->GetLibType());
		//::SetDataToTable(ui->tableWidget, 0, row, LibTypeName);
		::SetDataToTable(ui->tableWidget, 0, row, QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidget, 1, row, a->GetLibName());
	}
}

void SelectLibraryDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	on_toolButtonSelect_clicked();
}

void SelectLibraryDialog::on_toolButtonCancel_clicked()
{
	done(false);
}

void SelectLibraryDialog::on_toolButtonSelect_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	Selected=List.GetItem(Row);
	if(Selected!=NULL){
		done(true);
	}
}