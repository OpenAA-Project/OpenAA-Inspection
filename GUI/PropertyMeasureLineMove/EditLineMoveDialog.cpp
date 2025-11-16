#include "PropertyMeasureLineMoveFormResource.h"
#include "EditLineMoveDialog.h"
#include "ui_EditLineMoveDialog.h"

EditLineMoveDialog::EditLineMoveDialog(LayersBase *base, QString &itemName ,MeasureLineMoveThreshold *_ThreData ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,ThreData(_ThreData)
    ,ui(new Ui::EditLineMoveDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->EditName				->setText(itemName);
	ui->doubleSpinBoxThresholdM	->setValue(ThreData->ThresholdM);	//micron size
	ui->doubleSpinBoxThresholdP	->setValue(ThreData->ThresholdP);	//micron size
	ui->EditEdgeWidth			->setValue(ThreData->EdgeWidth);
	ui->EditSearchDot			->setValue(ThreData->SearchDot);
	ui->checkBoxPrevailLeft		->setChecked(ThreData->PrevailLeft);
	ui->checkBoxPrevailRight	->setChecked(ThreData->PrevailRight);
	InstallOperationLog(this);
}

EditLineMoveDialog::~EditLineMoveDialog()
{
    delete ui;
}

void EditLineMoveDialog::on_ButtonOK_clicked()
{
	ItemName				=ui->EditName					->text();
	ThreData->ThresholdM	=ui->doubleSpinBoxThresholdM	->value();	//micron size
	ThreData->ThresholdP	=ui->doubleSpinBoxThresholdP	->value();	//micron size
	ThreData->EdgeWidth		=ui->EditEdgeWidth				->value();
	ThreData->SearchDot		=ui->EditSearchDot				->value();
	ThreData->PrevailLeft	=ui->checkBoxPrevailLeft		->isChecked();
	ThreData->PrevailRight	=ui->checkBoxPrevailRight		->isChecked();
	done(true);
}

void EditLineMoveDialog::on_ButtonCancel_clicked()
{
	done(false);
}
