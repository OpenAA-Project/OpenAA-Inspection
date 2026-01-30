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

#include "SettingDustReducerDialog.h"
#include "ui_SettingDustReducerDialog.h"
#include "DustReducer.h"
#include "XGeneralFunc.h"

SettingDustReducerDialog::SettingDustReducerDialog(LayersBase *base ,DustReducer *P,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,Parent(P)
    ,ui(new Ui::SettingDustReducerDialog)
{
    ui->setupUi(this);

	ui->spinBoxVLayer		->setValue(P->VLayer);
	ui->spinBoxBrightnessL	->setValue(P->BrightnessL	);
	ui->spinBoxBrightnessH	->setValue(P->BrightnessH	);
	ui->spinBoxMaxAreaDots	->setValue(P->MaxAreaDots	);
	ui->spinBoxMaxLength	->setValue(P->MaxLength		);
	ui->doubleSpinBoxMaxV	->setValue(P->MaxV			);

	ui->tableWidgetResult->setColumnWidth(0,48);
	ui->tableWidgetResult->setColumnWidth(1,48);
	ui->tableWidgetResult->setColumnWidth(2,48);
	ui->tableWidgetResult->setColumnWidth(3,48);
	ui->tableWidgetResult->setColumnWidth(4,48);
	ui->tableWidgetResult->setColumnWidth(5,60);
	ui->tableWidgetResult->setColumnWidth(6,60);
	ui->tableWidgetResult->setColumnWidth(7,60);
}

SettingDustReducerDialog::~SettingDustReducerDialog()
{
    delete ui;
}

void SettingDustReducerDialog::on_pushButtonOK_clicked()
{
	Parent->VLayer		=ui->spinBoxVLayer		->value();
	Parent->BrightnessL	=ui->spinBoxBrightnessL	->value();
	Parent->BrightnessH	=ui->spinBoxBrightnessH	->value();
	Parent->MaxAreaDots	=ui->spinBoxMaxAreaDots	->value();
	Parent->MaxLength	=ui->spinBoxMaxLength	->value();
	Parent->MaxV		=ui->doubleSpinBoxMaxV	->value();
	done(true);
}

void SettingDustReducerDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingDustReducerDialog::on_pushButtonUpdateResult_clicked()
{
	ui->tableWidgetResult->setRowCount(Parent->WPoint);
	for(int row=0;row<Parent->WPoint;row++){
		QColor	Col;
		if(Parent->Dim[row].Dust==true)
			Col=Qt::yellow;
		else
			Col=Qt::white;
	
		::SetTableColor(ui->tableWidgetResult,0,row ,Col);
		::SetTableColor(ui->tableWidgetResult,1,row ,Col);
		::SetTableColor(ui->tableWidgetResult,2,row ,Col);
		::SetTableColor(ui->tableWidgetResult,3,row ,Col);
		::SetTableColor(ui->tableWidgetResult,4,row ,Col);
		::SetTableColor(ui->tableWidgetResult,5,row ,Col);
		::SetTableColor(ui->tableWidgetResult,6,row ,Col);
		::SetTableColor(ui->tableWidgetResult,7,row ,Col);

		::SetDataToTable(ui->tableWidgetResult,0,row ,QString::number(Parent->Dim[row].Phase));
		::SetDataToTable(ui->tableWidgetResult,1,row ,QString::number(Parent->Dim[row].Page));
		::SetDataToTable(ui->tableWidgetResult,2,row ,QString::number(Parent->Dim[row].Layer));
		::SetDataToTable(ui->tableWidgetResult,3,row ,QString::number(Parent->Dim[row].ItemID));
		::SetDataToTable(ui->tableWidgetResult,4,row ,QString::number(Parent->Dim[row].PosNo));
		::SetDataToTable(ui->tableWidgetResult,5,row ,QString::number(Parent->Dim[row].Dots));
		::SetDataToTable(ui->tableWidgetResult,6,row ,QString::number(Parent->Dim[row].Length));
		::SetDataToTable(ui->tableWidgetResult,7,row ,QString::number(Parent->Dim[row].S,'f',3));
	}
		
}