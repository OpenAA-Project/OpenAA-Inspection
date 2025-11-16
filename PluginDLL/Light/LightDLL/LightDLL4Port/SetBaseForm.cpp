#include "SetBaseForm.h"
#include "ui_SetBaseForm.h"
#include "LightDLL4PortForm.h"

SetBaseForm::SetBaseForm(LayersBase *base, int BasePort[],QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetBaseForm),ServiceForLayers(base)
{
    ui->setupUi(this);
	ui->spinBoxPort0->setValue(BasePort[0]);
	ui->spinBoxPort1->setValue(BasePort[1]);
	ui->spinBoxPort2->setValue(BasePort[2]);
	ui->spinBoxPort3->setValue(BasePort[3]);

	InstallOperationLog(this);
}

SetBaseForm::~SetBaseForm()
{
    delete ui;
}

void SetBaseForm::on_pushButtonOK_clicked()
{
	LightDLL4PortForm::BasePort[0]	=ui->spinBoxPort0->value();
	LightDLL4PortForm::BasePort[1]	=ui->spinBoxPort1->value();
	LightDLL4PortForm::BasePort[2]	=ui->spinBoxPort2->value();
	LightDLL4PortForm::BasePort[3]	=ui->spinBoxPort3->value();
	done(true);
}
