/*
 * Copyright (C) 2025
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

#include "AddEditItemDialog.h"
#include "ui_AddEditItemDialog.h"
#include "XDataInLayer.h"
#include "XAlignmentBlockLibrary.h"

AddEditItemDialog::AddEditItemDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::AddEditItemDialog)
{
    ui->setupUi(this);

    GetLayersBase()->InstallOperationLog(this);
}

AddEditItemDialog::~AddEditItemDialog()
{
    delete ui;
}

void AddEditItemDialog::Initial(AlgorithmLibrary *Lib)
{
    AlignmentBlockLibrary   *ALib=dynamic_cast<AlignmentBlockLibrary *>(Lib);
    if(ALib!=NULL){
        ui->spinBoxSearchDot		->setValue(ALib->SearchDot	);
        ui->doubleSpinBoxMaxDegree	->setValue(ALib->MaxDegree	);
        ui->spinBoxLineLength		->setValue(ALib->LineLength	);
        ui->doubleSpinBoxMinVar	    ->setValue(ALib->MinVar		);
    }
}

void AddEditItemDialog::on_pushButtonOK_clicked()
{
	SearchDot		=ui->spinBoxSearchDot		->value();
	MaxDegree		=ui->doubleSpinBoxMaxDegree	->value();
	LineLength		=ui->spinBoxLineLength		->value();
	MinVar			=ui->doubleSpinBoxMinVar	->value();

    done(true);
}
