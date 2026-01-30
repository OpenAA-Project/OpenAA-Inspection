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

#include "AddSourceItemDialogResource.h"
#include "AddSourceItemDialog.h"
#include "ui_AddSourceItemDialog.h"
#include "SearchItemDialog.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"

AddSourceItemDialog::AddSourceItemDialog(LayersBase *Base,int _GlobalPage ,int _Layer,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::AddSourceItemDialog)
{
    ui->setupUi(this);
	
	GlobalPage	=_GlobalPage;
	Layer		=_Layer;
	GetLayersBase()->GetAlgorithmByType(AlgoBases ,AlgorithmBit_TypeProcessing);
	ui->tableWidgetAlgorithm->setRowCount(AlgoBases.GetCount());
	int	Row=0;
	for(AlgorithmBasePointerList *a=AlgoBases.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		QString	DLLRoot,DLLName;
		a->GetAlgorithmBase()->GetAlgorithmRootName(DLLRoot,DLLName);
		::SetDataToTable(ui->tableWidgetAlgorithm,0,Row ,DLLRoot);
		::SetDataToTable(ui->tableWidgetAlgorithm,1,Row ,DLLName);
	}
	InstallOperationLog(this);
}

AddSourceItemDialog::~AddSourceItemDialog()
{
    delete ui;
}

void AddSourceItemDialog::on_pushButtonSearch_clicked()
{
	int	R=ui->tableWidgetAlgorithm->currentRow();
	if(R<0)
		return;
	SearchItemDialog	D(GetLayersBase(),AlgoBases[R]->GetAlgorithmBase(),GlobalPage ,Layer);
	if(D.exec()==(int)true){
		ui->spinBoxItemID	->setValue(D.ItemID);
	}
}

void AddSourceItemDialog::on_pushButtonOK_clicked()
{
	int	R=ui->tableWidgetAlgorithm->currentRow();
	if(R<0)
		return;
	AlgoBases[R]->GetAlgorithmBase()->GetAlgorithmRootName(AlgoRoot,AlgoName);
	ItemID=ui->spinBoxItemID->value();
	done(true);
}

void AddSourceItemDialog::on_pushButtonCancel_clicked()
{
	done(false);
}