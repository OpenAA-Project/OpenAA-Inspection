#include "AddManualItemFormResource.h"
#include "AddManualItemForm.h"
#include "XRememberer.h"

AddManualItemForm::AddManualItemForm(LayersBase *Base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	ControlRememberer::LoadValue(ui.doubleSpinBoxMatchingRate	,0.8);
	ControlRememberer::LoadValue(ui.spinBoxSearchDot			,2);
	InstallOperationLog(this);
}

AddManualItemForm::~AddManualItemForm()
{

}


void AddManualItemForm::on_pushButtonOK_clicked()
{
	MatchingRate=ui.doubleSpinBoxMatchingRate->value();
	SearchDot	=ui.spinBoxSearchDot->value();

	ControlRememberer::SetValue(ui.doubleSpinBoxMatchingRate);
	ControlRememberer::SetValue(ui.spinBoxSearchDot			);

	done(true);
}

void AddManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}