/*
 * Copyright (C) 2017
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

#include "ConfirmDialog.h"
#include "ui_ConfirmDialog.h"
#include "ButtonOutputToPrinter.h"
#include "XPrinterDLLBaseClass.h"

ConfirmDialog::ConfirmDialog(ButtonOutputToPrinter *p ,PrinterClass *PC ,LayersBase *pbase ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmDialog)
	,ServiceForLayers(pbase)
	,Parent(p)
{
    ui->setupUi(this);

	QStringList StrList;
	PC->GetHandle()->OutputPrinter(StrList);

	QString	Txt;
	for(int i=0;i<StrList.count();i++){
		Txt += StrList[i];
		Txt += QString(/**/"\r\n");
	}
	ui->plainTextEdit->setPlainText(Txt);
}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}

void ConfirmDialog::on_pushButtonClose_clicked()
{
	close();
}