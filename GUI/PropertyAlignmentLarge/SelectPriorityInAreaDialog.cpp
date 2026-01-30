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

#include "SelectPriorityInAreaDialog.h"
#include "ui_SelectPriorityInAreaDialog.h"

SelectPriorityInAreaDialog::SelectPriorityInAreaDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectPriorityInAreaDialog)
{
    ui->setupUi(this);
}

SelectPriorityInAreaDialog::~SelectPriorityInAreaDialog()
{
    delete ui;
}

void SelectPriorityInAreaDialog::on_pushButtonOK_clicked()
{
	if(ui->radioButtonPriorityHigh->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityHigh;
	}
	else if(ui->radioButtonPriorityMiddle->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityMiddle;
	}
	else if(ui->radioButtonPriorityLow->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityLow;
	}
	else if(ui->radioButtonPriorityLGlobal->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityGlobal;
	}
	done(true);
}


void SelectPriorityInAreaDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
