#include "SetBaseForm.h"
#include "LightDLL2PortForm.h"

SetBaseForm::SetBaseForm(LayersBase *base, int BasePort[],QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	ui.spinBoxPort0->setValue(BasePort[0]);
	ui.spinBoxPort1->setValue(BasePort[1]);

	InstallOperationLog(this);
}

SetBaseForm::~SetBaseForm()
{

}


void SetBaseForm::on_pushButtonOK_clicked()
{
	LightDLL2PortForm::BasePort[0]	=ui.spinBoxPort0->value();
	LightDLL2PortForm::BasePort[1]	=ui.spinBoxPort1->value();
	done(true);
}