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

#include "AddItemDialogResource.h"
#include "AddItemDialog.h"
#include "ui_AddItemDialog.h"

AddItemDialog::AddItemDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}

void	AddItemDialog::Reflect(void)
{
	ui->lineEditItemName->setText(ItemName);
	if(Condition	==CheckBrightnessItem::_AverageMustBeInside)
		ui->comboBoxCondition->setCurrentIndex(0);
	else if(Condition	==CheckBrightnessItem::_AllMustBeInside)
		ui->comboBoxCondition->setCurrentIndex(1);
	else if(Condition	==CheckBrightnessItem::_OneMustBeInsideAtLeast)
		ui->comboBoxCondition->setCurrentIndex(2);
	else if(Condition	==CheckBrightnessItem::_AverageMustBeOutside)
		ui->comboBoxCondition->setCurrentIndex(3);
	else if(Condition	==CheckBrightnessItem::_AllMustBeOutside)
		ui->comboBoxCondition->setCurrentIndex(4);
	else if(Condition	==CheckBrightnessItem::_OneMustBeOutsideAtLeast)
		ui->comboBoxCondition->setCurrentIndex(5);

	ui->spinBoxThreshL	->setValue(ThreshL);
	ui->spinBoxThreshH	->setValue(ThreshH);
	ui->spinBoxRegNumber->setValue(RegNumber);
	ui->spinBoxRepeatableCount	->setValue(RepeatableCount);
}

void AddItemDialog::on_pushButtonOK_clicked()
{
	ItemName	=ui->lineEditItemName->text();
	if(ui->comboBoxCondition->currentIndex()==0)
		Condition	=CheckBrightnessItem::_AverageMustBeInside;
	else if(ui->comboBoxCondition->currentIndex()==1)
		Condition	=CheckBrightnessItem::_AllMustBeInside;
	else if(ui->comboBoxCondition->currentIndex()==2)
		Condition	=CheckBrightnessItem::_OneMustBeInsideAtLeast;
	else if(ui->comboBoxCondition->currentIndex()==3)
		Condition	=CheckBrightnessItem::_AverageMustBeOutside;
	else if(ui->comboBoxCondition->currentIndex()==4)
		Condition	=CheckBrightnessItem::_AllMustBeOutside;
	else if(ui->comboBoxCondition->currentIndex()==5)
		Condition	=CheckBrightnessItem::_OneMustBeOutsideAtLeast;
	ThreshL	=ui->spinBoxThreshL->value();
	ThreshH	=ui->spinBoxThreshH->value();
	RegNumber		=ui->spinBoxRegNumber		->value();
	RepeatableCount	=ui->spinBoxRepeatableCount	->value();
	done(true);
}

void AddItemDialog::on_pushButtonCancel_clicked()
{
	done(false);
}