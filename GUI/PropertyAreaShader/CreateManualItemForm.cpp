#include "BrightHistgramFormResource.h"
#include "CreateManualItemForm.h"
#include "XRememberer.h"

CreateManualItemForm::CreateManualItemForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	ui.spinBoxCellSize			->setValue	(ControlRememberer::GetInt(ui.spinBoxCellSize,50));
	ui.doubleSpinBoxAdoptRate	->setValue	(ControlRememberer::GetDouble(ui.doubleSpinBoxAdoptRate,50));
	ui.checkBoxFixed			->setChecked(ControlRememberer::GetBool(ui.checkBoxFixed,false));
	ui.doubleSpinBoxAverage		->setValue	(ControlRememberer::GetDouble(ui.doubleSpinBoxAverage	,100.0));
	ui.doubleSpinBoxSigma		->setValue	(ControlRememberer::GetDouble(ui.doubleSpinBoxSigma	,5.0));

	InstallOperationLog(this);
}

CreateManualItemForm::~CreateManualItemForm()
{

}


void CreateManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}

void CreateManualItemForm::on_pushButtonOK_clicked()
{
	CellSize	=ui.spinBoxCellSize->value();
	AdoptRate	=ui.doubleSpinBoxAdoptRate->value();
	Fixed		=ui.checkBoxFixed->isChecked();
	Average		=ui.doubleSpinBoxAverage->value();
	Sigma		=ui.doubleSpinBoxSigma->value();

	ControlRememberer::SetValue(ui.spinBoxCellSize			,ui.spinBoxCellSize->value()		);
	ControlRememberer::SetValue(ui.doubleSpinBoxAdoptRate	,ui.doubleSpinBoxAdoptRate->value()	);
	ControlRememberer::SetValue(ui.checkBoxFixed			,ui.checkBoxFixed->isChecked()		);
	ControlRememberer::SetValue(ui.doubleSpinBoxAverage		,ui.doubleSpinBoxAverage->value()	);
	ControlRememberer::SetValue(ui.doubleSpinBoxSigma		,ui.doubleSpinBoxSigma->value()		);

	done(true);
}