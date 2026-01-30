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

#include "SettingLoadReleaseDialog.h"
#include "ui_SettingLoadReleaseDialog.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

SettingLoadReleaseDialog::SettingLoadReleaseDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::SettingLoadReleaseDialog)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,32);
	ui->tableWidget->setColumnWidth(1,200);

	int	N=GetLayersBase()->GetLogicDLLBase()->GetCount();
	ui->tableWidget->setRowCount(N);
	SettingData.RemoveAll();
	int	row=0;
	for(LogicDLL *d=GetLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
		::SetDataToTableCheckable(ui->tableWidget,0,row ,/**/"",false);
		QString	s=d->GetDLLRoot()
				+ ::GetSeparator()
				+ d->GetDLLName();
		::SetDataToTable		 (ui->tableWidget,1,row ,s);

		LoadReleaseAlgoList	*k=new LoadReleaseAlgoList();
		k->DLLRoot	=d->GetDLLRoot();
		k->DLLName	=d->GetDLLName();
		SettingData.AppendList(k);
		row++;
	}

	InstallOperationLog(this);
}

SettingLoadReleaseDialog::~SettingLoadReleaseDialog()
{
    delete ui;
}

void SettingLoadReleaseDialog::Merge(LoadReleaseAlgoContainer &SrcSettingData)
{
	SettingData.ReleaseableMasterBuff	=SrcSettingData.ReleaseableMasterBuff;
	SettingData.ReleaseableTargetBuff	=SrcSettingData.ReleaseableTargetBuff;

	for(LoadReleaseAlgoList *a=SrcSettingData.GetFirst();a!=NULL;a=a->GetNext()){
		for(LoadReleaseAlgoList *b=SettingData.GetFirst();b!=NULL;b=b->GetNext()){
			if(a->DLLRoot==b->DLLRoot && a->DLLName==b->DLLName){
				b->Releaseable=a->Releaseable;
				break;
			}
		}
	}
}
void SettingLoadReleaseDialog::ReflectToWindow(void)
{
	ui->checkBoxMasterBuff	->setChecked(SettingData.ReleaseableMasterBuff);
	ui->checkBoxTargetBuff	->setChecked(SettingData.ReleaseableTargetBuff);
	int	row=0;
	for(LogicDLL *d=GetLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
		LoadReleaseAlgoList *b=SettingData[row];
		::SetDataToTableCheckable(ui->tableWidget,0,row ,/**/"",b->Releaseable);
		row++;
	}
}

void SettingLoadReleaseDialog::on_pushButtonOK_clicked()
{
	SettingData.ReleaseableMasterBuff	=ui->checkBoxMasterBuff	->isChecked();
	SettingData.ReleaseableTargetBuff	=ui->checkBoxTargetBuff	->isChecked();
	int	row=0;
	for(LogicDLL *d=GetLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
		LoadReleaseAlgoList *b=SettingData[row];
		b->Releaseable	=	GetCheckedFromTable(ui->tableWidget,0,row);
		row++;
	}
	done(true);
}