/*
 * Copyright (C) 2024
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

#include "MasterLotListForm.h"
#include "ui_MasterLotListForm.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"

MasterLotListForm::MasterLotListForm(LayersBase *base ,const QString &root ,const QString &name
						 ,QWidget *parent) :
    PQSystemRunner(base ,root ,name,parent),
    ui(new Ui::MasterLotListForm)
{
    ui->setupUi(this);
	ui->dateTimeEditStart	->setDateTime(QDateTime::currentDateTime());
	ui->dateTimeEditEnd		->setDateTime(QDateTime::currentDateTime());
}

MasterLotListForm::~MasterLotListForm()
{
    delete ui;
}
bool	MasterLotListForm::Initial(void)
{
	return true;
}
const QString	MasterLotListForm::GetPath(void)
{
	return "設定時系列表示/マスター、ロットのリスト表示";
}
void MasterLotListForm::showEvent(QShowEvent *event)
{
}
void MasterLotListForm::on_pushButtonStartSearch_clicked()
{

}

void MasterLotListForm::on_pushButtonView_clicked()
{

}

void MasterLotListForm::on_pushButtonExcel_clicked()
{

}