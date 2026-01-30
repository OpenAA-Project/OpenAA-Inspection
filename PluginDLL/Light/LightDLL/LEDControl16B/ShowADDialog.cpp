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

#include "ShowADDialog.h"
#include "ui_ShowADDialog.h"
#include "LEDControl16B.h"

ShowADDialog::ShowADDialog(LEDControl16BPanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::ShowADDialog)
{
    ui->setupUi(this);
}

ShowADDialog::~ShowADDialog()
{
    delete ui;
}

void ShowADDialog::on_pushButtonClose_clicked()
{
	close();
}

void ShowADDialog::on_pushButtonReqAD_clicked()
{
	int	BoardNumber=ui->comboBoxBoardNumber->currentIndex();
	Panel->LoadADData(BoardNumber);
	ui->listWidgetADValue	->clear();
	for(int i=0;i<16;i++){
		ui->listWidgetADValue->addItem(QString::number(Panel->BoardData[BoardNumber].ADData[i]));
	}
}