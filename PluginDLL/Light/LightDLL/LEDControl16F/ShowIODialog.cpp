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

#include "ShowIODialog.h"
#include "ui_ShowIODialog.h"
#include "LEDControl16F.h"
#include "swap.h"

ShowIODialog::ShowIODialog(LEDControl16FPanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::ShowIODialog)
{
    ui->setupUi(this);

	TM.setInterval(300);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

ShowIODialog::~ShowIODialog()
{
    delete ui;
}

void ShowIODialog::on_pushButton_clicked()
{
    close();
}

void	ShowIODialog::SlotTimeOut()
{
	int	BoardNumber=ui->comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0)
		return;
	Panel->LoadInputData(BoardNumber);
	ui->checkBoxInput1	->setChecked((Panel->BoardData[BoardNumber].InputData[0]!=0)?true:false);
	ui->checkBoxInput2	->setChecked((Panel->BoardData[BoardNumber].InputData[1]!=0)?true:false);
}