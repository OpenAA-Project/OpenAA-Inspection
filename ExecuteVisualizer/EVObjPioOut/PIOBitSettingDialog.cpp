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

#include "PIOBitSettingDialog.h"
#include "ui_PIOBitSettingDialog.h"
#include "EVObjPioOut.h"
#include "XDataInLayer.h"
#include "ThreadSequence.h"
#include "XPIOButton.h"

PIOBitSettingDialog::PIOBitSettingDialog(RunnerPIOOut *obj,QWidget *parent) :
    QDialog(parent),
	Obj(obj),
    ui(new Ui::PIOBitSettingDialog)
{
    ui->setupUi(this);
	ui->spinBoxBoardNumber	->setValue(Obj->BoardNumber);
	ui->spinBoxPortNumber	->setValue(Obj->Port);
	ui->comboBoxBitNumber	->setCurrentIndex(Obj->BitNumber);
}

PIOBitSettingDialog::~PIOBitSettingDialog()
{
    delete ui;
}

void PIOBitSettingDialog::on_pushButtonOK_clicked()
{
	Obj->BoardNumber	=ui->spinBoxBoardNumber	->value();
	Obj->Port			=ui->spinBoxPortNumber	->value();
	Obj->BitNumber		=ui->comboBoxBitNumber	->currentIndex();

	done(true);
}

void PIOBitSettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void PIOBitSettingDialog::on_spinBoxBoardNumber_valueChanged(int arg1)
{
	int	V=ui->spinBoxBoardNumber	->value();
	ThreadSequence	*w=Obj->GetLayersBase()->GetSequenceInstance();
	if(w!=NULL){
		PIOClass *s=w->GetFirstPIO();
		//SeqControl	*s=w->GetMainSeqControl();
		if(s!=NULL){
			ui->lineEdit->setText(s->GetBoardName(V));
		}
	}
}