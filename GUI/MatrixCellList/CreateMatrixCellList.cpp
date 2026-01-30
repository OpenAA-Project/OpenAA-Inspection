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

#include "CreateMatrixCellListResource.h"
#include "CreateMatrixCellList.h"
#include "MatrixCellListForm.h"
#include "FormMatrixPieceColor.h"

CreateMatrixCellList::CreateMatrixCellList(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	InstallOperationLog(this);
	Form=NULL;
}

void	CreateMatrixCellList::ShowItem(MatrixCellListForm *form)
{
	Form=form;
	ui.spinBoxCellSizeX	->setValue(Form->CellSizeX);
	ui.spinBoxCellSizeY	->setValue(Form->CellSizeY);
	ui.spinBoxStartX	->setValue(Form->StartX);
	ui.spinBoxStartY	->setValue(Form->StartY);
	ui.spinBoxEndX		->setValue(Form->EndX);
	ui.spinBoxEndY		->setValue(Form->EndY);
}

CreateMatrixCellList::~CreateMatrixCellList()
{

}


void CreateMatrixCellList::on_pushButtonOK_clicked()
{
	Form->CellSizeX	=ui.spinBoxCellSizeX->value();
	Form->CellSizeY	=ui.spinBoxCellSizeY->value();
	Form->StartX	=ui.spinBoxStartX	->value();
	Form->StartY	=ui.spinBoxStartY	->value();
	Form->EndX		=ui.spinBoxEndX		->value();
	Form->EndY		=ui.spinBoxEndY		->value();

	Form->CreateCells(ui.comboBox->currentIndex());
	done(0);
}

void CreateMatrixCellList::on_pushButtonColor_clicked()
{
	FormMatrixPieceColor	Q(GetLayersBase(),Form,this);
	Q.exec();
}

void CreateMatrixCellList::on_pushButtonClose_clicked()
{
	close();
}