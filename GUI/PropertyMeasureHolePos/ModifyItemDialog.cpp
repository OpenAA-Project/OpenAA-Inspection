#include "CreateManualItemFormResource.h"
#include "ModifyItemDialog.h"
#include "ui_ModifyItemDialog.h"

ModifyItemDialog::ModifyItemDialog(LayersBase *base, QString &itemName ,MeasureHolePosThreshold *_ThreData ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,ThreData(_ThreData)
    ,ui(new Ui::ModifyItemDialog)
{
    ui->setupUi(this);
	ItemName	=itemName;

	ui->EditName					->setText(ItemName);
	ui->doubleSpinBoxDiaPrecision	->setValue(ThreData->DiaPrecision);
	ui->doubleSpinBoxPosPrecision	->setValue(ThreData->PosPrecision);
	ui->spinBoxNoiseSize			->setValue(ThreData->NoiseSize);
	ui->spinBoxBandWidth			->setValue(ThreData->BandWidth);
	ui->EditSearchDot				->setValue(ThreData->SearchDot);
	InstallOperationLog(this);
}

ModifyItemDialog::~ModifyItemDialog()
{
    delete ui;
}

void ModifyItemDialog::on_ButtonOK_clicked()
{
	ItemName				=ui->EditName					->text();
	ThreData->DiaPrecision	=ui->doubleSpinBoxDiaPrecision	->value();
	ThreData->PosPrecision	=ui->doubleSpinBoxPosPrecision	->value();
	ThreData->NoiseSize		=ui->spinBoxNoiseSize			->value();
	ThreData->BandWidth		=ui->spinBoxBandWidth			->value();
	ThreData->SearchDot		=ui->EditSearchDot				->value();
	done(true);
}

void ModifyItemDialog::on_ButtonCancel_clicked()
{
	done(false);
}
