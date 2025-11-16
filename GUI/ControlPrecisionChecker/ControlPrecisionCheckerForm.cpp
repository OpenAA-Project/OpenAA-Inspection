#include "ControlPrecisionCheckerResource.h"
#include "ControlPrecisionCheckerForm.h"

ControlPrecisionCheckerForm::ControlPrecisionCheckerForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

ControlPrecisionCheckerForm::~ControlPrecisionCheckerForm()
{

}


void ControlPrecisionCheckerForm::on_pushButtonSetParam_clicked()
{
	on_ParamButton_clicked();
}

void ControlPrecisionCheckerForm::on_pushButtonGrp_clicked()
{
	//on_GRP_clicked();
}

void ControlPrecisionCheckerForm::on_pushButtonFocus_clicked()
{
	on_Focus_clicked();
}

void ControlPrecisionCheckerForm::on_pushButtonBrightness_clicked()
{
	on_Brightness_clicked();
}

void ControlPrecisionCheckerForm::on_pushButtonResolution_clicked()
{
	on_Resolution_clicked();
}

void ControlPrecisionCheckerForm::on_pushButtonAngle_clicked()
{
	on_Angle_clicked();
}

void ControlPrecisionCheckerForm::on_comboBoxPage_currentIndexChanged(int index)
{
	CurrentPage=index;
}