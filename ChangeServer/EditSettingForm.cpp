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

#include "ChangeServerResource.h"
#include "EditSettingForm.h"
#include <QTextStream>
#include <QFileDialog>

EditSettingForm::EditSettingForm(int row
								,ChangeServerContainer	&serverContainer
								,QWidget *parent)
	: QDialog(parent),ServerContainer(serverContainer)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	Row=row;
	if(Row<0){
		ui.pushButtonUpdate->setEnabled(false);
	}
	else{
		ui.pushButtonUpdate->setEnabled(true);

		ChangeServerItem *a=ServerContainer.GetItem(Row);
		if(a!=NULL){
			ui.lineEditServerName->setText	(a->ServerName);
			ui.lineEditRemark->setText		(a->Remark);
			ui.lineEditExeFilePath->setText	(a->ExeFilePath);
			ui.radioButtonFromBAT	->setChecked(a->ExecuteBatMode);
			ui.radioButton_2		->setChecked(!a->ExecuteBatMode);

			QString	txt;
			QTextStream	FTxt(&txt);
			for(int i=0;i<a->DirectCommandLine.count();i++){
				FTxt<<a->DirectCommandLine[i];
				FTxt<<LangSolver.GetString(EditSettingForm_LS,LID_3)/*"\n"*/;
			}
			ui.textEditCommandLine->document ()->setPlainText(txt);
		}
	}
	on_radioButtonFromBAT_toggled(true);
}

EditSettingForm::~EditSettingForm()
{

}


void EditSettingForm::on_pushButtonCreateNew_clicked()
{
	int	StartID=0;
	for(ChangeServerItem *a=ServerContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ID>StartID){
			StartID=a->ID;
		}
	}
	StartID++;
	ChangeServerItem *d=new ChangeServerItem();
	d->ID=StartID;
	GetFromWindow(d);
	ServerContainer.AppendList(d);
	done(true);
}

void EditSettingForm::GetFromWindow(ChangeServerItem *d)
{
	d->ServerName		=ui.lineEditServerName->text();
	d->Remark			=ui.lineEditRemark->text();
	d->ExeFilePath		=ui.lineEditExeFilePath->text();
	d->ExecuteBatMode	=ui.radioButtonFromBAT->isChecked();
	
	QString	txt=ui.textEditCommandLine->document ()->toPlainText();
	QTextStream	FTxt(&txt);
	d->DirectCommandLine.clear();
	while(FTxt.atEnd()==false){
		QString R=FTxt.readLine ();
		d->DirectCommandLine.append(R);
	}
}

void EditSettingForm::on_pushButtonUpdate_clicked()
{
	ChangeServerItem *a=ServerContainer.GetItem(Row);
	if(a!=NULL){
		GetFromWindow(a);
	}
	done(true);
}

void EditSettingForm::on_pushButtonDelete_clicked()
{
	ChangeServerItem *a=ServerContainer.GetItem(Row);
	if(a!=NULL){
		ServerContainer.RemoveList(a);
		delete	a;
	}
	done(true);
}

void EditSettingForm::on_pushButtonCancel_clicked()
{
	done(false);
}

void EditSettingForm::on_pushButtonFile_clicked()
{
	QString FileName=QFileDialog::getOpenFileName (this);
	if(FileName.isEmpty()==false){
		ui.lineEditExeFilePath->setText(FileName);
	}
}

void EditSettingForm::on_radioButtonFromBAT_toggled(bool)
{
	if(ui.radioButtonFromBAT->isChecked()==true){
		ui.lineEditExeFilePath	->setEnabled(true);
		ui.pushButtonFile		->setEnabled(true);
		ui.textEditCommandLine	->setEnabled(false);
	}
	else{
		ui.lineEditExeFilePath	->setEnabled(false);
		ui.pushButtonFile		->setEnabled(false);
		ui.textEditCommandLine	->setEnabled(true);
	}
}

void EditSettingForm::on_radioButton_2_toggled(bool)
{
	on_radioButtonFromBAT_toggled(true);
}