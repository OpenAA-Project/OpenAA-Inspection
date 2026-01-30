/*
 * Copyright (C) 2021
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

#include "ForceRebootSettingDialog.h"
#include "ui_ForceRebootSettingDialog.h"
#include "SettingPartnerDialog.h"
#include <QInputDialog>
#include "XGeneralFunc.h"

ForceRebootSettingDialog::ForceRebootSettingDialog(RebooterParam *param ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForceRebootSettingDialog)
{
    ui->setupUi(this);
	Param	=*param;

	ShowPartnerList();
	ShowPromramList();
	ui->spinBoxOwnPort	->setValue(Param.OwnPortNumber);
}

ForceRebootSettingDialog::~ForceRebootSettingDialog()
{
    delete ui;
}

void ForceRebootSettingDialog::ShowPartnerList(void)
{
	ui->tableWidget->setRowCount(Param.GetCount());
	int	Row=0;
	for(PartnerInfo *a=Param.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui->tableWidget,0,Row,a->HostName);
		::SetDataToTable(ui->tableWidget,1,Row,QString::number(a->PortNumber));
		::SetDataToTable(ui->tableWidget,2,Row,a->Remark);
		Row++;
	}
}

void ForceRebootSettingDialog::ShowPromramList(void)
{
	ui->listWidget->clear();
	ui->listWidget->addItems(Param.RebootedPrograms);
}

void ForceRebootSettingDialog::on_pushButtonAddPartner_clicked()
{
	SettingPartnerDialog	D;
	if(D.exec()==(int)true){
		PartnerInfo	*a=new PartnerInfo();
		*a=D.Info;
		Param.AppendList(a);
		ShowPartnerList();
	}
}

void ForceRebootSettingDialog::on_pushButtonDelPartner_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	PartnerInfo *a=Param.GetItem(Row);
	if(a!=NULL){
		Param.RemoveList(a);
		delete	a;
		ShowPartnerList();
	}
}

void ForceRebootSettingDialog::on_pushButtonAddProgram_clicked()
{
	QString f=QInputDialog::getText ( NULL, "Program", "Program : ", QLineEdit::Normal, QString("InspectionPlayer.exe"));
	if(f.isEmpty()==false){
		Param.RebootedPrograms.append(f);
		ShowPromramList();
	}
}

void ForceRebootSettingDialog::on_pushButtonDelProgram_clicked()
{
	int	Row=ui->listWidget->currentRow();
	if(Row<0)
		return;
	Param.RebootedPrograms.removeAt(Row);
	ShowPromramList();
}

void ForceRebootSettingDialog::on_pushButtonOK_clicked()
{
	Param.OwnPortNumber	=ui->spinBoxOwnPort	->value();
	done(true);
}

void ForceRebootSettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void ForceRebootSettingDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	PartnerInfo *a=Param.GetItem(Row);
	if(a!=NULL){
		SettingPartnerDialog	D;
		D.Info=*a;
		D.Init();
		if(D.exec()==(int)true){
			*a=D.Info;
			ShowPartnerList();
		}
	}
}

void ForceRebootSettingDialog::on_listWidget_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->listWidget->currentRow();
	if(Row<0)
		return;
	QString f=QInputDialog::getText ( NULL, "Program", "Program : ", QLineEdit::Normal, Param.RebootedPrograms[Row]);
	if(f.isEmpty()==false){
		Param.RebootedPrograms[Row]=f;
		ShowPromramList();
	}
}