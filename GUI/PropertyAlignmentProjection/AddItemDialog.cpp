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

#include "AddItemDialog.h"
#include "ui_AddItemDialog.h"

AddItemDialog::AddItemDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
	PeakCount		=2;
	Angle			=90;
	PeakIsolation	=30;
	UsageLayer		=0;
	AbandonRateL	=0.1;
	AbandonRateH	=0.2;
	InstallOperationLog(this);
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}
void	AddItemDialog::SetInitial(QString &ItemName,int PeakCount,double Angle,int PeakIsolation ,int UsageLayer,double AbandonRateL ,double AbandonRateH)
{
	ui->lineEditItemName			->setText (ItemName		);
	ui->spinBoxPeakCount			->setValue(PeakCount	);
	ui->doubleSpinBoxAngle			->setValue(Angle		);
	ui->doubleSpinBoxPeakIsolation	->setValue(PeakIsolation		);
	ui->spinBoxUsageLayer			->setValue(UsageLayer	);
	ui->doubleSpinBoxAbandonRateL	->setValue(AbandonRateL	);
	ui->doubleSpinBoxAbandonRateH	->setValue(AbandonRateH	);
}

void AddItemDialog::on_pushButtonOK_clicked()
{
	ItemName		=ui->lineEditItemName			->text();
	PeakCount		=ui->spinBoxPeakCount			->value();
	Angle			=ui->doubleSpinBoxAngle			->value();
	PeakIsolation	=ui->doubleSpinBoxPeakIsolation	->value();
	UsageLayer		=ui->spinBoxUsageLayer			->value();
	AbandonRateL	=ui->doubleSpinBoxAbandonRateL	->value();
	AbandonRateH	=ui->doubleSpinBoxAbandonRateH	->value();

	done(true);
}

void AddItemDialog::on_pushButtonCancel_clicked()
{
	done(false);
}