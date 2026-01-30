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

#include "IntegrationNewMasterResource.h"
#include "NewMasterDialog.h"
#include "IntegrationNewMaster.h"
#include "ui_NewMasterDialog.h"
#include "InputPanelDialog.h"
#include "IntegrationShowName.h"
#include <QMessageBox>

NewMasterDialog::NewMasterDialog(LayersBase *Base,IntegrationNewMaster *P,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base)
	,Parent(P)
    ,ui(new Ui::NewMasterDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ShowName",/**/"");
	if(f!=NULL){
		IntegrationShowName	*Fs=dynamic_cast<IntegrationShowName *>(f);
		if(Fs!=NULL){
			ui->labelTitleNumber->setText(Fs->TitleMasterNumber);
			ui->labelTitleName	->setText(Fs->TitleMasterName);
			ui->labelTitleRemark->setText(Fs->TitleRemark);
		}
	}
	ui->doubleSpinBoxSizeX->setMaximum(Parent->MaxWidth );
	ui->doubleSpinBoxSizeY->setMaximum(Parent->MaxLength);
}

NewMasterDialog::~NewMasterDialog()
{
    delete ui;
}

void NewMasterDialog::on_pushButtonInputPanelName_clicked()
{
	InputPanelDialog	D(-1 ,ui->EditMasterName->text());
	if(D.exec()==(bool)true){
		ui->EditMasterName->setText(D.GetResult());
	}
}

void NewMasterDialog::on_pushButtonInputPanelRemark_clicked()
{
	InputPanelDialog	D(-1 ,ui->EditRemark->text());
	if(D.exec()==(bool)true){
		ui->EditRemark->setText(D.GetResult());
	}
}

void NewMasterDialog::on_pushButtonInputPanelSizeX_clicked()
{
	InputPanelDialog	D(IPD_Number ,QString::number(ui->doubleSpinBoxSizeX->value(),'f',1));
    if(D.exec()==(bool)true){
		ui->doubleSpinBoxSizeX->setValue(D.GetResult().toDouble());
    }
}

void NewMasterDialog::on_pushButtonInputPanelSizeY_clicked()
{
    InputPanelDialog	D(IPD_Number ,QString::number(ui->doubleSpinBoxSizeY->value(),'f',1));
    if(D.exec()==(bool)true){
        ui->doubleSpinBoxSizeY->setValue(D.GetResult().toDouble());
    }
}

void NewMasterDialog::on_pushButtonSaveNew_clicked()
{
	ResultName		=ui->EditMasterName->text();
	ResultRemark	=ui->EditRemark->text();
	ResultNumber	=ui->EditNumber->text();

	if(ResultNumber.isEmpty()==true && ResultName.isEmpty()!=true){
		ResultNumber=ResultName;
	}
	if(ResultNumber.isEmpty()!=true && ResultName.isEmpty()==true){
		ResultName=ResultNumber;
	}
	if(Parent->CheckDupInMaster(ResultName,ResultNumber,ResultRemark)==false){
		QMessageBox::critical(NULL
								,LangSolver.GetString(NewMasterDialog_LS,LID_2)/*"Error"*/
								,LangSolver.GetString(NewMasterDialog_LS,LID_3)/*"Please set unique name."*/);
		return;
	}
	CommonData.CommonSizeX		=ui->doubleSpinBoxSizeX	->value();
	CommonData.CommonSizeY		=ui->doubleSpinBoxSizeY	->value();
	CommonData.RelationNumber	=ResultNumber;
	CommonData.RelationName		=ResultName;
	CommonData.RelationRemark	=ResultRemark;
	done(true);
}

void NewMasterDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void NewMasterDialog::on_pushButtonInputPanelNumber_clicked()
{
    InputPanelDialog	D(-1 ,ui->EditNumber->text());
    if(D.exec()==(bool)true){
        ui->EditNumber->setText(D.GetResult());
    }
}