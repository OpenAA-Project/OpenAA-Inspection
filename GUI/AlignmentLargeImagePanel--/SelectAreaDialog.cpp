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

#include "SelectAreaDialog.h"
#include "ui_SelectAreaDialog.h"
#include "AlignmentLargeImagePanel.h"
#include "XGeneralFunc.h"
#include "XPacketAlignmentLarge.h"
#include "XAlignmentLarge.h"

SelectAreaDialog::SelectAreaDialog(ListAreaIDInfoContainer &PickedAreasWithPage
								   ,LayersBase *Base
								   ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,Areas(PickedAreasWithPage)
    ,ui(new Ui::SelectAreaDialog)
{
    ui->setupUi(this);

	::SetColumnWidthInTable(ui->tableWidget ,0, 20);
	::SetColumnWidthInTable(ui->tableWidget ,1, 20);
	::SetColumnWidthInTable(ui->tableWidget ,2, 20);
	::SetColumnWidthInTable(ui->tableWidget ,3, 40);

	ui->tableWidget->setRowCount(Areas.GetCount());
	int	Row=0;
	for(ListAreaIDInfo *a=Areas.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget, 0, Row, QString::number(a->GlobalPage));
		::SetDataToTable(ui->tableWidget, 1, Row, QString::number(a->Layer));
		::SetDataToTable(ui->tableWidget, 2, Row, QString::number(a->AreaID));
		switch(a->Priority){
		case XAlignmentLargeArea::_PriorityGlobal:
			::SetDataToTable(ui->tableWidget, 3, Row, QString("Global"));	break;
		case XAlignmentLargeArea::_PriorityHigh:
			::SetDataToTable(ui->tableWidget, 3, Row, QString("High"));		break;
		case XAlignmentLargeArea::_PriorityMiddle:
			::SetDataToTable(ui->tableWidget, 3, Row, QString("Middle"));	break;
		case XAlignmentLargeArea::_PriorityLow:
			::SetDataToTable(ui->tableWidget, 3, Row, QString("Low"));		break;
		case XAlignmentLargeArea::_PriorityNone:
			::SetDataToTable(ui->tableWidget, 3, Row, QString("None"));		break;
		}
	}
}

SelectAreaDialog::~SelectAreaDialog()
{
    delete ui;
}

void SelectAreaDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	on_pushButtonOK_clicked();
}

void SelectAreaDialog::on_pushButtonOK_clicked()
{
	IntList	Rows;
	::GetSelectedRows(ui->tableWidget, Rows);
	for(IntClass *c=Rows.GetFirst();c!=NULL;c=c->GetNext()){
		ListAreaIDInfo	*a=new ListAreaIDInfo();
		*a=*Areas[c->GetValue()];
		SelectedAreas.AppendList(a);
	}
	done(true);
}

void SelectAreaDialog::on_pushButtonCancel_clicked()
{
	done(false);
}