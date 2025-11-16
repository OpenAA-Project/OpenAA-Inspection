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