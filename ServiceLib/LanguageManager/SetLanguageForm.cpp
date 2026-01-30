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

#include "SetLanguageForm.h"
#include "ui_SetLanguageForm.h"
#include "XLanguageManager.h"
#include "SetLanguageDetailForm.h"
#include "XGeneralFunc.h"
#include <QMessageBox>

SetLanguageForm::SetLanguageForm(LanguagePack &Lng, QWidget *parent) :
    QDialog(parent)
	,LangPack(Lng)
    ,ui(new Ui::SetLanguageForm)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,40);
	ui->tableWidget->setColumnWidth(1,150);
	ui->tableWidget->setColumnWidth(2,150);
	ui->tableWidget->setColumnWidth(3,150);

	ShowList();
}

SetLanguageForm::~SetLanguageForm()
{
    delete ui;
}

void SetLanguageForm::ShowList(void)
{
	ui->tableWidget->setRowCount(LangPack.GetCount());
	int	Row=0;
	for(LanguageClass *a=LangPack.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui->tableWidget,0,Row,QString::number(a->ColumnNo));
		::SetDataToTable(ui->tableWidget,1,Row,a->LanguageName);
		::SetDataToTable(ui->tableWidget,2,Row,a->ExcelFont);
		::SetDataToTable(ui->tableWidget,3,Row,a->QtCotec);
		Row++;
	}
}

void SetLanguageForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	LanguageClass *a=LangPack.GetItem(Row);
	SetLanguageDetailForm	D(a);
	int	ret=D.exec();
	if((bool)ret==true){
		ShowList();
	}
}

void SetLanguageForm::on_pushButtonInsertNew_clicked()
{
	LanguageClass	*a=new LanguageClass();
	SetLanguageDetailForm	D(a);
	if(D.exec()==true){
		LangPack.AppendList(a);
		ShowList();
	}
	else{
		delete	a;
	}
}

void SetLanguageForm::on_pushButtonChange_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	LanguageClass *a=LangPack.GetItem(Row);
	SetLanguageDetailForm	D(a);
	D.exec();
	ShowList();
}

void SetLanguageForm::on_pushButtonDelete_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	if(QMessageBox::warning(NULL,"Select","Delete project?",QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		LanguageClass *a=LangPack.GetItem(Row);
		LangPack.RemoveList(a);
		delete	a;
		ShowList();
	}
}

void SetLanguageForm::on_pushButtonUp_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<1)
		return;
	LanguageClass *a1=LangPack.GetItem(Row);
	LanguageClass *a2=LangPack.GetItem(Row-1);
	LangPack.Swap(a1,a2);
	ShowList();
}

void SetLanguageForm::on_pushButtonDown_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0 || (Row+1)<LangPack.GetCount())
		return;
	LanguageClass *a1=LangPack.GetItem(Row);
	LanguageClass *a2=LangPack.GetItem(Row+1);
	LangPack.Swap(a1,a2);
	ShowList();
}

void SetLanguageForm::on_pushButtonClose_clicked()
{
	LangPack.SaveDefault();
	close();
}