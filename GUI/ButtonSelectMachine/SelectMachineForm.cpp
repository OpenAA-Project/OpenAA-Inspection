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


#include <QSqlQuery>
#include <QSqlRecord>
#include "SelectMachineForm.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XDatabaseLoader.h"
#include "XOutlineOffset.h"
#include "XFileRegistry.h"
#include "ButtonSelectMachine.h"

SelectMachineForm::SelectMachineForm(LayersBase *Base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LBase=Base;
	Parent=dynamic_cast<ButtonSelectMachine *>(parent);

	//�}�V�[���e�[�u���\��
	MFieldNames << tr(/**/"MACHINEID") << tr(/**/"NAME") << tr(/**/"REMARK");
	ui.twMachineList->setColumnCount(MFieldNames.count());
	ui.twMachineList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.twMachineList->setHorizontalHeaderLabels(MFieldNames);
	ui.twMachineList->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

	//MACHINE�e�[�u���ꗗ�̕\��
	QSqlQuery query(/**/"SELECT MACHINEID,NAME,REMARK from MACHINE order by MACHINEID" ,Base->GetDatabase());
	int Row=0;
	int NumRowsAffected;
	while(query.next()){
		if(Row==0){
			NumRowsAffected=query.numRowsAffected();
			ui.twMachineList->setRowCount(NumRowsAffected);
		}
		if(Row>=NumRowsAffected){
			NumRowsAffected=query.numRowsAffected();
			ui.twMachineList->setRowCount(NumRowsAffected);
		}
		for(int Col=0;Col<ui.twMachineList->columnCount();Col++){
			ui.twMachineList->model()->setData(ui.twMachineList->model()->index(Row,Col),query.value(query.record().indexOf(MFieldNames.at(Col))));
		}
		Row++;
	}

	//�\���ݒ�
	if(ui.twMachineList->rowCount()==0)
		ui.pbOK->setEnabled(false);
	else
		ui.twMachineList->setCurrentIndex(ui.twMachineList->model()->index(0,0));

	//connect
	connect(ui.pbOK,	SIGNAL(clicked()),this,SLOT(pbOKClicked()));
	connect(ui.pbCancel,SIGNAL(clicked()),this,SLOT(pbCancelClicked()));
	InstallOperationLog(this);
}

SelectMachineForm::~SelectMachineForm()
{
}

void SelectMachineForm::pbOKClicked()
{
	int32 MachineID=ui.twMachineList->item(ui.twMachineList->currentIndex().row(),MFieldNames.indexOf(/**/"MACHINEID"))->text().toInt();
	//MACHINE�e�[�u���ꗗ�̕\��
	Parent->SelectMachine(MachineID);

	accept();
}

void SelectMachineForm::pbCancelClicked()
{
	reject();
}