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

#include "AddItemDialogResource.h"
#include "PropertyPieceForReviewResource.h"
#include "AddItemDialog.h"
#include "ui_AddItemDialog.h"
#include "XDataInLayer.h"
#include "ThreadSequence.h"
#include "XSequence.h"
#include "XRememberer.h"

AddItemDialog::AddItemDialog(int globalPage ,LayersBase *base,QWidget *parent
							,int	_AreaNumber
							,QString _AreaName
							,int	_SysRegNumber) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::AddItemDialog)
	
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	
	AreaNumber	=_AreaNumber;
	AreaName	=_AreaName;
	SysRegNumber=_SysRegNumber;

	ui->spinBoxAreaNumber->setValue(AreaNumber);
	ui->lineEditAreaName->setText(AreaName);
	ui->spinBoxSysRegNumber->setValue(SysRegNumber);

	InstallOperationLog(this);
}

AddItemDialog::AddItemDialog(int globalPage ,LayersBase *base,QWidget *parent)
    :QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	
	int	iAreaNumber=ControlRememberer::GetInt(ui->spinBoxAreaNumber	,0);
	ui->spinBoxAreaNumber	->setValue(iAreaNumber+1);

	ui->lineEditAreaName	->setText(ControlRememberer::GetString(ui->lineEditAreaName	,/**/"A-1"));

	int	iSysRegNumber=ControlRememberer::GetInt(ui->spinBoxSysRegNumber	,350);
	ui->spinBoxSysRegNumber->setValue(iSysRegNumber+1);
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}

void AddItemDialog::on_pushButtonOK_clicked()
{
	AreaNumber	=ui->spinBoxAreaNumber->value();
	AreaName	=ui->lineEditAreaName->text();
	SysRegNumber=ui->spinBoxSysRegNumber->value();

	ControlRememberer::SetValue(ui->spinBoxAreaNumber		,ui->spinBoxAreaNumber->value());
	ControlRememberer::SetValue(ui->lineEditAreaName		,ui->lineEditAreaName->text());
	ControlRememberer::SetValue(ui->spinBoxSysRegNumber		,ui->spinBoxSysRegNumber->value());

	done(true);
}

void AddItemDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void AddItemDialog::on_spinBoxSysRegNumber_valueChanged(int arg1)
{
	ThreadSequence	*Th=GetLayersBase()->GetSequenceInstance();
	if(Th==NULL){
		ui->labelSeqStatus->setText(/**/"");
		return;
	}
	SeqControl	*SC=Th->GetMainSeqControl();
	if(SC==NULL){
		ui->labelSeqStatus->setText(/**/"");
		return;
	}
	Operand *r=SC->SearchReg(KindCodeSpecial ,arg1);
	if(r!=NULL){
		ui->labelSeqStatus->setText(/**/"Defined");
		return;
	}
	ui->labelSeqStatus->setText(/**/"OK");
}