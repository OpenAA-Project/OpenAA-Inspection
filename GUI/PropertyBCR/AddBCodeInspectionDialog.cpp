/*
 * Copyright (C) 2026
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

#include "PropertyBCRResource.h"
#include "AddBCodeInspectionDialog.h"
#include "ui_AddBCodeInspectionDialog.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XRememberer.h"

AddBCodeInspectionDialog::AddBCodeInspectionDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::AddBCodeInspectionDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	CheckType   =1;		//0:Read	1:Quality Check
	QuilityGrade=10.0;

	int	W=ui->tableWidgetGradeList->width()-ui->tableWidgetGradeList->verticalHeader()->width()-40;
	ui->tableWidgetGradeList->setColumnWidth(0,W*0.5);
	ui->tableWidgetGradeList->setColumnWidth(1,W*0.5);

	//on_comboBoxCheckType_currentIndexChanged(0);

	ui->comboBoxCheckType			->setCurrentIndex(ControlRememberer::GetInt(ui->comboBoxCheckType,0));
	ui->doubleSpinBoxQuilityGrade	->setValue(ControlRememberer::GetDouble(ui->doubleSpinBoxQuilityGrade,0));

	InstallOperationLog(this);
}

AddBCodeInspectionDialog::~AddBCodeInspectionDialog()
{
    delete ui;
}

void	AddBCodeInspectionDialog::GetDataFromWindow(void)
{
	CheckType			=ui->comboBoxCheckType	->currentIndex();
	QuilityGrade		=ui->doubleSpinBoxQuilityGrade	->value();
	BarcodeIsOnlyDigit	=ui->checkBoxBarcodeIsOnlyDigit->isChecked();

	LoadGradeListFromWindow(GradeList);
}

void	AddBCodeInspectionDialog::SetDataToWindow(void)
{
	ui->comboBoxCheckType			->setCurrentIndex(CheckType);
	ui->doubleSpinBoxQuilityGrade	->setValue(QuilityGrade);
	ui->checkBoxBarcodeIsOnlyDigit	->setChecked(BarcodeIsOnlyDigit);
	ShowGradeList(GradeList);
}

void    AddBCodeInspectionDialog::ShowGradeList(BCRGradeListContainer &List)
{
	ui->tableWidgetGradeList->setRowCount(List.GetCount());
	int	Row=0;
	for(BCRGradeList *a=List.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetGradeList, 0, Row, a->Grade, Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetGradeList, 1, Row, QString::number(a->Quality,'f',3), Qt::ItemIsEditable);
	}
}
void    AddBCodeInspectionDialog::LoadGradeListFromWindow(BCRGradeListContainer &List)
{
	List.RemoveAll();
	int	N=ui->tableWidgetGradeList->rowCount();
	int	Row=0;
	for(int Row=0;Row<N;Row++){
		BCRGradeList *a=new BCRGradeList();
		a->Grade	=GetDataToTable(ui->tableWidgetGradeList, 0, Row);
		a->Quality	=GetDataToTable(ui->tableWidgetGradeList, 1, Row).toDouble();;
		List.AppendList(a);
	}
}
void AddBCodeInspectionDialog::on_comboBoxCheckType_currentIndexChanged(int index)
{
	if(ui->comboBoxCheckType->currentIndex()==0)
		ui->stackedWidget->setCurrentIndex(0);
	else
	if(ui->comboBoxCheckType->currentIndex()==1)
		ui->stackedWidget->setCurrentIndex(1);
	else
		ui->stackedWidget->setCurrentIndex(0);
}

void AddBCodeInspectionDialog::on_pushButtonLoad_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(nullptr,LangSolver.GetString(AddBCodeInspectionDialog_LS,LID_0)/*"Load BCR Grade file"*/,QString()
											,/**/"Grade file(BCRGrade.dat);;Data file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){

			BCRGradeListContainer	List;
			if(List.Load(&File)==true){
				ShowGradeList(List);
			}
		}
	}
}

void AddBCodeInspectionDialog::on_pushButtonSave_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(nullptr,LangSolver.GetString(AddBCodeInspectionDialog_LS,LID_1)/*"Save BCR Grade file"*/,QString()
											,/**/"Grade file(BCRGrade.dat);;Data file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){

			BCRGradeListContainer	List;
			LoadGradeListFromWindow(List);
			List.Save(&File);
		}
	}
}

void AddBCodeInspectionDialog::on_pushButtonAdd_clicked()
{
	int	N=ui->tableWidgetGradeList->rowCount();
	ui->tableWidgetGradeList->setRowCount(N+1);
}

void AddBCodeInspectionDialog::on_pushButtonSub_clicked()
{
	int	N=ui->tableWidgetGradeList->rowCount();
	ui->tableWidgetGradeList->setRowCount(N-1);
}

void AddBCodeInspectionDialog::on_pushButtonSet_clicked()
{
	GetDataFromWindow();

	ControlRememberer::SetValue(ui->comboBoxCheckType ,ui->comboBoxCheckType->currentIndex());
	ControlRememberer::SetValue(ui->doubleSpinBoxQuilityGrade ,ui->doubleSpinBoxQuilityGrade->value());

	done(true);
}

void AddBCodeInspectionDialog::on_pushButtonClose_clicked()
{
	done(false);
}