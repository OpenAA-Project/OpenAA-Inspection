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

#include "TestFluorescentFlat.h"
#include <QString>
#include <QTableWidget>

TestFluorescentFlat::TestFluorescentFlat(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	for(int sheet=0;sheet<SheetCountInSystem;sheet++){
		ui.tableWidget->setColumnWidth(sheet,32);
	}
	ToWindow();
	SystemData.Initial();
}

TestFluorescentFlat::~TestFluorescentFlat()
{

}

QString	GetDataToTable(QTableWidget *W ,int col ,int row)
{
	return(W->model()->data(W->model()->index(row,col)).toString());
}

void	SetDataToTable(QTableWidget *W ,int col ,int row ,const QVariant &value)
{
	W->model()->setData(W->model()->index(row,col),value);
}

void TestFluorescentFlat::FromWindow(void)
{
	for(int sheet=0;sheet<SheetCountInSystem;sheet++){
		for(int LED=0;LED<LEDCountInSheet;LED++){
			QString	s=GetDataToTable(ui.tableWidget ,sheet,LED);
			bool	ok;
			int	d=s.toInt(&ok);
			if(ok==true){
				SystemData.Sheet[sheet].Data[LED]=d;
			}
		}
	}
}
void	TestFluorescentFlat::ToWindow(void)
{
	for(int sheet=0;sheet<SheetCountInSystem;sheet++){
		for(int LED=0;LED<LEDCountInSheet;LED++){
			QString	d=QString::number(SystemData.Sheet[sheet].Data[LED]);
			SetDataToTable(ui.tableWidget ,sheet,LED,d);
		}
	}
}

void TestFluorescentFlat::on_pushButtonSetAll_clicked()
{
	SystemData.SetAll(ui.spinBoxSetAll->value());
	ToWindow();
}

void TestFluorescentFlat::on_pushButtonOK_clicked()
{
	FromWindow();
	SystemData.Transfer();
}

void TestFluorescentFlat::on_toolButtonOnOff_clicked()
{
	if(ui.toolButtonOnOff->isChecked()==true)
		SystemData.SetOn(true);
	else
		SystemData.SetOn(false);
}