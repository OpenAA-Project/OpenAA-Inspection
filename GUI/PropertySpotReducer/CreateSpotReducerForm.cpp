#include "CreateSpotReducerFormResource.h"
#include "CreateSpotReducerForm.h"
#include "XRememberer.h"

CreateSpotReducerForm::CreateSpotReducerForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	ControlRememberer::LoadValue(ui.spinBoxSpotBrightness,200);
	ControlRememberer::LoadValue(ui.doubleSpinBoxReductionLevel,50);
	ControlRememberer::LoadValue(ui.spinBoxSpotArea,4);
	ControlRememberer::LoadValue(ui.spinBoxSpotCount,6);
	InstallOperationLog(this);
}

CreateSpotReducerForm::~CreateSpotReducerForm()
{

}


void CreateSpotReducerForm::on_pushButtonOK_clicked()
{
	SpotBrightness	=ui.spinBoxSpotBrightness		->value();
	ReductionLevel	=ui.doubleSpinBoxReductionLevel	->value();
	SpotArea		=ui.spinBoxSpotArea				->value();
	SpotCount		=ui.spinBoxSpotCount			->value();

	ControlRememberer::SetValue(ui.spinBoxSpotBrightness	);
	ControlRememberer::SetValue(ui.doubleSpinBoxReductionLevel	);
	ControlRememberer::SetValue(ui.spinBoxSpotArea		);
	ControlRememberer::SetValue(ui.spinBoxSpotCount		);
	done((int)true);
}

void CreateSpotReducerForm::on_pushButtonCancel_clicked()
{
	done((int)false);
}